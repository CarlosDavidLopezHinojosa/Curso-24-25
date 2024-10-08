#include "servidor.h"


Cola * colaPartida;
Usuario usuarios [MAX_USUARIOS];
Partida partidas [MAX_PARTIDAS];

Cola * crear_cola() 
{
    Cola *cola = (Cola*)malloc(sizeof(Cola));
    cola->frente = NULL;
    cola->final = NULL;
    return cola;
}

void encolar(Cola * cola, Usuario * user) 
{
    Nodo *nuevo_nodo = (Nodo*)malloc(sizeof(Nodo));
    nuevo_nodo->user = user;
    nuevo_nodo->siguiente = NULL;

    if (cola->final == NULL) 
    {  // Si la cola está vacía
        nuevo_nodo->anterior = NULL;
        cola->frente = nuevo_nodo;
        cola->final = nuevo_nodo;
    } 
    else 
    {  // Agrega al final
        nuevo_nodo->anterior = cola->final;
        cola->final->siguiente = nuevo_nodo;
        cola->final = nuevo_nodo;
    }
}

Usuario * desencolar(Cola * cola) 
{
    if (cola->frente == NULL) 
    {  // Cola vacía
        return NULL;
    }

    Nodo *nodo_eliminar = cola->frente;
    Usuario *user = nodo_eliminar->user;

    cola->frente = nodo_eliminar->siguiente;

    if (cola->frente == NULL) 
    {  // Si la cola quedó vacía
        cola->final = NULL;
    } 
    else 
    {
        cola->frente->anterior = NULL;
    }

    free(nodo_eliminar);  // Libera el nodo
    return user;  // Retorna el usuario desencolado
}

int esta_vacia(Cola * cola) 
{
    return (cola->frente == NULL);
}

void liberar_cola(Cola * cola) 
{
    while (!esta_vacia(cola)) 
    {
        desencolar(cola);
    }
    free(cola);
}

void inicializarEstructuras() 
{
    colaPartida = crear_cola();

    for (int i = 0; i < MAX_USUARIOS; i++)
        usuarios[i] = (Usuario) {0, 0, 0};
        
    for (size_t i = 0; i < MAX_PARTIDAS; i++)
        partidas[i] = (Partida) {NULL,NULL,1};
    
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

void verActividadSockets(fd_set * readSet, int * max, struct timeval * timeout, int * socketServidor)
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
            Mensaje msg;
            int readVal = read(*socketUsuario, (Mensaje *)&msg, sizeof(msg));
            printf("Peticion: %s User: %s\n",msg.peticion,msg.usuario.nombreUsuario);
            if (readVal == 0)
            {
                close(*socketUsuario);
                *socketUsuario = 0;
                printf("Usuario %s desconectado.\n", usuarios[i].nombreUsuario);
            }
            else
            {                
                msg.peticion[readVal] = '\0';
                interpretarComandos(&msg);
            }
        }
    }
}

void comenzarPartida()
{

    if (colaPartida->frente != NULL && colaPartida->frente->anterior != NULL)
    {
        Usuario * user1 = desencolar(colaPartida);
        Usuario * user2 = desencolar(colaPartida);

        Mensaje msg1 = {"COMENZAR-PARTIDA", *user1};
        Mensaje msg2 = {"COMENZAR-PARTIDA", *user2};

        printf("Que comience la partida de %s y %s\n",user1->nombreUsuario,user2->nombreUsuario);
        if (send(user1->socket, &msg1, sizeof(msg1), 0) < 0) error("Error al comenzar la partida del jugador 1");
        if (send(user1->socket, &msg2, sizeof(msg2), 0) < 0) error("Error al comenzar la partida del jugador 2");

        for (size_t i = 0; i < MAX_PARTIDAS; i++)
        {
            if (partidas[i].estaLibre == 1)
            {
                partidas[i] = (Partida) {user1,user2,0};
                break;
            }
        }   
    }
}

void liberarEstructuras(int * socketServidor)
{
    liberar_cola(colaPartida);
    close(*socketServidor);
}