/**
 * @file firewall.cpp
 * @brief Implements the Firewall class for blocking requests by IP range.
 *
 * This file contains the implementation of IPv4 string-to-integer conversion,
 * range blocking, and request filtering based on configured blocked ranges.
 */

#include "firewall.h"

/**
 * @brief Constructs an empty Firewall with no blocked ranges.
 */
Firewall::Firewall() = default;

/**
 * @brief Converts a dotted-quad IPv4 string into an unsigned integer.
 *
 * The IPv4 address is parsed as four octets separated by '.' and packed into a
 * 32-bit unsigned integer using left shifts.
 *
 * @param ip IPv4 address as a string in dotted-quad form (e.g., "192.168.0.1").
 * @return Unsigned integer representation of the IPv4 address.
 */
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

/**
 * @brief Blocks an inclusive IPv4 address range.
 *
 * Converts the provided start/end IP strings to integer form and stores the
 * inclusive range. If the start value is greater than the end value, the
 * values are swapped to normalize the range.
 *
 * @param start_ip Starting IPv4 address (inclusive).
 * @param end_ip Ending IPv4 address (inclusive).
 */
void Firewall::blockRange(const std::string& start_ip, const std::string& end_ip) {
    unsigned int start = ip_to_int(start_ip);
    unsigned int end = ip_to_int(end_ip);
    if (start > end) {
        std::swap(start, end);
    }
    blockedRanges.emplace_back(start, end);
}

/**
 * @brief Determines whether an incoming request should be blocked.
 *
 * The request is blocked if its source IP (request.get_ip_in()) falls within
 * any stored blocked range (inclusive).
 *
 * @param request The incoming request to evaluate.
 * @return true if the request's IP is in a blocked range, false otherwise.
 */
bool Firewall::isBlocked(const Request& request) const {
    unsigned int ip_in = ip_to_int(request.get_ip_in());
    for (const auto& range : blockedRanges) {
        if (ip_in >= range.first && ip_in <= range.second) {
            return true;
        }
    }
    return false;
}