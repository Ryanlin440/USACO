#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric> // Added for std::accumulate
#include <vector>

// Calculates the likelihood of seeing a specific measurement 'z' 
// at each position in the hallway.
std::vector<double> lh_hallway(const std::vector<int>& hallway, int z, double z_prob) {
    std::vector<double> likelihood;
    for (int cell : hallway) {
        if (cell == z) {
            likelihood.push_back(z_prob);
        } else {
            likelihood.push_back(1.0 - z_prob);
        }
    }
    return likelihood;
}

// Normalizes the vector so that all probabilities sum to 1.0.
void normalize(std::vector<double>& pdf) {
    double sum = std::accumulate(pdf.begin(), pdf.end(), 0.0);
    if (sum > 0) {
        for (double& val : pdf) val /= sum;
    }
}

// Multiplies the prior by the likelihood to get the posterior.
std::vector<double> update(const std::vector<double>& likelihood, const std::vector<double>& prior) {
    std::vector<double> posterior(prior.size());
    for (size_t i = 0; i < prior.size(); ++i) {
        posterior[i] = likelihood[i] * prior[i];
    }
    normalize(posterior);
    return posterior;
}
std::vector<double> predict(std::vector<double>& posterior, int step, std::vector<double>& kernel){
    int n = posterior.size();
    std::vector<double> next_prior(n, 0.0);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < kernel.size(); j++){
            int offset = (j - (int)(kernel.size() / 2));//over shoot or undershoot
            int prev_idx = (i - step - offset + n) % n;
            next_prior[i] += posterior[prev_idx] * kernel[j];
        }
    }
    return next_prior;
}
int main() {
    std::vector<int> hallway = {1, 1, 0, 0, 0, 0, 0, 0, 1, 0};
    std::vector<double> prior(10, 0.1);
    
    // Perform update step
    std::vector<double> likelihood = lh_hallway(hallway, 1, 0.75); //update ratios
    std::vector<double> posterior = update(likelihood, prior);//normalize to adds to 1
    std::vector<double> kernel = {.1, .8, .1};

    auto oneRun = [&](int door){
        prior = predict(posterior, 1, kernel);
        likelihood = lh_hallway(hallway, door, .75);
        posterior = update(likelihood, prior);
    };
    oneRun(1);
    oneRun(1);
    oneRun(0);
    oneRun(0);
    std::cout << "Posterior Probabilities:" << std::endl;
    for (double p : posterior) {
        std::cout << std::fixed << std::setprecision(4) << p << " ";
    }
    std::cout << std::endl;
    return 0;
}
