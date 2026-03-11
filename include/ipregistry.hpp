#ifndef IP_REGISTRY_HPP
#define IP_REGISTRY_HPP

#include <string>
#include <unordered_map>
#include <mutex>
#include <vector>
#include <utility>

using SortedIPList = std::vector<std::pair<std::string, int>>;

class IPRegistry {

public:
// Receive an IP and increment its counter in the map
void recordIP(const std::string& ip);

// Sort the list of IPs
SortedIPList getSortedData() const;

// Print results
void printResults(size_t limit) const;

private:
    std::unordered_map<std::string, int> ipCounts;
    mutable std::mutex registryMutex;

    // Lock already held
    SortedIPList getSortedDataUnlocked() const;
};

#endif