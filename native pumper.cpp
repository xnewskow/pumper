#include <iostream>
#include <fstream>
#include <string>

void addWeightToFile(const std::string& filePath, size_t additionalWeight, bool inMB) {
    // Convert weight to bytes
    size_t bytesToAdd = inMB ? additionalWeight * 1024 * 1024 : additionalWeight * 1024;

    // Open the file in binary append mode
    std::ofstream file(filePath, std::ios::binary | std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filePath << std::endl;
        return;
    }

    // Create a buffer to add "junk" data
    char* buffer = new char[bytesToAdd];
    memset(buffer, 0, bytesToAdd); // Fill buffer with zeros

    // Add "junk" to the end of the file
    file.write(buffer, bytesToAdd);

    // Free resources
    delete[] buffer;
    file.close();

    if (file.good()) {
        std::cout << "Successfully added " << additionalWeight << (inMB ? " MB" : " KB") << " to the file " << filePath << "." << std::endl;
    }
    else {
        std::cerr << "Error adding weight to the file." << std::endl;
    }
}

int main() {
    std::string filePath;
    size_t weight;
    std::string unit;

    std::cout << "Enter the file path: ";
    std::getline(std::cin, filePath);

    std::cout << "Enter the amount of weight to add: ";
    std::cin >> weight;

    std::cout << "Enter the unit of measurement (KB or MB): ";
    std::cin >> unit;

    // Check if the input is MB or KB
    bool inMB = (unit == "MB" || unit == "mb");
    if (unit != "KB" && unit != "kb" && !inMB) {
        std::cerr << "Invalid unit. Please enter 'KB' for kilobytes or 'MB' for megabytes." << std::endl;
        return 1;
    }

    addWeightToFile(filePath, weight, inMB);

    return 0;
}
