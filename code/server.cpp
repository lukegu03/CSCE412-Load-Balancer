#include <string>
#include "server.h"

int Server::next_id = 0;

Server::Server() : server_id(next_id++), server_ip(""), active_request_id(-1), busy_until_time(0) {}

void Server::start_request(const Request& request) {
    active_request_id = request.get_request_id();
    busy_until_time += request.get_time_to_process();
}

bool Server::is_available() const {
    return busy_until_time <= 0;
}

int Server::get_server_id() const {
    return server_id;
}

int Server::get_active_request_id() const {
    return active_request_id;
}

int Server::get_busy_until_time() const {
    return busy_until_time;
}

void Server::update_busy_time() {
    if (busy_until_time > 0) {
        busy_until_time -= 1;
    }
}
