#ifndef SERVER_H
#define SERVER_H
#include "request.h"
#include <string>

class Server {
public:
    Server();
    void start_request(const Request& request);
    bool is_available() const;
    int get_server_id() const;
    int get_active_request_id() const;
    int get_busy_until_time() const;
    void update_busy_time();
private:
    static int next_id;
    int server_id;
    std::string server_ip;
    int active_request_id;
    int busy_until_time;
};

#endif