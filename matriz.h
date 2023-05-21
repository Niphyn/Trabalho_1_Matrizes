#ifndef _LIST_
#define _LIST_

#include "node.h"

typedef struct Matriz 
{
    Node **linhas;
    int qtd_linhas;
    Node **colunas;
    int qtd_colunas;
} Matriz;

Matriz *matriz_construct(int l, int c);

void matriz_destroy(Matriz *matriz);

void matriz_read(Matriz *m);

void matriz_node_mudar_valor(int l, int c, Matriz *matriz, float valor);

void matriz_inserir_celula(Matriz *m, Node *celula);

Node *matriz_node_get(int l, int c, Matriz *matriz);

void matriz_densa_print(Matriz *m);

void matriz_apaga_celula(Matriz *m, Node *celula);

Matriz *matriz_soma(Matriz *a, Matriz *b);

void matriz_esparsa_print(Matriz *a);

Matriz *matriz_multiplicar_escalar(Matriz *a, float num);

Matriz *matriz_multiplicacao_ponto_a_ponto(Matriz *a, Matriz *b);

Matriz *matriz_troca_linhas(int l1, int l2, Matriz *a);

Matriz *matriz_troca_colunas(int c1, int c2, Matriz *a);

Matriz *matriz_multiplicacao(Matriz *a, Matriz *b);

Matriz *matriz_slice(Matriz *a, int l_inicio, int c_inicio, int l_fim, int c_fim);

Matriz *matriz_transposta(Matriz *a);

Matriz *matriz_covulacao(Matriz *a, Matriz *kernel);

void matriz_salvar_binario(Matriz *a);

Matriz *matriz_ler_binario();

#endif