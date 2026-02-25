/**
 * @file load_balancer.h
 * @brief Declares the LoadBalancer class for managing incoming requests.
 *
 * This header defines a simple load balancer that stores incoming requests
 * in a queue and provides logic to determine system load conditions.
 */

#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#include "request.h"
#include <queue>

/**
 * @class LoadBalancer
 * @brief Manages and distributes incoming requests using a FIFO queue.
 *
 * The LoadBalancer maintains a queue of Request objects. It provides
 * functionality for enqueueing, processing, and evaluating load
 * conditions based on the number of active servers.
 */
class LoadBalancer {
    public:

        /**
         * @brief Constructs an empty LoadBalancer.
         */
        LoadBalancer();

        /**
         * @brief Adds a request to the processing queue.
         *
         * @param request The incoming request to enqueue.
         */
        void queue_request(const Request& request);

        /**
         * @brief Removes and returns the next request in the queue.
         *
         * Requests are processed in First-In-First-Out (FIFO) order.
         *
         * @return The next Request to be processed.
         */
        Request process_request();

        /**
         * @brief Checks whether the request queue is empty.
         *
         * @return true if the queue contains no requests, false otherwise.
         */
        bool is_empty() const;

        /**
         * @brief Determines if the system is under low load.
         *
         * The load condition is evaluated based on the current queue size
         * and the number of active servers.
         *
         * @param server_count The number of active servers.
         * @return true if the system is considered under low load, false otherwise.
         */
        bool low_load(int server_count) const;

        /**
         * @brief Determines if the system is under high load.
         *
         * The load condition is evaluated based on the current queue size
         * and the number of active servers.
         *
         * @param server_count The number of active servers.
         * @return true if the system is considered under high load, false otherwise.
         */
        bool high_load(int server_count) const;

        /**
         * @brief Retrieves the current simulation time.
         *
         * @return The current time value used by the load balancer.
         */
        int get_time() const;

        /**
         * @brief Returns the number of requests currently in the queue.
         *
         * @return The size of the request queue.
         */
        int get_queue_size() const;

    private:

        /**
         * @brief Queue storing pending requests.
         *
         * Requests are processed in FIFO order.
         */
        std::queue<Request> requestQueue;
};

#endif