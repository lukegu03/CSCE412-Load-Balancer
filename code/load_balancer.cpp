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

bool LoadBalancer::low_load() const {
    return requestQueue.size() < 50;
}

bool LoadBalancer::high_load() const {
    return requestQueue.size() > 80;
}


int LoadBalancer::get_queue_size() const {
    return requestQueue.size();
}

