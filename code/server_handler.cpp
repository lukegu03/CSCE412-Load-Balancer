#include "server_handler.h"
#include "server.h"
#include <iostream>

#define ORANGE  "\033[38;5;208m"
#define RESET   "\033[0m"


ServerHandler::ServerHandler() {} // start with no servers

void ServerHandler::add_server() {
    servers.emplace_back(new Server());
}

void ServerHandler::remove_server(Server* server) {
    int server_id = server->get_server_id();
    for (auto it = servers.begin(); it != servers.end(); ++it) {
        if ((*it)->get_server_id() == server_id) {
            servers.erase(it);
            break;
        }
    }
}

Server* ServerHandler::get_available_server() {
    for (auto& server : servers) {
        if (server->is_available()) {
            return server.get();
        }
    }
    return nullptr;
}

Server* ServerHandler::assign_request(const Request& request) {
    Server* server = get_available_server();
    if (server) {
        server->start_request(request);
    }
    return server;
}

void ServerHandler::scale_up() {
    add_server();
}

void ServerHandler::scale_down(Server* server) {
    remove_server(server);
}

int ServerHandler::get_server_count() const {
    return servers.size();
}

void ServerHandler::update_servers() {
    for (auto& server : servers) {
        if (server->is_available() == false) {
            std::cout << ORANGE << "Server " << server->get_server_id() << " is busy with request " << server->get_active_request_id() << " until time " << server->get_busy_until_time() << "." << RESET << std::endl;
            server->update_busy_time();
        }
    }
}
