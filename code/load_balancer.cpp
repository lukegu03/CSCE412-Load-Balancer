/**
 * @file load_balancer.cpp
 * @brief Implements the LoadBalancer class for managing queued requests.
 *
 * This file contains the implementation of request queueing, processing,
 * and load evaluation logic for the LoadBalancer class.
 */

#include "load_balancer.h"
#include <queue>
# include "request.h"

/**
 * @brief Constructs an empty LoadBalancer.
 *
 * Initializes the internal request queue.
 */
LoadBalancer::LoadBalancer() {}

/**
 * @brief Adds a request to the processing queue.
 *
 * The request is appended to the internal FIFO queue and will be processed
 * in the order it was received.
 *
 * @param request The incoming request to enqueue.
 */
void LoadBalancer::queue_request(const Request& request) {
    requestQueue.push(request);
}

/**
 * @brief Removes and returns the next request in the queue.
 *
 * The request at the front of the queue is retrieved and removed.
 *
 * @return The next Request to be processed.
 */
Request LoadBalancer::process_request(){
    Request req = requestQueue.front();
    requestQueue.pop();
    return req;
}

/**
 * @brief Checks whether the request queue is empty.
 *
 * @return true if there are no pending requests, false otherwise.
 */
bool LoadBalancer::is_empty() const {
    return requestQueue.empty();
}

/**
 * @brief Determines whether the system is under low load.
 *
 * The system is considered under low load if the number of queued
 * requests is less than 50 times the number of active servers.
 *
 * @param server_count The number of active servers.
 * @return true if the queue size is below the low-load threshold.
 */
bool LoadBalancer::low_load(int server_count) const {
    return requestQueue.size() < 50*server_count;
}

/**
 * @brief Determines whether the system is under high load.
 *
 * The system is considered under high load if the number of queued
 * requests exceeds 80 times the number of active servers.
 *
 * @param server_count The number of active servers.
 * @return true if the queue size exceeds the high-load threshold.
 */
bool LoadBalancer::high_load(int server_count) const {
    return requestQueue.size() > 80*server_count;
}

/**
 * @brief Returns the number of requests currently in the queue.
 *
 * @return The size of the internal request queue.
 */
int LoadBalancer::get_queue_size() const {
    return requestQueue.size();
}