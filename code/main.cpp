#include <iostream>
#include "server_handler.h"
#include "request.h"
#include "firewall.h"
#include "load_balancer.h"
#include <vector>
#include <string>
#include <unistd.h>
#include <ctime>
#include <fstream>

// color codes
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define RESET   "\033[0m"

std::string generate_random_ip() {
    return std::to_string(rand() % 256) + "." +
           std::to_string(rand() % 256) + "." +
           std::to_string(rand() % 256) + "." +
           std::to_string(rand() % 256);
}

char generate_random_request_type() {
    const char types[] = {'P', 'S'};
    return types[rand() % 2];
}

int generate_random_time() {
    return rand() % 10 + 1;
}

int generate_random_request_count(){
    return rand() % 20 + 1;
}


int main(){
    std::srand(static_cast<unsigned>(std::time(nullptr))); // seed random number generator
    std::ofstream logFile("log.txt");

    int initial_streaming_server_count = 0;
    std::cout << "Enter an initial streaming server count: ";
    std::cin >> initial_streaming_server_count;

    int initial_processing_server_count = 0;
    std::cout << "Enter an initial processing server count: ";
    std::cin >> initial_processing_server_count;

    int total_simulation_time = 0;
    std::cout << "Enter total simulation time (clock cycles): ";
    std::cin >> total_simulation_time;
    int initial_request_count = (initial_streaming_server_count + initial_processing_server_count) * 100;

    int total_request_generated = initial_request_count;
    int total_servers_created = initial_streaming_server_count + initial_processing_server_count;
    int total_servers_removed = 0;

    int clock = 0;
    int check_server_count_buffer = 5;
    int time_to_add_requests = generate_random_time();

    int requests_per_clock = generate_random_request_count();

    Firewall firewall;
    logFile << "Firewall initialized" << std::endl;
    LoadBalancer streaming_load_balancer;
    logFile << "Streaming load balancer initialized" << std::endl;
    LoadBalancer processing_load_balancer;
    logFile << "Processing load balancer initialized" << std::endl;
    ServerHandler streaming_server_handler;
    logFile  << "Streaming server handler initialized" << std::endl;
    ServerHandler processing_server_handler;
    logFile << "Processing server handler initialized" << std::endl;

    std::string block_choice;
    std:: cout << "Would you like to block any IP ranges in the firewall before starting the simulation? (yes/no): ";
    std::cin >> block_choice;

    if (block_choice == "yes") {
        std::cout << "Enter IP range to block in the format start_ip end_ip (e.g. 192.168.1.1 192.168.1.255): ";
        std::string start_ip, end_ip;
        std::cin >> start_ip >> end_ip;
        firewall.blockRange(start_ip, end_ip);
    }
   

    // initialize servers
    for (int i = 0; i < initial_streaming_server_count; ++i) {
        streaming_server_handler.add_server();
    }
    for (int i = 0; i < initial_processing_server_count; ++i) {
        processing_server_handler.add_server();
    }

    //initialze request and add to load balancers
    for (int i = 0; i < initial_request_count; ++i){
        Request request(generate_random_ip(), generate_random_ip(), generate_random_time(), generate_random_request_type());
        if (firewall.isBlocked(request) == false){
            if (request.get_request_type() == 'P') {
                processing_load_balancer.queue_request(request);
            } else {
                streaming_load_balancer.queue_request(request);
            }
        }else{
            std::cout << YELLOW <<  "Request from " << request.get_ip_in() << " is blocked by the firewall." << RESET << std::endl;
            logFile << "Request from " << request.get_ip_in() << " is blocked by the firewall." << std::endl;
        }
    }

    // Simulate processing requests
    while (clock < total_simulation_time) {
        // step 1: add new requests to the load balancers
        if(time_to_add_requests <= 0){
            for (int i = 0; i < requests_per_clock; ++i){
                Request request(generate_random_ip(), generate_random_ip(), generate_random_time(), generate_random_request_type());
                if (firewall.isBlocked(request) == false){
                    if (request.get_request_type() == 'P') {
                        processing_load_balancer.queue_request(request);
                    } else {
                        streaming_load_balancer.queue_request(request);
                    }
                    total_request_generated++;
                }else{
                    std::cout << YELLOW <<  "Request from " << request.get_ip_in() << " is blocked by the firewall." << RESET << std::endl;
                    logFile << "Request from " << request.get_ip_in() << " is blocked by the firewall." << std::endl;
                }
            }
            time_to_add_requests = generate_random_time();
            requests_per_clock = generate_random_request_count();
        }


        //step 2: check each server's busy time and update it
        streaming_server_handler.update_servers();
        processing_server_handler.update_servers();

        // step 3: check if there are any open servers and assign requests to them

        while (!streaming_load_balancer.is_empty() && streaming_server_handler.get_available_server() != nullptr){
            Request request = streaming_load_balancer.process_request();
            Server* server = streaming_server_handler.assign_request(request);
            if (server) {
                std::cout << BLUE << "Assigned request from " << request.get_ip_in() << " sent to streaming server " << server->get_server_id() << "." << RESET << std::endl;
            } else {
                std::cout << YELLOW << "No available servers to handle the request from " << request.get_ip_in() << "." << RESET << std::endl;
            }   
        }
        while (!processing_load_balancer.is_empty() && processing_server_handler.get_available_server() != nullptr){
            Request request = processing_load_balancer.process_request();
            Server* server = processing_server_handler.assign_request(request);
            if (server) {
                std::cout << BLUE << "Assigned request from " << request.get_ip_in() << " sent to processing server " << server->get_server_id() << "." << RESET << std::endl;
            } else {
                std::cout << YELLOW << "No available servers to handle the request from " << request.get_ip_in() << "." << RESET << std::endl;
            }   
        }

        //step 4: check load balancer and scale up or down servers only every check_server_count_buffer clocks
        if (clock % check_server_count_buffer == 0) {
            if (streaming_load_balancer.low_load(streaming_server_handler.get_server_count()) && streaming_server_handler.get_server_count() > 1){
                // only scale down if there is a server that is not busy
                Server* down_server = streaming_server_handler.get_available_server();
                if (down_server) {
                    streaming_server_handler.scale_down(down_server);
                    total_servers_removed++;
                    std::cout << RED << "Scaling down streaming servers. Current server count: " << streaming_server_handler.get_server_count() << "." << RESET << std::endl;
                }
            }else if (streaming_load_balancer.high_load(streaming_server_handler.get_server_count())){
                streaming_server_handler.scale_up();
                total_servers_created++;
                std::cout << GREEN << "Scaling up streaming servers. Current server count: " << streaming_server_handler.get_server_count() << "." << RESET << std::endl;
             } 

             if(processing_load_balancer.low_load(processing_server_handler.get_server_count()) && processing_server_handler.get_server_count() > 1){
                // only scale down if there is a server that is not busy
                Server* down_server = processing_server_handler.get_available_server();
                if (down_server) {
                    processing_server_handler.scale_down(down_server);
                    total_servers_removed++;
                    std::cout << RED << "Scaling down processing servers. Current server count: " << processing_server_handler.get_server_count() << "." << RESET << std::endl;
                }
            }else if (processing_load_balancer.high_load(processing_server_handler.get_server_count())){
                processing_server_handler.scale_up();
                total_servers_created++;
                std::cout << GREEN << "Scaling up processing servers. Current server count: " << processing_server_handler.get_server_count() << "." << RESET << std::endl;
             }
        }

        // step 5: increment clock
        clock++;
        time_to_add_requests--;
        std::cout << BLUE << "Clock: " << clock << RESET << std::endl;
        if (clock % 25 == 0) {
            logFile << std::endl;
            logFile << "Clock: " << clock << std::endl;
            logFile << "Current streaming server count: " << streaming_server_handler.get_server_count() << "." << std::endl;
            logFile << "Current streaming load balancer queue size: " << streaming_load_balancer.get_queue_size() << "." << std::endl;

            logFile << "Current processing server count: " << processing_server_handler.get_server_count() << "." << std::endl;
            logFile << "Current processing load balancer queue size: " << processing_load_balancer.get_queue_size() << "." << std::endl;

            logFile << "Requests processed (or currentlty processing) so far: " << total_request_generated - streaming_load_balancer.get_queue_size() - processing_load_balancer.get_queue_size() << "." << std::endl;
        }
    }

    logFile << std::endl << std::endl;
    logFile << "Simulation ended at clock " << clock << "." << std::endl;
    logFile << "Final streaming server count: " << streaming_server_handler.get_server_count() << "." << std::endl;
    logFile << "Final streaming load balancer queue size: " << streaming_load_balancer.get_queue_size() << "." << std::endl;

    logFile << "Final processing server count: " << processing_server_handler.get_server_count() << "." << std::endl;
    logFile << "Final processing load balancer queue size: " << processing_load_balancer.get_queue_size() << "." << std::endl;

    logFile << "Total requests generated: " << total_request_generated << "." << std::endl;
    logFile << "Total requests processed (or currently processing): " << total_request_generated - streaming_load_balancer.get_queue_size() - processing_load_balancer.get_queue_size() << "." << std::endl;
    
    logFile << "Total servers created: " << total_servers_created << "." << std::endl;
    logFile << "Total servers removed: " << total_servers_removed << "." << std::endl;
    logFile.close();
}