#include <zmq.hpp>
#include <string.h>
#include <unistd.h>
#include  "iostream"
#include "common.hpp"
#include "pthread.h"

using namespace std;

#define NUM_THREADS 5

void *server_fn (void *socket);



int main () {
    int i =0, rc;
    //  Prepare our context and socket
    pthread_t thread[NUM_THREADS];
    char port[25];
    for (i=0; i< NUM_THREADS; i++)
    {
    	void *context = zmq_init(1);
        std::cout << "Server: main.. " ;
        void *socket = (void *)zmq_socket (context, ZMQ_REP);
        assert(socket);
	cout << "Server: main..Creating thread " << i << std::endl;
	sprintf(port, "tcp://*:555%d", i);
    	rc = zmq_bind (socket, port);
        //assert(rc==0);
    	std::cout << "Server: bind error " << rc << std::endl;
    	std::cout << "Server: bind done " << port << std::endl;
	rc = pthread_create(&thread[i], NULL, server_fn, (void *)socket);
	if (rc) 
  	{
		cout << "Error creating thread\n";
	        exit (-1);
	}
	sleep(5); // Added for timing
    }
    for (i=0; i< NUM_THREADS; i++)
    {
    	 pthread_join(thread[i],NULL);
    }


}


void *server_fn (void *threadid)
{
    

   int len =0;
   while (1) { 
	//sleep(20);        
   	void *socket = (void *)threadid;       
   	zmq::message_t request;
   	weather_msg wmsg;
   	wmsg.message_code = 0;
   //  Wait for next request from client
   	zmq_recv (socket, &request, len, 0);
   	if (len > 0) {
		memcpy(&wmsg.message_code, request.data(), sizeof(int));
		std::cout << "Server:data" << wmsg.message_code << std::endl;

  	}	
  	 sleep(1);
   //  Send reply back to client
 	  zmq_send (socket, "Got", 5, 0);
    }  
    return 0;
}


