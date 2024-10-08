#ifndef SERVIDOR_H
#define SERVIDOR_H

#include "comunes.h"

#define MAX_USUARIOS 20
#define MAX_PARTIDAS 10


/**
 * @brief Esta función inicializa la rutina del servidor a la vez que tambien inicializa las estructuras de 
 * datos que seran necesarias para su desempeño
 * 
 * Esta función establece el socket del servidor para el protocolo TCP a través del puerto 8080
 * 
 * @param socketServidor Referencia al socket del Servidor
 * @param servidorAddress Refencia a la dirección de Internet del Socket del Servidor
 */
void iniciarRutina(int * socketServidor, struct sockaddr_in * servidorAddress);

/**
 * @brief Reinicia y actualiza el conjunto de descriptores de fichero que se están procesando por los nuevos 
 * si los hubiera para que se pueda atender el servidor a nuevas peticiones de usuarios
 * 
 * @param readSet Conjunto de descriptores de fichero
 * @param max Referencia al descriptor de fichero mayor
 * @param socketServidor Referencia al socket del servidor  
 */
void actualizarConjunto(fd_set * readSet, int * max, int * socketServidor);

/**
 * @brief Selecciona si lo hubiera al descriptor de fichero que este solicitando algun servicio
 * 
 * @param readSet Conjunto de descriptores de fichero
 * @param max Referencia al descriptor de fichero mayor
 * @param timeout Referencia a un tipo de dato que marca el tiempo máximo de espera
 * @param socketServidor Referencia al socket del servidor 
 */
void comprobarActividad(fd_set * readSet, int * max, struct timeval * timeout);


/**
 * @brief Comprueba si un nuevo usuario inicio algun tipo de conexión al servidor y si no esta lo añade
 * 
 * @param readSet Conjunto de descriptores de fichero
 * @param socketServidor Referencia al socket del servidor 
 * @param socketUsuario Referencia al socket del cliente
 * @param servidorAddress Refencia a la dirección de Internet del socket del usuario
 */
void comprobarNuevaConexion(fd_set * readSet, int * socketServidor, int * socketUsuario, struct sockaddr_in * usuarioAddress );


/**
 * @brief Devuelve un mensaje o paquete en función de un mensaje recibido por un usuario
 * 
 * @param mensaje Estructura de datos para mandar o recibir mensajes
 * @return Mensaje de respuesta
 */
Mensaje interpretarMensajeServidor(Mensaje * mensaje);


/**
 * @brief Se encarga de recibir los mensaje enviados por los usuarios y enviar las respuestas pertinentes
 * 
 * @param readSet Conjunto de descriptores de fichero
 * @see interpretarMensajeServidor
 */
void responderMensajeServidor(fd_set * readSet);

// void registrarUsuario();

// void validarUsuario();

// void iniciarPartida();

// void finalizarPartida();

// void guardarUsuarios();

// void guardarUsuariosLegible();

// void iniciarUsuariosGuardados();

// void finalizarRutina();

// void menuServidor();




#endif