/* Hangclient.c - Client for hangman server.  */

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
 

 int main (int argc, char * argv [])
 {
 	struct addrinfo hints, *server; /* Server's address  assembled here */
 	
 	int sock, count, r;
 	 char i_line[LINESIZE];
 	 char o_line[LINESIZE];
 	char * server_name;

 	/* Get server name from the command line.  If none, use 'localhost' 

 	server_name = (argc = 1)?  argv [1]: "localhost";
 	*/
 	/*configuring the server address*/
 	
 	printf("Configuring the server.....,\n");
 	memset(&hints, 0, sizeof(struct addrinfo) );
 	
 	hints.ai_family = AF_INET;
 	hints.ai_socktype = SOCK_STREAM;
 	
 	r=getaddrinfo(0, "8080", &hints, &server);
 	
 	if(r!=0)
 	{
 		perror("failed");
 		exit(1);
 	} 	
 	puts("server configured,\n");

 	/* Create the socket */
 	/*create the socket for the server*/
 	
 	printf("assign client socket");

 	sock = socket (server->ai_family, server->ai_socktype,server->ai_protocol);//0 or IPPROTO_TCP
 	if (sock ==-1) { //This error checking is the code Stevens wraps in his Socket Function etc
 		perror ("Erro creating server socket");
 		exit (1);
 	}
 	puts("Client socket created");
 	/*............................ */
	
 	

 	/* Set up the server's socket address, then connect */

 	hints.ai_family = AF_INET;
 	hints.ai_socktype = SOCK_STREAM;
 	
 	r=getaddrinfo(0, "8080", &hints, &server);
 	
 	if(r!=0)
 	{
 		perror("failed");
 		exit(1);
 	} 	
 	puts("connecting .....,\n");
 	/*server.sin_port = htons (HANGMAN_TCP_PORT);*/

 	r = connect(sock, server->ai_addr, server->ai_addrlen); 
 	freeaddrinfo(server);
 	
 	
 	/*OK connected to the server.  
 Take a line from the server and show it, take a line and send the user input to the server. 
 Repeat until the server terminates the connection. */

 	printf ("Connected to server% s \ n", server_name);
 	while ((count = read (sock, i_line, LINESIZE)) > 0) {
 		write (1, i_line, count);
 		count = read (0, o_line, LINESIZE);//0 = STDIN
 		write (sock, o_line, count);
 		};
 	
}
