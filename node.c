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

Node *node_prev_linha(Node *head_linha, Node *searched){
    Node *prev = NULL, *current = NULL;
    current = head_linha;
    while((current != searched)&&(searched != NULL)&&(current != NULL)){
        prev = current;
        current = current->next_l;
    }
    if((searched == NULL)||(current == NULL)){
        printf("Não há node anterior\n");
        return NULL;
    }else{
        return prev;
    }
}

Node *node_prev_coluna(Node *head_coluna, Node *searched){
    Node *prev = NULL, *current = NULL;
    current = head_coluna;
    while((current != searched)&&(searched != NULL)&&(current != NULL)){
        prev = current;
        current = current->next_c;
    }
    if((searched == NULL)||(current == NULL)){
        printf("Não há node anterior\n");
        return NULL;
    }else{
        return prev;
    }
}