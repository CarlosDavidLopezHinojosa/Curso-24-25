#include "COMMON.h"
#include <time.h>

#define PUERTO 8080
#define MAX_USUARIOS 20

Cola * colaPartida;
Usuario * usuarios;

void error(const char *msg) 
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void inicializarEstructuras() 
{
    colaPartida = crear_cola();
    usuarios = (Usuario *) malloc(sizeof(Usuario) * MAX_USUARIOS);

    for (int i = 0; i < MAX_USUARIOS; i++) 
        usuarios[i] = (Usuario) {0, 0, 0, NULL, NULL, NULL};
}

void iniciarSocketServidor(int * socketServidor, struct sockaddr_in * servidorAddress)
{
    *socketServidor = socket(AF_INET, SOCK_STREAM, 0);
    if (*socketServidor < 0) error("Error al crear el socket");

    servidorAddress->sin_family = AF_INET;
    servidorAddress->sin_addr.s_addr = INADDR_ANY;
    servidorAddress->sin_port = htons(PUERTO);

    if (bind(*socketServidor, (struct sockaddr *) servidorAddress, sizeof(*servidorAddress)) < 0) 
        error("Error al hacer bind del Servidor");

    if (listen(*socketServidor, 5) < 0) 
        error("Error al hacer listen del Servidor");

    printf("Escuchando en el puerto %d\n", PUERTO);
}

void refrescarConjunto(fd_set * readSet, int * max, int * socketServidor)
{
    FD_ZERO(readSet);
    FD_SET(*socketServidor, readSet);
    *max = *socketServidor;

    for (size_t i = 0; i < MAX_USUARIOS; i++)
    {
        int * socketUsuario = &usuarios[i].socket;
        if (*socketUsuario > 0)
        {
            FD_SET(*socketUsuario, readSet);

            if (*socketUsuario > *max)
                *max = *socketUsuario;
        }
    }
}

void verActividadSockets(fd_set * readSet, int * max, timeval * timeout, int * socketServidor)
{
    int elegido = select(*max + 1, readSet, NULL, NULL, timeout);
    if ((elegido < 0) && (errno != EINTR)) error("Error en el select");
}

void comprobarNuevaConexion(fd_set * readSet, int * socketServidor, int * socketCliente, struct sockaddr_in * clienteAddress )
{
    if (FD_ISSET(*socketServidor, readSet))
    {
        socklen_t len = sizeof(*clienteAddress);
        *socketCliente = accept(*socketServidor, (struct sockaddr *) clienteAddress, &len);

        if (*socketCliente < 0) error("Error en accept");
        printf("Nueva conexión aceptada de %d\n", *socketCliente);
        
        // Encontrar un slot vacío para el nuevo usuario
        for (int i = 0; i < MAX_USUARIOS; i++) 
        {
            if (usuarios[i].socket == 0) 
            {
                usuarios[i].socket = *socketCliente;
                usuarios[i].validado = 0;
                usuarios[i].jugando = 0;
                break;
            }
        }
    }
}

void interpretarComandos(Mensaje * msg)
{
    if (strcmp(msg->peticion, "CREDENCIALES") == 0)
    {
        msg->usuario.validado = 1;
        printf("Usuario %s autenticado correctamente.\n", msg->usuario.nombreUsuario);
        // Aquí se puede añadir lógica para validar las credenciales
    }
    else if (strcmp(msg->peticion, "INICIAR-PARTIDA") == 0)
    {
        printf("El usuario %s ha solicitado iniciar una partida.\n", msg->usuario.nombreUsuario);
        encolar(colaPartida, &(msg->usuario));
    }
    else if (strcmp(msg->peticion, "PEDIR-CARTA") == 0)
    {
        printf("El usuario %s ha pedido una carta.\n", msg->usuario.nombreUsuario);
        // Aquí puedes añadir la lógica para repartir una carta
    }
    else
    {
        printf("Comando no reconocido: %s\n", msg->peticion);
    }
}

void manejarComandos(fd_set * readSet)
{
    for (size_t i = 0; i < MAX_USUARIOS; i++)
    {
        int * socketUsuario = &(usuarios[i].socket);
        if (FD_ISSET(*socketUsuario, readSet))
        {
            printf("Holaaa");
            Mensaje msg;
            int readVal = read(*socketUsuario, (Mensaje *)&msg, sizeof(msg));
            printf("Peticion: %s User: %s",msg.peticion,msg.usuario.nombreUsuario);
            if (readVal == 0)
            {
                close(*socketUsuario);
                *socketUsuario = 0;
                printf("Usuario %s desconectado.\n", usuarios[i].nombreUsuario);
            }
            else
            {
                if (*socketUsuario != msg.usuario.socket) 
                    error("Error: no se está trabajando con el mismo usuario");
                
                msg.peticion[readVal] = '\0';
                interpretarComandos(&msg);
            }
        }
    }
}

void liberarEstructuras(int * socketServidor)
{
    liberar_cola(colaPartida);
    free(usuarios);
    close(*socketServidor);
}

int main()
{
    int socketServidor, socketCliente, max;
    struct sockaddr_in servidorAddress, clienteAddress;
    fd_set readSet;
    timeval timeout = {1, 0};

    inicializarEstructuras();
    iniciarSocketServidor(&socketServidor, &servidorAddress);

    while (1)
    {
        refrescarConjunto(&readSet, &max, &socketServidor);
        verActividadSockets(&readSet, &max, &timeout, &socketServidor);
        comprobarNuevaConexion(&readSet, &socketServidor, &socketCliente, &clienteAddress);
        manejarComandos(&readSet);
    }

    liberarEstructuras(&socketServidor);
    return 0;
}
