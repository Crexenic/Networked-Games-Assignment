#include <sys/socket.h>

 // ---------------- Socket TCP Functions ---------------------

// Function to create the server socket and bind it. Return sock.
int newServerSocketTCP() {
		
	struct addrinfo hints, *server;
	int sock, r;
	
	memset(&hints, 0, sizeof(struct addrinfo));
		
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	
	r = getaddrinfo(0, "8080", &hints, &server);
 	if (r != 0) {
 		perror("failed");
 		exit(1);
 	} 	
	
	// Create the socket for the server.
 	if ((sock = socket (server->ai_family, server->ai_socktype, server->ai_protocol)) < 0) {
 		perror ("Error creating server socket");
 		exit (1);
 	}
	
	// Bind socket. Throw error if not created.
 	if (bind(sock, server -> ai_addr, server -> ai_addrlen) < 0) {
 		perror ("binding socket");
	 	exit (2);
 	}
 	
 	// Await client connection and response.
 	listen (sock, 5);
	
	//close(sock);
	
	// Return created and bound socket.
	return sock;
}
