// src/animal.c
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
    // se não achar, mata o bicho
    a->vivo = 0;
}

Animal* init_animal(Floresta *f) {
    Animal *a = malloc(sizeof(Animal));
    posicionar_inicial(f, a);
    return a;
}

void move_animal(Floresta *f, Animal *a) {
    if (!a->vivo) return;

    int cx = a->x, cy = a->y;
    int val = f->matriz[cx][cy];

    // se está em água, converte em vazio e regenera árvores ao redor
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

    // se está em área vazia e ainda pode ficar, incrementa e permanece
    if (val == 0 && a->iteracoes_no_local < 3) {
        a->iteracoes_no_local++;
        return;
    }

    // caso contrário, tenta mover-se para o melhor vizinho
    int dx[4] = {-1,1,0,0}, dy[4] = {0,0,-1,1};
    int best_prio = 0, best_nx = -1, best_ny = -1;

    for (int k = 0; k < 4; k++) {
        int nx = cx + dx[k], ny = cy + dy[k];
        if (nx<0||nx>=f->linhas||ny<0||ny>=f->colunas) continue;
        int v = f->matriz[nx][ny], prio = 0;
        if (v == 4)       prio = 4;
        else if (v == 0 || v == 1) prio = 3;
        else if (v == 3)  prio = 2;
        else if (v == 2)  prio = 0;
        if (prio > best_prio) {
            best_prio = prio;
            best_nx = nx;
            best_ny = ny;
        }
    }

    // se não há para onde ir (todas ortogonais em chamas)
    if (best_prio == 0) {
        a->vivo = 0;
        return;
    }

    // move para a melhor posição
    a->x = best_nx;
    a->y = best_ny;
    a->iteracoes_no_local = 0;
}
