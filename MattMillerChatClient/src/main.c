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
	struct sockaddr_in rodServer; //rodServer is the struct for the server I'm connecting to
	int status;
	int descriptor;
	char *name = malloc(80);//allocating memory
	bzero(name,sizeof(name));
	//bcopy(src,dst,nchars);
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	rodServer.sin_family = AF_INET;
	rodServer.sin_port = htons(49153);//49153 is at the beginning of the dynamic/private range of ports. It is a TCP port.
	inet_pton(AF_INET, "10.115.20.250", &rodServer.sin_addr);
	status=connect(sockfd, (const struct sockaddr *) &rodServer, sizeof(rodServer));
	printf("Connected, status=%d\n",status);

	//opening the socket
	descriptor = socket(PF_INET,SOCK_STREAM, PF_INET);

}
