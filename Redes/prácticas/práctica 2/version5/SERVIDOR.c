#include "servidor.h"

    int socketServidor;

    void manejarSIGINT(int signo) {
    printf("\nRecibida señal SIGINT. Cerrando el servidor...\n");
    cerrarSocket(&socketServidor); // Cerrar el socket del servidor
    exit(0); // Salir del programa
    }

int main() 
{
    int socketCliente;
    struct sockaddr_in servidorAddress, clienteAddress;
    fd_set readSet;   // Conjunto de descriptores de fichero
    int maxDescriptor;
    struct timeval timeout = {0,50000};

    signal(SIGINT,manejarSIGINT);

    // Inicializar la rutina del servidor
    iniciarRutina(&socketServidor, &servidorAddress);

    // Ciclo principal del servidor
    while (1) 
    {
        // Actualizar el conjunto de descriptores de fichero
        actualizarConjunto(&readSet, &maxDescriptor, &socketServidor);

        // Comprobar la actividad en los descriptores
        comprobarActividad(&readSet, &maxDescriptor, &timeout);

        // Comprobar si hay nuevas conexiones
        comprobarNuevaConexion(&readSet, &socketServidor, &socketCliente, &clienteAddress);

        // Responder a mensajes de los clientes existentes
        responderMensajeServidor(&readSet);
    }

    // Cerrar el socket del servidor al final (opcional si deseas agregar una forma de finalizar)
    cerrarSocket(&socketServidor);

    return 0;
}
