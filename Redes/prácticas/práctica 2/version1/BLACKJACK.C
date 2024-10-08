#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CARTAS 11 // Max cartas en mano (siempre menos que 21)

int obtener_valor_carta() {
    int carta = rand() % 13 + 1; // Genera un número entre 1 y 13
    if (carta > 10) return 10;   // J, Q, K valen 10 puntos
    return carta;                // Cartas numéricas valen su número
}

void imprimir_mano(int *mano, int n_cartas) {
    printf("Cartas: ");
    for (int i = 0; i < n_cartas; i++) {
        printf("%d ", mano[i]);
    }
    printf("\n");
}

int puntaje_total(int *mano, int n_cartas) {
    int total = 0, ases = 0;
    for (int i = 0; i < n_cartas; i++) {
        if (mano[i] == 1) ases++;
        total += mano[i];
    }
    while (ases > 0 && total <= 11) {
        total += 10; // El As puede ser 1 o 11
        ases--;
    }
    return total;
}

void jugar(int jugador, int *mano, int *n_cartas) {
    char opcion;
    do {
        imprimir_mano(mano, *n_cartas);
        printf("Puntaje actual: %d\n", puntaje_total(mano, *n_cartas));
        printf("Jugador %d, ¿deseas pedir otra carta (p) o plantarte (s)? ", jugador);
        scanf(" %c", &opcion);
        if (opcion == 'p') {
            mano[*n_cartas] = obtener_valor_carta();
            (*n_cartas)++;
            if (puntaje_total(mano, *n_cartas) > 21) {
                printf("¡Jugador %d se ha pasado!\n", jugador);
                break;
            }
        }
    } while (opcion == 'p');
}

int main() {
    srand(time(0)); // Semilla para la generación aleatoria de cartas
    
    int mano_jugador1[MAX_CARTAS], mano_jugador2[MAX_CARTAS];
    int n_cartas_jugador1 = 2, n_cartas_jugador2 = 2;
    
    // Repartir 2 cartas a cada jugador al inicio
    mano_jugador1[0] = obtener_valor_carta();
    mano_jugador1[1] = obtener_valor_carta();
    mano_jugador2[0] = obtener_valor_carta();
    mano_jugador2[1] = obtener_valor_carta();

    printf("¡Comienza el juego!\n");

    // Turno del jugador 1
    printf("Turno del Jugador 1:\n");
    jugar(1, mano_jugador1, &n_cartas_jugador1);

    // Turno del jugador 2
    printf("Turno del Jugador 2:\n");
    jugar(2, mano_jugador2, &n_cartas_jugador2);

    // Mostrar resultados finales
    int puntaje1 = puntaje_total(mano_jugador1, n_cartas_jugador1);
    int puntaje2 = puntaje_total(mano_jugador2, n_cartas_jugador2);

    printf("\nResultados finales:\n");
    printf("Jugador 1: %d puntos\n", puntaje1);
    printf("Jugador 2: %d puntos\n", puntaje2);

    if (puntaje1 > 21 && puntaje2 > 21) {
        printf("Ambos jugadores se han pasado. ¡Empate!\n");
    } else if (puntaje1 > 21) {
        printf("Jugador 1 se pasó. ¡Jugador 2 gana!\n");
    } else if (puntaje2 > 21) {
        printf("Jugador 2 se pasó. ¡Jugador 1 gana!\n");
    } else if (puntaje1 > puntaje2) {
        printf("¡Jugador 1 gana!\n");
    } else if (puntaje2 > puntaje1) {
        printf("¡Jugador 2 gana!\n");
    } else {
        printf("¡Es un empate!\n");
    }

    return 0;
}
