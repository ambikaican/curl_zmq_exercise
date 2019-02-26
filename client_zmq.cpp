#include <zmq.hpp>
#include <string>
#include <iostream>
#include "common.hpp"


int main (int argc, char *argv[])
{
    //  Prepare our context and socket
    void *context = zmq_init(1);
    int rc = 0;
    char port[25];
    std::cout << "Server: main.. " ;
    void *socket = (void *)zmq_socket (context, ZMQ_REQ);
    assert(socket);
    weather_msg wmsg;
    wmsg.message_code = (argc == 3) ? atoi(argv[2]): 1;

    std::cout << "Connecting to hello world server…" << std::endl;
    sprintf(port, "tcp://localhost:%d", (argc > 2) ? atoi(argv[1]): 5550);
    rc = zmq_connect (socket, port);
    assert(rc==0);
    std::cout << "Client: Sending Message " << \
	    wmsg.message_code << "…" << std::endl;
    rc = zmq_send (socket, &wmsg.message_code, sizeof(int), 0);
    //std::cout << "Client:" << rc << std::endl;
    //assert(rc==0);

    //  Get the reply.
    char reply[5];
    zmq_recv (socket, reply, 5, 0);
    std::cout << "Client: Received Temp ";
    return 0;
}
