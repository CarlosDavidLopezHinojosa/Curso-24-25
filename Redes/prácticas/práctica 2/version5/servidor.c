#include "servidor.h"

Usuario usuarios[MAX_USUARIOS];
Cola * cola;

Cola * crearCola() 
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

int estaVacia(Cola * cola) 
{
    return (cola->frente == NULL);
}

void imprimirCola(Cola * cola)
{
    if (cola == NULL || cola->frente == NULL) 
    {
        printf("La cola está vacía.\n");
        return;
    }

    Nodo *actual = cola->frente;
    printf("Usuarios en la cola:\n");
    while (actual != NULL) 
    {
        Usuario *user = actual->user;
        printf("Usuario: %s, Validado: %d, Jugando: %d\n", 
                user->nombreUsuario, user->validado, user->jugando);
        actual = actual->siguiente;
    }
    printf("\n");
}

void liberarCola(Cola * cola) 
{
    while (!estaVacia(cola)) 
    {
        desencolar(cola);
    }
    free(cola);
}




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

    cola = crearCola();
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
    else if (strcmp("INICIAR-PARTIDA",mensaje->peticion) == 0)
    {
        encolar(cola,&(mensaje->usuario));
        printf("Se ha metido en la cola de espera a %s\n",mensaje->usuario.nombreUsuario);
        imprimirCola(cola);
        return (Mensaje){"SE TE HA METIDO EN LA COLA DE ESPERA"};
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

int buscarSocket(Usuario * usuario)
{
    for (size_t i = 0; i < MAX_USUARIOS; i++)
        if (strcmp(usuarios[i].nombreUsuario,usuario->nombreUsuario) == 0)
            return usuarios[i].socket;
    return -1;
    
}

void iniciarPartida()
{
    if (cola->frente != NULL && cola->frente->anterior != NULL)
    {
        Usuario * usuario1 = desencolar(cola);
        Usuario * usuario2 = desencolar(cola);

        Mensaje mensaje1 = (Mensaje) {"PUEDES JUGAR",*usuario1};
        Mensaje mensaje2 = (Mensaje) {"PUEDES JUGAR",*usuario2};


        enviarMensaje(&(usuario1->socket),&mensaje1);
        enviarMensaje(&(usuario2->socket),&mensaje2);
    }
}
