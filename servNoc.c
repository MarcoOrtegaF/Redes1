#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (){
  int udp_socket;
  int lbind;
  int tam;
  int lrecv;
  struct sockaddr_in servidor, cliente;
  unsigned char msj[100] = "Hola red soy Marco";
  unsigned char paqRec [512];
  udp_socket = socket(AF_INET, SOCK_DGRAM, 0);

  printf("Estableciendo conexion ... \n");

  if(udp_socket == -1){
    perror("\nSocket ");
    exit(0);
  }
  else{
    perror("\nSocket");
    servidor.sin_family = AF_INET; /* address family: AF_INET */
    servidor.sin_port = htons(8080);   /* port in network byte order */
    servidor.sin_addr.s_addr = INADDR_ANY;   /* internet address */
    lbind = bind(udp_socket, (struct sockaddr *)&servidor, sizeof(servidor));

    if(lbind == -1){
      perror("Bind ");
      exit(0);
    }
    else{
      perror("Bind ");

      lrecv = sizeof(cliente);

      printf("\nEsperando Mensaje ...\n\n");

      do {              //CICLO PARA ENVIAR Y RECIBIR PAQUETES DEL CLIENTE AL SERVIDOR
        tam = recvfrom(udp_socket, paqRec, 512, 0, (struct sockaddr *)&cliente, &lrecv);      //RECIBIR MENSAJE

        if(tam == -1){
          //perror("\nERROR al recibir");
          exit(0);
        }else{
          printf("\t\t\tC: %s", paqRec);   //Salida del mensaje

          printf("S: ");    //SOLICITUD DEL MENSAJE PARA RESPONDER
          fgets(msj, 100, stdin);

          tam = sendto(udp_socket, msj, strlen(msj) + 1, 0, (struct sockaddr *)&cliente, sizeof(cliente));  //ENVIO DE MENSAJE AL CLIENTE

          if(tam == -1){
            //perror("\nERROR al enviar");
            exit(0);
          }else{
            //error("\nEXITO al enviar");
          }
        }
      }while(1);
    }
  }
  close(udp_socket);
  return 0;
}
