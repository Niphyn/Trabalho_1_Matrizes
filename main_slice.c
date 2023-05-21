#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
    int linha, coluna;
    FILE *f = fopen("write.bin","wb");
    scanf("%d %d",&linha, &coluna);
    Matriz *a = matriz_construct(linha,coluna),*b;
    matriz_read(a);
     printf("Matriz A\n");
    matriz_densa_print(a);
    matriz_escrever_binario(f,a);
    matriz_destroy(a);
    fclose(f);
    f = fopen("write.bin","rb");
    b = matriz_ler_binario(f);
    fclose(f);
    printf("Matriz B\n");
    matriz_densa_print(b);
    matriz_destroy(b);
}