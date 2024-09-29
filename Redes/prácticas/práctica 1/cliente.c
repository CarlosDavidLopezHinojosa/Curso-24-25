#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define MAX_ATTEMPTS 3
#define TIMEOUT 5
#define PORT 12345  // Puerto fijo en el cliente

int main(int argc, char *argv[]) 
{
    if (argc != 3) 
    {
        printf("Uso: %s <IP servidor> <SOLICITUD>\n", argv[0]);
        return -1;
    }

    const char *server_ip = argv[1];
    const char *request = argv[2];
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(server_addr);

    // Crear socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
    {
        perror("Error al crear socket");
        exit(EXIT_FAILURE);
    }

    // Configurar timeout
    struct timeval tv;
    tv.tv_sec = TIMEOUT;
    tv.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    // Configurar dirección del servidor
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);  // Usamos el puerto fijo
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

    int attempts = 0;
    while (attempts < MAX_ATTEMPTS) 
    {
        // Enviar solicitud al servidor
        sendto(sockfd, request, strlen(request), 0, (const struct sockaddr *)&server_addr, addr_len);
        printf("Solicitud enviada: %s\n", request);

        // Intentar recibir respuesta
        if (recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, &addr_len) > 0) 
        {
            printf("Respuesta del servidor: %s\n", buffer);
            break;
        } 
        else 
        {
            printf("No se recibió respuesta, reintentando...\n");
        }

        attempts++;
    }

    if (attempts == MAX_ATTEMPTS) 
    {
        printf("Error: No se pudo obtener respuesta después de 3 intentos.\n");
    }

    close(sockfd);
    return 0;
}
