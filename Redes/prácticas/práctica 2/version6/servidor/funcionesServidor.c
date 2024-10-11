#include "funcionesServidor.h"


void error(const char * mensaje)
{
    perror(mensaje);
    exit(EXIT_FAILURE);
}

ssize_t enviarPaquete(int * socketDestino, Paquete * paquete)
{
    ssize_t s = send(*socketDestino,(Paquete *) paquete, sizeof(*paquete),0); 
    if (s < 0) error("Error al enviar un Paquete");
    return s;
}

ssize_t recibirPaquete(int * socketOrigen, Paquete * paquete )
{   
    ssize_t r = read(*socketOrigen,(Paquete *) paquete, sizeof(*paquete));
    if (r < 0) error("Error al recibir un mensaje");
    return r;
}

void cerrarSocket(int * socket)
{
    close(*socket);
    *socket = 0;
}




void iniciarRutina(Usuario * usuarios, Cola * cola, int * socketServidor, struct sockaddr_in * servidorAddress)
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

    usuarios = (Usuario *) malloc(sizeof(Usuario) * MAX_USUARIOS);
    iniciarCola(cola);
}

void actualizarConjunto(Usuario * usuarios, fd_set * readSet, int * max, int * socketServidor)
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

void comprobarNuevaConexion(Usuario * usuarios, fd_set * readSet, int * socketServidor, int * socketUsuario, struct sockaddr_in * usuarioAddress )
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
                break;
            }
        }
    }
}