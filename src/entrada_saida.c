// === src/entrada_saida.c ===
// === versão final ===
#include <stdio.h>
#include <stdlib.h>
#include "entrada_saida.h"

Floresta* ler_input(const char *caminho) {
    FILE *arquivo = fopen(caminho, "r");
    if (!arquivo) return NULL;

    Floresta *f = malloc(sizeof(Floresta));
    fscanf(arquivo, "%d %d %d %d", &f->linhas, &f->colunas, &f->fogo_x, &f->fogo_y);

    f->matriz = malloc(f->linhas * sizeof(int*));
    for (int i = 0; i < f->linhas; i++) {
        f->matriz[i] = malloc(f->colunas * sizeof(int));
        for (int j = 0; j < f->colunas; j++) {
            fscanf(arquivo, "%d", &f->matriz[i][j]);
        }
    }
    fclose(arquivo);
    return f;
}

void escrever_output(const char *caminho, Floresta *f, int iteracao) {
    FILE *arquivo = fopen(caminho, "a");
    if (!arquivo) return;

    fprintf(arquivo, "Iteracao %d:\n", iteracao);
    for (int i = 0; i < f->linhas; i++) {
        for (int j = 0; j < f->colunas; j++) {
            fprintf(arquivo, "%d ", f->matriz[i][j]);
        }
        fprintf(arquivo, "\n");
    }
    fprintf(arquivo, "\n");
    fclose(arquivo);
}

void liberar_floresta(Floresta *f) {
    for (int i = 0; i < f->linhas; i++) free(f->matriz[i]);
    free(f->matriz);
    free(f);
}

