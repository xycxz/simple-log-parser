#ifndef IP_REGISTRY_HPP
#define IP_REGISTRY_HPP

#include <string>
#include <unordered_map>

class IPRegistry {
    
public:
// Receive an IP and increment its counter in the map
void recordIP(const std::string& ip);

// Report how many times we've seen a specific IP
int getCount(const std::string& ip) const;

// See the total number of unique IPs
size_t totalUniqueIPs() const;

// Print top results
void printTopResults(int limit = 10) const;

private:
    std::unordered_map<std::string, int> ipCounts;
};

#endif