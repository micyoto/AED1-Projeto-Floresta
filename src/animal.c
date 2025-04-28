// === src/animal.c ===
// === versão final ===
#include <stdlib.h>
#include "animal.h"

static void posicionar_inicial(Floresta *f, Animal *a) {
    for (int i = 0; i < f->linhas; i++)
        for (int j = 0; j < f->colunas; j++)
            if (f->matriz[i][j] == 0) {
                a->x = i;
                a->y = j;
                a->iteracoes_no_local = 0;
                a->vivo = 1;
                return;
            }
    a->vivo = 0;
}

Animal* init_animal(Floresta *f) {
    Animal *a = malloc(sizeof(Animal));
    posicionar_inicial(f, a);

    a->passos = 0;
    a->caminho_capacidade = 1000;
    a->caminho_tamanho = 0;
    a->caminho_x = malloc(a->caminho_capacidade * sizeof(int));
    a->caminho_y = malloc(a->caminho_capacidade * sizeof(int));

    a->caminho_x[a->caminho_tamanho] = a->x;
    a->caminho_y[a->caminho_tamanho] = a->y;
    a->caminho_tamanho++;

    return a;
}

void move_animal(Floresta *f, Animal *a) {
    if (!a->vivo) return;

    int cx = a->x, cy = a->y;
    int val = f->matriz[cx][cy];

    if (val == 4) {
        f->matriz[cx][cy] = 0;
        int dx[4] = {-1,1,0,0}, dy[4] = {0,0,-1,1};
        for (int k = 0; k < 4; k++) {
            int nx = cx + dx[k], ny = cy + dy[k];
            if (nx>=0 && nx<f->linhas && ny>=0 && ny<f->colunas)
                f->matriz[nx][ny] = 1;
        }
        a->iteracoes_no_local = 0;
        return;
    }

    if (val == 0 && a->iteracoes_no_local < 3) {
        a->iteracoes_no_local++;
        return;
    }

    int dx[4] = {-1,1,0,0}, dy[4] = {0,0,-1,1};
    int best_prio = 0, best_nx = -1, best_ny = -1;

    for (int k = 0; k < 4; k++) {
        int nx = cx + dx[k], ny = cy + dy[k];
        if (nx<0||nx>=f->linhas||ny<0||ny>=f->colunas) continue;
        int v = f->matriz[nx][ny], prio = 0;
        if (v == 4) prio = 4;
        else if (v == 0 || v == 1) prio = 3;
        else if (v == 3) prio = 2;
        if (prio > best_prio) {
            best_prio = prio;
            best_nx = nx;
            best_ny = ny;
        }
    }

    if (best_prio == 0) {
        a->vivo = 0;
        return;
    }

    a->x = best_nx;
    a->y = best_ny;
    a->iteracoes_no_local = 0;
    a->passos++;

    if (a->caminho_tamanho >= a->caminho_capacidade) {
        a->caminho_capacidade *= 2;
        a->caminho_x = realloc(a->caminho_x, a->caminho_capacidade * sizeof(int));
        a->caminho_y = realloc(a->caminho_y, a->caminho_capacidade * sizeof(int));
    }

    a->caminho_x[a->caminho_tamanho] = a->x;
    a->caminho_y[a->caminho_tamanho] = a->y;
    a->caminho_tamanho++;
}

void liberar_animal(Animal *a) {
    free(a->caminho_x);
    free(a->caminho_y);
    free(a);
}
