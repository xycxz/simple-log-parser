#ifndef APACHE_LOG_PARSER_HPP
#define APACHE_LOG_PARSER_HPP

#include "../interface/ilogparser.hpp"

class ApacheLogParser : public ILogParser {
public:
    // Override for a particular implementation
    std::string parseIP(const std::string& line) const override;
};

#endif