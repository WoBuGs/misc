#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#define BUFF_LEN 1024


int main(int argc, char ** argv){
  int sock;
  struct sockaddr_in server;
  struct hostent * hp;
  char buff[BUFF_LEN];

  if (argc != 4) {
    fprintf(stderr,"usage: %s host sport message\n",argv[0]);
    exit(1);
  }


  sock = socket(AF_INET, SOCK_STREAM, 0);
  if(sock < 0){
    perror("Echec lors de la creation du socket");
    exit(1);
  }

  server.sin_family = AF_INET;

  hp = gethostbyname(argv[1]);
  if(hp == 0){
    perror("Echec lors du gethostbyname");
    exit(1);
  }

  memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
  server.sin_port = htons(atoi(argv[2]));

  if(connect(sock, (struct sockaddr *) &server, sizeof(sockaddr_in)) < 0){
    perror("Echec lors du connect");
    close(sock);
    exit(1);
  }

  memset(buff, 0, BUFF_LEN);
  sprintf(buff, argv[3]);
  if(write(sock, buff, strlen(buff)) < 0){
    perror("Echec lors du send");
    close(sock);
    exit(1);
  }

  close(sock);

  return 0;
}
