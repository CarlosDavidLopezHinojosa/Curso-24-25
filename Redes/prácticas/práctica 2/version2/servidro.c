// servidor.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PUERTO 8080
#define BUFFER_SIZE 1024

typedef struct {
    char nombre[50];
    char password[50];
} Usuario;

typedef struct {
    char peticion[50];
    Usuario u; // Estructura Usuario integrada
} Mensaje;

void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    int socketServidor, socketCliente;
    struct sockaddr_in servidorAddress, clienteAddress;
    Mensaje mensaje;

    // Crear socket
    socketServidor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketServidor < 0) {
        error("Error al crear el socket");
    }

    // Configurar la dirección del servidor
    servidorAddress.sin_family = AF_INET;
    servidorAddress.sin_addr.s_addr = INADDR_ANY;
    servidorAddress.sin_port = htons(PUERTO);

    // Vincular el socket a la dirección
    if (bind(socketServidor, (struct sockaddr *) &servidorAddress, sizeof(servidorAddress)) < 0) {
        error("Error en bind");
    }

    // Escuchar por conexiones entrantes
    if (listen(socketServidor, 1) < 0) {
        error("Error en listen");
    }
    printf("Servidor escuchando en el puerto %d...\n", PUERTO);

    socklen_t clienteLen = sizeof(clienteAddress);

    // Aceptar una conexión del cliente
    socketCliente = accept(socketServidor, (struct sockaddr *) &clienteAddress, &clienteLen);
    if (socketCliente < 0) {
        error("Error en accept");
    }
    printf("Cliente conectado.\n");

    // Leer la estructura Mensaje del cliente
    int readVal = read(socketCliente, &mensaje, sizeof(Mensaje));
    if (readVal < 0) {
        error("Error al leer del cliente");
    }

    // Imprimir los datos del mensaje recibido
    printf("Petición: %s\n", mensaje.peticion);
    printf("Usuario: %s\n", mensaje.u.nombre);
    printf("Contraseña: %s\n", mensaje.u.password);

    close(socketCliente);
    close(socketServidor);
    return 0;
}
