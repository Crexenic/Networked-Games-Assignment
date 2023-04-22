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
 	
 	/* added fork variable*/
 	pid_t forkpid;
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

 	while (1) {
 	
 		client_len = sizeof (client);
 		
 		if ((fd = accept (sock,  &client, &client_len)) <0) {
 			perror ("accepting connection");
 			exit (3);
 		}
 		
 		//fork section
 		if((forkpid = fork())==0){
 			close(sock);
 			play_hangman (fd, fd);
 			puts("dead");
 			exit(0);
 		}
 		close (fd);
 	}
 }

void catch_sigchld(int signum){
	int process_id, status;
	
	while((process_id = waitpid(-1 &status, WNOHANG)) > 0){
		printf("&d n", process_id);
	}
}
 
