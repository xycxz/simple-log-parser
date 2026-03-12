#include "include/ipregistry.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

void IPRegistry::recordIP(const std::string& ip) {
    std::lock_guard<std::mutex> lock(registryMutex);
    ipCounts[ip]++; // Critical section
}

SortedIPList IPRegistry::getSortedDataUnlocked() const {
    // Transform the unordered map into a vector
    // Critical Section down below
    SortedIPList sortedList(ipCounts.begin(), ipCounts.end());

    // Sort the Data
    std::sort(sortedList.begin(), sortedList.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; // Descending order
    });

    return sortedList;
}

// Using this in case of adding future methods
SortedIPList IPRegistry::getSortedData() const {
    std::lock_guard<std::mutex> lock(registryMutex);
    return getSortedDataUnlocked(); // Lock is already held
}

void IPRegistry::printResults(size_t limit) const {
    // Get the pre-sorted data relevant properties
    SortedIPList data = getSortedData();
    size_t actualSize = data.size();

    if (limit > actualSize) {

        std::cerr << "Warning: Requested " << limit << " IPs, but only " 
                  << actualSize << " unique IPs exist.\n";
        limit = actualSize;
    }

    std::cout << "\n--- Displaying Top " << limit << " IPs ---\n";
    for (size_t i = 0; i < limit; ++i) {
        std::cout << data[i].first << " : " << data[i].second << " requests\n";
    }
}
