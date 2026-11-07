#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int main() {
    std::ifstream file("file.csv");
    
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    // Read line by line
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> row;

        // Split the line by commas
        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        // Output the contents of the row
        for (const auto& val : row) {
            std::cout << val << " | ";
        }
        std::cout << "\n";
    }

    file.close();
    return 0;
}