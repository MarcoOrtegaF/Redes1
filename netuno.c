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
  struct sockaddr_in local, remota;
  unsigned char msj[100] = "Hola red soy Marco";
  unsigned char paqRec [512];
  udp_socket = socket(AF_INET, SOCK_DGRAM, 0);

  printf("Estableciendo conexion ... \n");
  if(udp_socket == -1){
    perror("\nSocket ");
    exit(0);
  }
  else{
    perror("\nSocket ");
    local.sin_family = AF_INET; /* address family: AF_INET */
    local.sin_port = htons(0);   /* port in network byte order */
    local.sin_addr.s_addr = INADDR_ANY;   /* internet address */
    lbind = bind(udp_socket, (struct sockaddr *)&local, sizeof(local));

    if(lbind == -1){
      perror("Bind ");
      exit(0);
    }
    else{
      perror("Bind ");

      remota.sin_family = AF_INET; /* address family: AF_INET */
      remota.sin_port = htons(8080);   /* port in network byte order */
      remota.sin_addr.s_addr = inet_addr("192.168.100.8");   /* internet address */

      //iniciar ciclo
      printf("\n");
      do {
        printf("C: ");
        fgets(msj, 100, stdin);

        tam = sendto(udp_socket, msj, strlen(msj) + 1, 0, (struct sockaddr *)&remota, sizeof(remota));    //ENCIA EL MENSAJE AL SEERVIDOR

        if(tam == -1){
          //perror("\nERROR al enviar");        //NOTRIFICACIOND EXITO AL ENVIAR EL MENSAJE
          exit(0);
        }else{
          //perror("\nEXITO al enviar");        //NOTIFICACION DE ERROR AL ENCIAR EL MENSAJE

          lrecv = sizeof(remota);

          tam = recvfrom(udp_socket, paqRec, 512, 0, (struct sockaddr *)&remota, &lrecv);     //ESPERA LA RECEPCION DEL MENSAJE

          if(tam == -1){
            //perror("\nERROR al recibir");
            exit(0);
          }else{
            printf("\t\t\tS: %s", paqRec);   //Salida del mensaje
          }

        }

      } while(1);
    }
  }
  close(udp_socket);
  return 0;
}
