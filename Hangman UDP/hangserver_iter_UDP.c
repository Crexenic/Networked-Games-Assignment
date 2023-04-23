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
#include "hangmanUDP.h"

// Define default IP and port for server.
#define UDPSERVERADDR "127.0.0.1"
#define UDPSERVERPORT 8068
 
# define LINESIZE 80
 
 main () {
 	int sock;
 	char message[LINESIZE];
 	struct sockaddr_in serverAddress, clientAddress;
 	int clientAddressSize = sizeof(clientAddress);
 	
 	// Configuring host.
 	puts("Configuring the host.....");
 	
 	 // Create the socket for the server. Throw error if not.
 	sock = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);
 	if (sock < 0) {
 		perror ("Error creating server socket");
 		exit (1);
 	}
 	puts("Server socket created.....");
 	
 	// Zero out server address.
 	//memset((char *) &serverAddress, 0, sizeof(serverAddress));
 	
 	serverAddress.sin_family = AF_INET;
 	serverAddress.sin_port = htons(UDPSERVERPORT);
 	serverAddress.sin_addr.s_addr = inet_addr(UDPSERVERADDR);

 	// Bind server socket. Terminate server if not created.
 	if (bind(sock, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
 		perror ("binding socket failed");
	 	exit (2);
 	}
 	puts("Server socket bound.....");

	// Randomize the seed. New word each game from list of words.
 	srand ((int) time ((long *) 0)); 

	// Acknowlegdge waiting for potential clients.
	puts ("Awaiting connection from clients.....");

	// Eternal loop to play game of hangman!
 	while (1) {
 	
 		// Receive first datagram from client. Then proceed.
		if (recvfrom(sock, message, sizeof(message), 0, (struct sockaddr *) &clientAddress, &clientAddressSize) < 0) {
			perror ("error receiving response from client");
			break;
		}
	printf("Received following from client: %s \n", message);

		// Play a game of hangman, using outsourced header file.
		puts("Lets play hangman!");
		playHangmanUDP(sock, sock, clientAddress, clientAddressSize);
		
		// Announce game of hangman is concluded.
		puts("game over");
		
		// Close connection.
 		close (sock);
 	}
 }
