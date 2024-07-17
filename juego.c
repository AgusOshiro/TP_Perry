#include <stdio.h>
#include "feria.h"
#include <stdlib.h>
#include <time.h>

#define ARRIBA 'W'
#define IZQUIERDA 'A'
#define ABAJO 'S'
#define DERECHA 'D'
#define CAMUFLARSE 'Q'
#define ARRIBA_MINUSCULA 'w'
#define IZQUIERDA_MINUSCULA 'a'
#define ABAJO_MINUSCULA 's'
#define DERECHA_MINUSCULA 'd'
#define CAMUFLARSE_MINUSCULA 'q'
#define PERRY_ESTA_VIVO 0

void pedir_letra(char* accion){
    scanf(" %c", &(*accion)); 
    while((*accion) != ARRIBA && (*accion) != ARRIBA_MINUSCULA && (*accion) != IZQUIERDA && (*accion) != IZQUIERDA_MINUSCULA && (*accion) != ABAJO && (*accion) != ABAJO_MINUSCULA && (*accion) != DERECHA && (*accion) != DERECHA_MINUSCULA && (*accion) != CAMUFLARSE && (*accion) != CAMUFLARSE_MINUSCULA){
        scanf(" %c", &(*accion));
        printf("Por favor, Ingrese un movimiento valido:");
    }
}

int main(){
    srand((unsigned) time(NULL));
    juego_t juego;
    inicializar_juego(&juego);
    int estado = estado_juego(juego);
    char accion;

    while(estado == PERRY_ESTA_VIVO){ 
        imprimir_terreno(juego);
        pedir_letra(&accion);
        realizar_jugada(&juego,accion);
        estado = estado_juego(juego);
        system("clear");
    }

    return 0;
}