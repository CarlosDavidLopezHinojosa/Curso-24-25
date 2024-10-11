#ifndef FUNCIONESSERVIDOR_H
#define FUNCIONESSERVIDOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

#include <signal.h>
#include <errno.h>

#include "estructuras.h"

#define PUERTO 2060

/**
 * @section General
 * 
 * @brief En caso de que se detecte un error, usar esta función
 * imprimirá por consola el error designado por el programador y terminará el programa.
 * 
 * @param mensaje El mensaje de error designado por el programador.
 */
void error(const char * mensaje);

/**
 * @section General
 * 
 * @brief Envía un paquete a un socket dado.
 * 
 * Esta función permite enviar un paquete de datos a través de un socket específico, asegurando la correcta comunicación en el servidor.
 * 
 * @param socketDestino Referencia al socket de destino.
 * @param paquete Paquete a enviar.
 * @return ssize_t Número de bytes enviados o -1 en caso de error.
 */
ssize_t enviarPaquete(int * socketDestino, Paquete * paquete);

/**
 * @section General
 * 
 * @brief Recibe un paquete de un socket dado.
 * 
 * Esta función permite recibir un paquete de datos a través de un socket específico, asegurando la correcta comunicación desde un cliente hacia el servidor.
 * 
 * @param socketOrigen Referencia al socket de origen.
 * @param paquete Paquete a recibir.
 * @return ssize_t Número de bytes recibidos o -1 en caso de error.
 */
ssize_t recibirPaquete(int * socketOrigen, Paquete * paquete);

/**
 * @section General
 * 
 * @brief Cierra un socket dado.
 * 
 * Esta función cierra la conexión del socket especificado, liberando los recursos asociados.
 * 
 * @param socket El socket a cerrar.
 */
void cerrarSocket(int * socket);

/**
 * @section Servidor
 * 
 * @brief Inicializa la rutina del servidor, configurando el socket del servidor y las estructuras de datos.
 * 
 * Establece el socket del servidor para el protocolo TCP en el puerto 2060 y prepara la dirección del servidor.
 * Además, inicializa el array de usuarios y la cola.
 * 
 * @param usuarios Referencia al array de usuarios.
 * @param cola Referencia a la cola de usuarios.
 * @param socketServidor Referencia al socket del servidor.
 * @param servidorAddress Referencia a la dirección de Internet del socket del servidor.
 */
void iniciarRutina(Usuario * usuarios, Cola * cola, int * socketServidor, struct sockaddr_in * servidorAddress);

/**
 * @section Servidor
 * 
 * @brief Actualiza el conjunto de descriptores de fichero que el servidor está monitoreando.
 * 
 * Añade los descriptores de fichero (sockets) al conjunto de lectura si es necesario,
 * permitiendo que el servidor pueda manejar nuevas peticiones de clientes.
 * 
 * @param usuarios Referencia al array de usuarios conectados.
 * @param readSet Conjunto de descriptores de fichero.
 * @param max Referencia al descriptor de fichero mayor.
 * @param socketServidor Referencia al socket del servidor.
 */
void actualizarConjunto(Usuario * usuarios, fd_set * readSet, int * max, int * socketServidor);

/**
 * @section Servidor
 * 
 * @brief Monitorea los descriptores de fichero para identificar actividad.
 * 
 * Esta función monitorea los descriptores de fichero activos para identificar si alguna actividad ha ocurrido en ellos.
 * 
 * @param readSet Conjunto de descriptores de fichero.
 * @param max Referencia al descriptor de fichero mayor.
 * @param timeout Referencia a un tipo de dato que marca el tiempo máximo de espera.
 */
void comprobarActividad(fd_set * readSet, int * max, struct timeval * timeout);

/**
 * @section Servidor
 * 
 * @brief Comprueba si un nuevo usuario ha iniciado una conexión y lo añade al array de usuarios.
 * 
 * Esta función revisa si algún cliente ha solicitado una nueva conexión al servidor.
 * Si es una conexión válida, el cliente es añadido al array de usuarios.
 * 
 * @param usuarios Referencia al array de usuarios conectados.
 * @param readSet Conjunto de descriptores de fichero.
 * @param socketServidor Referencia al socket del servidor.
 * @param socketUsuario Referencia al socket del nuevo usuario.
 * @param usuarioAddress Referencia a la dirección de Internet del socket del usuario.
 */
void comprobarNuevaConexion(Usuario * usuarios, fd_set * readSet, int * socketServidor, int * socketUsuario, struct sockaddr_in * usuarioAddress);

#endif
