/**
 * @file request.cpp
 * @brief Implements the Request class representing a network request.
 *
 * This file contains the implementation of the Request constructor
 * and accessor methods. Each Request is automatically assigned a
 * unique ID using a static counter.
 */

#include "request.h"
#include <string>

/**
 * @brief Static counter used to assign unique IDs to requests.
 *
 * This value increments each time a new Request object is constructed.
 */
int Request::next_id = 0;

/**
 * @brief Constructs a Request object and assigns a unique ID.
 *
 * The constructor initializes all member variables using an initializer list.
 * The request_id is assigned using the static next_id counter.
 *
 * @param ip_in Source IP address of the request.
 * @param ip_out Destination IP address of the request.
 * @param time_to_process Time required to process the request.
 * @param request_type Type of request (e.g., 'P' for processing, 'S' for streaming).
 */
Request::Request(const std::string& ip_in, const std::string& ip_out, int time_to_process, char request_type)
    : request_id(next_id++), ip_in(ip_in), ip_out(ip_out), time_to_process(time_to_process), request_type(request_type) {}

/**
 * @brief Returns the unique identifier of this request.
 *
 * @return The request ID.
 */
int Request::get_request_id() const {
    return request_id;
}

/**
 * @brief Returns the source IP address.
 *
 * @return The incoming IP address as a string.
 */
std::string Request::get_ip_in() const {
    return ip_in;
}

/**
 * @brief Returns the destination IP address.
 *
 * @return The outgoing IP address as a string.
 */
std::string Request::get_ip_out() const {
    return ip_out;
}

/**
 * @brief Returns the processing time required for this request.
 *
 * @return The time (in simulation units) needed to process the request.
 */
int Request::get_time_to_process() const {
    return time_to_process;
}

/**
 * @brief Returns the request type.
 *
 * @return A character representing the request type.
 */
char Request::get_request_type() const {
    return request_type;
}