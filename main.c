#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
    int linha, coluna;
    scanf("%d %d",&linha, &coluna);
    Matriz *a = matriz_construct(linha,coluna),*b = matriz_construct(linha,coluna),*c;
    matriz_read(a);
    matriz_read(b);
    c = matriz_multiplicacao_ponto_a_ponto(a,b);
    printf("\nMatriz A\n");
    matriz_densa_print(a);
    printf("\nMatriz B\n");
    matriz_densa_print(b);
    printf("\nMatriz C\n");
    matriz_densa_print(c);
    matriz_destroy(a);
    matriz_destroy(b);
    matriz_destroy(c);
}