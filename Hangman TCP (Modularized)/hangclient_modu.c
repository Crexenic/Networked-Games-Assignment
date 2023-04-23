#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

# define LINESIZE 80
 
 int main (int argc, char * argv []) {
 
 	// Server's address instantiate.
 	struct addrinfo hints, *server; 
 	
 	// Create new int for socket, size of buffer, and remaining hints value.
 	int sock, count, r;
 	
 	// Input / output buffer declaration.
 	char i_line[LINESIZE];
 	char o_line[LINESIZE];
 	
 	//Get server name from the command line. If none, use 'localhost'. 
 	char * server_name = (argc = 1)?  argv [1]: "localhost";
 	
 	// Configuring the server address.
 	printf("Configuring server.....\n");
 	memset(&hints, 0, sizeof(struct addrinfo) );
 	
 	hints.ai_family = AF_INET;
 	hints.ai_socktype = SOCK_STREAM;
 	
 	r = getaddrinfo(0, "8080", &hints, &server);
 	if (r != 0) {
 		perror("failed");
 		exit(1);
 	} 	

 	/* Create the socket */
 	sock = socket (server->ai_family, server->ai_socktype,server->ai_protocol);
 	
 	// If cannot create socket successfully, terminate.
 	if (sock == -1) { 
 		perror ("Error creating server socket");
 		exit (1);
 	}
 	puts("Client socket created.....\n");

	// Attempt connection to server.
 	r = connect(sock, server->ai_addr, server->ai_addrlen); 
 	freeaddrinfo(server);
 	
 	// Successful connection to server.  
 	printf ("Connected to server% s \ n", server_name);
 	
 	// Take a line from the server and show it.
 	// Take a line and send the user input to the server. 
 	// Repeat until the server terminates the connection.
 	while ((count = read (sock, i_line, LINESIZE)) > 0) {
 		write (1, i_line, count);
 		// 0 = Standard input, no issues.
 		count = read (0, o_line, LINESIZE);
 		
 		// Send client response (inputted letter) to server.
 		write (sock, o_line, count);
 	};
}
