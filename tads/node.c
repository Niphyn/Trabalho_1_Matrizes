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
}//Complexidade do tempo: O(1), pois tem um tempo de execução constante porque não ha loop na função

void node_destroy(Node *node){
    free(node);
}//Complexidade do tempo: O(1), pois tem um tempo de execução constante porque não ha loop na função

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
/*Complexidade do tempo: O(N), pois se trata de uma busca linear, ou seja, 
quanto mais distante o componente procurado se encontra do head da linha mais demorar*/

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
/*Complexidade do tempo: O(N), pois se trata de uma busca linear, ou seja, 
quanto mais distante o componente procurado se encontra do head da linha mais demorar*/