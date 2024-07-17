#include "feria.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

//PERRY
const char PERRY = 'P';
const int VIDAS_PERRY = 3;
const int ENERGIA_PERRY = 100;
const bool CAMUFLAJE_PERRY = false;
const int ENERGIA_PERDIDA = 10;
const int ENERGIA_PERDIDA_POR_ROBOT = 5;
//MOVIMIENTOS
const char ARRIBA = 'W';
const char IZQUIERDA = 'A';
const char ABAJO = 'S';
const char DERECHA = 'D';
const char CAMUFLARSE = 'Q';
const char ARRIBA_MINUSCULA = 'w';
const char IZQUIERDA_MINUSCULA = 'a';
const char ABAJO_MINUSCULA = 's';
const char DERECHA_MINUSCULA = 'd';
const char CAMUFLARSE_MINUSCULA = 'q';
const int POSICION_MINIMA = 0;
const int POSICION_MAXIMA = 19;
const int MOVIMIENTOS_INICIALES = 0;
//FAMILIARES
const char PHINEAS = 'H';
const char FERB = 'F';
const char CANDACE = 'C';
const int POSICION_PHINEAS = 0;
const int POSICION_FERB = 1;
const int POSICION_CANDACE = 2;
const int FAMILIARES_INICIALES = 3;
const int DISTANCIA_DEL_FAMILIAR = 1;
//MANHATTAN
const int ABSOLUTO = -1;
//OBSTACULO
const char BOMBAS = 'B';
const int BOMBAS_INICIALES = 10;
const bool BOMBAS_DESACTIVADAS = false;
const int TIEMPO_MINIMO = 50;
const int TIEMPO_MAXIMO = 251;
//HERRAMIENTAS
const char SOMBREROS = 'S';
const char GOLOSINAS = 'G';
const int HERRAMIENTAS_INICIALES = 8;
const int CANT_SOMBREROS = 3;
const int EFECTO_GOLOSINA = 20;
//ROBOTS
const char ROBOTS = 'R';
const int ROBOTS_INICIALES = 0;
const int DISTANCIA_DEL_ROBOTS = 2;
const int ENERGIA_NECESARIA = 5;
//TERRENO
const char VACIO = ' ';
const int MAX_FILAS = 20;
const int MAX_COLUMNAS = 20;
const int MAX_COORDENADAS = 400;
//ESTADO DEL JUEGO
const int GANADO = 1;
const int PERDIDO = -1;
const int JUGANDO = 0;
const int PERRY_MUERTO = 0;
// ------- FUNCIONES DE INICIALIZAR_JUEGO() --------
/*
PRE:-
POST:Carga los datos a la variable perry y le asigna una posicion en el terreno
*/
personaje_t inicializa_perry(){
    personaje_t perry;
    perry.vida = VIDAS_PERRY;
    perry.energia = ENERGIA_PERRY;
    perry.camuflado = CAMUFLAJE_PERRY;
    perry.posicion.fil = rand() % MAX_FILAS;
    perry.posicion.col = rand() % MAX_COLUMNAS;
    return perry;
}
 
/*
PRE:-
POST:Carga el dato ingresado a las variables de las bombas y les asigna una posicion en el terreno
*/
bomba_t inicializa_bomba(){
    bomba_t bomba;
    bomba.posicion.fil = rand() % MAX_FILAS;
    bomba.posicion.col = rand() % MAX_COLUMNAS;
    bomba.timer = rand() % TIEMPO_MAXIMO + TIEMPO_MINIMO; 
    bomba.desactivada = BOMBAS_DESACTIVADAS;
    return bomba;
}
/* 
PRE:Tipo_de_herramienta debe ser G o S
POST:Carga el dato ingresado a las variables de las herramientas y les asigna una posicion en el terreno
*/
herramienta_t inicializa_herramientas(char tipo_de_herramienta){
    herramienta_t herramienta;
    herramienta.posicion.fil = rand() % MAX_FILAS;
    herramienta.posicion.col = rand() % MAX_COLUMNAS;
    herramienta.tipo = tipo_de_herramienta;
    return herramienta;
}   


/*
PRE:inicial_familiar debe ser H F o C
POST:carga el dato ingresado a las variables de cada familiar y les asigna una posicion en el terreno
*/
familiar_t inicializa_familiar(char inicial_familiar){
    familiar_t familiar;
    familiar.posicion.fil = rand() % MAX_FILAS;
    familiar.posicion.col = rand() % MAX_COLUMNAS;
    familiar.inicial_nombre = inicial_familiar;
    familiar.sentido = DERECHA;
    return familiar;
}

/*
PRE:-
POST:Le da al robot una fila y una columna aleatoria
*/
coordenada_t inicializa_robots(){
    coordenada_t robot;
    robot.fil = rand() % MAX_FILAS;
    robot.col = rand() % MAX_COLUMNAS;
    return robot;
}

/*
PRE:Se ingresa un vector de coordenada_t y su tope, inicializado con la coordenada de perry, y una coordenada_t
POST:Verifica que la coordenada ingresada no se encuentre en el vector de coordenadas_t
*/
bool verificar_coordenadas(coordenada_t vector_coordenadas[MAX_COORDENADAS], int tope_coordenadas, coordenada_t coordenada){
    bool esta_ocupada = false;
    for(int i=0; i<tope_coordenadas;i++){
        if(vector_coordenadas[i].fil == coordenada.fil && vector_coordenadas[i].col == coordenada.col){
            esta_ocupada = true;
        }
    }
    return esta_ocupada;
}
/*
PRE:Se le ingresa un vector de coordenada_t y su tope
POST:Agrega las posiciones verificadas al vector de coordenadas y devuelve la bombas con posiciones validas
*/
bomba_t cargar_vector_coordenadas_bombas(coordenada_t vector_coordenadas[MAX_COORDENADAS], int* tope_coordenadas){
    bool ocupado = false;
    bomba_t bomba_validada;
    do{
        bomba_validada = inicializa_bomba();
        ocupado = verificar_coordenadas(vector_coordenadas, *tope_coordenadas, bomba_validada.posicion);
    }while(ocupado);
    vector_coordenadas[*tope_coordenadas] = bomba_validada.posicion;
    *tope_coordenadas +=1;
    return bomba_validada;
}

/*
PRE:Se le ingresa un vector de coordenada_t y su tope
POST:Agrega las posiciones verificadas al vector de coordenadas y devuelve una herramienta con una posicion valida
*/
herramienta_t cargar_vector_coordenadas_herramientas(coordenada_t vector_coordenadas[MAX_COORDENADAS], int* tope_coordenadas){
    bool ocupado = false;
    herramienta_t herramienta_validada;
    do{
        herramienta_validada = inicializa_herramientas(SOMBREROS);
        ocupado = verificar_coordenadas(vector_coordenadas, *tope_coordenadas, herramienta_validada.posicion);
    }while(ocupado);
    vector_coordenadas[*tope_coordenadas] = herramienta_validada.posicion;
    *tope_coordenadas +=1;
    return herramienta_validada;
}
/*
PRE:Se le ingresa un vector de coordenada_t y su tope
POST:Agrega las posiciones verificadas al vector de coordenadas y devuelve un familiar con una posicion valida
*/
familiar_t cargar_vector_coordenadas_familiares(coordenada_t vector_coordenadas[MAX_COORDENADAS], int* tope_coordenadas){
    bool ocupado = false;
    familiar_t familiar_validado;
    do{
        familiar_validado = inicializa_familiar(PHINEAS);
        ocupado = verificar_coordenadas(vector_coordenadas, *tope_coordenadas, familiar_validado.posicion);
    }while(ocupado);
    vector_coordenadas[*tope_coordenadas] = familiar_validado.posicion;
    *tope_coordenadas +=1;
    return familiar_validado;
}
/*
PRE:Se debe ingresar un vector del tipo bomba_t y su tope = 10
POST:Se llena ese vector con bombas
*/
void llenar_vector_bombas(bomba_t vector_bombas[MAX_BOMBAS],int tope_bombas,coordenada_t vector_coordenadas[], int* tope_coordenadas){
    for(int i=0; i< tope_bombas;i++){
        vector_bombas[i] = cargar_vector_coordenadas_bombas(vector_coordenadas, tope_coordenadas);
    }

}

/*
PRE:Se debe ingresar un vector del tipo herramientas_t y su tope = 8
POST:Llena el vector de herramientas con las herramientas correspondientes G o S
*/
void llenar_vector_herramientas(herramienta_t vector_herramientas[MAX_HERRAMIENTAS], int tope_herramientas,coordenada_t vector_coordenadas[], int* tope_coordenadas){
    for(int i=0; i<tope_herramientas; i++){
        vector_herramientas[i] = cargar_vector_coordenadas_herramientas(vector_coordenadas,tope_coordenadas);
        if(i >= CANT_SOMBREROS){
            vector_herramientas[i].tipo = GOLOSINAS;
        }
    }
}

/*
PRE:Se debe ingresar el vector del tipo familiar_t y su tope = 3
POST:llena ese vector con cada familiar de perry
*/
void llenar_vector_familiares(familiar_t vector_familiares[MAX_FAMILIARES], int tope_familiares, coordenada_t vector_coordenadas[], int* tope_coordenadas){
    for(int i=0; i<tope_familiares; i++){
        vector_familiares[i] = cargar_vector_coordenadas_familiares(vector_coordenadas,tope_coordenadas);
        if(i==POSICION_FERB){ 
            vector_familiares[i].inicial_nombre = FERB;
            vector_familiares[i].sentido = IZQUIERDA;
        }else if(i==POSICION_CANDACE){
            vector_familiares[i].inicial_nombre = CANDACE;
            vector_familiares[i].sentido = ARRIBA;
        }
    }   
}

// ------ FUNCIONES DE REALIZAR_JUGADA() -------

/*
PRE:Recibe un familiar_t y un personaje_t
POST:Calcula la distancia manhattan entre perry y los familiares
*/
int distancia_manhattan(coordenada_t primer_coordenada, coordenada_t segunda_coordenada){
    int distancia_filas = primer_coordenada.fil - segunda_coordenada.fil;
    int distancia_columnas = primer_coordenada.col - segunda_coordenada.col;    
    if(distancia_filas < 0){         
        distancia_filas = (distancia_filas * (-1));
    }
    if(distancia_columnas < 0){
        distancia_columnas = (distancia_columnas * (-1));

    }    
    int distancia_total = distancia_filas + distancia_columnas;    
    return distancia_total;
}

/*
PRE:Recibe un juego_t por referencia e inicializado
POST:Cuando perry pisa las bombas y (camuflado == false) se desactivan las bombas
*/
void desactivar_bombas(bomba_t vector_bombas[MAX_BOMBAS],int tope_bombas, personaje_t* perry){  
    int i=0;
    int bomba_a_desactivar;
    bool perry_pisa_bomba = false;
    while((i<tope_bombas && !(perry_pisa_bomba))){
        if(vector_bombas[i].posicion.fil == perry->posicion.fil && vector_bombas[i].posicion.col == perry->posicion.col){
            bomba_a_desactivar = i;
            perry_pisa_bomba = true;
            if(perry_pisa_bomba && perry->camuflado == false){
                if(perry->energia >= ENERGIA_PERDIDA){
                    perry->energia -= ENERGIA_PERDIDA;
                    vector_bombas[bomba_a_desactivar].desactivada = true;
                }
            }
        }
        i ++;
    }
}

/*
PRE:Recibe el vector bombas, su tope y el robot a verificar
POST:Verifica que la coordenada del robot no coincida con ninguna coordenada de las bombas
*/
bool verificar_coordenadas_robots_bombas(bomba_t vector_bombas[MAX_BOMBAS],int tope_bombas, coordenada_t robot){
    bool ocupado = false;
    int i=0;
    while(!ocupado && i<tope_bombas){ 
        if(vector_bombas[i].posicion.fil == robot.fil && vector_bombas[i].posicion.col == robot.col){
            ocupado = true;
        }
        i++;
    }
    return ocupado;
}

/*
PRE:Recibe el vector herramientas, su tope y el robot a verificar
POST:Verifica que la coordenada del robot no coincida con ninguna de las herramientas
*/
bool verificar_coordenadas_robots_herramientas(herramienta_t vector_herramientas[MAX_HERRAMIENTAS],int tope_herramientas, coordenada_t robot){
    bool ocupado = false;
    int i=0;
    while(!ocupado && i<tope_herramientas){ 
        if(vector_herramientas[i].posicion.fil == robot.fil && vector_herramientas[i].posicion.col == robot.col){
            ocupado = true;
        }
        i++;
    }
    return ocupado;
}

/*
PRE:Recibe el vector familiares, su tope y el robot a verificar
POST:Verifica que la coordenada del robot no coincida con ninguna de los familiares
*/
bool verificar_coordenadas_robots_familiares(familiar_t vector_familiares[MAX_FAMILIARES],int tope_familiares, coordenada_t robot){
    bool ocupado = false;
    int i=0;
    while(!ocupado && i<tope_familiares){ 
        if(vector_familiares[i].posicion.fil == robot.fil && vector_familiares[i].posicion.col == robot.col){
            ocupado = true;
        }
        i++;
    }
    return ocupado;
}

/*
PRE:Recibe un juego_t inicializado
POST:Devuelve una coordenada_t y verifica que esa coordenada no coincida con ninguna de las coordenadas
 de los elementos de los vectores de juego_t
*/
coordenada_t robot_validado(juego_t juego){
    bool ocupado_bombas = false;
    bool ocupado_herramientas = false;
    bool ocupado_familiares = false;
    coordenada_t robot_validado;
    do{
        robot_validado = inicializa_robots();
        ocupado_bombas = verificar_coordenadas_robots_bombas(juego.bombas,juego.tope_bombas,robot_validado);
        ocupado_herramientas = verificar_coordenadas_robots_herramientas(juego.herramientas, juego.tope_herramientas, robot_validado);
        ocupado_familiares = verificar_coordenadas_robots_familiares(juego.familiares, juego.tope_familiares, robot_validado);
    }while(ocupado_bombas|| ocupado_herramientas || ocupado_familiares);
    
    return robot_validado;
}

/*
PRE:Recibe el vector de robots por referencia, su tope y la cantidad movimientos
POST:le asigna una fila y una columna a cada robot del vector cada 10 movimientos
*/
void generar_robots(juego_t juego,coordenada_t* *robots, int* cant_robots,int movimientos){
    if((movimientos > 0) && (movimientos % 10 == 0)){
        if(*cant_robots == 0){
            *robots = realloc(*robots,(unsigned)(*cant_robots+1) * sizeof(coordenada_t));
            if(*robots == NULL){
                printf("Robots null");
            }
            (*robots)[*cant_robots] = robot_validado(juego);
            (*cant_robots)++;    
        }else{
            *robots = realloc(*robots,(unsigned)(*cant_robots+1) * sizeof(coordenada_t));
            if(*robots == NULL){
                printf("Robots null");
            }
            (*robots)[*cant_robots-1] = robot_validado(juego);
            (*cant_robots)++;
        }
    }
   
}
/*
PRE:Debe recibir un juego_t inicializado
POST:Elimina del vector de herramientas a los elementos pisados por perry 
*/
void eliminar_herramientas(herramienta_t vector_herramientas[MAX_HERRAMIENTAS], int* tope_herramientas, personaje_t* perry){
    bool perry_pisa_herramienta = false;
    int herramienta_por_eliminar = 0;
    int i =0;
    while((i<(*tope_herramientas)) && (!perry_pisa_herramienta)){   
        if(vector_herramientas[i].posicion.fil == perry->posicion.fil && vector_herramientas[i].posicion.col == perry->posicion.col){
            perry_pisa_herramienta = true;
            herramienta_por_eliminar = i;
            if(vector_herramientas[i].tipo == SOMBREROS){
                perry->vida++; 
            }else if(vector_herramientas[i].tipo == GOLOSINAS){
                perry->energia += EFECTO_GOLOSINA;
            }
        }
        i++;
        if(perry_pisa_herramienta){
            for(i = herramienta_por_eliminar; i<(*tope_herramientas)-1; i++){
                vector_herramientas[i] = vector_herramientas[i+1];
            }
            (*tope_herramientas)--;
        }
    }
}



/*
PRE:Se le debe ingresar un vector de familiar_t con los familiares
POST:Hara los movimientos correspondientes dependiendo el sentido del personaje
*/
void mover_familiares(familiar_t vector_familiares[MAX_FAMILIARES],int phineas, int ferb, int candace){
    //movimiento phineas
    if(vector_familiares[phineas].sentido == DERECHA && vector_familiares[phineas].posicion.col != POSICION_MAXIMA){
        vector_familiares[phineas].posicion.col++;
    }else if(vector_familiares[phineas].posicion.col == POSICION_MAXIMA){
        vector_familiares[phineas].posicion.col--;
        vector_familiares[phineas].sentido = IZQUIERDA;
    }else if(vector_familiares[phineas].sentido == IZQUIERDA && vector_familiares[phineas].posicion.col != POSICION_MINIMA){
        vector_familiares[phineas].posicion.col--;
    }else if(vector_familiares[phineas].posicion.col == POSICION_MINIMA){
        vector_familiares[phineas].posicion.col++;
        vector_familiares[phineas].sentido = DERECHA;
    }
    //movimiento ferb
    if(vector_familiares[ferb].sentido == IZQUIERDA && vector_familiares[ferb].posicion.col != POSICION_MINIMA){
        vector_familiares[ferb].posicion.col--;
    }else if(vector_familiares[ferb].posicion.col == POSICION_MINIMA){
        vector_familiares[ferb].posicion.col++;
        vector_familiares[ferb].sentido = DERECHA;
    }else if(vector_familiares[ferb].sentido == DERECHA && vector_familiares[ferb].posicion.col != POSICION_MAXIMA){
        vector_familiares[ferb].posicion.col++;
    }else if(vector_familiares[ferb].posicion.col == POSICION_MAXIMA){
        vector_familiares[ferb].posicion.col--;
        vector_familiares[ferb].sentido = IZQUIERDA;
    }
    //movimiento candace
    if(vector_familiares[candace].sentido == ARRIBA && vector_familiares[candace].posicion.fil != POSICION_MINIMA){
        vector_familiares[candace].posicion.fil--;
    }else if(vector_familiares[candace].posicion.fil == POSICION_MINIMA){
        vector_familiares[candace].posicion.fil ++;
        vector_familiares[candace].sentido = ABAJO;
    }else if(vector_familiares[candace].sentido == ABAJO && vector_familiares[candace].posicion.fil != POSICION_MAXIMA){
        vector_familiares[candace].posicion.fil++;
    }else if(vector_familiares[candace].posicion.fil == POSICION_MAXIMA){
        vector_familiares[candace].posicion.fil--;
        vector_familiares[candace].sentido = ARRIBA;
    }
}
/*
PRE:Recibe el vector de bombas con su tope
POST:Resta 1 al timer 
*/
void restar_timer(bomba_t vector_bombas[MAX_BOMBAS], int tope_bombas){
    for(int i=0;i<tope_bombas;i++){
        if(vector_bombas[i].timer != 0 && vector_bombas[i].desactivada != true){
            vector_bombas[i].timer--;
        }
    }
}

/*
PRE:Recibe un juego_t por referencia
POST:Resta vida a perry cuando la bomba explota
*/
void explotar_bombas(bomba_t vector_bombas[MAX_BOMBAS], int tope_bombas, personaje_t* perry){
    for(int i=0;i<tope_bombas;i++){
        if(vector_bombas[i].timer == 0 && vector_bombas[i].desactivada != true){
            vector_bombas[i].desactivada = true;
            perry->vida--;
        }
    }
}

/*
PRE:Se le ingresa un caracter valido (W A S D Q)
POST:Cambia las filas o columnas de perry y los familiares dependiendo del movimiento valido realizado
*/
void hacer_movimientos(juego_t* juego, char movimiento){
    if(movimiento == ARRIBA || movimiento == ARRIBA_MINUSCULA){
        if(juego->perry.posicion.fil != POSICION_MINIMA){
            restar_timer(juego->bombas, juego->tope_bombas);
            mover_familiares(juego->familiares,POSICION_PHINEAS, POSICION_FERB, POSICION_CANDACE);
            juego->perry.posicion.fil -=1;
            juego->movimientos+=1;
        }
    }else if(movimiento == ABAJO || movimiento == ABAJO_MINUSCULA){
        if(juego->perry.posicion.fil != POSICION_MAXIMA){
            restar_timer(juego->bombas, juego->tope_bombas);
            mover_familiares(juego->familiares,POSICION_PHINEAS, POSICION_FERB, POSICION_CANDACE);
            juego->perry.posicion.fil +=1;
            juego->movimientos+=1;
        }
    }else if(movimiento == DERECHA || movimiento == DERECHA_MINUSCULA){
        if(juego->perry.posicion.col != POSICION_MAXIMA){
            restar_timer(juego->bombas, juego->tope_bombas);
            mover_familiares(juego->familiares,POSICION_PHINEAS, POSICION_FERB, POSICION_CANDACE);
            juego->perry.posicion.col +=1;
            juego->movimientos+=1;
        }
    }else if(movimiento == IZQUIERDA || movimiento == IZQUIERDA_MINUSCULA){
        if(juego->perry.posicion.col != POSICION_MINIMA){
            restar_timer(juego->bombas,juego->tope_bombas);
            mover_familiares(juego->familiares,POSICION_PHINEAS, POSICION_FERB, POSICION_CANDACE);
            juego->perry.posicion.col -=1;
            juego->movimientos+=1;
        }
    }else if(movimiento == CAMUFLARSE || movimiento == CAMUFLARSE_MINUSCULA){
        juego->perry.camuflado = !juego->perry.camuflado;
    }
    
}

/*
PRE:Recibe el puntero de robots, su tope y perry
POST:Si perry se encuentra a una distancia manhattan <= 2 y esta camuflado, se le resta una vida
*/
void restar_vida_robots(coordenada_t* robots, int tope_robots, personaje_t* perry){
    for(int i=0;i<tope_robots;i++){
        if((distancia_manhattan(robots[i],perry->posicion) <= DISTANCIA_DEL_ROBOTS) && (perry->camuflado == true)){
            perry->vida--;
        }
    }
}

/*
PRE:Recibe el puntero de robotso por referencia, el tope y a perry
POST:Si Perry se encuentra a <= 2 manhattan y perry no esta camuflado se destruye el robot 
y saca vida o resta energia a perry
*/
void destruir_robots(coordenada_t* *robots, int* cant_robots, personaje_t* perry){
    coordenada_t robot_aux = inicializa_robots();
    int robot_a_destruir = 0;
    bool hay_que_destruir = false;
    for(int i=0;i<*cant_robots;i++){
        if(distancia_manhattan(*robots[i],perry->posicion) <= DISTANCIA_DEL_ROBOTS && (perry->camuflado == false)){
            hay_que_destruir = true;
            robot_a_destruir = i;
            if(perry->energia >= ENERGIA_NECESARIA){
                perry->energia -= ENERGIA_PERDIDA_POR_ROBOT;
            }else{
                perry->vida--;
            }
        }
    }
    if(hay_que_destruir){
        if(*cant_robots == 1){
            *robots = realloc(*robots, sizeof(coordenada_t) * (unsigned)(*cant_robots-1));
            *cant_robots -=1;
            if(*robots == NULL){
                printf("robots null");
            }
        }else{
            robot_aux = (*robots)[(*cant_robots)-1];
            (*robots)[(*cant_robots)-1] = (*robots)[robot_a_destruir];
            (*robots)[robot_a_destruir] = robot_aux;
            *robots = realloc(*robots, sizeof(coordenada_t) * (unsigned)(*cant_robots-1));
            *cant_robots -=1;
            if(*robots == NULL){
                printf("robots null");
            }
        }
    }
}


/*
PRE:Recibe un juego_t por referencia
POST:Resta vida a perry si se encuentra a <= 1 distancia de un familiar
*/
void restar_vida_familiares(familiar_t vector_familiares[MAX_FAMILIARES], int tope_familiares, personaje_t* perry){
    for(int i=0;i<tope_familiares;i++){
        if((distancia_manhattan(vector_familiares[i].posicion,perry->posicion) <= DISTANCIA_DEL_FAMILIAR) && (perry->camuflado != true)){
            perry->vida--;
        }
    }
}

//   ------- FUNCIONES DE IMPRIMIR_TERRENO() -------
/*
PRE:Se ingresa una variable del tipo juego_t inicializado
POST:Dependiendo del bool del camuflaje de perry, muestra si es true o false
*/
void mostrar_estado_camuflaje(personaje_t perry){
    if(perry.camuflado){
        printf("Perry esta camuflado\n");
    }else{
        printf("Perry no esta camuflado\n");
    }
}

/*
PRE:Se debe recibir una variable juego con un vector de tipo bomba_t no vacio
POST:Recorre el vector bombas de la variable juego e imprime el timer de cada bomba
*/
void mostrar_timer_bombas(bomba_t vector_bombas[MAX_BOMBAS], int tope_bombas){
    for(int i=0;i<tope_bombas;i++){
        int timer = vector_bombas[i].timer;
        int columna = vector_bombas[i].posicion.col;
        int fila = vector_bombas[i].posicion.fil;
        printf("Timer bomba %d : %d \t Fila: %i \t Columna: %i \n", i,timer,fila+1, columna+1);
    }
}

/*
PRE:Debe recibir una matriz de 20 filas y 20 columnas
POST:Inicializa la matriz con espacios vacios
*/
void inicializar_terreno(char terreno[MAX_FILAS][MAX_COLUMNAS]){
    for(int i=0;i<MAX_FILAS; i++){ 
        for(int j=0;j<MAX_COLUMNAS;j++){
            terreno[i][j] = VACIO; 
        }
    }
}

/*
PRE:Debe recibir un juego de tipo juego_t inicializado y una matriz 20x20
POST:De la variable juego accede al vector de bombas y las posiciona en la matriz
*/
void asignar_posicion_bombas(bomba_t vector_bombas[MAX_BOMBAS], int tope_bombas,char matriz[MAX_FILAS][MAX_COLUMNAS]){
    for(int i=0; i< tope_bombas;i++){       
        bomba_t bomba = vector_bombas[i];
        coordenada_t posicion_bomba = bomba.posicion;
        int fila = posicion_bomba.fil;
        int columna = posicion_bomba.col;
        matriz[fila][columna] = BOMBAS;
        if(vector_bombas[i].desactivada == true){
            matriz[vector_bombas[i].posicion.fil][vector_bombas[i].posicion.col] = VACIO;
        }
    }

}
/*
PRE:Debe recibir una matriz 20x20 y un juego de tipo juego_t inicializado
POST:De la variable juego accede al vector de herramientas y las posiciona en la matriz
*/
void asignar_posicion_herramientas(herramienta_t vector_herramientas[MAX_HERRAMIENTAS],int tope_herramientas,char matriz[MAX_FILAS][MAX_COLUMNAS]){
    for(int i=0; i < tope_herramientas;i++){
        herramienta_t herramienta = vector_herramientas[i];
        coordenada_t posicion_herramienta = herramienta.posicion;
        int fila = posicion_herramienta.fil;
        int columna = posicion_herramienta.col;
        matriz[fila][columna] = herramienta.tipo; 
    }

}
/*
PRE:Debe recibir una matriz de caracteres y una variable juego de tipo juego_t
POST:Asigna a cada familiar del vector familiares su posicion en la matriz
*/
void asignar_posicion_familiares(familiar_t vector_familiares[MAX_FAMILIARES], int tope_familiares,char matriz[MAX_FILAS][MAX_COLUMNAS]){
    for(int i=0; i < tope_familiares;i++){
        familiar_t familiar = vector_familiares[i];
        coordenada_t posicion_familiar = familiar.posicion;
        int fila = posicion_familiar.fil;
        int columna = posicion_familiar.col;
        matriz[fila][columna] = familiar.inicial_nombre; 
    }

}

/*
PRE:Debe recibir una matriz de caracteres y una variable juego de tipo juego_t
POST:Asigna a cada robot una posicion en la matriz
*/
void asignar_posicion_robots(coordenada_t* robots, int cant_robots,char matriz[MAX_FILAS][MAX_COLUMNAS]){
    for(int i=0;i<cant_robots;i++){
        coordenada_t robot = robots[i];
        matriz[robot.fil][robot.col] = ROBOTS;
    }
}
/*
PRE:Debe recibir una matriz de caracteres y un juego tipo juego_t 
POST:Muestra por pantalla a la matriz 
*/
void mostrar_terreno(char terreno[MAX_FILAS][MAX_COLUMNAS],personaje_t perry){
    for(int i=0;i<MAX_FILAS; i++){ 
        for(int j=0;j<MAX_COLUMNAS;j++){
            int fila_perry = perry.posicion.fil;
            int columna_perry = perry.posicion.col;
            terreno[fila_perry][columna_perry] = PERRY;
            printf("| %c|\t",terreno[i][j]);    
        }
        printf("\n");
    }
}
// ------ FUNCIONES ESTADO_JUEGO() ------
/*
PRE:Se ingresa un vector de bombas_t con su tope
POST:Accede al vector bombas y verifica si todas estan desactivadas, en ese caso devuelve true y si no devuelve false
*/
bool bombas_desactivadas(bomba_t vector_bombas[MAX_BOMBAS], int tope_bombas){
    bool todas_desactivadas = true;
    for(int i=0; i<tope_bombas; i++) {
        if(vector_bombas[i].desactivada != true) {
            todas_desactivadas = false; 
        }
    }
    return todas_desactivadas;
}

/*
 * Inicializará el juego, cargando toda la información inicial de Perry, los obstáculos, las herramientas y la familia Flynn.
 */
void inicializar_juego(juego_t* juego){
    coordenada_t vector_coordenadas[MAX_COORDENADAS];
    int tope_coordenadas = 1;
    juego->cantidad_robots = ROBOTS_INICIALES;
    juego->movimientos = MOVIMIENTOS_INICIALES;
    juego->robots = NULL;
    //Perry
    juego->perry = inicializa_perry();
    vector_coordenadas[0] = juego->perry.posicion;
    //Bombas
    juego->tope_bombas = BOMBAS_INICIALES;
    llenar_vector_bombas(juego->bombas,juego->tope_bombas,vector_coordenadas,&tope_coordenadas); 
    //Herramientas
    juego->tope_herramientas = HERRAMIENTAS_INICIALES;
    llenar_vector_herramientas(juego->herramientas,juego->tope_herramientas, vector_coordenadas, &tope_coordenadas);
    //Familiares
    juego->tope_familiares = FAMILIARES_INICIALES;
    llenar_vector_familiares(juego->familiares,juego->tope_familiares, vector_coordenadas, &tope_coordenadas);
}

/*
 * Realizará la acción recibida por parámetro. 
 * La acción recibida deberá ser válida.
 * Solo se podrá mover a Perry y camuflarlo.
 */
void realizar_jugada(juego_t* juego, char accion){
    hacer_movimientos(juego, accion);
    generar_robots(*juego,&juego->robots, &juego->cantidad_robots,juego->movimientos);        
    desactivar_bombas(juego->bombas,juego->tope_bombas,&juego->perry);
    eliminar_herramientas(juego->herramientas, &juego->tope_herramientas, &juego->perry);
    explotar_bombas(juego->bombas,juego->tope_bombas,&juego->perry);
    restar_vida_familiares(juego->familiares, juego->tope_familiares, &juego->perry);
    restar_vida_robots(juego->robots, juego->cantidad_robots, &juego->perry);
    destruir_robots(&juego->robots, &juego->cantidad_robots, &juego->perry);
}

/*
 * Imprime el juego por pantalla
 */
void imprimir_terreno(juego_t juego){
    char terreno[MAX_FILAS][MAX_COLUMNAS];
    inicializar_terreno(terreno);
    asignar_posicion_bombas(juego.bombas,juego.tope_bombas,terreno);
    asignar_posicion_herramientas(juego.herramientas,juego.tope_herramientas,terreno);
    asignar_posicion_familiares(juego.familiares,juego.tope_familiares,terreno);
    asignar_posicion_robots(juego.robots,juego.cantidad_robots,terreno);
    printf("¿Un ornitorrinco...? ¡Perry El Ornitorrinco!\n");
    printf("Movimientos validos: ARRIBA (W), ABAJO (S), IZQUIERDA (A), DERECHA (D)\n");
    printf("Vidas de perry: %i\n", juego.perry.vida);
    printf("Energia de perry: %i\n", juego.perry.energia);
    printf("Haga su movimiento \n");
    printf("Cantidad de movimientos: %i\n", juego.movimientos);
    mostrar_estado_camuflaje(juego.perry);
    mostrar_timer_bombas(juego.bombas,juego.tope_bombas);
    mostrar_terreno(terreno,juego.perry);
    if(juego.perry.vida == 1){
        printf("CUIDADO TENES UNA SOLA VIDA!\n");
    }
}


/*
 * El juego se dará por ganado cuando estén todas las bombas desactivadas.
 * Si el personaje se queda sin vidas, el juego se dará por perdido.
 * Devuelve:
 * --> 1 si es ganado
 * --> -1 si es perdido
 * --> 0 si se sigue jugando
 * 
 * En caso de ganado o perdido esta función liberará la memoria reservada a lo largo del juego.
 * Queda como responsabilidad del usuario no llamar a esta función dos veces en caso de que se
 * devuelva un valor distinto de 0 (para no hacer doble liberación).
*/
int estado_juego(juego_t juego){
    int estado = JUGANDO;
    bool desactivadas = bombas_desactivadas(juego.bombas, juego.tope_bombas);
    if(juego.perry.vida == PERRY_MUERTO){
        estado = PERDIDO;
        free(juego.robots);
    }else if(desactivadas == true){
        estado = GANADO;
        free(juego.robots);
    }
    return estado;
}