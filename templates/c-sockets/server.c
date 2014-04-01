#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define BUFF_LEN 1024


int main(int argc, char ** argv){
  /* Variables */
  int sock;
  struct sockaddr_in server, client;
  int client_len;
  int mysock;
  char buff[BUFF_LEN];
  int rval;

  /* Create socket */
  sock =socket(AF_INET, SOCK_STREAM, 0);
  if(sock < 0){
    perror("Echec lors de la creation du socket");
    exit(1);
  }

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(5000);/* port utilisé par le serveur */

  /* Call bind */
  if(bind(sock, (struct sockaddr *)&server, sizeof(server))){
    perror("Echec lors du bind");
    exit(1);
  }

  /* Listen */
  listen(sock, 5);

  /* Accept */
  while(1){
    client_len = sizeof(client);
    mysock = accept(sock, (struct sockaddr *) &client, &client_len);
    if(mysock == -1){
      perror("Echec lors du accept");
    }else{
      memset(buff, 0, BUFF_LEN);
      if((rval = recv(mysock, buff, BUFF_LEN, 0)) < 0)
        perror("Echec lors de la lecture");
      else if(rval == 0)
        printf("Fin de la connection");
      else
        printf("Message : %s\n", buff);
      
      printf("Message reçu ! (rval=%d)\n",rval);
      close(mysock);
      }
    }

  return 0;
}