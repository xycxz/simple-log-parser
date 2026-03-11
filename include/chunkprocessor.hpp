#ifndef CHUNK_PROCESSOR_HPP
#define CHUNK_PROCESSOR_HPP

#include <vector>
#include <string>
#include "../interface/ilogparser.hpp"
#include "../include/ipregistry.hpp"

namespace LogProcessor {
    
    void processChunk(const std::vector<std::string>& chunk, 
                      const ILogParser& parser, 
                      IPRegistry& registry);
}

#endif