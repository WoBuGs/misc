#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


#define BUFF_LEN 1024


int main(int argc, char ** argv){
  int sock;
  struct sockaddr_in server;
  int mysock;
  char buff[BUFF_LEN];
  int rval;
  int pid;


  if (argc != 2) {
    fprintf(stderr,"usage: %s port\n",argv[0]);
    exit(1);
  }


  sock = socket(AF_INET, SOCK_STREAM, 0);
  if(sock < 0){
    perror("Echec lors de la creation du socket");
    exit(1);
  }


  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(atoi(argv[1]));/* port utilisé par le serveur */


  if(bind(sock, (struct sockaddr *) &server, sizeof(struct sockaddr_in))){
    perror("Echec lors du bind");
    exit(1);
  }


  listen(sock, 5);

  
  printf("Serveur en écoute sur le port %d\n", ntohs(server.sin_port));



  while(1){
    struct sockaddr_in client = { 0 };
    int client_len = sizeof(struct sockaddr_in);

    mysock = accept(sock, (struct sockaddr *) &client, &client_len);

    /* fork() qui permet au serveur de rester à l'écoute */
    switch(pid=fork()){
      case -1: printf("Erreur fork()");
               exit(1);
      case 0: 
               printf("Connection ouverte (fils) : %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
               if(mysock == -1){
                 perror("Echec lors du accept");
               }else{
                 memset(buff, 0, BUFF_LEN);
                 if((rval = read(mysock, buff, BUFF_LEN)) < 0)
                   perror("Echec lors de la lecture");
                 else if(rval == 0)
                   printf("Fin de la connection");
                 else
                   printf("Message reçu : %s", buff);

                 printf(" (rval=%d)\n",rval);
                 close(mysock);
               }
               break;
      default: 
               if(mysock == -1){
                 perror("Echec lors du accept");
               }else{
                 close(mysock);
               }
               break;
    }
  }
  return 0;
}
