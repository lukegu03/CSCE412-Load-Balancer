#include "request.h"
#include <string>

int Request::next_id = 0;

Request::Request(const std::string& ip_in, const std::string& ip_out, int time_to_process, char request_type)
    : request_id(next_id++), ip_in(ip_in), ip_out(ip_out), time_to_process(time_to_process), request_type(request_type) {}

int Request::get_request_id() const {
    return request_id;
}

std::string Request::get_ip_in() const {
    return ip_in;
}

std::string Request::get_ip_out() const {
    return ip_out;
}

int Request::get_time_to_process() const {
    return time_to_process;
}

char Request::get_request_type() const {
    return request_type;
}  