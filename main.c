#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
    int linha, coluna;
    scanf("%d %d",&linha, &coluna);
    Matriz *m = matriz_construct(linha,coluna);
    matriz_read(m);
    matriz_densa_print(m);
    matriz_destroy(m);
    return 0; 
}