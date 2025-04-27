// src/main.c
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "entrada_saida.h"
#include "fogo.h"
#include "animal.h"

int main() {
    Floresta *f = ler_input("input.dat");
    if (!f) {
        fprintf(stderr, "Erro ao ler input.dat\n");
        return 1;
    }

    // inicializa animal
    Animal *a = init_animal(f);

    // limpa output.dat
    FILE *out = fopen("output.dat", "w");
    if (out) fclose(out);

    // iteração zero (estado inicial)
    escrever_output("output.dat", f, 0);

    // loop principal
    for (int iter = 1; iter <= MAX_ITERACOES; iter++) {
        // 1) animal se move (ou permanece)
        move_animal(f, a);

        // 2) propaga fogo
        int spread;
        propagar_fogo(f, &spread);

        // 3) grava estado
        escrever_output("output.dat", f, iter);

        // 4) se fogo não se espalhou mais, acaba
        if (!spread) break;
    }

    // exibe resultado final na tela
    printf("Matriz final:\n");
    for (int i = 0; i < f->linhas; i++) {
        for (int j = 0; j < f->colunas; j++)
            printf("%d ", f->matriz[i][j]);
        printf("\n");
    }
    printf("Animal %s\n", (a->vivo ? "sobreviveu" : "morreu"));

    // libera memória
    free(a);
    liberar_floresta(f);
    return 0;
}
