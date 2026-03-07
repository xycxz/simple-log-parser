#ifndef ILOG_PARSER_HPP // Prevents the file from being read twice
#define ILOG_PARSER_HPP
#include <string>

class ILogParser {
public:
    virtual ~ILogParser() = default;
    // It takes a line and returns the extracted IP (The Essence)
    virtual std::string parseIP(const std::string& line) const = 0;
};

#endif