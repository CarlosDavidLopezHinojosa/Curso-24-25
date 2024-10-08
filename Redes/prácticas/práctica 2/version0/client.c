#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char *message = "Hola desde mi máquina local!";
    char buffer[1024] = {0};

    // Crear socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error al crear el socket\n");
        return -1;
    }

    // Configurar la dirección del servidor (IP de la VM)
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Reemplaza "VM_IP_ADDRESS" con la IP de tu VM
    if (inet_pton(AF_INET, "13.39.86.135", &serv_addr.sin_addr) <= 0) {
        printf("Dirección IP no válida\n");
        return -1;
    }

    // Conectar al servidor en la VM
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Conexión fallida\n");
        return -1;
    }

    // Enviar mensaje al servidor
    send(sock, message, strlen(message), 0);
    printf("Mensaje enviado: %s\n", message);

    // Leer respuesta del servidor
    int valread = read(sock, buffer, 1024);
    printf("Respuesta del servidor: %s\n", buffer);

    // Cerrar el socket
    close(sock);
    return 0;
}
