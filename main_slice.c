#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
    int linha, coluna;
    scanf("%d %d",&linha, &coluna);
    Matriz *a = matriz_construct(linha,coluna),*b,*c;
    matriz_read(a);
    printf("Matriz A\n");
    matriz_densa_print(a);
    scanf("%d %d",&linha, &coluna);
    b = matriz_construct(linha,coluna);
    matriz_read(b);
    printf("Kernel\n");
    matriz_densa_print(b);
    c = matriz_covulacao(a,b);
    printf("????\n");
    matriz_densa_print(c);
    matriz_destroy(a);
    matriz_destroy(b);
    matriz_destroy(c);
}