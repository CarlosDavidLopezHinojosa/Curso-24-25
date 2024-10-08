// cliente.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PUERTO 8080
#define IP_SERVIDOR "127.0.0.1"

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
    int socketCliente;
    struct sockaddr_in servidorAddress;
    Mensaje mensaje;

    // Llenar los datos del usuario
    strcpy(mensaje.u.nombre, "Juan");
    strcpy(mensaje.u.password, "mi_contraseña");
    strcpy(mensaje.peticion, "CREDENCIALES"); // Ejemplo de petición

    // Crear socket
    socketCliente = socket(AF_INET, SOCK_STREAM, 0);
    if (socketCliente < 0) {
        error("Error al crear el socket");
    }

    // Configurar la dirección del servidor
    servidorAddress.sin_family = AF_INET;
    servidorAddress.sin_port = htons(PUERTO);
    if (inet_pton(AF_INET, IP_SERVIDOR, &servidorAddress.sin_addr) <= 0) {
        error("Dirección inválida/No soportada");
    }

    // Conectar al servidor
    if (connect(socketCliente, (struct sockaddr *) &servidorAddress, sizeof(servidorAddress)) < 0) {
        error("Error en connect");
    }

    // Enviar la estructura Mensaje al servidor
    if (write(socketCliente, &mensaje, sizeof(Mensaje)) < 0) {
        error("Error al enviar el mensaje");
    }

    printf("Mensaje enviado al servidor\n");

    close(socketCliente);
    return 0;
}
