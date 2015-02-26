//
//  SocketClient.cpp
//  Project 1
//
//  Created by Eduardo Almeida on 27/11/14.
//  Copyright (c) 2014 Eduardo Almeida. All rights reserved.
//

#include "SocketClient.h"


#include <stdio.h>
#include <string.h>	// for memcpy()...
#include <string>
#include <stdlib.h>	// for atoi()...
#include <ctype.h>	// for tolower()...
#include <ctype.h>

#define perror(s)	\
	fprintf(stderr,"\n%s %d\n", s, WSAGetLastError())

char nclient[64];

SocketClient::SocketClient(std::string host, int port) {
	WORD wVersionRequested = MAKEWORD(1, 1);	// request Winsock 1.1
	WSADATA wsaData;
	SOCKET sock;
	struct sockaddr_in server;
	struct hostent *hp;

	// Initialize Winsockets
	if (WSAStartup(wVersionRequested, &wsaData) == 0)	// allways needed
		printf("\nVersion allowed: %d.%d\n",
		LOBYTE(wsaData.wHighVersion), HIBYTE(wsaData.wHighVersion));
	else
	{
		fprintf(stderr, "\n Wrong version\n");
		WSACleanup();
		exit(1);
	}

	/* Create socket */
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		perror("Opening stream socket");
		exit(1);
	}
	setbuf(stdout, NULL);	// do not buffer output - DEBUGING!!	

	server.sin_family = AF_INET;
	hp = gethostbyname(host.c_str());
	if (hp == NULL)
	{
		perror("Trying to get host by name");
		exit(2);
	}
	memcpy((char *)&server.sin_addr, (char *)hp->h_addr, hp->h_length);
	server.sin_port = htons((short) port );

	if (connect(sock, (struct sockaddr *)&server, sizeof server) == SOCKET_ERROR)
	{
		perror("Connecting stream socket");
		exit(1);
	}

	_sockfd = sock;
   
}

void SocketClient::write(std::string data) {
    if (send(_sockfd, data.c_str(), strlen(data.c_str()) + 1 ,0) == SOCKET_ERROR)
		perror("Writing on stream socket");
}

std::string SocketClient::read() {
	std::string bufstr, bufclean;

    char *buf = (char *) malloc(4096 * sizeof(char));
    
    recv(_sockfd, buf, 4096,0);
	
	bufstr = buf;
	bufclean = bufstr.substr(0, bufstr.find(".", 0));
	std::cout << "[READ Debug]: " << bufclean << std::endl;

	return bufclean;
}

SocketClient::~SocketClient() {
	if (closesocket(_sockfd) == SOCKET_ERROR)
		perror("Closing message socket");
}
