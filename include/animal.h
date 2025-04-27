// include/animal.h
#ifndef ANIMAL_H
#define ANIMAL_H

#include "entrada_saida.h"

typedef struct {
    int x, y;                  // posição atual
    int iteracoes_no_local;    // contador de permanência em área segura
    int vivo;                  // 1 = vivo, 0 = morto
} Animal;

// cria e posiciona o animal na primeira célula '0'
Animal* init_animal(Floresta *f);

// tenta mover o animal (ou mantê-lo) conforme regras; ajusta .vivo e .iteracoes_no_local
void move_animal(Floresta *f, Animal *a);

#endif // ANIMAL_H
