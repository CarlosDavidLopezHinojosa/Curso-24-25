#include "estructuras.h"


void imprimirUsuario(Usuario * usuario)
{
    printf("(%s) ",usuario->nombre);
}

void iniciarCola(Cola * cola) 
{
    cola->size = 0;
    cola->posicionInsertar = 0;
    for (int i = 0; i < MAX_USUARIOS; i++) 
        cola->cola[i] = NULL;
}

int estaVacia(Cola * cola) 
{
    return cola->size == 0;
}

void push(Cola * cola, Usuario * nuevoUsuario) 
{
    if (cola->size < MAX_USUARIOS) 
    {
        cola->cola[cola->posicionInsertar] = nuevoUsuario;
        cola->posicionInsertar = (cola->posicionInsertar + 1) % MAX_USUARIOS;
        cola->size++;
    } 
    else 
    {
        printf("La cola está llena, no se puede insertar más usuarios.\n");
    }
}

Usuario * pop(Cola * cola) 
{
    if (!estaVacia(cola)) 
    {
        int posicionRemover = (cola->posicionInsertar - cola->size + MAX_USUARIOS) % MAX_USUARIOS;
        Usuario *usuarioRemovido = cola->cola[posicionRemover];
        cola->cola[posicionRemover] = NULL;
        cola->size--;
        return usuarioRemovido;
    } 
    else 
    {
        printf("La cola está vacía, no hay usuarios para remover.\n");
        return NULL;
    }
}

void liberarCola(Cola * cola)
{
    while (!estaVacia(&cola)) 
    {
        Usuario *removido = pop(&cola);
        if (removido != NULL) 
        {
            free(removido);
        }
    }
}

void imprimirCola(Cola * cola) 
{
    printf("Estado de la cola: \n");
    if (estaVacia(cola)) 
    {
        printf("La cola está vacía.\n");
        return;
    }
    
    int posicionActual = (cola->posicionInsertar - cola->size + MAX_USUARIOS) % MAX_USUARIOS;
    for (int i = 0; i < cola->size; i++) 
        printf("(Usuario %d: %s) ", i + 1, cola->cola[(posicionActual + i) % MAX_USUARIOS]->nombre);

    printf("\nTotal de usuarios en la cola: %d\n", cola->size);
}

int hayDosUsuariosEsperando(Cola * cola, Usuario ** usuario1, Usuario ** usuario2) 
{
    if (cola->size >= 2) 
    {
        *usuario1 = pop(cola);
        *usuario2 = pop(cola);
        
        return 1;  
    }
    return 0; 
}

