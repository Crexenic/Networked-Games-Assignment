 /* Network server for hangman game */
 /* File: hangserver.c */

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
 


 extern time_t time ();


 # define NUM_OF_WORDS (sizeof (word) / sizeof (word [0]))
 # define MAXLEN 80 /* Maximum size in the world of Any string */
 /*# define HANGMAN_TCP_PORT 1066*/

 main ()
 {
 	int sock, fd, client_len, r;
 	struct addrinfo hints, *server;
 	struct sockaddr client;
 	
 	
 	/*configuring the host*/
 	
 	printf("Configuring the host.....,\n");
 	memset(&hints, 0, sizeof(struct addrinfo) );
 	
 	hints.ai_family = AF_INET;
 	hints.ai_socktype = SOCK_STREAM;
 	
 	r=getaddrinfo(0, "8080", &hints, &server);
 	
 	if(r!=0)
 	{
 		perror("failed");
 		exit(1);
 	} 	
 	puts("host configured,\n");

 	srand ((int) time ((long *) 0)); /* randomize the seed */
 	
 	/*create the socket for the server*/
 	
 	printf("assign a socket");

 	sock = socket (server->ai_family, server->ai_socktype,server->ai_protocol);//0 or IPPROTO_TCP
 	if (sock ==-1) { //This error checking is the code Stevens wraps in his Socket Function etc
 		perror ("Erro creating server socket");
 		exit (1);
 	}
 	puts("Server socket created");

 	

 	if (bind(sock, server->ai_addr,server->ai_addrlen) <0) {
 		perror ("binding socket");
	 	exit (2);
 	}
	puts("Server socket is listening for incoming requests from Clients");
	puts("Lets play hangman!");
 	listen (sock, 5);
	fd_set current_sockets, ready_sockets;
	//initialize
	FD_ZERO(&current_sockets);
	FD_SET(sock, &current_sockets);
	
 	while (1) {
 		ready_sockets = current_sockets;
 		client_len = sizeof (client);
 		if (select(FD_SETSIZE, &ready_sockets, NULL, NULL, NULL) <0){
 			perror ("error");
 			exit (3);
 		}
 		
 		
 		//Select code starts here
 		//Loop for handling multiple clients
 		for(int i=0; i< FD_SETSIZE; i++){
 			if(FD_ISSET(i, &ready_sockets)){
 				//If for new connections
 				if(i== sock){
 					//int for holding client bits
 					int client_socket;
 					puts("accepting new connection");
 					if ((client_socket = accept (sock,  &client, &client_len)) <0) {
 						perror ("accepting connection");
 						exit (3);
 					}
 					//Will store the client in the file descriptor set
 					FD_SET(client_socket, &current_sockets);
 					//Message to display when client connects
 					puts("start");
 					//Will play hangman with current client, won't connect with another client until hangman complete, doesn't allow for concurrency unfortunately
 					play_hangman(client_socket, client_socket);
 					
 				}
 				//If for ongoing connections
 				else{
 					//Clears the client from the file descriptor set
 					FD_CLR(i, &current_sockets);
 					//Message to display when client disconnects
 					puts("end");
 				}
 				//Once a second client has connected, the server will run into an error
 				
 			}
 		}
 		
 		close (fd);
 	}
 }

 
