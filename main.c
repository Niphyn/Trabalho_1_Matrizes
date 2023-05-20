#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
    int linha, coluna;
    scanf("%d %d",&linha, &coluna);
    Matriz *a = matriz_construct(linha,coluna),*b = matriz_construct(linha,coluna);
    Matriz *soma, *escalar, *ponto_a_ponto;
    Matriz *troca_linha, *troca_coluna,*multiplicacao;
    matriz_read(a);
    matriz_read(b);
    printf("Acabou de ler\n");
    ponto_a_ponto = matriz_multiplicacao_ponto_a_ponto(a,b);
    soma = matriz_soma(a,b);
    escalar = matriz_multiplicar_escalar(a,2);
    printf("Escalar\n");
    troca_linha = matriz_troca_linhas(2,0,a);
    troca_coluna = matriz_troca_colunas(1,0,a);
    printf("Trocas\n");
    multiplicacao = matriz_multiplicacao(a,b);
    printf("\nMatriz A\n");
    matriz_densa_print(a);
    printf("\nMatriz B\n");
    matriz_densa_print(b);
    printf("\nMatriz de Multiplicação ponto a ponto\n");
    matriz_densa_print(ponto_a_ponto);
    printf("\nMatriz soma\n");
    matriz_densa_print(soma);
    printf("\nMatriz de Multiplicação escalar por 2\n");
    matriz_densa_print(escalar);
    printf("\nMatriz de troca de linha\n");
    matriz_densa_print(troca_linha);
    printf("\nMatriz de troca de coluna\n");
    matriz_densa_print(troca_coluna);
    printf("\nMatriz de multiplicação de duas matrizes\n");
    matriz_densa_print(multiplicacao);
    matriz_destroy(a);
    matriz_destroy(b);
    matriz_destroy(ponto_a_ponto);
    matriz_destroy(soma);
    matriz_destroy(escalar);
    matriz_destroy(troca_coluna);
    matriz_destroy(troca_linha);
    matriz_destroy(multiplicacao);
}