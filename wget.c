
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#define BUFFLEN 2500



int main(int argc, char* argv[]) {
  if (argc != 2) { 
    perror("Usage: hostnamelookup <hostname>\n");
    exit(1);
  }
  FILE *fptr;
  char buf[516]; 
  char * web_address = argv[1]; 
  char wget[BUFFLEN] = "wget ";
  strcat(wget,web_address);
  system(wget); //Downloads all the information from any website I request in a file 

  fptr = fopen("index.html", "r");
  while (fgets(buf,516,fptr))
  {
    printf("%s", buf);
  }
  fclose(fptr);
  system("rm index.html");
  exit(0);

}
