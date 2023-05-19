#include "node.h"
#include <stdio.h>
#include <stdlib.h>


Node *node_construct(int linha, int coluna, float valor, Node *next_l, Node *next_c){
    Node *celula = (Node *)calloc(1,sizeof(Node));
    celula->l = linha;
    celula->c = coluna;
    celula->value = valor;
    celula->next_l = next_l;
    celula->next_c = next_c;
    return celula;
}

void node_destroy(Node *node){
    free(node);
}