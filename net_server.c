#include <sys/types.h>
#include <unistd.h>          
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>     
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#define SIM_LENGTH 10
#define PORT 9999 //the port the server listen to

int main(void)
{ 
  
  // define the variables
  int sock; 
  int connect_sock; 
  struct sockaddr_in serv_name; 
  size_t len; 
  int count;
  
  sock = socket(AF_INET, SOCK_STREAM, 0);  // creating the socket 
    
  bzero(&serv_name, sizeof(serv_name)); 
  // define sockets properties so the socket could listen  
  serv_name.sin_family = AF_INET;   // address is set to AF_INET                     
  serv_name.sin_port = htons(PORT); //change the host address to network addres

  bind(sock, (struct sockaddr *)&serv_name, sizeof(serv_name));
          
  listen(sock, 1); 

  len = sizeof(serv_name);  //waiting for connection request to come
  
  connect_sock = accept(sock, (struct sockaddr *)&serv_name, &len);// accept the first connection from the client 

  for (count = 1; count <= SIM_LENGTH; count++) // Write a response on the connected socket, loop till ten
    { write(connect_sock, &count, 4);
      printf("Server has written %d to socket.\n", count);
    }

  close(connect_sock);  // Close the connected socket
  close(sock);

}
