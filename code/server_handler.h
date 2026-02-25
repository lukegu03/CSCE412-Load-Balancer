/**
 * @file server_handler.h
 * @brief Declares the ServerHandler class responsible for managing servers.
 *
 * This header defines the ServerHandler class, which maintains a collection
 * of Server instances, assigns requests to available servers, and supports
 * dynamic scaling of server resources.
 */

#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H

#include "server.h"
#include "firewall.h"
#include "load_balancer.h"
#include <vector>
#include <memory>

/**
 * @class ServerHandler
 * @brief Manages a pool of servers and distributes requests among them.
 *
 * The ServerHandler maintains ownership of multiple Server objects using
 * std::unique_ptr to ensure proper memory management. It supports adding
 * and removing servers, assigning requests, and scaling server capacity
 * based on system load.
 */
class ServerHandler {
public:

    /**
     * @brief Constructs an empty ServerHandler with no active servers.
     */
    ServerHandler();

    /**
     * @brief Adds a new server to the pool.
     *
     * Creates and stores a new Server instance.
     */
    void add_server();

    /**
     * @brief Removes a server from the pool.
     *
     * @param server Pointer to the Server to remove.
     */
    void remove_server(Server* server);

    /**
     * @brief Retrieves an available server.
     *
     * Searches for a server that is currently not processing a request.
     *
     * @return Pointer to an available Server, or nullptr if none are available.
     */
    Server* get_available_server();

    /**
     * @brief Assigns a request to an available server.
     *
     * If a server is available, the request is assigned to it.
     *
     * @param request The Request to assign.
     * @return Pointer to the Server handling the request, or nullptr if none are available.
     */
    Server* assign_request(const Request& request);

    /**
     * @brief Scales the system up by adding a server.
     */
    void scale_up();

    /**
     * @brief Scales the system down by removing a server.
     *
     * @param server Pointer to the Server to remove.
     */
    void scale_down(Server* server);

    /**
     * @brief Returns the number of active servers.
     *
     * @return The current server count.
     */
    int get_server_count() const;

    /**
     * @brief Updates the state of all servers.
     *
     * Typically used to advance simulation time or process
     * server state transitions.
     */
    void update_servers();

private:

    /**
     * @brief Collection of managed Server instances.
     *
     * Servers are owned via std::unique_ptr to ensure automatic
     * cleanup and exclusive ownership.
     */
    std::vector<std::unique_ptr<Server>> servers;
};

#endif