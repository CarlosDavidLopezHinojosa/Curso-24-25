#include "comunes.h"

void error(const char * mensaje)
{
    perror(mensaje);
    exit(EXIT_FAILURE);
}

ssize_t enviarMensaje(int * socketDestino, Mensaje * mensaje)
{
    ssize_t s = send(*socketDestino,(Mensaje *) mensaje, sizeof(*mensaje),0); 
    if (s < 0) error("Error al enviar un mensaje");
    return s;
}

ssize_t recibirMensaje(int * socketOrigen, Mensaje * mensaje )
{   
    ssize_t r = read(*socketOrigen,(Mensaje *) mensaje, sizeof(*mensaje));
    if (r < 0) error("Error al recibir un mensaje");
    return r;
}

void cerrarSocket(int * socket)
{
    close(*socket);
    *socket = 0;
}