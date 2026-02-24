#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H
#include "server.h"
#include "firewall.h"
#include "load_balancer.h"
#include <vector>
#include <memory>

class ServerHandler {
public:
    ServerHandler();
    void add_server();
    void remove_server(Server* server);
    Server* get_available_server();
    Server* assign_request(const Request& request);
    void scale_up();
    void scale_down(Server* server);
    int get_server_count() const;
    void update_servers();
private:
    std::vector<std::unique_ptr<Server>> servers;
};

#endif