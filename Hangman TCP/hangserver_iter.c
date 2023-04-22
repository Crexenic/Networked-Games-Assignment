#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <syslog.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include "hangman.h"
 
 main () {
 	int sock, fd, client_len, r;
 	struct addrinfo hints, *server;
 	struct sockaddr client;
 	
 	// Configuring host.
 	printf("Configuring the host.....\n");
 	memset(&hints, 0, sizeof(struct addrinfo) );
 	
 	hints.ai_family = AF_INET;
 	hints.ai_socktype = SOCK_STREAM;
 	
 	r = getaddrinfo(0, "8080", &hints, &server);
 	if (r != 0) {
 		perror("failed");
 		exit(1);
 	} 	

	// Randomize the seed. New word each game from list of words.
 	srand ((int) time ((long *) 0)); 
 	
 	// Create the socket for the server.
 	sock = socket (server->ai_family, server->ai_socktype,server->ai_protocol);
 	
 	// Throw error is socket is not created.
 	if (sock == -1) { 
 		perror ("Error creating server socket");
 		exit (1);
 	}
 	puts("Server socket created.....\n");

	// Bind socket. Terminate server if not created.
 	if (bind(sock, server->ai_addr,server->ai_addrlen) <0) {
 		perror ("binding socket");
	 	exit (2);
 	}
	puts("Server is listening for incoming requests from clients");
	
	// Await client connection and response.
 	listen (sock, 5);

	// Eternal loop to play game of hangman!
 	while (1) {
 		client_len = sizeof (client);

		// Create listening socket. Terminate if not accepted or error.
 		if ((fd  = accept (sock, &client, &client_len)) < 0) {
			perror ("accepting connection");
			exit (3);
		}		
			
		// Play a game of hangman, using outsourced header file.
		puts("Lets play hangman!");
		play_hangman (fd, fd);
 		close (fd);
 	}
 }
