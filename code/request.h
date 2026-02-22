#pragma once
#include <string>

struct Request{
    int id;
    std::string IP_in;
    std::string IP_out;
    int time_to_process;
    char job_type;
};