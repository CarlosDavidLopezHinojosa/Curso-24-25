#ifndef USUARIO_H
#define USUARIO_H

#include "comunes.h"

/**
 * @brief Realiza la conexión al servidor a través de su IP
 * 
 * @param clienteSocket Referencia al socket del Servidor
 * @param servidorAddress Refencia a la dirección de Internet del Socket del Servidor
 */
void conectarAlServidor(int * clienteSocket, struct sockaddr_in * servidorAddress);

/**
 * @brief Rellena los campos del usuario
 * 
 * @param usuario Referencia a la estructura del propio usuario
 * @param socketUsuario Referencia al socket del usuario
 */
void rellenarDatos(Usuario * usuario, int * socketUsuario);

/**
 * @brief Si el usuario es de nuevo ingreso se introducira dentro de la Base de Datos del servidor
 * en caso contrario se avisara al usuario de que ya tiene cuenta y se le pedira iniciar sesión
 */
void registrarse();


/**
 * @brief Se le solicitará al usuario sus credenciales para iniciar sesión dentro del servidor
 */
void iniciarSesion();

/**
 * @brief Despues de que el servidor haya enviado una respuesta el usuario debera elegir como responder
 * @param mensaje Mensaje recibido del servidor
 */
Mensaje interpretarMensajeUsuario(Mensaje * mensaje);

/**
 * @brief Envia el mensaje elegido por el usuario al servidor
 */
void interactuarServidor(Usuario * usuario);

void jugarBlackJack();

void menuUsuario();


#endif