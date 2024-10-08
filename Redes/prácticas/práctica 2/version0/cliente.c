#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 256

int main() 
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    // Crear socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    {
        printf("\n Error al crear socket \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convertir dirección IP de texto a formato binario
    if (inet_pton(AF_INET, "13.39.86.135", &serv_addr.sin_addr) <= 0) 
    {
        printf("\n Dirección inválida o no soportada \n");
        return -1;
    }

    // Conectar al servidor
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    {
        printf("\n Conexión fallida \n");
        return -1;
    }
    
    char msg [30];
    fgets(msg,sizeof(msg),stdin);
    
    if (msg[strlen(msg) - 1] == '\n') msg[strlen(msg) - 1] = '\0'; 
    // Enviar mensaje
    send(sock, msg, strlen(msg), 0);
    printf("Mensaje enviado\n");

    // Leer respuesta
    valread = read(sock, buffer, BUFFER_SIZE);
    printf("%s\n", buffer);

    return 0;
}
