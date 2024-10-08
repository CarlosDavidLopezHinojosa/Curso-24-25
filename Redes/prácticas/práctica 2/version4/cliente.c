#include "cliente.h"

void inicializarSocketCliente(int * cliente_socket, struct sockaddr_in * servidor_addr) 
{
    *cliente_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (*cliente_socket < 0) error("Error al crear el socket");

    servidor_addr->sin_family = AF_INET;
    servidor_addr->sin_port = htons(PUERTO);

    const char * servidor_ip = "127.0.0.1";
    if (inet_pton(AF_INET, servidor_ip, &servidor_addr->sin_addr) <= 0) error("Dirección IP no válida o no soportada");

    if (connect(*cliente_socket, (struct sockaddr *)servidor_addr, sizeof(*servidor_addr)) < 0) error("Error al conectar con el servidor");
    
    printf("+Ok. Usuario Conectado\n");
}

void enviarAutenticacion(int * cliente_socket, Usuario * user)
{
    printf("Ingrese usuario: ");
    scanf("%s", user->nombreUsuario);
    printf("Ingrese password: ");
    scanf("%s", user->credendiales);
    
    user->socket = *cliente_socket;

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
            if (strstr(msg->peticion, "COMENZAR-PARTIDA") != NULL) 
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