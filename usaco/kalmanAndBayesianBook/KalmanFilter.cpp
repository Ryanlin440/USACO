#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

// Eigen is standard for UKF math. In PROS, you can drop the Eigen folder 
// into your 'include' directory. It's a header-only library.
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

// ---------------------------------------------------------
// PROS / LEMLIB MOCK (For testing on desktop)
// ---------------------------------------------------------
struct Pose {
    double x, y, theta; 
};
Pose lemlib_pose = {24.0, 24.0, 0.0}; // Starting at 24", 24", facing 0 rad
double getIMUHeadingRad() { return lemlib_pose.theta; } // Mock IMU

struct pros_Distance {
    double dist;
    double get() { return dist; }
};
pros_Distance front_sensor = {120.0};
pros_Distance back_sensor = {24.0};
pros_Distance left_sensor = {24.0};
pros_Distance right_sensor = {120.0};

// ---------------------------------------------------------
// UKF CLASS (Refactored for X, Y only)
// ---------------------------------------------------------
class LemLibUKF {
private:
    Matrix2d P; // 2x2 Covariance matrix for X, Y
    
    // UKF Parameters
    double alpha = 10e-3;
    double beta = 2.0;
    double kappa = 0.0;
    double n = 2.0; // State dimension is now just 2 (X, Y)
    double lambda = pow(alpha, 2) * (n + kappa) - n;

    // Field configuration (VEX is 144x144 inches)
    const double FIELD_MAX = 144.0;
    const double FIELD_MIN = 0.0;

public:
    Vector2d x; // State: [X, Y]

    LemLibUKF(double init_x, double init_y) {
        x << init_x, init_y;
        P = Matrix2d::Identity() * 0.1; // Initial uncertainty
    }

    vector<Vector2d> generateSigmaPoints(Vector2d x_state, Matrix2d P_cov) {
        // Cholesky decomposition for 2x2 matrix
        Matrix2d A = ((n + lambda) * P_cov).llt().matrixL();
        vector<Vector2d> sigma;
        sigma.push_back(x_state);
        for(int i = 0; i < n; i++){
            sigma.push_back(x_state + A.col(i));
            sigma.push_back(x_state - A.col(i));
        }
        return sigma; // Returns 5 points for 2D state
    }

    // Instead of raw v and omega, we just pass the Delta X and Delta Y 
    // calculated by LemLib's internal tracking wheel odometry!
    void predict(double delta_x, double delta_y) {
        auto sigma = generateSigmaPoints(x, P);

        // 1. Propagate through linear motion model (Odometry delta)
        vector<Vector2d> sigma_pred;
        for(const auto& s : sigma) {
            Vector2d next_s;
            next_s << s[0] + delta_x, s[1] + delta_y;
            sigma_pred.push_back(next_s);
        }

        // 2. Compute Mean
        Vector2d x_pred = Vector2d::Zero();
        for(int i = 0; i < sigma_pred.size(); i++){
            double w = (i == 0) ? lambda/(n+lambda) : 1.0/(2*(n+lambda));
            x_pred += w * sigma_pred[i];
        }

        // 3. Compute Covariance
        Matrix2d P_pred = Matrix2d::Zero();
        for(int i = 0; i < sigma_pred.size(); i++){
            double w = (i == 0) ? (lambda/(n+lambda) + (1 - alpha*alpha + beta)) : 1.0/(2*(n+lambda));
            Vector2d dx = sigma_pred[i] - x_pred;
            P_pred += w * (dx * dx.transpose());
        }

        // Add Process Noise (How much do we distrust odometry?)
        Matrix2d Q = Matrix2d::Identity() * 0.05; 
        P_pred += Q;

        x = x_pred;
        P = P_pred;
    }

    void update(Vector4d z, double current_heading_rad) {
        auto sigma = generateSigmaPoints(x, P);
        
        // Predict measurements based on our current heading
        vector<Vector4d> z_sigma;
        for(auto &s : sigma){
            z_sigma.push_back(sensorModel(s, current_heading_rad));
        }

        // Measurement Mean
        Vector4d z_pred = Vector4d::Zero();
        for(int i = 0; i < z_sigma.size(); i++){
            double w = (i == 0) ? lambda/(n+lambda) : 1.0/(2*(n+lambda));
            z_pred += w * z_sigma[i];
        }

        // Measurement Covariance
        Matrix4d S = Matrix4d::Zero();
        for(int i = 0; i < z_sigma.size(); i++){
            double w = (i == 0) ? (lambda/(n+lambda) + (1 - alpha*alpha + beta)) : 1.0/(2*(n+lambda));
            Vector4d dz = z_sigma[i] - z_pred;
            S += w * (dz * dz.transpose());
        }

        // Add Measurement Noise (How much do we distrust distance sensors?)
        Matrix4d R = Matrix4d::Identity() * 2.0; // Distance sensors can be noisy
        
        // DYNAMIC NOISE: If a sensor reads > 100 inches, we trust it LESS because 
        // it might be hitting a robot instead of a wall.
        for(int i=0; i<4; i++) {
             if (z[i] > 100.0) R(i,i) = 100.0; // High variance = ignore this sensor
        }
        S += R;

        // Cross Covariance & Kalman Gain
        MatrixXd Pxz = MatrixXd::Zero(2, 4);
        for(int i = 0; i < sigma.size(); i++){
            double w = (i == 0) ? (lambda/(n+lambda) + (1 - alpha*alpha + beta)) : 1.0/(2*(n+lambda));
            Vector2d dx = sigma[i] - x;
            Vector4d dz = z_sigma[i] - z_pred;
            Pxz += w * (dx * dz.transpose());
        }

        MatrixXd K = Pxz * S.inverse();
        Vector4d residual = z - z_pred;

        x = x + K * residual;
        P = P - K * S * K.transpose();
    }

    // ---------------------------------------------------------
    // RAYCASTING ENGINE for VEX Field (144" x 144")
    // ---------------------------------------------------------
    double raycast(double rx, double ry, double angle_rad) {
        double d_x = 9999.0;
        double d_y = 9999.0;

        // Check intersection with vertical walls (X = 0, X = 144)
        if (cos(angle_rad) > 0.001) d_x = (FIELD_MAX - rx) / cos(angle_rad);
        else if (cos(angle_rad) < -0.001) d_x = (FIELD_MIN - rx) / cos(angle_rad);

        // Check intersection with horizontal walls (Y = 0, Y = 144)
        if (sin(angle_rad) > 0.001) d_y = (FIELD_MAX - ry) / sin(angle_rad);
        else if (sin(angle_rad) < -0.001) d_y = (FIELD_MIN - ry) / sin(angle_rad);

        // Discard backwards rays
        if (d_x < 0) d_x = 9999.0;
        if (d_y < 0) d_y = 9999.0;

        return std::min(d_x, d_y);
    }

    Vector4d sensorModel(Vector2d s, double theta) {
        Vector4d z;
        double rx = s[0];
        double ry = s[1];

        // Raycast outward from the robot based on its current IMU heading
        z[0] = raycast(rx, ry, theta);                 // Front
        z[1] = raycast(rx, ry, theta + M_PI);          // Back
        z[2] = raycast(rx, ry, theta + (M_PI / 2.0));  // Left
        z[3] = raycast(rx, ry, theta - (M_PI / 2.0));  // Right
        return z;
    }
};

// ---------------------------------------------------------
// PROS BACKGROUND TASK IMPLEMENTATION
// ---------------------------------------------------------
void localization_task() {
    // Initialize UKF at LemLib's starting pose
    LemLibUKF ukf(lemlib_pose.x, lemlib_pose.y);
    
    Pose last_lemlib_pose = lemlib_pose;

    // In PROS, this would be: while(true)
    for(int step = 0; step < 10; step++) {
        
        // 1. Get current data from LemLib and IMU
        Pose current_pose = lemlib_pose; // chassis.getPose()
        double heading = getIMUHeadingRad(); // Standardize to radians

        // 2. Calculate how much LemLib's odometry thinks we moved
        double delta_x = current_pose.x - last_lemlib_pose.x;
        double delta_y = current_pose.y - last_lemlib_pose.y;

        // 3. UKF Predict step (Shift UKF forward by odometry delta)
        ukf.predict(delta_x, delta_y);

        // 4. Get raw distance sensor data (converted to inches)
        Vector4d z;
        z << front_sensor.get(), back_sensor.get(), left_sensor.get(), right_sensor.get();

        // 5. UKF Update step (Correct the predicted pose against field walls)
        ukf.update(z, heading);

        // 6. Push the corrected pose back to LemLib!
        // chassis.setPose(ukf.x[0], ukf.x[1], heading);
        
        // Update variables for next loop
        lemlib_pose.x = ukf.x[0];
        lemlib_pose.y = ukf.x[1];
        last_lemlib_pose = lemlib_pose; 

        cout << "Step " << step << " | Corrected X: " << ukf.x[0] << ", Y: " << ukf.x[1] << endl;

        // pros::delay(10); // Loop at 100Hz
    }
}

int main() {
    cout << "Starting PROS UKF Task..." << endl;
    localization_task();
    return 0;
}