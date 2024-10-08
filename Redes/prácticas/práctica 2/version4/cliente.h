#ifndef CLIENTE_H
#define CLIENTE_H
#include "comunes.h"



void inicializarSocketCliente(int * cliente_socket, struct sockaddr_in * servidor_addr);

void enviarAutenticacion(int * cliente_socket, Usuario * user);

void solicitarPartida(int *cliente_socket, Usuario *user);

void manejarComunicacion(int *cliente_socket, Mensaje *msg);
#endif