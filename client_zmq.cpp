#include <zmq.hpp>
#include <string>
#include <iostream>
#include "common.hpp"



#define INITIAL_SETTING  wmsg.city_id = 0; \
		wmsg.lon = 0.0; wmsg.lat = 0.0; \
		wmsg.city_name.assign(" "); \
		memset(&wmsg.zip_code, '\0', 5)

#define CHECK_ARGC(X) if (argc != X) \
	{ std::cout << "Usage<>\n" \
  "./client 1 <cityid>\n" \
 		"       2 <long>  <lat>\n" \
  		"       3  <city name>\n" \
  		"       4 <zip code>\n"; return -1;}

/* 
 * Returns the City name, temperature and timestamp as output
 * argv[1] - enum message
 * ./client.out 1 <cityid> 
 * 		2 <long>  <lat>
 * 		3  <city name>
 * 		4 <zip code> 
 *
 */
int main (int argc, char *argv[])
{
    //  Prepare our context and socket
    void *context = zmq_init(1);
    int rc = 0, port_num;
    char port[25];
    std::cout << "Client: main.. " ;
    void *socket = (void *)zmq_socket (context, ZMQ_REQ);
    assert(socket);
    weather_msg wmsg;
    int request_size = sizeof(weather_msg_t);
    zmq::message_t request(request_size);
    char w_msg[100]; //TODO
    //memset(&wmsg, '0', sizeof(weather_msg_t));  
    port_num = 5550 + (rand() % 5); 
    sprintf(port, "tcp://localhost:%d", port_num);
    std::cout << "Connecting to server…" << port_num << std::endl;
    rc = zmq_connect (socket, port);
    assert(rc==0);
    
    wmsg.message_code = (argc >= 2) ? atoi(argv[1]): 1;
    INITIAL_SETTING;
    std::cout << "Client: Setting " << \
	    wmsg.message_code << \
	    wmsg.city_id << \
	    wmsg.lon << "…" << std::endl;

    switch(wmsg.message_code) {
	    case wmsg.GET_BY_CITY_ID:
		CHECK_ARGC(3);
		wmsg.city_id = atoi(argv[2]);
		break;
	    case wmsg.GET_BY_LON_LAT:
		CHECK_ARGC(4);
		wmsg.lon = atof(argv[2]);
		wmsg.lat = atof(argv[3]);
		break;
	    case wmsg.GET_BY_CITY_NAME:
		CHECK_ARGC(3);
		wmsg.city_name.assign(argv[2]);
		break;
	    case wmsg.GET_BY_ZIP_CODE:
		CHECK_ARGC(3);
		memcpy(wmsg.zip_code, argv[2], 6);
		break;
    }
    snprintf(w_msg, request_size, "%d %d %f %f %s %s\n", 
	    wmsg.message_code, 
	    wmsg.city_id, wmsg.lon, wmsg.lat, wmsg.city_name.c_str(),
	    	wmsg.zip_code);
    std::cout << "Client: Sending Message " << \
	    wmsg.message_code << "\n" << \
	    wmsg.city_name.c_str() << "\n"  << \
	    wmsg.zip_code << "…" << std::endl;
    rc = zmq_send (socket, &w_msg, request_size, 0);
    char reply[5];
    zmq_recv (socket, reply, 5, 0);
    std::cout << "Client: Received Temp " << reply << std::endl;
    return 0;
}
