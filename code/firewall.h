#ifndef FIREWALL_H
#define FIREWALL_H
#include "request.h"
#include <string>
#include <vector>
#include <utility>

class Firewall {
public:
    Firewall();
    unsigned int ip_to_int(const std::string& ip) const;
    bool isBlocked(const Request& request) const;
    void blockRange(const std::string& start_ip, const std::string& end_ip);
private:
    std::vector<std::pair<unsigned int, unsigned int>> blockedRanges;
};

#endif