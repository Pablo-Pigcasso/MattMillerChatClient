/*
 * MattMillerChatClient
 *
 *  Created on: Jan 23, 2019
 *      Author: Matthew
 *
 *The purpose of this project is to connect to pilot.westmont.edu as a client.
 *After connecting with the server, the chat client will send and receive messages
 *from other users connected to the same port. New messages will be grabbed upon
 *pressing enter. New messages will be sent after being typed and pressing enter.
 *
 *  Tanner Leslie: helped me get my IDE working (using Eclipse 2018-12), my compiler
 *  was not cooperating with Eclipse and Tanner helped me trouble shoot it.
 *
 *  John Rodkey: helped me troubleshoot an "indirection requires pointer" error which
 *  persisted despite not actually being a problem. Issue was resolved via a power cycle
 *  and coping the code over to a new project.
 *
 *
 */


#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(){
/* The first part of the code here is used to connect to the port, family, and socket
 * of the server. It also checks the status of the server.
 */
	struct sockaddr_in server;
	int status;
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
	server.sin_port = htons(49153);
	inet_pton(AF_INET, "10.115.20.250", &server.sin_addr);
	status=connect(sockfd, (const struct sockaddr *) &server, sizeof(server));
	printf("Connected, status=%d\n",status);
	connect(sockfd, (const struct sockaddr *) &server, sizeof(server));



}
