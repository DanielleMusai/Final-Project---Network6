#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

/*creates a socket to receive datagrams from any host on port P+1, 
then enters an infinite loop where it receives a datagram and prints to the screen 
the information of where the datagram came from and what message it contains */

void printsin(struct sockaddr_in *s, char *str1, char *str2) {
  printf("%s\n", str1);
  printf("%s ", str2);
  printf("ip= %s , port= %d", inet_ntoa(s->sin_addr), s->sin_port);
  printf("\n");
}

int main(int argc, char *argv[])
{
    // Define varibales
  int socket_fd, cc, fsize;
  struct sockaddr_in  s_in, from;
  struct { int body;} msg;
// create a new socket of type ipv4 and udp without stating the protocol and returning its ptr
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);

  bzero((char *) &s_in, sizeof(s_in));  // all the value in the buffer goes to 0

  s_in.sin_family = (short)AF_INET;
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);    /* WILDCARD */
  s_in.sin_port = htons((u_short)0x3333)+1;  // convert the decimal 13107 to TCP/IP network byte order port value


  // check if port is available 
  bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));

  for(;;) {// Recieving a message
    fsize = sizeof(from);
    cc = recvfrom(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&from,&fsize);
    printsin( &from, "recv data: ", "Packet from:");
    printf("got data : %d\n",(int)msg.body); 
    fflush(stdout);
    
  }
  
  return 0;
}





