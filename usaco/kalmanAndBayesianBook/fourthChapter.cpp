#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <iomanip>

// Structure to represent a Gaussian distribution N(mean, var)
struct Gaussian {
    double mean;
    double var;

};
Gaussian gaussian(double mean, double var){
    return {mean, var};
}
Gaussian predict(Gaussian prior, Gaussian product_model){
    return {prior.mean+product_model.mean, prior.var+product_model.var};      //current pose + motion, always add variance
}   
Gaussian update(Gaussian prior, Gaussian likelihood){
    double mu = (prior.var * likelihood.mean + likelihood.var * prior.mean) / (prior.var + likelihood.var);   //top part of bayesian checking where belief for both is best
    double var = (prior.var * likelihood.var) / (prior.var + likelihood.var);
    return {mu, var};
}
class DogSimulation {
    private:
        double x;
        double velocity;
        double measurement_noise_std;//uncertainty in measurement
        double process_noise_std; //uncertainty in motion/wheel slippage, friction etc, uncertainty in our prediction
        std::mt19937 gen;
        std::normal_distribution<double> dist;
    public:
        DogSimulation(double x0, double vel, double meas_var, double proc_var) : x(x0), velocity(vel), gen(13) {
            measurement_noise_std = std::sqrt(meas_var);
            process_noise_std = std::sqrt(proc_var);
            std::normal_distribution<double>::param_type param(0.0, 1.0);
            dist.param(param);
        }
        std::pair<double, double> move_and_sense(double dt = 1.0){
            velocity += dist(gen) * process_noise_std;
            x+=velocity*dt;
            double z = x+dist(gen)*measurement_noise_std;
            return {x, z};
        }

        double get_x() const {
            return x;
        }
        double get_velocity(){
            return velocity;
        }
};
int main()
{  
    double process_var = 1.0;
    double sensor_var = 200.0;
    double velocity = 1.0;
    double dt = 1.0;
    
    Gaussian x_state = gaussian(0.0, std::pow(20.0,2));

    Gaussian process_model = gaussian(velocity*dt, process_var);

    DogSimulation dog(x_state.mean, process_model.mean, sensor_var, process_var);

    std::vector<double> measurements;
    for (int i = 0; i <1000; ++i) {
        measurements.push_back(dog.move_and_sense().second);
    }
    std::cout << "PREDICT\t\t\tUPDATE" << std::endl;
    std::cout << " x var\t\t z\t x var" << std::endl;
    std::cout << std::fixed << std::setprecision(3);

    for(double z : measurements){
        Gaussian process_model = gaussian(dog.get_velocity()*dt, process_var);
        Gaussian prior = predict(x_state, process_model);
        Gaussian likelihood = gaussian(z, sensor_var);

        x_state = update(prior, likelihood);
        std::cout << prior.mean << " " << prior.var << "\t"
                  << z << "\t"
                  << x_state.mean << " " << x_state.var << std::endl;
    }
    std::cout << "\nfinal estimate: " << std::setw(10) << x_state.mean << std::endl;
    std::cout << "actual final position: " << std::setw(10) << dog.get_x() << std::endl;

    return 0;
}
