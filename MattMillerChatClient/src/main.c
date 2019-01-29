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
 *  perror manual and example: https://www.tutorialspoint.com/c_standard_library/c_function_perror.htm
 *
 *	printf with variable example and help: https://stackoverflow.com/questions/16675287/printf-a-variable-in-c
 *
 *	scanf help: https://en.wikibooks.org/wiki/C_Programming/Simple_input_and_output
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
	char name[20]; //allocating memory for screen name
	char message[80], serverReply[500]; //allocating memory for message


	//Opening the socket
	descriptor = socket(PF_INET,SOCK_STREAM, 0); //opens the socket
	if(descriptor == -1){
		perror("Socket not created successfully");
		return 1;
	}
	puts("Socket Created\n");

	//Connecting to the server
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET; //convention
	server.sin_port = htons( 49153 ); //49153 is at the beginning of the dynamic/private range of ports. It is a TCP port.
	inet_pton(AF_INET, "10.115.20.250", &server.sin_addr);
	status=connect(sockfd, (const struct sockaddr *) &server, sizeof(server));
	if(status < 0){
		perror("Connection failed. Error");
		return 1;
	}
	puts("Connected\n");
	sleep(1);

	//Ask for username and then pass it to the server
	puts("Enter Username:");
	fgets(name, sizeof(name), stdin);
	send(sockfd, name, strlen(name), 0);
	sleep(3);

	//Staying connected to the server until done.
	while(1){
		printf("Enter message or command: ");
		fgets(message, sizeof(message), stdin);
		sleep(1);
		if(read(sockfd, serverReply, sizeof(serverReply)) < 0){
			puts("Failed to get new messages\n");
			return 1;
		}
		sleep(1);
		puts(serverReply);
		sleep(1);

		//else send it
		if(send(sockfd, message, strlen(message),0)<0){
			puts("Failed to send message\n");
			return 1;
		}
		sleep(1);
		memset(serverReply, 0, sizeof(serverReply));
		memset(message, 0, sizeof(message));
		sleep(1);
	}

	close(sockfd);
	return 0;

}
