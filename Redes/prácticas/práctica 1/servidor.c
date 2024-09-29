#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <unistd.h>  // Incluir unistd.h para la función close()

#define PORT 12345  // Puerto fijo
#define BUFFER_SIZE 1024

int main() 
{
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(client_addr);

    // Crear socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
    {
        perror("Error al crear socket");
        exit(EXIT_FAILURE);
    }

    // Configurar dirección del servidor
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);  // Usamos el puerto fijo

    // Enlazar el socket al puerto
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) 
    {
        perror("Error al enlazar");
        exit(EXIT_FAILURE);
    }

    printf("Servidor escuchando en el puerto %d...\n", PORT);

    while (1) 
    {
        // Recibir mensaje del cliente
        recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
        buffer[strcspn(buffer, "\n")] = 0;  // Eliminar nueva línea
        
        // Obtener tiempo actual
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        char response[BUFFER_SIZE] = "";

        // Procesar solicitud
        if(strcmp(buffer, "DAY") == 0) 
        {
            strftime(response, sizeof(response), "%A, %d de %B de %Y", t);
        } 
        else if (strcmp(buffer, "TIME") == 0) 
        {
            strftime(response, sizeof(response), "%H:%M:%S", t);
        } 
        else if (strcmp(buffer, "DAYTIME") == 0) 
        {
            strftime(response, sizeof(response), "%A, %d de %B de %Y; %H:%M:%S", t);
        } 
        else 
        {
            strcpy(response, "Solicitud no válida.");
        }

        // Enviar respuesta al cliente
        sendto(sockfd, response, strlen(response), 0, (const struct sockaddr *)&client_addr, addr_len);
    }

    close(sockfd);
    return 0;
}
