#include "include/apachelogparser.hpp"

std::string ApacheLogParser::parseIP(std::string_view line) const {
    // Find the position of the very first space character
    size_t spacePos = line.find(' ');

    if (spacePos != std::string::npos) {
        return std::string(line.substr(0, spacePos));
    }
    
    return ""; 
}