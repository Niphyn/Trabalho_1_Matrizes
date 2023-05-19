#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
    int linha, coluna;
    float num;
    scanf("%d %d",&linha, &coluna);
    Matriz *a = matriz_construct(linha,coluna),*b;
    matriz_read(a);
    printf("Multiplicar a matriz pelo número: ");
    scanf("%f",&num);
    matriz_densa_print(a);
    matriz_esparsa_print(a);
    b = matriz_multiplicar_escalar(a,num);
    matriz_densa_print(b);
    matriz_esparsa_print(b);
    matriz_destroy(a);
    matriz_destroy(b);
}