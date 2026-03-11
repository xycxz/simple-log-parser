#include "../include/chunkprocessor.hpp"

namespace LogProcessor {
    
    void processChunk(const std::vector<std::string>& chunk, 
                      const ILogParser& parser, 
                      IPRegistry& registry) {

        for (const auto& line : chunk) {
            std::string extractedIP = parser.parseIP(line);

            if (!extractedIP.empty()) {
                registry.recordIP(extractedIP);
            }
        }
    }
}