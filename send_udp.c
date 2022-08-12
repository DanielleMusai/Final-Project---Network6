#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  // Define varibales
  int socket_fd;
  struct sockaddr_in  dest;
  struct hostent *hostptr;
  struct { char head; u_long body; char tail; } msgbuf;
// create a new socket of type ipv4 and udp without stating the protocol and returning its ptr
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);//AF_INET - internet domain ,SOCK_DGRAM - Type of socket.
  bzero((char *) &dest, sizeof(dest)); // They say you must do this 
  hostptr = gethostbyname(argv[1]); //gethostbyname -retrieves host information corresponding to a host name from a host database.
  dest.sin_family = (short) AF_INET;
  bcopy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);
  dest.sin_port = htons((u_short)0x3333); // convert the decimal 13107 to TCP/IP network byte order port value

  msgbuf.head = '<';
  msgbuf.body = htonl(getpid()); // IMPORTANT! 
  msgbuf.tail = '>';

  sendto(socket_fd,&msgbuf,sizeof(msgbuf),0,(struct sockaddr *)&dest,
                  sizeof(dest));//used to transmit a message to another socket

  return 0;
}
