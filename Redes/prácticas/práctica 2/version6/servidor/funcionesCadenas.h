#ifndef FUNCIONESCADENAS_H
#define FUNCIONESCADENAS_H

#include <string.h>
#include "estructuras.h"


/**
 * @brief Compara si dos cadenas de texto son iguales.
 * 
 * Esta función compara dos cadenas de caracteres y determina si son exactamente iguales. 
 * Retorna 1 si las cadenas son iguales, o 0 si son diferentes.
 * 
 * @param cadena1 La primera cadena de texto a comparar.
 * @param cadena2 La segunda cadena de texto a comparar.
 * @return int 1 si las cadenas son iguales, 0 si son diferentes.
 */
int cadenasIguales(char * cadena1, char * cadena2);

/**
 * @brief Compara los primeros n caracteres de dos cadenas de texto.
 * 
 * Esta función compara hasta los primeros `n` caracteres de dos cadenas de caracteres. 
 * Retorna 1 si las primeras `n` posiciones son iguales, o 0 si son diferentes.
 * 
 * @param cadena1 La primera cadena de texto a comparar.
 * @param cadena2 La segunda cadena de texto a comparar.
 * @param n El número de caracteres a comparar.
 * @return int 1 si las primeras `n` posiciones son iguales, 0 si son diferentes.
 */
int cadenasIgualesN(char * cadena1, char * cadena2, int n);

/**
 * @brief Copia el contenido de una cadena en otra.
 * 
 * Esta función copia el contenido de `cadena1` en `cadena2`. El espacio de memoria para `cadena1` 
 * debe ser suficientemente grande para almacenar el contenido de `cadena2`.
 * 
 * @param cadena1 La cadena fuente cuyo contenido será copiado.
 * @param cadena2 La cadena de destino donde se copiará el contenido.
 */
void copiarCadena(char * cadena1, char * cadena2);

/**
 * @brief Extrae la petición del paquete y la guarda en una cadena.
 * 
 * Esta función extrae la petición de un paquete y la almacena en una cadena de caracteres proporcionada.
 * 
 * @param paquete El paquete que contiene la petición.
 * @param peticion La cadena de destino donde se guardará la petición.
 */
void saberPeticion(Paquete * paquete, char * peticion);

/**
 * @brief Registra un usuario en base a la información contenida en un paquete.
 * 
 * Esta función extrae los datos de un paquete y los utiliza para registrar un usuario.
 * 
 * @param paquete El paquete que contiene la información del usuario.
 * @param usuario El usuario que será registrado.
 */
void regitrarUsuario(Paquete * paquete, Usuario * usuario);

#endif