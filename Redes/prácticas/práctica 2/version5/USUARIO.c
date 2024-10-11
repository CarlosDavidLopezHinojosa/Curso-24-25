#include "usuario.h"

int main() 
{
    int clienteSocket;
    struct sockaddr_in servidorAddress;

    // Conectar al servidor
    conectarAlServidor(&clienteSocket, &servidorAddress);

    Usuario usuario;
    rellenarDatos(&usuario, &clienteSocket);

    // Bucle principal para enviar y recibir mensajes del servidor
    interactuarServidor(&usuario);

    return 0;
}
