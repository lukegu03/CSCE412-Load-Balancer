#include "firewall.h"

Firewall::Firewall() = default;

Firewall::Firewall(const std::unordered_set<std::string>& initialBlocked)
    : blockedIPs(initialBlocked) {}

bool Firewall::isBlocked(const Request& request){
    return blockedIPs.find(request.get_ip_in()) != blockedIPs.end();
}
