#include <iostream>
#include "entero.hpp"

using namespace std;

int main() 
{
    int opcion;
    Entero e1, e2, resultado;

    do 
    {
        cout << "\nMenú de Operaciones" << endl;
        cout << "1. Sumar" << endl;
        cout << "2. Multiplicar" << endl;
        cout << "3. Factorial" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) 
        {
            case 1:
                cout << "\nIngrese el primer número: ";
                cin >> e1;
                cout << "Ingrese el segundo número: ";
                cin >> e2;
                resultado = e1 + e2;
                cout << "El resultado de la suma es: " << resultado << endl;
                break;
            case 2:
                cout << "\nIngrese el primer número: ";
                cin >> e1;
                cout << "Ingrese el segundo número: ";
                cin >> e2;
                resultado = e1 * e2;
                cout << "El resultado de la multiplicación es: " << resultado << endl;
                break;
            case 3:
                cout << "\nIngrese un número para calcular el factorial: ";
                cin >> e1;
                resultado = e1.factorial();
                cout << "El factorial es: " << resultado << endl;
                break;
            case 4:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción inválida. Intente de nuevo." << endl;
                break;
        }
    } while (opcion != 4);

    return 0;
}
