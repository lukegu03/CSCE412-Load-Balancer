/**
 * @file server.h
 * @brief Declares the Server class representing a processing server instance.
 *
 * This header defines the Server class, which models an individual server
 * capable of processing requests. Each server maintains its own unique ID,
 * tracks the currently active request, and records how long it will remain busy.
 */

#ifndef SERVER_H
#define SERVER_H

#include "request.h"
#include <string>

/**
 * @class Server
 * @brief Represents a single server capable of processing requests.
 *
 * Each Server instance has a unique identifier and can process one request
 * at a time. The server tracks the ID of the active request and the time
 * until which it remains busy.
 */
class Server {
public:

    /**
     * @brief Constructs a Server and assigns it a unique ID.
     */
    Server();

    /**
     * @brief Starts processing a request.
     *
     * Marks the server as busy and records the request ID and
     * processing completion time.
     *
     * @param request The Request to begin processing.
     */
    void start_request(const Request& request);

    /**
     * @brief Checks whether the server is available.
     *
     * @return true if the server is not currently processing a request,
     *         false otherwise.
     */
    bool is_available() const;

    /**
     * @brief Returns the unique identifier of the server.
     *
     * @return The server ID.
     */
    int get_server_id() const;

    /**
     * @brief Returns the ID of the currently active request.
     *
     * @return The active request ID.
     */
    int get_active_request_id() const;

    /**
     * @brief Returns the time until which the server remains busy.
     *
     * @return The simulation time when the server will become available.
     */
    int get_busy_until_time() const;

    /**
     * @brief Updates the server's busy state.
     *
     * Typically called during simulation updates to decrement
     * or evaluate the server’s busy time.
     */
    void update_busy_time();

private:

    /**
     * @brief Static counter used to assign unique server IDs.
     */
    static int next_id;

    /**
     * @brief Unique identifier for this server.
     */
    int server_id;

    /**
     * @brief IP address assigned to the server.
     */
    std::string server_ip;

    /**
     * @brief ID of the request currently being processed.
     */
    int active_request_id;

    /**
     * @brief Simulation time until which the server remains busy.
     */
    int busy_until_time;
};

#endif