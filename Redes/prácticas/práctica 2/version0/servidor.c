#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

#define PORT 8080
#define MAX_CLIENTS 30
#define BUFFER_SIZE 256

void error(const char *msg) 
{
    perror(msg);
    exit(1);
}

int main() 
{
    int server_fd, new_socket, client_socket[MAX_CLIENTS], activity, i, valread, sd;
    int max_sd;
    struct sockaddr_in address;
    fd_set readfds;
    char buffer[BUFFER_SIZE];
    socklen_t addrlen;
    
    // Inicializar sockets de clientes
    for (i = 0; i < MAX_CLIENTS; i++) 
    {
        client_socket[i] = 0;
    }
    
    // Crear socket TCP
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    {
        error("Socket failed");
    }

    // Configurar servidor
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Vincular socket con el puerto
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) 
    {
        error("Bind failed");
    }

    // Escuchar hasta 10 conexiones entrantes
    if (listen(server_fd, 10) < 0) 
    {
        error("Listen failed");
    }
    
    printf("Servidor esperando conexiones en el puerto %d...\n", PORT);

    // Aceptar múltiples conexiones usando select()
    while (1) 
    {
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds);
        max_sd = server_fd;

        // Añadir sockets de cliente al set
        for (i = 0; i < MAX_CLIENTS; i++) 
        {
            sd = client_socket[i];
            if (sd > 0) FD_SET(sd, &readfds);
            if (sd > max_sd) max_sd = sd;
        }

        // Esperar actividad en uno de los sockets
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
        if ((activity < 0) && (errno != EINTR)) 
        {
            error("Select error");
        }

        // Nueva conexión entrante
        if (FD_ISSET(server_fd, &readfds)) 
        {
            int addrlen = sizeof(address);
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) 
            {
                error("Accept failed");
            }

            printf("Nueva conexión, socket fd: %d, ip: %s, puerto: %d\n", new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

            // Añadir nuevo socket al array de clientes
            for (i = 0; i < MAX_CLIENTS; i++) 
            {
                if (client_socket[i] == 0) 
                {
                    client_socket[i] = new_socket;
                    printf("Añadido a la lista de sockets en la posición %d\n", i);
                    break;
                }
            }
        }

        // Ver si hay I/O en otros sockets
        for (i = 0; i < MAX_CLIENTS; i++) 
        {
            sd = client_socket[i];
            if (FD_ISSET(sd, &readfds)) 
            {
                // Leer datos del cliente
                if ((valread = read(sd, buffer, BUFFER_SIZE)) == 0) 
                {
                    // Cliente desconectado
                    getpeername(sd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
                    printf("Cliente desconectado, ip: %s, puerto: %d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
                    close(sd);
                    client_socket[i] = 0;
                } 
                else 
                {
                    // Procesar mensaje del cliente
                    buffer[valread] = '\0';
                    printf("Mensaje recibido: %s\n", buffer);
                    send(sd, "Mensaje recibido\n", strlen("Mensaje recibido\n"), 0);
                }
            }
        }
    }
    
    return 0;
}
