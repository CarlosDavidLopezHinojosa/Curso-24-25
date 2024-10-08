#include "usuario.h"

void conectarAlServidor(int * socketUsuario, struct sockaddr_in * servidorAddress)
{
    *socketUsuario = socket(AF_INET, SOCK_STREAM, 0);
    if (*socketUsuario < 0) error("Error al crear el socket");

    servidorAddress->sin_family = AF_INET;
    servidorAddress->sin_port = htons(PUERTO);

    const char * servidor_ip = "127.0.0.1";
    if (inet_pton(AF_INET, servidor_ip, &servidorAddress->sin_addr) <= 0) error("Dirección IP no válida o no soportada");

    if (connect(*socketUsuario, (struct sockaddr *)servidorAddress, sizeof(*servidorAddress)) < 0) error("Error al conectar con el servidor");

    printf("+Ok: Usuario conectado al servidor\n");
} 

void rellenarDatos(Usuario * usuario, int * socketUsuario)
{
    printf("Por favor ingrese su nombre se usuario\n");
    scanf("%s",usuario->nombreUsuario);

    printf("Por favor ingrese su contraseña\n");
    scanf("%s",usuario->credendiales);

    usuario->socket = *socketUsuario;
    usuario->validado = 0;
    usuario->jugando = 0;
}

void responderMensajeUsuario()
{
    
}
