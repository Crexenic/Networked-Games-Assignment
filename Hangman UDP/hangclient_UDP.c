#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

// Define default IP and port for server.
#define UDPSERVERADDR "127.0.0.1"
#define UDPSERVERPORT 8068
 
# define LINESIZE 80
 
 int main (int argc, char * argv []) {
 
 	// Server's address instantiate.
 	struct sockaddr_in serverAddress;
 	int serverAddressSize = sizeof(serverAddress);
 	
 	// New int for socket, size of buffer, and remaining hints value.
 	int sock, count, r, recieveTest;
 	
 	// Input / output buffer declaration.
 	char i_line[LINESIZE];
 	char o_line[LINESIZE];
 	
 	// Create the client socket. If cannot create socket, terminate.
 	// Instead of SOCK STREAM and IPPROTO_TCP, use connection-less sets.
 	sock = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);
 	
 	if (sock < 0) {
 		perror ("Error creating UDP socket");
 		exit (1);
 	}
 	puts("UDP Client socket created.....");
 	
 	// Configuring the server address. Zero out first.
 	puts("Configuring server.....");
 	//memset((char *) &serverAddress, 0, sizeof(serverAddress));
 	serverAddress.sin_family = AF_INET;
 	serverAddress.sin_port = htons(UDPSERVERPORT);
 	serverAddress.sin_addr.s_addr = inet_addr(UDPSERVERADDR);
 	
 	puts("Server address configured.....");
 	
 	// Send an initial message to the server.
 	puts ("Enter any message to begin game of hangman");
 	gets (i_line);
 	if (sendto (sock, i_line, strlen(i_line), 0, (struct sockaddr *) &serverAddress, serverAddressSize) < 0) {
 		perror ("Error sending initiating message");
 		exit (1);
 	}
 	puts ("Successfully sent initial message.....");
 	
 	// Infinite game loop.
 	while (1) {
 		// Check if received letter valid, throw error if not.
 		if (recieveTest = recvfrom (sock, o_line, LINESIZE, 0,  (struct sockaddr *) &serverAddress, &serverAddressSize) < 0) {
 		 	perror ("Error receiving server response");
 			break;
 		}
 		
 		// Display the word progress and lives.
 		printf("%s \n", o_line);
 		
 		// If game still going, send next letter to server.
 		gets (i_line);
 		sendto (sock, i_line, strlen(i_line), 0,  (struct sockaddr *) &serverAddress, serverAddressSize);
 		
 	}
 	
 	// Close connection.
 	close(sock);
 	exit(0);
}
