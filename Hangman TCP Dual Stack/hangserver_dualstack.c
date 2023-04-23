/* Michael Ryan */
/* K00245087 */
/* TCP Dual Stack */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <syslog.h>
#include <signal.h>
#include <errno.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "hangman.h"

main()
{
    struct sockaddr_in6 server, client;
    struct addrinfo hints;
    int sock, fd, client_len, r, option, level, optname;
    socklen_t len = sizeof client;
    socklen_t optlen;
    char *optval;

    /*configuring the host*/
    printf("Configuring the host.....,\n");

    hints.ai_family = AF_INET6;
    hints.ai_flags = AI_PASSIVE;

    option = 0;
    r = setsockopt(
            sock,
            IPPROTO_IPV6,
            IPV6_V6ONLY,
            (void *)&option,
            sizeof(option)
            );

    if(r == 1)
    {
        perror("failed");
        exit(1);
    }
    puts("Host configured,\n");

    srand((int) time ((long*) 0)); /*randomize the seed */

    printf("Assign a socket\n");

    if (sock == -1){
        perror("Error creating server socket");
        exit(1);
    }
    puts("Server socket created");

    sock = socket(AF_INET6, SOCK_STREAM, 0);
    setsockopt(sock, level, optname,*optval, optlen);

    if(bind(sock, (struct sockaddr *) & server, sizeof (server)) < 0) {
        perror("Binding Socket");
        exit(2);
    }
    puts("Server socket is listening for incoming requests from clients");
    puts("Let's play hangman!");
    listen (sock, 5);

    while(1){
        client_len = sizeof(client);
        if((fd = accept(sock,(struct sockaddr*)&client,&client_len)) < 0){
            perror("accepting connection");
            exit(3);
        }
        play_hangman(fd, fd);
        exit(4);
    }
    close(fd);
}
