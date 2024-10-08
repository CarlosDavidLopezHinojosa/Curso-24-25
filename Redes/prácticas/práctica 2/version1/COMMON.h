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

typedef struct Carta
{
    char palo;
    int numero;
} Carta;

typedef struct Usuario
{
    int socket;
    int validado;
    int jugando;
    char * nombreUsuario;
    char * credendiales;
    Carta * Mano;

} Usuario;

typedef struct Mensaje
{
    char peticion [50];
    Usuario  usuario;
} Mensaje;

typedef struct Nodo
{
    Usuario * user;
    struct Nodo * anterior;   
    struct Nodo * siguiente;  
}; 

// Definición de la estructura Cola
typedef struct Cola
{
    struct Nodo * frente;
    struct Nodo * final;
} Cola;

// Función para crear una cola vacía
Cola * crear_cola() 
{
    Cola *cola = (Cola*)malloc(sizeof(Cola));
    cola->frente = NULL;
    cola->final = NULL;
    return cola;
}

// Función para encolar un usuario
void encolar(Cola * cola, Usuario * user) 
{
    Nodo *nuevo_nodo = (Nodo*)malloc(sizeof(Nodo));
    nuevo_nodo->user = user;
    nuevo_nodo->siguiente = NULL;

    if (cola->final == NULL) 
    {  // Si la cola está vacía
        nuevo_nodo->anterior = NULL;
        cola->frente = nuevo_nodo;
        cola->final = nuevo_nodo;
    } 
    else 
    {  // Agrega al final
        nuevo_nodo->anterior = cola->final;
        cola->final->siguiente = nuevo_nodo;
        cola->final = nuevo_nodo;
    }
}

// Función para desencolar un usuario
Usuario * desencolar(Cola * cola) 
{
    if (cola->frente == NULL) 
    {  // Cola vacía
        return NULL;
    }

    Nodo *nodo_eliminar = cola->frente;
    Usuario *user = nodo_eliminar->user;

    cola->frente = nodo_eliminar->siguiente;

    if (cola->frente == NULL) 
    {  // Si la cola quedó vacía
        cola->final = NULL;
    } 
    else 
    {
        cola->frente->anterior = NULL;
    }

    free(nodo_eliminar);  // Libera el nodo
    return user;  // Retorna el usuario desencolado
}

// Función para verificar si la cola está vacía
int esta_vacia(Cola * cola) 
{
    return (cola->frente == NULL);
}

// Función para liberar toda la memoria de la cola
void liberar_cola(Cola * cola) 
{
    while (!esta_vacia(cola)) 
    {
        desencolar(cola);
    }
    free(cola);
}


#endif