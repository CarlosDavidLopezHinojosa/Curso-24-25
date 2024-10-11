// server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <errno.h>

#define PORT 8080
#define MAX_QUEUE 2
#define MAX_CLIENTS 10

typedef struct {
    int client_socket;
} Player;

Player queue[MAX_QUEUE];
int queue_size = 0;

void add_player_to_queue(int client_socket) {
    if (queue_size < MAX_QUEUE) {
        queue[queue_size].client_socket = client_socket;
        queue_size++;
    }
}

void notify_players_to_start_game() {
    if (queue_size == MAX_QUEUE) {
        // Notificar a los jugadores que pueden comenzar el juego
        for (int i = 0; i < MAX_QUEUE; i++) {
            char message[] = "Ready to start the game!";
            send(queue[i].client_socket, message, sizeof(message), 0);
        }
        // Vaciar la cola
        queue_size = 0;
    }
}

int main() {
    int server_socket, new_socket, max_sd, sd, activity;
    struct sockaddr_in address;
    fd_set readfds;

    // Crear socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Configurar el servidor
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Enlazar el socket al puerto
    if (bind(server_socket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Escuchar conexiones
    if (listen(server_socket, 3) < 0) {
        perror("Listen");
        exit(EXIT_FAILURE);
    }

    printf("Servidor escuchando en el puerto %d...\n", PORT);

    while (1) {
        // Limpiar el conjunto de descriptores
        FD_ZERO(&readfds);

        // Agregar el servidor al conjunto de lectura
        FD_SET(server_socket, &readfds);
        max_sd = server_socket;

        // Agregar sockets de clientes al conjunto de lectura
        for (int i = 0; i < MAX_CLIENTS; i++) {
            sd = queue[i].client_socket;
            if (sd > 0) FD_SET(sd, &readfds);
            if (sd > max_sd) max_sd = sd;
        }

        // Esperar actividad en algún socket
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR)) {
            printf("Error en select\n");
        }

        // Si hay una nueva conexión entrante
        if (FD_ISSET(server_socket, &readfds)) {
            int addrlen = sizeof(address);
            new_socket = accept(server_socket, (struct sockaddr *)&address, (socklen_t *)&addrlen);
            if (new_socket < 0) {
                perror("Error en accept");
                exit(EXIT_FAILURE);
            }
            printf("Nuevo cliente conectado: socket %d\n", new_socket);
        }

        // Revisar si algún cliente envió un mensaje
        for (int i = 0; i < MAX_CLIENTS; i++) {
            sd = queue[i].client_socket;
            if (FD_ISSET(sd, &readfds)) {
                char buffer[1024] = {0};
                int valread = read(sd, buffer, 1024);
                if (valread == 0) {
                    close(sd);
                    queue[i].client_socket = 0;
                } else {
                    // Si el cliente pide iniciar una partida
                    if (strcmp(buffer, "INICIAR-PARTIDA") == 0) {
                        add_player_to_queue(sd);
                        notify_players_to_start_game();
                    }
                }
            }
        }
    }

    return 0;
}
