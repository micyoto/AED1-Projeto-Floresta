// include/fogo.h
#ifndef FOGO_H
#define FOGO_H

#include "entrada_saida.h"

// Propaga o fogo uma iteração.  
//   f: ponteiro para a floresta  
//   spread: retorna 1 se houve novas chamas, 0 caso contrário
void propagar_fogo(Floresta *f, int *spread);

#endif // FOGO_H
