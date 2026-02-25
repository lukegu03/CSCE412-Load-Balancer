/**
 * @file request.h
 * @brief Declares the Request class representing a network request.
 *
 * This header defines the Request class, which models an incoming
 * network request with source and destination IP addresses,
 * processing time, and request type metadata.
 */

#ifndef REQUEST_H
#define REQUEST_H

#include <string>

/**
 * @class Request
 * @brief Represents a single network request handled by the system.
 *
 * Each Request object contains identifying information including
 * source IP, destination IP, processing time, and request type.
 * A unique request ID is automatically assigned using a static counter.
 */
class Request {
public:

    /**
     * @brief Constructs a Request object.
     *
     * Assigns a unique request ID and initializes all request fields.
     *
     * @param ip_in Source IP address of the request.
     * @param ip_out Destination IP address of the request.
     * @param time_to_process Time required to process the request.
     * @param request_type Type of request (e.g., 'P' for processing, 'S' for streaming).
     */
    Request(const std::string& ip_in, const std::string& ip_out, int time_to_process, char request_type);

    /**
     * @brief Returns the unique identifier for this request.
     *
     * @return The request ID.
     */
    int get_request_id() const;

    /**
     * @brief Returns the source IP address.
     *
     * @return The incoming IP address as a string.
     */
    std::string get_ip_in() const;

    /**
     * @brief Returns the destination IP address.
     *
     * @return The outgoing IP address as a string.
     */
    std::string get_ip_out() const;

    /**
     * @brief Returns the processing time required for this request.
     *
     * @return The time (in simulation units) needed to process the request.
     */
    int get_time_to_process() const;

    /**
     * @brief Returns the request type.
     *
     * @return A character representing the request type.
     */
    char get_request_type() const;

private:

    /**
     * @brief Static counter used to generate unique request IDs.
     */
    static int next_id;

    /**
     * @brief Unique identifier for this request.
     */
    int request_id;

    /**
     * @brief Source IP address of the request.
     */
    std::string ip_in;

    /**
     * @brief Destination IP address of the request.
     */
    std::string ip_out;

    /**
     * @brief Time required to process the request.
     */
    int time_to_process;

    /**
     * @brief Type of request (e.g., processing or streaming).
     */
    char request_type;
};

#endif