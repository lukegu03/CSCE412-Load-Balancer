/**
 * @file server_handler.cpp
 * @brief Implements the ServerHandler class for managing server instances.
 *
 * This file contains the logic for adding, removing, and assigning requests
 * to servers, as well as updating server states during simulation.
 */

#include "server_handler.h"
#include "server.h"
#include <iostream>

/**
 * @brief ANSI escape code for orange-colored console output.
 */
#define ORANGE  "\033[38;5;208m"

/**
 * @brief ANSI escape code to reset console color formatting.
 */
#define RESET   "\033[0m"

/**
 * @brief Constructs an empty ServerHandler.
 *
 * Initializes the handler with no active servers.
 */
ServerHandler::ServerHandler() {} // start with no servers

/**
 * @brief Adds a new server to the server pool.
 *
 * A new Server instance is dynamically allocated and stored
 * using std::unique_ptr for automatic memory management.
 */
void ServerHandler::add_server() {
    servers.emplace_back(new Server());
}

/**
 * @brief Removes a server from the server pool.
 *
 * The server is identified by its unique server ID and erased
 * from the internal vector.
 *
 * @param server Pointer to the Server to remove.
 */
void ServerHandler::remove_server(Server* server) {
    int server_id = server->get_server_id();
    for (auto it = servers.begin(); it != servers.end(); ++it) {
        if ((*it)->get_server_id() == server_id) {
            servers.erase(it);
            break;
        }
    }
}

/**
 * @brief Retrieves an available server.
 *
 * Searches through the server pool and returns the first server
 * that is not currently processing a request.
 *
 * @return Pointer to an available Server, or nullptr if none are available.
 */
Server* ServerHandler::get_available_server() {
    for (auto& server : servers) {
        if (server->is_available()) {
            return server.get();
        }
    }
    return nullptr;
}

/**
 * @brief Assigns a request to an available server.
 *
 * If a server is available, the request is started on that server.
 *
 * @param request The Request to assign.
 * @return Pointer to the Server handling the request, or nullptr if none are available.
 */
Server* ServerHandler::assign_request(const Request& request) {
    Server* server = get_available_server();
    if (server) {
        server->start_request(request);
    }
    return server;
}

/**
 * @brief Scales the system up by adding a new server.
 */
void ServerHandler::scale_up() {
    add_server();
}

/**
 * @brief Scales the system down by removing a server.
 *
 * @param server Pointer to the Server to remove.
 */
void ServerHandler::scale_down(Server* server) {
    remove_server(server);
}

/**
 * @brief Returns the number of active servers.
 *
 * @return The total number of servers currently managed.
 */
int ServerHandler::get_server_count() const {
    return servers.size();
}

/**
 * @brief Updates all busy servers.
 *
 * Iterates through the server pool and updates the busy time
 * for servers that are currently processing a request.
 * Console output is displayed to indicate server activity.
 */
void ServerHandler::update_servers() {
    for (auto& server : servers) {
        if (server->is_available() == false) {
            std::cout << ORANGE
                      << "Server " << server->get_server_id()
                      << " is busy with request " << server->get_active_request_id()
                      << " until time " << server->get_busy_until_time()
                      << "."
                      << RESET << std::endl;

            server->update_busy_time();
        }
    }
}