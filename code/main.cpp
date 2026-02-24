#include <iostream>
#include "server_handler.h"
#include "request.h"
#include "firewall.h"
#include "load_balancer.h"
#include <vector>
#include <string>
#include <unistd.h>
#include <fstream>

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



int main(){
    std::ofstream logFile("log.txt");

    int initial_server_count = 0;
    std::cout << "Enter an initial server count: ";
    std::cin >> initial_server_count;
    int total_simulation_time = 0;
    std::cout << "Enter total simulation time (clock cycles): ";
    std::cin >> total_simulation_time;
    int initial_request_count = initial_server_count * 100;

    int total_request_generated = initial_request_count;
    int total_servers_created = initial_server_count;
    int total_servers_removed = 0;

    int clock = 0;
    int check_server_count_buffer = 5;
    int time_to_add_requests = generate_random_time();

    // should request random number of requests per clock
    int requests_per_clock = generate_random_time();

    Firewall firewall;
    logFile << "Firewall initialized" << std::endl;
    LoadBalancer load_balancer;
    logFile << "Load balancer initialized" << std::endl;
    ServerHandler server_handler;
    logFile  << "Server handler initialized" << std::endl;

    // initialize servers
    for (int i = 0; i < initial_server_count; ++i) {
        server_handler.add_server();
    }

    //initialze request and add to load balancer
    for (int i = 0; i < initial_request_count; ++i){
        Request request(generate_random_ip(), generate_random_ip(), generate_random_time(), generate_random_request_type());
        if (firewall.isBlocked(request) == false){
            load_balancer.queue_request(request);
        }else{
            std::cout << "Request from " << request.get_ip_in() << " is blocked by the firewall." << std::endl;
            logFile << "Request from " << request.get_ip_in() << " is blocked by the firewall." << std::endl;
        }
    }

    // Simulate processing requests
    while (clock < total_simulation_time) {
        // step 1: add new requests to the load balancer
        if(time_to_add_requests <= 0){
            for (int i = 0; i < requests_per_clock; ++i){
                Request request(generate_random_ip(), generate_random_ip(), generate_random_time(), generate_random_request_type());
                if (firewall.isBlocked(request) == false){
                    load_balancer.queue_request(request);
                    total_request_generated++;
                }else{
                    std::cout << "Request from " << request.get_ip_in() << " is blocked by the firewall." << std::endl;
                    logFile << "Request from " << request.get_ip_in() << " is blocked by the firewall." << std::endl;
                }
            }
            time_to_add_requests = generate_random_time();
            requests_per_clock = generate_random_time();
        }


        //step 2: check each server's busy time and update it
        server_handler.update_servers();

        // step 3: check if there are any open servers and assign requests to them
        while (!load_balancer.is_empty() && server_handler.get_available_server() != nullptr){
            Request request = load_balancer.process_request();
            Server* server = server_handler.assign_request(request);
            if (server) {
                std::cout << "Assigned request from " << request.get_ip_in() << " sent to server " << server->get_server_id() << "." << std::endl;
                logFile << "Assigned request from " << request.get_ip_in() << " sent to server " << server->get_server_id() << "." << std::endl;
            } else {
                std::cout << "No available servers to handle the request from " << request.get_ip_in() << "." << std::endl;
                logFile << "No available servers to handle the request from " << request.get_ip_in() << "." << std::endl;
            }   
        }

        //step 4: check load balancer and scale up or down servers only every check_server_count_buffer clocks
        if (clock % check_server_count_buffer == 0) {
            if (load_balancer.low_load() && server_handler.get_server_count() > 1){
                // only scale down if there is a server that is not busy
                Server* down_server = server_handler.get_available_server();
                if (down_server) {
                    server_handler.scale_down(down_server);
                    total_servers_removed++;
                    std::cout << "Scaling down servers. Current server count: " << server_handler.get_server_count() << "." << std::endl;
                    logFile << "Scaling down servers. Current server count: " << server_handler.get_server_count() << "." << std::endl;
                }
            }else if (load_balancer.high_load()){
                server_handler.scale_up();
                total_servers_created++;
                std::cout << "Scaling up servers. Current server count: " << server_handler.get_server_count() << "." << std::endl;
                logFile << "Scaling up servers. Current server count: " << server_handler.get_server_count() << "." << std::endl;
             } 
        }

        // step 5: increment clock
        clock++;
        time_to_add_requests--;
        std::cout << "Clock: " << clock << std::endl;
        logFile << "Clock: " << clock << std::endl;
    }
    logFile << std::endl << std::endl;
    logFile << "Simulation ended at clock " << clock << "." << std::endl;
    logFile << "Final server count: " << server_handler.get_server_count() << "." << std::endl;
    logFile << "Final load balancer queue size: " << load_balancer.get_queue_size() << "." << std::endl;
    logFile << "Total requests generated: " << total_request_generated << "." << std::endl;
    logFile << "Total servers created: " << total_servers_created << "." << std::endl;
    logFile << "Total servers removed: " << total_servers_removed << "." << std::endl;
    logFile.close();
}