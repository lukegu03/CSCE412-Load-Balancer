# ifndef LOAD_BALANCER_H
# define LOAD_BALANCER_H
#include "request.h"
#include <queue>

class LoadBalancer {
    public:
        LoadBalancer();
        void queue_request(const Request& request);
        Request process_request();
        bool is_empty() const;
        bool low_load(int server_count) const;
        bool high_load(int server_count) const;
        int get_time() const;
        int get_queue_size() const;
    private:
        std::queue<Request> requestQueue;
};

#endif