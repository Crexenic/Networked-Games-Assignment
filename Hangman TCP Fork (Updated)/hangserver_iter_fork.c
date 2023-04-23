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
 #include <sys/wait.h> // included to avoid warnings for using waitpid
 #include "hangman.h"
 


 extern time_t time ();


 # define NUM_OF_WORDS (sizeof (word) / sizeof (word [0]))
 # define MAXLEN 80 /* Maximum size in the world of Any string */
 /*# define HANGMAN_TCP_PORT 1066*/

 int main ()
 {
 	int sock, fd, client_len, r;
 	struct addrinfo hints, *server;
 	struct sockaddr client;
 	
 	/* added fork variable*/
 	pid_t forkpid;
	// catch_sigchld declaration for the later signal function call
	void catch_sigchld(int signum);
 	/*configuring the host*/
 	
 	printf("Configuring the host.....,\n");
 	memset(&hints, 0, sizeof(struct addrinfo) );
 	
 	hints.ai_family = AF_INET; // set the address family to IPv4
 	hints.ai_socktype = SOCK_STREAM; // set the socket type to sock_stream for TCP
 	
 	r=getaddrinfo(0, "8080", &hints, &server);
 	
 	if(r!=0)
 	{
 		perror("failed");
 		exit(1);
 	} 	
 	puts("host configured,\n");

 	srand ((int) time ((long *) 0)); /* randomize the seed */
 	
 	/*create the socket for the server*/
 	
 	printf("assign a socket\n");

 	sock = socket (server->ai_family, server->ai_socktype,server->ai_protocol);//0 or IPPROTO_TCP
 	
 	
 	if (sock ==-1) { //This error checking is the code Stevens wraps in his Socket Function etc
 		perror ("Error creating server socket");
 		exit (1);
 	}
 	puts("Server socket created\n");

 	

 	if (bind(sock, server->ai_addr,server->ai_addrlen) <0) {
 		perror ("binding socket");
	 	exit (2);
 	}
	puts("Server socket is listening for incoming requests from Clients\n");
	puts("Lets play hangman!\n");
 	listen (sock, 5);

	// signal function
	signal(SIGCHLD, catch_sigchld); // signal function is sent to the parent process, and is used to handle zombies by deleting them

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
	
	while((process_id = waitpid(-1, &status, WNOHANG)) > 0){
		printf("%d n", process_id);
	}
}
 
