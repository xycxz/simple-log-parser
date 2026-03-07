#include "../include/ipregistry.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

void IPRegistry::recordIP(const std::string& ip) {
    ipCounts[ip]++;
}

int IPRegistry::getCount(const std::string& ip) const {

    auto it = ipCounts.find(ip);
    
    // If the iterator reaches the 'end', the IP is not in records.
    if (it == ipCounts.end()) {
        return 0;
    }
    
    // If found, return the value
    return it->second; 
}

size_t IPRegistry::totalUniqueIPs() const {
    return ipCounts.size();
}

void IPRegistry::printTopResults(int limit) const {
    // Copy the map pairs to a vector to sort them by count
    std::vector<std::pair<std::string, int>> vec(ipCounts.begin(), ipCounts.end());
    std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; // Sort descending by count
    });

    std::cout << "\n--- Top " << limit << " IPs ---\n\n";
    for (int i = 0; i < limit && i < vec.size(); ++i) {
        std::cout << vec[i].first << " : " << vec[i].second << " requests\n";
    }
}