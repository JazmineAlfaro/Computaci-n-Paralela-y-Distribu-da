/* Player code in C++ */

//g++ player.cpp -o player -std=c++11 -lpthread

/*
rules:
send 1 to confirm connection and play
send 2 position (1-9) to put your play
*/


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <thread>

int SocketFD;
bool end = false;
char buffer[256];
int port = 45506;

void send_msg(){
	char msg[256];
	int n;
	do{
		std::cin.getline(msg, 255);
		n = write(SocketFD,msg,255); 
		
		msg[n] = '\0';
		if (strcmp(msg, "8") == 0) end = true;
	} while(!end);
}
	
void rcv_msg(){
	int n;
	do{	
		bzero(buffer,256);
		n = read(SocketFD,buffer,255);
		if (n < 0) perror("ERROR reading from socket");
		buffer[n] = '\0';
		//printf("Here is the message: [%s]\n",buffer);
		printf("%s\n",buffer);
		n = write(SocketFD,"Ok. Message recieved.",21); 
	} while(!end);
}
		
int main(void){
	struct sockaddr_in stSockAddr;
	int Res;
	SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	int n;
	char msg[256];
	
	if (-1 == SocketFD)
	{
		perror("cannot create socket");
		exit(EXIT_FAILURE);
	}
	
	memset(&stSockAddr, 0, sizeof(struct sockaddr_in));
	
	stSockAddr.sin_family = AF_INET;
	stSockAddr.sin_port = htons(port); //port
	Res = inet_pton(AF_INET, "127.0.1.1", &stSockAddr.sin_addr);
	
	if (0 > Res)
	{
		perror("error: first parameter is not a valid address family");
		close(SocketFD);
		exit(EXIT_FAILURE);
	}
	else if (0 == Res)
	{
		perror("char string (second parameter does not contain valid ipaddress");
		close(SocketFD);
		exit(EXIT_FAILURE);
	}
	
	int cnct = connect(SocketFD, (const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in));
	if (-1 == cnct)
	{
		perror("connect failed");
		close(SocketFD);
		exit(EXIT_FAILURE);
	}
	
	std::thread t1(send_msg);
	std::thread t2(rcv_msg);
	
	t1.detach();
	t2.detach();
	
	rcv_msg(); //confirming disconnection
	shutdown(SocketFD, SHUT_RDWR);
	
	close(SocketFD);
	
	return 0;
}
