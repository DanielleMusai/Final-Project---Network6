#include <sys/types.h>
#include <unistd.h>          
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>    
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define SIM_LENGTH 10 
#define IP_ADDRESS "127.0.0.1" 
#define PORT 1337 //the port the server listen to

int main(int argc, char* argv[])
{ 
  // define variables
  struct addrinfo* res;
  char* hostname;
  char* hostaddr;
  struct sockaddr_in* saddr;
  int sock; 
  struct sockaddr_in cli_name; 
  int count;
  int value; 

if (argc != 2) {
    perror("Usage: hostnamelookup <hostname>\n\n");
    exit(1);
  }

  hostname = argv[1];
  
  if (0 != getaddrinfo(hostname, NULL, NULL, &res)) {
    fprintf(stderr, "Error in resolving hostname %s\n", hostname);
    exit(1);
  }
  
  saddr = (struct sockaddr_in*)res->ai_addr;
  hostaddr = inet_ntoa(saddr->sin_addr);
  printf("Client is alive and establishing socket connection.\n");
  sock = socket(AF_INET, SOCK_STREAM, 0); // creating the socket 
  if (sock < 0) // if the socket unsecssed error and close it up
    { perror ("Error opening channel");
      close(sock);
      exit(1);
    }
      
  bzero(&cli_name, sizeof(cli_name)); 
  // define properties required to connect to the socket, bzero function write zero into cli_name 
  cli_name.sin_family = AF_INET; // address is set to AF_INET
  cli_name.sin_addr.s_addr = inet_addr(IP_ADDRESS); // casting from ipv4 to binary 
  cli_name.sin_port = htons(PORT);// change the host address to network addres 


  if (connect(sock, (struct sockaddr *)&cli_name, sizeof(cli_name)) < 0) //connecting the socket if return zero we succed 
    { perror ("Error establishing communications"); // otherwise error 
      close(sock);
      exit(1);
    }

  for (count = 1; count <= SIM_LENGTH; count++) // // Write a response on the connected socket ,loop till ten
    { read(sock, &value, 4);
      printf("Client has received %d from socket.\n", value);
    }

  printf("Exiting now.\n"); 
  close(sock);  // closing the socket 
  exit(0); 

} 


