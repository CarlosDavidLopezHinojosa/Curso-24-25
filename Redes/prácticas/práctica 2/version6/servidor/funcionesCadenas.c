#include "funcionesCadenas.h"

int cadenasIguales(char * cadena1, char * cadena2) 
{
    return strcmp(cadena1, cadena2) == 0;
}

int cadenasIgualesN(char * cadena1, char * cadena2, int n) 
{
    return strncmp(cadena1, cadena2, n) == 0;
}

void copiarCadena(char * cadena1, char * cadena2) 
{
    strcpy(cadena2, cadena1);
}

void saberPeticion(Paquete * paquete, char * peticion) 
{
    if (cadenasIgualesN(paquete->peticion,"INICIAR-PARTIDAD",17))
    {
        copiarCadena("INICIAR-PARTIDAD",peticion);
    }
    else if (cadenasIgualesN(paquete->peticion,"PLANTARSE",10))
    {
        copiarCadena("PLANTARSE",peticion);
    }
    else if (cadenasIgualesN(paquete->peticion,"REGISTRO",9))
    {
        copiarCadena("REGISTRO",peticion);
    }
    
    
    
}

void regitrarUsuario(Paquete * paquete, Usuario * usuario) 
{

}
