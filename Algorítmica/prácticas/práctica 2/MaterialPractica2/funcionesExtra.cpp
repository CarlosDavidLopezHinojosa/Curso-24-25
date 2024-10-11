#include "entero.hpp"


int Entero::maxTam() const
{
    return tamanoMaximo_;
}


Entero& Entero::operator-(const Entero &e) const
{
    // Crear los dos enteros locales
    Entero e1 = *this;
    Entero e2 = e;

    // Comprobamos el tamaño de los enteros y añadimos ceros si es necesario
    if (e2.size() > e1.size())
    {
        e1.agregarCerosDelante(e2.size() - e1.size());
    }
    else if(e2.size() < e1.size())
    {
        e2.agregarCerosDelante(e1.size() - e2.size());
    }

    // Variables auxiliares para los strings y el resultado
    string resultado;
    string c1 = e1.getString();
    string c2 = e2.getString();

    // Inicializamos el borrow a 0
    int borrow = 0;

    // Recorremos los dígitos desde el final (dígito menos significativo)
    for (int i = c1.size() - 1; i >= 0; --i)
    {   
        // Realizamos la resta considerando el borrow
        int diff = (c1[i] - '0') - (c2[i] - '0') - borrow;

        // Si diff es negativo, necesitamos pedir prestado
        if (diff < 0)
        {
            diff += 10;  // Sumamos 10 para ajustar el dígito
            borrow = 1;  // Establecemos el borrow para la siguiente posición
        }
        else
        {
            borrow = 0;  // Si no hay borrow, lo reiniciamos
        }

        // Insertamos el dígito de resultado
        resultado.insert(0, 1, diff + '0');
    }

    // Si hay borrow restante al final, significa que e1 < e2 y el resultado debe ser negativo
    if (borrow == 1)
    {
        throw std::invalid_argument("Resultado negativo: no se permiten restas negativas entre enteros en esta implementación.");
    }

    // Quitamos ceros no significativos
    Entero result(resultado);
    result.quitarCerosNoSignificativos();

    return *(new Entero(result)); 
}
