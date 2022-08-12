#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
/*in each iteration of which it sends a datagram onto the socket carrying in
 its body an integer number, increments the integer, 
 then sleeps for one second only to repeat the cycle upon waking up*/
 
int main(int argc, char *argv[])
{
  // Define varibales
  int socket_fd; 
  struct sockaddr_in  dest; 
  struct hostent *hostptr;
  struct {int num;} msgbuf;
  // create a new socket of type ipv4 and udp without stating the protocol and returning its ptr
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);//AF_INET - internet domain ,SOCK_DGRAM - Type of socket.
  bzero((char *) &dest, sizeof(dest));
  hostptr = gethostbyname(argv[1]);  //gethostbyname -retrieves host information corresponding to a host name from a host database.
  dest.sin_family = (short) AF_INET; 
  dest.sin_port = htons((u_short)0x3333);// convert the decimal 13107 to TCP/IP network byte order port value
  printf("Send in port %d\n\n",htons(dest.sin_port));
  for(int i = 0;;i++){
    printf("send: %d\n", i);
    msgbuf.num = i; 
    sendto(socket_fd,&msgbuf,sizeof(msgbuf),0,(struct sockaddr *)&dest,
                  sizeof(dest));//used to transmit a message to another socket
    sleep(1); // sleep one second only to repeat the cycle upon waking up
  }
  return 0;
}
