#ifndef COMUNES_H
#define COMUNES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <signal.h>


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

/**
 * @brief En caso de que se detecte un error usar esta función
 * imprimira por consola el error designado por el programador y terminara el programa
 * 
 * @param mensaje El mensaje se error designado por el programador
 */
void error(const char * mensaje);

/**
 * @brief Envia un mensaje dado un socket
 * 
 * @param socketDestino Referencia al socket de destino
 * @param mensaje Mensaje a enviar
 */
ssize_t enviarMensaje(int * socketDestino, Mensaje * mensaje);
/**
 * @brief Recibe un mensaje dado un socket
 * 
 * @param socketDestino Referencia al socket de origen
 * @param mensaje Mensaje a recibir
 */
ssize_t recibirMensaje(int * socketOrigen, Mensaje * mensaje );

/**
 * @brief Cierra un socket dado
 * 
 * @param socket El socket a cerrar
 */
void cerrarSocket(int * socket);

#endif