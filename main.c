#include "tads/matriz.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

    Matriz *a, *b,*kernel,*soma,*escalar,*ponto_ponto,*troca_linha,*troca_coluna,*multiplicacao,
    *slice,*transposta,*covulacao;
    FILE *write, *read;
    
    read = fopen(argv[1],"rb");
    
    a = matriz_ler_binario(read);
    printf("Matriz A\n");
    matriz_densa_print(a);
    b =  matriz_ler_binario(read);
    printf("Matriz B\n");
    matriz_densa_print(b);
    kernel =  matriz_ler_binario(read);
    printf("Matriz Kernel\n");
    matriz_densa_print(kernel);
    soma = matriz_soma(a,b);
    escalar = matriz_multiplicar_escalar(a,2);
    ponto_ponto = matriz_multiplicacao_ponto_a_ponto(a,b);
    troca_linha = matriz_troca_linhas(0,1,a);
    troca_coluna = matriz_troca_colunas(0,1,a);
    multiplicacao = matriz_multiplicacao(a,b);
    slice = matriz_slice(a,1,1,3,3);
    transposta = matriz_transposta(a);
    covulacao = matriz_covulacao(a,kernel);
    fclose(read);
    printf("Soma\n");
    matriz_densa_print(soma);
    printf("Matriz escalar de A * 2\n");
    matriz_densa_print(escalar);
    printf("Matriz de multiplicação ponto a ponto de A e B\n");
    matriz_densa_print(ponto_ponto);
    printf("Troca de linha da Matriz A\n");
    matriz_densa_print(troca_linha);
    printf("Troca de coluna da Matriz A\n");
    matriz_densa_print(troca_coluna);
    printf("Multiplicação da Matriz A pela B\n");
    matriz_densa_print(multiplicacao);
    printf("Slice Matriz A\n");
    matriz_densa_print(slice);
    printf("Transposta da Matriz A\n");
    matriz_densa_print(transposta);
    printf("Covulação da Matriz A\n");
    matriz_densa_print(covulacao);
    write = fopen(argv[2],"wb");
    matriz_escrever_binario(write,a);
    matriz_escrever_binario(write,b);
    matriz_escrever_binario(write,kernel);
    fclose(write);
    matriz_destroy(a);
    matriz_destroy(b);
    matriz_destroy(kernel);
    matriz_destroy(soma);
    matriz_destroy(escalar);
    matriz_destroy(ponto_ponto);
    matriz_destroy(troca_linha);
    matriz_destroy(troca_coluna);
    matriz_destroy(multiplicacao);
    matriz_destroy(slice);
    matriz_destroy(transposta);
    matriz_destroy(covulacao);
}

/*
./main write.bin write.bin
Matriz A
0.00 1.00 1.00 1.00 0.00 0.00 0.00 
0.00 0.00 1.00 1.00 1.00 0.00 0.00 
0.00 0.00 0.00 1.00 1.00 1.00 0.00 
0.00 0.00 0.00 1.00 1.00 0.00 0.00 
0.00 0.00 1.00 1.00 0.00 0.00 0.00 
0.00 1.00 1.00 0.00 0.00 0.00 0.00 
1.00 1.00 0.00 0.00 0.00 0.00 0.00 
Matriz B
1.00 1.00 1.00 1.00 1.00 1.00 1.00 
2.00 2.00 2.00 2.00 2.00 2.00 2.00 
3.00 3.00 3.00 3.00 3.00 3.00 3.00 
4.00 4.00 4.00 4.00 4.00 4.00 4.00 
5.00 5.00 5.00 5.00 5.00 5.00 5.00 
6.00 6.00 6.00 6.00 6.00 6.00 6.00 
7.00 7.00 7.00 7.00 7.00 7.00 7.00 
Matriz Kernel
1.00 0.00 1.00 
0.00 1.00 0.00 
1.00 0.00 1.00 
Soma
1.00 2.00 2.00 2.00 1.00 1.00 1.00 
2.00 2.00 3.00 3.00 3.00 2.00 2.00 
3.00 3.00 3.00 4.00 4.00 4.00 3.00 
4.00 4.00 4.00 5.00 5.00 4.00 4.00 
5.00 5.00 6.00 6.00 5.00 5.00 5.00 
6.00 7.00 7.00 6.00 6.00 6.00 6.00 
8.00 8.00 7.00 7.00 7.00 7.00 7.00 
Matriz escalar de A * 2
0.00 2.00 2.00 2.00 0.00 0.00 0.00 
0.00 0.00 2.00 2.00 2.00 0.00 0.00 
0.00 0.00 0.00 2.00 2.00 2.00 0.00 
0.00 0.00 0.00 2.00 2.00 0.00 0.00 
0.00 0.00 2.00 2.00 0.00 0.00 0.00 
0.00 2.00 2.00 0.00 0.00 0.00 0.00 
2.00 2.00 0.00 0.00 0.00 0.00 0.00 
Matriz de multiplicação ponto a ponto de A e B
0.00 1.00 1.00 1.00 0.00 0.00 0.00 
0.00 0.00 2.00 2.00 2.00 0.00 0.00 
0.00 0.00 0.00 3.00 3.00 3.00 0.00 
0.00 0.00 0.00 4.00 4.00 0.00 0.00 
0.00 0.00 5.00 5.00 0.00 0.00 0.00 
0.00 6.00 6.00 0.00 0.00 0.00 0.00 
7.00 7.00 0.00 0.00 0.00 0.00 0.00 
Troca de linha da Matriz A
0.00 0.00 1.00 1.00 1.00 0.00 0.00 
0.00 1.00 1.00 1.00 0.00 0.00 0.00 
0.00 0.00 0.00 1.00 1.00 1.00 0.00 
0.00 0.00 0.00 1.00 1.00 0.00 0.00 
0.00 0.00 1.00 1.00 0.00 0.00 0.00 
0.00 1.00 1.00 0.00 0.00 0.00 0.00 
1.00 1.00 0.00 0.00 0.00 0.00 0.00 
Troca de coluna da Matriz A
1.00 0.00 1.00 1.00 0.00 0.00 0.00 
0.00 0.00 1.00 1.00 1.00 0.00 0.00 
0.00 0.00 0.00 1.00 1.00 1.00 0.00 
0.00 0.00 0.00 1.00 1.00 0.00 0.00 
0.00 0.00 1.00 1.00 0.00 0.00 0.00 
1.00 0.00 1.00 0.00 0.00 0.00 0.00 
1.00 1.00 0.00 0.00 0.00 0.00 0.00 
Multiplicação da Matriz A pela B
9.00 9.00 7.00 4.00 0.00 0.00 0.00 
12.00 12.00 12.00 9.00 5.00 0.00 0.00 
15.00 15.00 15.00 15.00 11.00 6.00 0.00 
9.00 9.00 9.00 9.00 5.00 0.00 0.00 
7.00 7.00 7.00 4.00 0.00 0.00 0.00 
5.00 5.00 3.00 0.00 0.00 0.00 0.00 
3.00 3.00 1.00 1.00 1.00 1.00 1.00 
Slice Matriz A
0.00 1.00 1.00 
0.00 0.00 1.00 
0.00 0.00 1.00 
Transposta da Matriz A
0.00 0.00 0.00 0.00 0.00 0.00 1.00 
1.00 0.00 0.00 0.00 0.00 1.00 1.00 
1.00 1.00 0.00 0.00 1.00 1.00 0.00 
1.00 1.00 1.00 1.00 1.00 0.00 0.00 
0.00 1.00 1.00 1.00 0.00 0.00 0.00 
0.00 0.00 1.00 0.00 0.00 0.00 0.00 
0.00 0.00 0.00 0.00 0.00 0.00 0.00 
Covulação da Matriz A
0.00 2.00 2.00 3.00 1.00 1.00 0.00 
1.00 1.00 4.00 3.00 4.00 1.00 1.00 
0.00 1.00 2.00 4.00 3.00 3.00 0.00 
0.00 1.00 2.00 3.00 4.00 1.00 1.00 
1.00 1.00 3.00 3.00 1.00 1.00 0.00 
1.00 3.00 3.00 1.00 1.00 0.00 0.00 
2.00 2.00 1.00 1.00 0.00 0.00 0.00 

*/