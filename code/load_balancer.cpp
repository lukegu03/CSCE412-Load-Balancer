#include "load_balancer.h"
#include <queue>
# include "request.h"

LoadBalancer::LoadBalancer() {}

void LoadBalancer::queue_request(const Request& request) {
    requestQueue.push(request);
}

Request LoadBalancer::process_request(){
    Request req = requestQueue.front();
    requestQueue.pop();
    return req;
}

bool LoadBalancer::is_empty() const {
    return requestQueue.empty();
}

bool LoadBalancer::low_load(int server_count) const {
    return requestQueue.size() < 50*server_count;
}

bool LoadBalancer::high_load(int server_count) const {
    return requestQueue.size() > 80*server_count;
}


int LoadBalancer::get_queue_size() const {
    return requestQueue.size();
}

