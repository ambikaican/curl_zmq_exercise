g++ client_zmq.cpp -o client.out -lzmq
g++ server_zmq.cpp -o server.out -lzmq -I/usr/include  -lpthread
g++ curl_detail.cpp -o curl.out -lcurl
