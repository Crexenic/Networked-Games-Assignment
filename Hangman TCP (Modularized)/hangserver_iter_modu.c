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

// Moved out of local directory.
#include "../hangman.h"
#include "../socketTCP.h"
 
 main () {
  	struct sockaddr client;
 	int sock, fd, client_len;

 	// Create new socket.
 	sock = newServerSocketTCP();

	// Randomize the seed. New word each game from list of words.
 	srand ((int) time ((long *) 0)); 

	// Eternal loop to play game of hangman!
 	while (1) {
 		client_len = sizeof (client);

		// Accept connection. Terminate if not accepted or error.
 		if ((fd = accept (sock, &client, &client_len)) < 0) {
			perror ("accepting connection");
			exit (3);
		}		
		// Play a game of hangman, using outsourced header file.
		puts("Lets play hangman!");
		play_hangman (fd, fd);
 		close (fd);
 	}
 }
