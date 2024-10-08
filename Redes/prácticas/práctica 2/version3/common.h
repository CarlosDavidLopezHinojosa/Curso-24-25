#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

#define PUERTO 8080

typedef struct
{
    char palo;
    int numero;
} Carta;

typedef struct
{
    int socket;
    int validado;
    int jugando;
    char nombreUsuario [100];
    char credendiales [100];
    Carta Mano [11];

} Usuario;

typedef struct
{
    char peticion [50];
    Usuario usuario;
} Mensaje;

void error(const char *msg);


#endif