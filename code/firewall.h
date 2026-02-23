#ifndef FIREWALL_H
#define FIREWALL_H
#include "request.h"
#include <string>
#include <unordered_set>

class Firewall {
public:
    Firewall();
    Firewall(const std::unordered_set<std::string>& initialBlocked);
    bool isBlocked(const Request& request);
private:
    std::unordered_set<std::string> blockedIPs;
};

#endif