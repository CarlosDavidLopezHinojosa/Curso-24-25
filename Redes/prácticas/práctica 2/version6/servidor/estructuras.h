#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_USUARIOS 30
#define MAX_PARTIDAS 10

/**
 * @struct Usuario
 * @section General
 * @brief Esta estructura simula información de un Usuario.
 * 
 * @param nombre El nombre del usuario.
 * @param password La contraseña del usuario.
 * @param socket El descriptor de socket asociado al usuario.
 * 
 * @warning Estas son las funciones con las que trabaja la estructura de datos `struct Usuario`:
 * 
 * - `imprimirUsuario(Usuario *usuario)`
 */
typedef struct Usuario
{
    char nombre[100];
    char password[100];
    int socket;
} Usuario;

/**
 * @struct Paquete
 * @section General
 * @brief Estructura que representa un paquete de datos que será enviado o recibido a través del socket.
 * 
 * @warning Esta estructura debe ser completada según los requisitos del sistema.
 */
typedef struct Paquete
{
    char peticion [250];
    Usuario usuario;
} Paquete;

/**
 * @section General
 * 
 * @brief Imprime los datos de un usuario.
 * 
 * Esta función se utiliza para mostrar por consola la información de un usuario, que incluye su nombre y el descriptor de socket asociado.
 * 
 * @param usuario Un puntero a la estructura Usuario cuyos datos se desean imprimir.
 */
void imprimirUsuario(Usuario * usuario);

/**
 * @struct Cola
 * @brief Estructura de datos para gestionar las peticiones de los usuarios, implementada con un array circular.
 * @section Servidor
 * 
 * @param cola Un array de punteros a estructuras Usuario.
 * @param size El tamaño actual de la cola (número de usuarios en la cola).
 * @param posicionInsertar La posición donde se debe insertar el siguiente usuario.
 * 
 * @warning Estas son las funciones con las que trabaja la estructura de datos `struct Cola`:
 * 
 * - `iniciarCola(Cola *cola)`
 * 
 * - `estaVacia(Cola *cola)`
 * 
 * - `push(Cola *cola, Usuario *nuevoUsuario)`
 * 
 * - `pop(Cola *cola)`
 * 
 * - `liberarCola(Cola *cola)`
 * 
 * - `imprimirCola(Cola *cola)`
 * 
 * - `hayDosUsuariosEsperando(Cola *cola, Usuario **usuario1, Usuario **usuario2)`
 */
typedef struct Cola
{
    Usuario * cola[MAX_USUARIOS];
    int size;
    int posicionInsertar;
} Cola;

/**
 * @section Servidor
 * 
 * @brief Inicializa una cola, estableciendo su tamaño en 0 y la posición de inserción inicial.
 * 
 * Esta función configura los valores iniciales de la cola para que esté lista para su uso.
 * 
 * @param cola Un puntero a la estructura Cola a inicializar.
 */
void iniciarCola(Cola * cola);

/**
 * @section Servidor
 * 
 * @brief Verifica si la cola está vacía.
 * 
 * Esta función comprueba si la cola tiene elementos, devolviendo 1 si está vacía o 0 en caso contrario.
 * 
 * @param cola Un puntero a la estructura Cola que se desea comprobar.
 * @return `int` Devuelve 1 si la cola está vacía, 0 en caso contrario.
 */
int estaVacia(Cola * cola);

/**
 * @section Servidor
 * 
 * @brief Inserta un nuevo usuario en la cola.
 * 
 * Añade un usuario a la cola, manteniendo el orden de llegada. Si la cola está llena, se sobrescribe el usuario más antiguo.
 * 
 * @param cola Un puntero a la estructura Cola donde se añadirá el nuevo usuario.
 * @param nuevoUsuario Un puntero a la estructura Usuario que se desea añadir a la cola.
 */
void push(Cola * cola, Usuario * nuevoUsuario);

/**
 * @section Servidor
 * 
 * @brief Elimina el primer usuario de la cola y lo devuelve.
 * 
 * Extrae el primer usuario que entró a la cola y reduce el tamaño de la cola. Si la cola está vacía, devuelve `NULL`.
 * 
 * @param cola Un puntero a la estructura Cola de donde se extraerá el primer usuario.
 * @return `Usuario*` Devuelve un puntero al usuario extraído de la cola.
 */
Usuario * pop(Cola * cola);

/**
 * @section Servidor
 * 
 * @brief Libera los recursos asignados a la cola.
 * 
 * Esta función limpia la memoria asociada a la cola y la deja en un estado inactivo, lista para ser reiniciada o destruida.
 * 
 * @param cola Un puntero a la estructura Cola cuyos recursos se desean liberar.
 */
void liberarCola(Cola * cola);

/**
 * @section Servidor
 * 
 * @brief Imprime los usuarios en la cola.
 * 
 * Esta función muestra por consola los usuarios actualmente en la cola, en el orden en que fueron añadidos.
 * 
 * @param cola Un puntero a la estructura Cola cuyos usuarios se desean imprimir.
 */
void imprimirCola(Cola * cola); 

/**
 * @section Servidor
 * 
 * @brief Verifica si hay dos usuarios esperando en la cola y los extrae si es el caso.
 * 
 * Si hay al menos dos usuarios en la cola, los extrae y asigna a los punteros `usuario1` y `usuario2`.
 * 
 * @param cola Un puntero a la estructura Cola que se desea comprobar.
 * @param usuario1 Un puntero doble donde se almacenará el primer usuario encontrado.
 * @param usuario2 Un puntero doble donde se almacenará el segundo usuario encontrado.
 * @return `int` Devuelve 1 si hay al menos dos usuarios en la cola, 0 en caso contrario.
 */
int hayDosUsuariosEsperando(Cola * cola, Usuario ** usuario1, Usuario ** usuario2);

#endif
