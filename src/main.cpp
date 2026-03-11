#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <future>

#include "../include/apachelogparser.hpp" 
#include "../include/ipregistry.hpp"
#include "../include/chunkprocessor.hpp"


// Note: I will consider using a Thread Pool for performance!
int main() {
    
    try {
    
        ApacheLogParser parser;
        IPRegistry registry;

        // Use a relative path based on where we assume the program is executed from
        std::string filePath = "data/apache.log"; // Hardcoded on purpose
        std::ifstream logFile(filePath);

        // Verify the file exists and is accessible
        if (!logFile.is_open()) {
            std::cerr << "Error: Could not open " << filePath << "\n";
            return 1;
        }

        std::cout << "Processing logs...\n";
        
        std::vector<std::future<void>> activeTasks; // Keeps track of our background threads
        std::vector<std::string> currentChunk;
        constexpr size_t CHUNK_SIZE = 10000; // Read 10k lines at a time.
        
        std::string currentLine;
        currentChunk.reserve(CHUNK_SIZE); // Pre-allocate to avoid reallocations during fill

        auto dispatchChunk = [&]() {
            activeTasks.push_back(std::async(std::launch::async,
                                     LogProcessor::processChunk,
                                     std::move(currentChunk),
                                     std::ref(parser),
                                     std::ref(registry)));
            currentChunk.reserve(CHUNK_SIZE);
        };

        while (std::getline(logFile, currentLine)) {
            currentChunk.emplace_back(std::move(currentLine));

            // When the chunk is full, send it to a background thread
            if (currentChunk.size() >= CHUNK_SIZE) {    
                dispatchChunk();
            }
        }

        // After the loop, process the final remaining lines that didn't reach 10,000
        if (!currentChunk.empty()) {
            dispatchChunk();
        }

        // Wait for all background threads to finish their work before printing results.
        for (auto& task : activeTasks) {
            task.get();
        }

        registry.printResults(10);

    } catch (const std::exception& e) {
        
        std::cerr << "\n--- ERROR ---\n" << e.what() << std::endl;
        return 1;
    }

    return 0;
}