CC      = g++
CFLAGS  = -I/usr/include -I. -I/usr/include/jsoncpp -I/root/curl/include 
LDFLAGS1 = -lzmq
LDFLAGS2 = -lpthread -lcurl -ljsoncpp
all: server client

client: client_zmq.o
	$(CC) -o $@ $^  $(LDFLAGS1) 

client_zmq.o: client_zmq.cpp
	$(CC) -c $(CFLAGS) $<

server: curl_detail.o server_zmq.o
	$(CC) -o $@ $^  $(LDFLAGS1) $(LDFLAGS2)

server_zmq.o: server_zmq.cpp 
	$(CC) -c $(CFLAGS) $<

curl_detail.o: curl_detail.cpp 
	$(CC) -c $(CFLAGS) $<


.PHONY: clean 

clean:
	rm *.o
	rm server 
	rm client


