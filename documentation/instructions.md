Project 3 Description - (LB)

Project 3 — Load balancer

Overview

In this project, we will learn how to model a simulation of a large company's load-balancing web requests using a load balancer. We will simulate requests that contain Ip addresses from the requester, Ip addresses for the results, and a time (in clock cycles)

This project will require a real-world implementation of a queue.
We also need a struct, a lower-level data structure that allows data to be contained in an object.

Load balancers are available commercially, but in this project, you will build one that has:
● Requests - generates random IP addresses, both in and out, and random times for each request to be processed.
o IP in
o IP out
o Time (integer)
o Job type (Character P (processing), S (streaming))
● Webserver(s)
o Takes requests from the Load Balancer
o Process the requests
o Asks for another
● Load Balancer(s)
o Queue of requests
o Keeps track of time.

Project Objectives:

You will be able to:
● Show your understanding of building and using a load balancer.
● Develop a guide for your load balancer that does not get overloaded or underutilized.
Bonus Objectives: (20 Points)
You will be able to:

● Build a Switch class or appropriately configure another instance of your load balancer, that can route jobs based on job type, Streaming or Processing.

● Run multiple load balancers concurrently, keeping statistics for each.

 

Instructions:
1. This is an individual project. You must turn in your own work.
2. Collaboration for ideas between classmates is acceptable, but duplication of work is not.
3. Use C++ to write this program.
      A) you must design the workflow and write the driver or main program on your own. 
      B) you must design the functions of the methods and classes you need, including the inputs and output of each function.
      C) you can then (and only after the design is complete) use AI to write the individual small functions. For example, using ChatGPT, say: "Write a function in C++ that will take a real number value as US currency and convert it to Singapore currency." Your driver program or other functions can call that AI-written function.
4. Your program will contain multiple .cpp  and .h files. The main program should set up the number of
servers (user input), the time you want to run the load balancer (user input) and generate a
full queue (usually servers * 100).
5. You will need a web server class so you can create the number of web servers requested.
6. You will need a request class (or struct) that holds a request.
7. You will need a queue of type requests. (called requestqueue?)
8. You will need a loadbalancer class that manages the webservers and the request queue. This should be for creating multiple load balancers.
9. You will need to add new requests at random times to simulate new requests after the initial full queue you set up.
10. Dynamically allocate and deallocate web servers to maintain a balance with your requests.
    Goal: Keep queue size between 50 and 80 requests times the number of servers you have. 
     Action: If queue goes below 50*servers, reduce 1 server, wait n clock cycles and check again.
    Action: If queue size goes above 80*servers, add 1 server, wait n clock cycles and check again.
11. Try different numbers as input to understand the capacity of your load balancer configurations.
    These values can be number of requests at random times. Rest between adding/removing servers (n above). Length of time a process takes.
12. All files must be commented with Doxygen using HTML output and loaded to a page on people.tamu.edu. Turn in this link. (having ChatGPT create Doxygen compensation is an excellent use of AI and acceptable in this assignment. Not many people like writing commentation of this type, but it is enjoyable seeing a tool create it for you.)
13. Be able to easily configure your load balancer, like a configuration file, vs having to edit the code. Make sure your output and log file have a summary of actions. (Think about what is important to know, and design an appropriate summary.)
14.  Add an IP range blocker to serve as a firewall or DOS attack prevention mechanism. 
15. Try using color in your output to show different events.
15. Bonus: Add a higher-level load balancer or switch that can sort jobs by type, sending streaming data to one load balancer (and therefore specific servers for that purpose) and processing data to another load balancer (and therefore specific servers for processing data). If everything above works and you choose this option, extra credit will be awarded.
Pre-Deliverable:
Create a design document for your project. Create a flow diagram, UML, or other visual document that shows your design and/or workflow. Then create a text description of this diagram. Output this in HTML/CSS and host it in a folder on people.tamu.edu. Make branding visible in this page. Turn in the link to that folder.

Deliverables:
All deliverables must provide a viable solution to the assigned problem. No attempt will be made to grade non-substantial submissions.
Create documentation for each of your code files in HTML, hosted on people.tamu.edu
Create a log of 10 servers running for 10000 clock cycles
Turn in your git repository link.  
Demonstration of usability and features in your video.
Create a make file and zip it together with all your .cpp and .h files. No executables. Turn in that zip file.
This project is worth 100 points.

Documentation (including pre-deliverable) 30%
Log and successful completion of load balancing 20%
Demonstration, code, and Git usage 50%