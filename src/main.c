// === src/main.c ===

#include <stdio.h>
#include <stdlib.h>
#include "entrada_saida.h"

int main() {
    Floresta *floresta = ler_input("input.dat");
    if (floresta == NULL) return 1;

    escrever_output("output.dat", floresta, 0);

    liberar_floresta(floresta);
    return 0;
}

