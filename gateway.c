#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
/*in each iteration of which it receives a datagram from port P, 
 then samples a random number using 
 ((float)random())/((float)RAND_MAX) - if the number obtained is greater than 0.5,
 the datagram received is forwarded onto the outgoing socket to port P+1, 
 otherwise the datagram is discarded and the process goes back to waiting for another incoming datagram*/

int main(int argc, char* argv[]) {
    // Define varibales
    float rand;
    int socket_recv, socket_send,recv_f, fsize, seed = 5; //seed- for a new sequence of pseudo-random numbers to be returned by subsequent calls to rand().
    struct sockaddr_in s_in, from, dest;
    struct hostent *hostptr = gethostbyname(argv[1]); //gethostbyname -retrieves host information corresponding to a host name from a host database.
    struct {char head; u_long  body; char tail;} msg, msgbuf;
    socket_recv = socket(AF_INET, SOCK_DGRAM, 0); // socket for in 
    socket_send = socket(AF_INET, SOCK_DGRAM, 0); // socket for out 
    srandom(seed); 
    bzero((char *) &s_in, sizeof(s_in)); // restart  the socket "in"
    s_in.sin_family = (short)AF_INET; 
    s_in.sin_addr.s_addr = htonl(INADDR_ANY); 
    s_in.sin_port =  htons((u_short)0x3333);
    bind(socket_recv, (struct sockaddr *)&s_in, sizeof(s_in));
    bzero((char *) &dest, sizeof(dest)); //restart the socket "out"
    dest.sin_family = (short) AF_INET;
    bcopy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length); 
    dest.sin_port =  htons((u_short)0x3333)+ 1;
    printf("Recv port %d \nSend port %d\n\n",s_in.sin_port,dest.sin_port);
    
    for(;;) {
        fsize = sizeof(from);// receive source
        recv_f = recvfrom(socket_recv,&msg,sizeof(msg),0,(struct sockaddr *)&from,&fsize);
        printf("Received data gram from source\n");
        fflush(stdout); 
        if ((((float)random()) / ((float)RAND_MAX))> 0.5) {
            printf("sended! \n\n",(((float)random()) / ((float)RAND_MAX))); // data gram has been sent
            sendto(socket_send,&msg,sizeof(msg),0,(struct sockaddr *)&dest,
                  sizeof(dest)); //the datagram received is forwarded onto the outgoing socket to port P+1
        }
        else { printf("blocked! \n\n",(((float)random()) / ((float)RAND_MAX)));
         } // the data gram blocked
    }
    return 0;
}

