CC=g++

.PHONY:All

All:Tcp_Sever Tcp_Client

Tcp_Client: Tcp_Client.cpp 
	$(CC) -o $@ $^ -std=c++11 -lpthread


Tcp_Sever:Tcp_Sever.cpp
	$(CC) -o $@ $^ -std=c++11 -static -lpthread

.PHONY:clean

clean:
	rm  -f Tcp_Sever Tcp_Client 
