 extern time_t time ();
 int maxlives = 12;
 char *word [] = {
 # include "words"
 };
 # define NUM_OF_WORDS (sizeof (word) / sizeof (word [0]))
 # define MAXLEN 80 // Max size of string.
#define UDPCLIENTPORT 8068

 // ---------------- Play Hangman (UDP Version) ---------------------
playHangmanUDP (int in, int out, struct sockaddr_in addr, int addrLength) {

 	char * whole_word, part_word [MAXLEN], guess[MAXLEN], outbuf [MAXLEN], hostname[MAXLEN];
 	int lives, i, good_guess, word_length, game_state;
 	
 	// I = Incomplete, while incomplete continue game of hangman.
 	game_state = 'I';
 	lives = maxlives;

	// Display host name info.
 	gethostname (hostname, MAXLEN);
 	sprintf(outbuf, "Playing hangman on host %s: \n \n", hostname);
 	write(out, outbuf, strlen (outbuf));

 	// Pick a word at random from the list.
 	whole_word = word[rand() % NUM_OF_WORDS];
 	word_length = strlen(whole_word);

 	// No letters are guessed initially.
 	for (i = 0; i < word_length; i++)
 		part_word[i]='-';
 		
	part_word[i] = '\0';

// ---------------------GAME-----------------------------------------
 	// Get a letter from player guess.
 	while (1) {
 	
 	 	// Display the current word guess progress.
 		sprintf (outbuf, "%s %d \n", part_word, lives);
 		
 		// Send current progress to client.
 		sendto(out, outbuf, MAXLEN, 0, (struct sockaddr*) &addr, addrLength);
 	
 		// Terminate game if win or loss.
 		if (game_state == 'L' || game_state == 'W') {
 			break;
 		}
 		
 		// Listen and receive input from client.
 		if (recvfrom (in, guess, MAXLEN, 0, (struct sockaddr *) &addr, &addrLength) < 0) {
 			puts("No response from client, exiting game.....");
 			break;
 		}
 		
 		// Test if input is a good guess. Deduct lives if not.
 		good_guess = 0;
 		for (int j = 0; j < word_length; j++) {
 			if (guess [0] == whole_word [j]) {
 				good_guess = 1;
 				part_word [j] = whole_word [j];
 			}
 		}
 	
 		// If incorrect guess, decrement lives counter.
 		if (!good_guess) {
 			lives--;
 		}
 		
 		// If user has correctly guessed entire word, victory!
 		if (strcmp (whole_word, part_word) == 0) {
 			// W = User has won the game.
 			game_state = 'W';
 		}
 		
 		// If user no remaining guesses left, loss!
 		else if (lives == 0) {
 	
 			// L ==> User has lost the game.
 			game_state = 'L';
 		
 			// User show the word.
 			strcpy (part_word, whole_word); 
 		}
 	}
 }
