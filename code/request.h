#ifndef REQUEST_H
#define REQUEST_H
#include <string>

class Request {
public:
    Request(const std::string& ip_in, const std::string& ip_out, int time_to_process, char request_type);
    int get_request_id() const;
    std::string get_ip_in() const;
    std::string get_ip_out() const;
    int get_time_to_process() const;
    char get_request_type() const;

private:
    static int next_id;
    int request_id;
    std::string ip_in;
    std::string ip_out;
    int time_to_process;
    char request_type;
};

#endif
