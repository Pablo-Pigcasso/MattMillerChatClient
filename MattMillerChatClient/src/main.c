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
#include <arpa/inet.h> //inet and others
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h> //sockets
#include <unistd.h> //write
#include <errno.h> //allows me to use errors
#include <string.h> //gives length of strings

int main(){
/* The first part of the code here is used to connect to the port, family, and socket
 * of the server. It also checks the status of the server.
 */
	//initial connection with the server
	struct sockaddr_in server; //rodServer is the struct for the server I'm connecting to
	int status;
	int descriptor;
	char name[7]; //allocating memory for screen name
	char message[80]; //allocating memory for message
//	char *name = malloc(80);
//	bzero(name,sizeof(name));
//	bcopy(src,dst,nchars);

	//Opening the socket
	descriptor = socket(PF_INET,SOCK_STREAM, 0); //opens the socket
	if(descriptor == -1){
		printf("Socket not created successfully");
	}
	puts("Socket Created\n");

	//Connecting to the server
	int sockFileDesc = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET; //convention
	server.sin_port = htons( 49153 ); //49153 is at the beginning of the dynamic/private range of ports. It is a TCP port.
	inet_pton(AF_INET, "10.115.20.250", &server.sin_addr);
	status=connect(sockFileDesc, (const struct sockaddr *) &server, sizeof(server));
	if(status < 0){
		perror("Connection failed. Error");
		return 1;
	}
	puts("Connected\n");


	//Staying connected to the server until done.
	/*
	 * while(1){
		printf("Enter Message : ");
		scanf("%s", message);
	}
	*/
}
