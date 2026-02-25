/**
 * @file firewall.h
 * @brief Declares the Firewall class used to block requests by IP range.
 *
 * This header defines a simple firewall that supports blocking inclusive IPv4
 * address ranges. Incoming requests can be checked against the configured
 * blocked ranges.
 */

#ifndef FIREWALL_H
#define FIREWALL_H

#include "request.h"
#include <string>
#include <vector>
#include <utility>

/**
 * @class Firewall
 * @brief Blocks requests based on IPv4 address ranges.
 *
 * The Firewall stores a list of blocked IP ranges. Each range is represented as
 * a pair of unsigned integers (start, end), where the integer form is derived
 * from a dotted-quad IPv4 string (e.g., "192.168.1.10").
 */
class Firewall {
public:
    /**
     * @brief Constructs an empty Firewall with no blocked ranges.
     */
    Firewall();

    /**
     * @brief Converts a dotted-quad IPv4 string into an unsigned integer.
     *
     * This helper is used to compare IP addresses efficiently by converting
     * them to an integer representation.
     *
     * @param ip IPv4 address as a string in dotted-quad form (e.g., "10.0.0.1").
     * @return Unsigned integer representation of the IPv4 address.
     */
    unsigned int ip_to_int(const std::string& ip) const;

    /**
     * @brief Determines whether an incoming request should be blocked.
     *
     * The request is considered blocked if its source IP falls within any
     * blocked range (inclusive).
     *
     * @param request The incoming request to evaluate.
     * @return true if the request's IP is in a blocked range, false otherwise.
     */
    bool isBlocked(const Request& request) const;

    /**
     * @brief Blocks an inclusive IPv4 address range.
     *
     * Adds a new blocked range defined by start and end IP addresses.
     * The order of the addresses is assumed to be start <= end; callers should
     * ensure the correct ordering (or the implementation may normalize it).
     *
     * @param start_ip Starting IPv4 address (inclusive).
     * @param end_ip Ending IPv4 address (inclusive).
     */
    void blockRange(const std::string& start_ip, const std::string& end_ip);

private:
    /**
     * @brief Collection of blocked IPv4 ranges.
     *
     * Each entry stores (start, end) as integer-converted IPv4 addresses.
     */
    std::vector<std::pair<unsigned int, unsigned int>> blockedRanges;
};

#endif