#include "COMMON.h"
#include <arpa/inet.h>

#define PUERTO 8080
#define BUFFER_SIZE 256

void error(const char *msg) 
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void inicializarSocketCliente(int * cliente_socket, struct sockaddr_in * servidor_addr) 
{
    *cliente_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (*cliente_socket < 0) error("Error al crear el socket");

    servidor_addr->sin_family = AF_INET;
    servidor_addr->sin_port = htons(PUERTO);

    const char * servidor_ip = "127.0.0.1";
    if (inet_pton(AF_INET, servidor_ip, &servidor_addr->sin_addr) <= 0) error("Dirección IP no válida o no soportada");

    if (connect(*cliente_socket, (struct sockaddr *)servidor_addr, sizeof(*servidor_addr)) < 0) error("Error al conectar con el servidor");

    printf("Conectado al servidor en %s.\n", servidor_ip);
}

void enviarAutenticacion(int * cliente_socket, Usuario * user)
{
    char username[50], password[50];
    printf("Ingrese usuario: ");
    scanf("%s", username);
    printf("Ingrese password: ");
    scanf("%s", password);

    // Asignar memoria dinámica para las cadenas en el usuario
    user->nombreUsuario = strdup(username);     // Copia del username
    user->credendiales = strdup(password);      // Copia del password

    Mensaje msg = {"CREDENCIALES", *user};

    if (send(*cliente_socket, (Mensaje *) &msg, sizeof(msg), 0) < 0) 
        error("Error al enviar autenticación");

    printf("Autenticación enviada al servidor...\n");
}


void solicitarPartida(int *cliente_socket, Usuario *user) 
{
    Mensaje msg = {"INICIAR-PARTIDA", *user};
    
    printf("Solicitando iniciar partida...\n");
    if (send(*cliente_socket, &msg, sizeof(msg), 0) < 0) error("Error al solicitar partida");
}

void manejarComunicacion(int *cliente_socket, Mensaje *msg)
{
    while (1) 
    {
        int valread = read(*cliente_socket, msg, sizeof(*msg));
        if (valread > 0) 
        {
            printf("Servidor: %s\n", msg->peticion);

            // Verificar si la partida ha comenzado
            if (strstr(msg->peticion, "La partida ha comenzado.") != NULL) 
            {
                printf("La partida ha comenzado. Esperando tu turno...\n");
            }
            else if (strstr(msg->peticion, "Es tu turno") != NULL) 
            {
                // Simular la acción del jugador pidiendo una carta
                printf("Pidiendo carta...\n");
                snprintf(msg->peticion, sizeof(msg->peticion), "PEDIR-CARTA");
                send(*cliente_socket, msg, sizeof(*msg), 0);
            }
        }
        else if (valread == 0) 
        {
            printf("Conexión cerrada por el servidor.\n");
            break;
        }
        else 
        {
            error("Error al leer del servidor");
            break;
        }
    }
}

int main() 
{
    int cliente_socket;
    struct sockaddr_in servidor_addr;
    Usuario user = {0};
    Mensaje msg;

    inicializarSocketCliente(&cliente_socket, &servidor_addr);
    enviarAutenticacion(&cliente_socket, &user);
    //solicitarPartida(&cliente_socket, &user);
    //manejarComunicacion(&cliente_socket, &msg);

    close(cliente_socket);
    return 0;
}
