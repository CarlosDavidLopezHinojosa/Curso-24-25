#include "cliente.h"

int main() 
{
    int cliente_socket;
    struct sockaddr_in servidor_addr;
    Usuario user = {0};
    Mensaje msg;

    inicializarSocketCliente(&cliente_socket, &servidor_addr);
    enviarAutenticacion(&cliente_socket, &user);
    solicitarPartida(&cliente_socket, &user);
    manejarComunicacion(&cliente_socket, &msg);
    printf("Mi numero de socket %d",cliente_socket);
    close(cliente_socket);
    return 0;
}