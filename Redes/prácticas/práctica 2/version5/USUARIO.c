#include "usuario.h"

int main() {
    int clienteSocket;
    struct sockaddr_in servidorAddress;

    // Conectar al servidor
    conectarAlServidor(&clienteSocket, &servidorAddress);

    Usuario usuario;
    rellenarDatos(&usuario, &clienteSocket);

    // Bucle principal para enviar y recibir mensajes del servidor
    while (1) 
    {
        Mensaje mensaje;

        printf("Escriba su petición (o 'SALIR' para desconectar): ");
        scanf("%s",mensaje.peticion); // Eliminar el salto de línea

        // Verificar si el usuario quiere salir
        if (strcmp(mensaje.peticion, "SALIR") == 0) {
            printf("Cerrando la conexión...\n");
            cerrarSocket(&clienteSocket);
            break;
        }

        // Rellenar el usuario en el mensaje
        mensaje.usuario = usuario;

        // Enviar el mensaje al servidor
        enviarMensaje(&clienteSocket, &mensaje);

        // Recibir la respuesta del servidor
        Mensaje respuesta;
        recibirMensaje(&clienteSocket, &respuesta);

        // Interpretar la respuesta
        printf("Respuesta del servidor: %s\n", respuesta.peticion);
    }

    return 0;
}
