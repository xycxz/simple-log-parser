#include "../include/apachelogparser.hpp"

std::string ApacheLogParser::parseIP(const std::string& line) const {
    // Find the position of the very first space character
    size_t spacePos = line.find(' ');

    if (spacePos != std::string::npos) {

        return line.substr(0, spacePos);
    }
    
    return line; 
}