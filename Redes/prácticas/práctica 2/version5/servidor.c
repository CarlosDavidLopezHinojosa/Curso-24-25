#include "servidor.h"

Usuario usuarios[MAX_USUARIOS];

void iniciarRutina(int * socketServidor, struct sockaddr_in * servidorAddress)
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

void actualizarConjunto(fd_set * readSet, int * max, int * socketServidor)
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

void comprobarActividad(fd_set * readSet, int * max, struct timeval * timeout)
{
    int elegido = select(*max + 1, readSet, NULL, NULL, timeout);
    if ((elegido < 0) && (errno != EINTR)) error("Error en el select");
}

void comprobarNuevaConexion(fd_set * readSet, int * socketServidor, int * socketUsuario, struct sockaddr_in * usuarioAddress )
{
    if (FD_ISSET(*socketServidor, readSet))
    {
        socklen_t len = sizeof(*usuarioAddress);
        *socketUsuario = accept(*socketServidor, (struct sockaddr *) usuarioAddress, &len);

        if (*socketUsuario < 0) error("Error en accept");
        printf("Nueva conexión aceptada de %d\n", *socketUsuario);
        
        // Encontrar un slot vacío para el nuevo usuario
        for (int i = 0; i < MAX_USUARIOS; i++) 
        {
            if (usuarios[i].socket == 0) 
            {
                usuarios[i].socket = *socketUsuario;
                usuarios[i].validado = 0;
                usuarios[i].jugando = 0;
                break;
            }
        }
    }
}

Mensaje interpretarMensajeServidor(Mensaje * mensaje)
{
    if (strcmp("SALUDO", mensaje->peticion) == 0)
    {
        return (Mensaje){"HOLA", mensaje->usuario};
    }

    return (Mensaje) {"PETICION NO ACEPTADA", mensaje->usuario};
}

void responderMensajeServidor(fd_set * readSet)
{
    for (size_t i = 0; i < MAX_USUARIOS; i++)
    {
        int * socketUsuario = &(usuarios[i].socket);
        if (FD_ISSET(*socketUsuario, readSet))
        {
            Mensaje mensaje;
            ssize_t readVal = recibirMensaje(socketUsuario,&mensaje);

            printf("Peticion: %s User: %s\n",mensaje.peticion,mensaje.usuario.nombreUsuario);

            if (readVal == 0)
            {
                cerrarSocket(socketUsuario);
                printf("Usuario %s desconectado.\n", usuarios[i].nombreUsuario);
            }
            else
            {                
                mensaje.peticion[readVal] = '\0';

                Mensaje respuesta = interpretarMensajeServidor(&mensaje);
                enviarMensaje(socketUsuario,&respuesta);
            }
        }
    }
}