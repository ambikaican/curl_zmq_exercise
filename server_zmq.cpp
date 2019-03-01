#include <zmq.hpp>
#include <string.h>
#include <unistd.h>
#include  "iostream"
#include "pthread.h"
#include "server_hdr.hpp"

using namespace std;

#define NUM_THREADS 5

void *server_fn (void *socket);



int main () {
    int i =0, rc;
    pthread_t thread[NUM_THREADS];
    char port[25];
    for (i=0; i< NUM_THREADS; i++)
    {
    	//  Prepare our context and socket
    	void *context = zmq_init(1);
        void *socket = (void *)zmq_socket (context, ZMQ_REP);
        assert(socket);
	cout << "Server: main..Creating thread " << i << std::endl;
	sprintf(port, "tcp://*:555%d", i);
    	rc = zmq_bind (socket, port);
        assert(rc==0);
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
    

   int len = sizeof(weather_msg_t);
   while (1) { 
	//sleep(20);        
   	void *socket = (void *)threadid;
	std::cout << "server socket" << socket << std::endl;
        	
   	zmq_msg_t request;
   	weather_msg wmsg;
	char cname[50], zcode[10];
	char w_msg[100]; //TODO
   	wmsg.message_code = 0;
	   //  Wait for next request from client
   	int rc = zmq_recv (socket, &w_msg, len, 0);
		//std::cout << "server return" << request << std::endl;
   	if (rc > 0) {
		sscanf((char *)w_msg, "%d %d %f %f %s %s\n", 
			 &wmsg.message_code, 
	   		 &wmsg.city_id, &wmsg.lon, &wmsg.lat, 
			 cname, zcode); 

	    std::cout << "server recieved Message " << \
	    wmsg.message_code  \
	    <<  ".." << cname << \
	    zcode << "…" << std::endl;
    		switch(wmsg.message_code) {
	    	   case wmsg.GET_BY_CITY_ID:
			wmsg.getCurrentTemp(wmsg.city_id);
			break;
	  	   case wmsg.GET_BY_LON_LAT:
			wmsg.getCurrentTemp(wmsg.lon, wmsg.lat);
			break;
	 	   case wmsg.GET_BY_CITY_NAME:
			wmsg.city_name.assign(cname);
			wmsg.getCurrentTemp(wmsg.city_name);
			break;
	           case wmsg.GET_BY_ZIP_CODE:
			wmsg.getCurrentTemp(cname);
			break;
		}
	}
  	sleep(1);
 	zmq_send (socket, "Got", 5, 0);
    }  
    return 0;
}


