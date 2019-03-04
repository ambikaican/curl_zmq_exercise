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
    void *context = zmq_init(1);
    for (i=0; i< NUM_THREADS; i++)
    {
    	//  Prepare our context and socket
        void *socket = (void *)zmq_socket (context, ZMQ_REP);
        assert(socket);
	sprintf(port, "tcp://*:555%d", i);
	cout << "Server: main..Creating thread " << i \
		<< " port "  << port << std::endl;
    	rc = zmq_bind (socket, port);
        assert(rc==0);
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
   	void *socket = (void *)threadid;
   	zmq_msg_t request;
   	weather_msg wmsg;
	char cname[50], zcode[10];
	char w_msg[100]; //TODO
	memset(w_msg, '\0', 100);
	std::string output_buf;
	char *output;
   	wmsg.message_code = 0;
	   //  Wait for next request from client
   	int rc = zmq_recv (socket, &w_msg, len, 0);
   	if (rc > 0) {
	    sscanf((char *)w_msg, "%d %d %f %f %s %s\n", 
			 &wmsg.message_code, 
	   		 &wmsg.city_id, &wmsg.lon, &wmsg.lat, 
			 cname, zcode);
	       // Either cname or zcode is empty	
	    std::cout << "server recieved Message code " << wmsg.message_code
		    << std::endl;
    		switch(wmsg.message_code) {
	    	   case wmsg.GET_BY_CITY_ID:
			wmsg.getCurrentTemp(wmsg.city_id, &output_buf);
			break;
	  	   case wmsg.GET_BY_LON_LAT:
			wmsg.getCurrentTemp(wmsg.lon, wmsg.lat, &output_buf);
			break;
	 	   case wmsg.GET_BY_CITY_NAME:
			wmsg.city_name.assign(cname);
			wmsg.getCurrentTemp(wmsg.city_name, &output_buf);
			break;
	           case wmsg.GET_BY_ZIP_CODE:
			wmsg.getCurrentTemp(cname, &output_buf);
			break;
		}
	}
  	sleep(1);
	char send_buf[100];
	memset(send_buf, '\0', 100);
	strcpy(send_buf, output_buf.c_str());
 	zmq_send (socket, send_buf, strlen(send_buf), 0);
	std::cout << "server: output: " << send_buf << std::endl;
   }  
   std::cout << "server: RETURN;\n";
    return 0;
}


