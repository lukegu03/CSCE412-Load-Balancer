/**
 * @file server.cpp
 * @brief Implements the Server class representing a processing server.
 *
 * This file contains the implementation of server initialization,
 * request processing, and busy-time management logic.
 */

#include <string>
#include "server.h"

/**
 * @brief Static counter used to assign unique IDs to servers.
 *
 * This value increments each time a new Server instance is created.
 */
int Server::next_id = 0;

/**
 * @brief Constructs a Server and assigns it a unique ID.
 *
 * Initializes the server with:
 * - A unique server ID
 * - An empty IP address
 * - No active request (active_request_id = -1)
 * - A busy time of 0 (available state)
 */
Server::Server() : server_id(next_id++), server_ip(""), active_request_id(-1), busy_until_time(0) {}

/**
 * @brief Starts processing a request.
 *
 * Sets the active request ID and updates the server's busy time
 * by adding the request's processing duration.
 *
 * @param request The Request to begin processing.
 */
void Server::start_request(const Request& request) {
    active_request_id = request.get_request_id();
    busy_until_time += request.get_time_to_process();
}

/**
 * @brief Checks whether the server is available.
 *
 * A server is considered available if its busy time
 * is less than or equal to zero.
 *
 * @return true if the server is available, false otherwise.
 */
bool Server::is_available() const {
    return busy_until_time <= 0;
}

/**
 * @brief Returns the unique identifier of the server.
 *
 * @return The server ID.
 */
int Server::get_server_id() const {
    return server_id;
}

/**
 * @brief Returns the ID of the currently active request.
 *
 * @return The active request ID.
 */
int Server::get_active_request_id() const {
    return active_request_id;
}

/**
 * @brief Returns the time until which the server remains busy.
 *
 * @return The remaining busy time in simulation units.
 */
int Server::get_busy_until_time() const {
    return busy_until_time;
}

/**
 * @brief Updates the server's busy time.
 *
 * Decrements the busy time by one simulation unit
 * if the server is currently busy.
 */
void Server::update_busy_time() {
    if (busy_until_time > 0) {
        busy_until_time -= 1;
    }
}