#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

typedef vector<double> Vector;
typedef vector<vector<double>> Matrix;

// --- Helper Functions ---

// 2D Nonlinear function: f(x,y) = [x*cos(y), x*sin(y)]
Vector f_nonlinear_xy(double x, double y) {
    return {x * cos(y), x * sin(y)};
}

// Cholesky Decomposition: Computes L such that L*L^T = A
Matrix cholesky(const Matrix& A) {
    int n = A.size();
    Matrix L(n, Vector(n, 0.0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            double sum = 0;
            for (int k = 0; k < j; k++) sum += L[i][k] * L[j][k];
            if (i == j) L[i][j] = sqrt(max(0.0, A[i][i] - sum));
            else L[i][j] = (1.0 / L[j][j] * (A[i][j] - sum));
        }
    }
    return L;
}

int main() {
    // 1. Initial State
    int n = 2;
    Vector mean = {0.0, 0.0};
    Matrix P = {{32.0, 15.0}, {15.0, 40.0}};

    // 2. Parameters for Merwe Scaled Sigma Points
    double alpha = 0.3;
    double beta = 2.0;
    double kappa = 0.1;
    double lambda = alpha * alpha * (n + kappa) - n;

    // 3. Compute Weights
    int num_sigmas = 2 * n + 1;
    Vector Wm(num_sigmas, 1.0 / (2.0 * (n + lambda)));
    Vector Wc = Wm;
    Wm[0] = lambda / (n + lambda);
    Wc[0] = Wm[0] + (1.0 - alpha * alpha + beta);

    // 4. Generate Sigma Points
    Matrix sigmas(num_sigmas, Vector(n));
    // Calculate sqrt((n + lambda) * P)
    Matrix scaled_P = P;
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) scaled_P[i][j] *= (n + lambda);
    
    Matrix L = cholesky(scaled_P);

    sigmas[0] = mean;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sigmas[i + 1][j] = mean[j] + L[j][i];      // + column of L
            sigmas[i + n + 1][j] = mean[j] - L[j][i];  // - column of L
        }
    }

    // 5. Pass through Nonlinear Function
    Matrix sigmas_f(num_sigmas, Vector(n));
    for (int i = 0; i < num_sigmas; i++) {
        sigmas_f[i] = f_nonlinear_xy(sigmas[i][0], sigmas[i][1]);
    }

    // 6. Unscented Transform (Compute Mean)
    Vector ukf_mean(n, 0.0);
    for (int i = 0; i < num_sigmas; i++) {
        for (int j = 0; j < n; j++) {
            ukf_mean[j] += Wm[i] * sigmas_f[i][j];
        }
    }

    // 7. Unscented Transform (Compute Covariance)
    Matrix ukf_cov(n, Vector(n, 0.0));
    for (int i = 0; i < num_sigmas; i++) {
        Vector diff(n);
        for (int j = 0; j < n; j++) diff[j] = sigmas_f[i][j] - ukf_mean[j];
        
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                ukf_cov[row][col] += Wc[i] * diff[row] * diff[col];
            }
        }
    }

    // Output Results
    cout << fixed << setprecision(4);
    cout << "UKF Mean: [" << ukf_mean[0] << ", " << ukf_mean[1] << "]" << endl;
    cout << "UKF Covariance:\n";
    for (auto& row : ukf_cov) {
        cout << "[" << row[0] << ", " << row[1] << "]\n";
    }

    return 0;
}
