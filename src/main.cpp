#include <iostream>
#include <fstream>
#include <string>

#include "../include/apachelogparser.hpp" 
#include "../include/ipregistry.hpp"

int main() {

    ApacheLogParser parser;
    IPRegistry registry;

    // Use a relative path based on where we assume the program is executed from
    std::string filePath = "data/apache.log"; // Harcoded on purpose
    std::ifstream logFile(filePath);

    // Verify the file exists and is accessible
    if (!logFile.is_open()) {
        std::cerr << "Error: Could not open " << filePath << "\n";
        return 1;
    }

    std::cout << "Processing logs...\n";
    std::string currentLine;
    
    while (std::getline(logFile, currentLine)) {

        std::string extractedIP = parser.parseIP(currentLine);
        
        if (!extractedIP.empty()) {
            registry.recordIP(extractedIP);
        }
    }

    logFile.close(); // Don't forget to close the file

    std::cout << "Total unique IPs found: " << registry.totalUniqueIPs() << "\n";
    
    registry.printTopResults(10);

    return 0;
}