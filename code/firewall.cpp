#include "firewall.h"

Firewall::Firewall() = default;

unsigned int Firewall::ip_to_int(const std::string& ip) const {
    unsigned int result = 0;
    size_t start = 0;
    for (int i = 0; i < 4; ++i) {
        size_t end = ip.find('.', start);
        if (end == std::string::npos) {
            end = ip.length();
        }
        result = (result << 8) | std::stoi(ip.substr(start, end - start));
        start = end + 1;
    }
    return result;
}

void Firewall::blockRange(const std::string& start_ip, const std::string& end_ip) {
    unsigned int start = ip_to_int(start_ip);
    unsigned int end = ip_to_int(end_ip);
    if (start > end) {
        std::swap(start, end);
    }
    blockedRanges.emplace_back(start, end);
}

bool Firewall::isBlocked(const Request& request) const {
    unsigned int ip_in = ip_to_int(request.get_ip_in());
    for (const auto& range : blockedRanges) {
        if (ip_in >= range.first && ip_in <= range.second) {
            return true;
        }
    }
    return false;
}
