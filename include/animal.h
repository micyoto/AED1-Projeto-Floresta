// === include/animal.h ===
#ifndef ANIMAL_H
#define ANIMAL_H

#include "entrada_saida.h"

typedef struct {
    int x, y;                   // Posição atual
    int iteracoes_no_local;     // Contador de permanência
    int vivo;                   // 1 = vivo, 0 = morto
    int passos;                 // Total de passos dados
    int *caminho_x;             // Lista de linhas percorridas
    int *caminho_y;             // Lista de colunas percorridas
    int caminho_capacidade;     // Capacidade alocada
    int caminho_tamanho;        // Tamanho atual
} Animal;

Animal* init_animal(Floresta *f);
void move_animal(Floresta *f, Animal *a);
void liberar_animal(Animal *a);

#endif // ANIMAL_H
