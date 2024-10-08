#include "servidor.h"
#include <time.h>
int main()
{
    int socketServidor, socketCliente, max;
    struct sockaddr_in servidorAddress, clienteAddress;
    fd_set readSet;
    struct timeval timeout = {1, 0};

    inicializarEstructuras();
    iniciarSocketServidor(&socketServidor, &servidorAddress);

    while (1)
    {
        refrescarConjunto(&readSet, &max, &socketServidor);
        verActividadSockets(&readSet, &max, &timeout, &socketServidor);
        comprobarNuevaConexion(&readSet, &socketServidor, &socketCliente, &clienteAddress);
        manejarComandos(&readSet);
        comenzarPartida();
    }

    liberarEstructuras(&socketServidor);
    return 0;
}