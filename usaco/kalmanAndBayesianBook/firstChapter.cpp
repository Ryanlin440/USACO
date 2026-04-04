#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>
void predict_using_gain_guess(float estimated_weight,float gain_rate, float weights[]);
int main()
{
    std::random_device rd{};
    std::mt19937 gen{rd()};
 
    // Values near the mean are the most likely. Standard deviation
    // affects the dispersion of generated values from the mean.
    std::normal_distribution d{5.0, 2.0};
 
    // Draw a sample from the normal distribution and round it to an integer. d(gen) = random double from normal dist
    auto random_int = [&d, &gen]{ return std::lround(d(gen)); };
 
    std::map<long, unsigned> histogram{};//key(long) = number generated ; value how many times it appears
    for (auto n{10000}; n; --n)
        ++histogram[random_int()];
 
    // for (const auto [k, v] : histogram)
    //     std::cout << std::setw(2) << k << ' ' << std::string(v / 200, '*') << '\n';

    float weights[] = {158.0, 164.2, 160.3, 159.9, 162.1, 164.6, 
           169.6, 167.4, 166.4, 171.0, 171.2, 172.6};
    predict_using_gain_guess(160, 1, weights);
    
}
float time_step=1.0;
float scale_factor=4/10.0;
void predict_using_gain_guess(float estimated_weight,float gain_rate, float weights[]){
    std::vector<float>estimates, predictions;
    // estimates.push_back(estimated_weight);
    for(int z = 0; z < 12; z++){

        double predicted_weight=estimated_weight+gain_rate*time_step;

        estimated_weight = predicted_weight + scale_factor*(weights[z]-predicted_weight);

        estimates.push_back(estimated_weight);
        predictions.push_back(predicted_weight);
        std::cout<< estimated_weight<<' '<<predicted_weight<<std::endl; 
    }
    
}