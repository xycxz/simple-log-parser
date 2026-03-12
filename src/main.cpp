#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <future>

#include "../include/apachelogparser.hpp" 
#include "../include/ipregistry.hpp"
#include "../include/chunkprocessor.hpp"


// Note: I will consider using a Thread Pool for performance!
int main(int argc, char* argv[]) {

    if (argc != 3) {
        std::cerr << "Usage: log_analyzer <file_path> <top_n>\n";
        return 1;
    }
    
    std::string filePath = argv[1];
    size_t topN = 0;

    try {

        if (argv[2][0] == '-') {
            std::cerr << "Error: <top_n> must be a positive number\n";
            return 1;
        }

        topN = std::stoul(argv[2]);

        if (topN == 0) {
            std::cerr << "Error: <top_n> must be a positive number\n";
            return 1;
        }

    } catch (const std::invalid_argument&) {
        std::cerr << "Error: <top_n> must be a valid number\n";
        return 1;

    } catch (const std::out_of_range&) {
        std::cerr << "Error: <top_n> is too large\n";
        return 1;
    }

    try {

        ApacheLogParser parser;
        IPRegistry registry;

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

        registry.printResults(topN);

    } catch (const std::exception& e) {
        
        std::cerr << "\n--- ERROR ---\n" << e.what() << std::endl;
        return 1;
    }

    return 0;
}