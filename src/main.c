// === src/main.c ===
// === versão final ===
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

    Animal *a = init_animal(f);

    FILE *out = fopen("output.dat", "w");
    if (out) fclose(out);

    escrever_output("output.dat", f, 0);

    for (int iter = 1; iter <= MAX_ITERACOES; iter++) {
        move_animal(f, a);

        int spread;
        propagar_fogo(f, &spread);

        escrever_output("output.dat", f, iter);

        if (!spread) break;
    }

    printf("Matriz final:\n");
    for (int i = 0; i < f->linhas; i++) {
        for (int j = 0; j < f->colunas; j++)
            printf("%d ", f->matriz[i][j]);
        printf("\n");
    }

    printf("Animal %s\n", (a->vivo ? "sobreviveu" : "morreu"));
    printf("Total de passos: %d\n", a->passos);
    printf("Caminho percorrido:\n");
    for (int i = 0; i < a->caminho_tamanho; i++) {
        printf("(%d, %d) ", a->caminho_x[i], a->caminho_y[i]);
        if ((i+1) % 10 == 0) printf("\n");
    }
    printf("\n");

    FILE *out_final = fopen("output.dat", "a");
    if (out_final) {
        fprintf(out_final, "Resultado Final:\n");
        fprintf(out_final, "Animal %s\n", (a->vivo ? "sobreviveu" : "morreu"));
        fprintf(out_final, "Total de passos: %d\n", a->passos);
        fprintf(out_final, "Caminho percorrido:\n");
        for (int i = 0; i < a->caminho_tamanho; i++) {
            fprintf(out_final, "(%d, %d) ", a->caminho_x[i], a->caminho_y[i]);
            if ((i+1) % 10 == 0) fprintf(out_final, "\n");
        }
        fprintf(out_final, "\n");
        fclose(out_final);
    }

    liberar_animal(a);
    liberar_floresta(f);

    return 0;
}
