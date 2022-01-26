CC=g++

.PHONY:All

All:udp_sever udp_client

udp_client: udp_client.cpp 
	$(CC) -o $@ $^ -std=c++11


udp_sever:udp_sever.cpp
	$(CC) -o $@ $^ -std=c++11 -static

.PHONY:clean

clean:
	rm  -f udp_sever udp_client 
