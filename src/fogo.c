// src/fogo.c
// === versão final ===
#include <stdlib.h>
#include "fogo.h"
#include "config.h"

void propagar_fogo(Floresta *f, int *spread) {
    int i, j;
    *spread = 0;
    // cria cópia da matriz
    int **nova = malloc(f->linhas * sizeof(int*));
    for (i = 0; i < f->linhas; i++) {
        nova[i] = malloc(f->colunas * sizeof(int));
        for (j = 0; j < f->colunas; j++)
            nova[i][j] = f->matriz[i][j];
    }

    // para cada célula em chamas, tenta alastrar
    for (i = 0; i < f->linhas; i++) {
        for (j = 0; j < f->colunas; j++) {
            if (f->matriz[i][j] == 2) {
                // vira queimado
                nova[i][j] = 3;
                // vizinhança ortogonal
                #if PROPAGA_CIMA
                if (i>0 && f->matriz[i-1][j]==1)   { nova[i-1][j] = 2; *spread = 1; }
                #endif
                #if PROPAGA_BAIXO
                if (i+1<f->linhas && f->matriz[i+1][j]==1) { nova[i+1][j] = 2; *spread = 1; }
                #endif
                #if PROPAGA_ESQUERDA
                if (j>0 && f->matriz[i][j-1]==1)   { nova[i][j-1] = 2; *spread = 1; }
                #endif
                #if PROPAGA_DIREITA
                if (j+1<f->colunas && f->matriz[i][j+1]==1) { nova[i][j+1] = 2; *spread = 1; }
                #endif
            }
        }
    }

    // grava de volta em f->matriz
    for (i = 0; i < f->linhas; i++) {
        for (j = 0; j < f->colunas; j++)
            f->matriz[i][j] = nova[i][j];
        free(nova[i]);
    }
    free(nova);
}
