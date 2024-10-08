#ifndef SERVIDOR_H
#define SERVIDOR_H
#include "comunes.h"
#include <time.h>

#define MAX_USUARIOS 20
#define MAX_PARTIDAS 10

typedef struct Nodo
{
    Usuario * user;
    struct Nodo * anterior;   
    struct Nodo * siguiente;  
} Nodo; 

typedef struct Cola
{
    struct Nodo * frente;
    struct Nodo * final;
} Cola;

typedef struct Partida
{
    Usuario * usuario1;
    Usuario * usuario2;
    int estaLibre;
}Partida;


//Crear cola
Cola * crear_cola();
//Encolar Usuario
void encolar(Cola * cola, Usuario * user);
//Quitar de la cola al primer usuario
Usuario * desencolar(Cola * cola);
//Devuelve si esta vacia la cola
int esta_vacia(Cola * cola);
//Destruye la cola
void liberar_cola(Cola * cola);



//Inicializar cola y usuarios
void inicializarEstructuras();
//Iniciar conexión del servidor
void iniciarSocketServidor(int * socketServidor, struct sockaddr_in * servidorAddress);
//Actualizar la informacion de los Set
void refrescarConjunto(fd_set * readSet, int * max, int * socketServidor);
//Ver si hay algo que hacer
void verActividadSockets(fd_set * readSet, int * max, struct timeval * timeout, int * socketServidor);
// Comprobar si hay un nuevo usuario
void comprobarNuevaConexion(fd_set * readSet, int * socketServidor, int * socketCliente, struct sockaddr_in * clienteAddress );
//Validar usuario
void validarUsuario(Usuario * usuario);
//En funcion del comando se comporta de manera distinta
void interpretarComandos(Mensaje * msg);
//Maneja la informacion y los comandos
void manejarComandos(fd_set * readSet);
//Comienza la partida si hay dos jugadores esperando
void comenzarPartida();
//Elininar dinamicamente todas las estructuras
void liberarEstructuras(int * socketServidor);
#endif