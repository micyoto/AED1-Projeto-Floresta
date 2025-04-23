
// === include/entrada_saida.h ===
#ifndef ENTRADA_SAIDA_H
#define ENTRADA_SAIDA_H

typedef struct {
    int linhas;
    int colunas;
    int fogo_x;
    int fogo_y;
    int **matriz;
} Floresta;

Floresta* ler_input(const char *caminho);
void escrever_output(const char *caminho, Floresta *f, int iteracao);
void liberar_floresta(Floresta *f);

#endif
