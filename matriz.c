#include "matriz.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>

Matriz *matriz_construct(int l, int c){
    Matriz *m = (Matriz *)calloc(1,sizeof(Matriz));
    m->qtd_linhas = l;
    m->qtd_colunas = c;
    m->linhas = (Node**)calloc(l,sizeof(Node*));
    m->colunas = (Node**)calloc(c,sizeof(Node*));
    return m;
}//implementada

void matriz_destroy(Matriz *matriz){
    Node *current, *next = NULL;
    for(int i = 0; i < matriz->qtd_linhas; i++){
        current = matriz->linhas[i];
        while(current != NULL){
            next = current->next_l;
            node_destroy(current);
            current = next;
        }
    }

    free(matriz->linhas);
    free(matriz->colunas);
    free(matriz);
}//implementada porcamente

void matriz_read(Matriz *m){
    float v;
    for(int i = 0; i < m->qtd_linhas; i++){
        for(int j = 0; j < m->qtd_colunas; j++){
            scanf("%f",&v);
            matriz_node_mudar_valor(i,j,m,v);
        }
    }
}//implementada

void matriz_node_mudar_valor(int l, int c, Matriz *matriz, float valor){

    Node *celula = matriz_node_get(l,c,matriz);

    if(celula != NULL){
        celula->value = valor;
        if(celula->value == 0){
            matriz_apaga_celula(matriz,celula);
        }
    }else{
        if(valor != 0){
            celula = node_construct(l,c,valor,NULL,NULL);
            matriz_inserir_celula(matriz,celula);
        }
    }
}//implementada

void matriz_apaga_celula(Matriz *m, Node *celula){

    Node *prev, *current;
    int i = 0;
    //Acertar linhas

    prev = NULL;
    current = m->linhas[celula->l];
    i = current->c;
    while(i != celula->c){ 
        prev = current;
        current = current->next_l;
        i = current->c;
    }
    prev->next_l = celula->next_l;
    
    //Acertar colunas
    i = 0;
    
    prev = NULL;
    current = m->colunas[celula->c];
    while(i != celula->l){
        prev = current;
        current = current->next_c;
        i = current->c;
    }
    prev->next_c = celula->next_c;
    node_destroy(celula);
}//implementada

void matriz_inserir_celula(Matriz *m, Node *celula){

    Node *prev, *current;
    int i = 0;
    //Acertar linhas
    if(m->linhas[celula->l] == NULL){
        m->linhas[celula->l] = celula;
    }else{
        prev = NULL;
        current = m->linhas[celula->l];
        i = current->c;
        while(i < celula->c){
            prev = current;
            current = current->next_l;
            if(current == NULL){
                break;
            }
            i = current->c;
        }
        prev->next_l = celula;
        celula->next_l = current;
    }
    //Acertar colunas
    i = 0;
    if(m->colunas[celula->c] == NULL){
        m->colunas[celula->c] = celula;
    }else{
        prev = NULL;
        current = m->colunas[celula->c];
        while(i < celula->l){
            prev = current;
            current = current->next_c;
            if(current == NULL){
                break;
            }
            i = current->c;
        }
        prev->next_c = celula;
        celula->next_c = current;
    }
}//implementada

Node *matriz_node_get(int l, int c, Matriz *matriz){

    Node *current = matriz->linhas[l],*retorno = NULL;

    while(current != NULL){
        if(current->c == c){
            retorno = current;
        }
        current = current->next_l;
    }
    return retorno;
}//implementada

void matriz_densa_print(Matriz *m){
    Node *current;
    for(int i = 0; i < m->qtd_linhas;i++){
        current = m->linhas[i];
        for(int j = 0; j < m->qtd_colunas; j++){
            if(current != NULL){
                if(current->c == j){
                    printf("%.2f ",current->value);
                    current = current->next_l;
                }else{
                    printf("0.00 ");
                }
            }else{
                printf("0.00 ");
            }
        }
        printf("\n");
    }
}//implementada

Matriz *matriz_soma(Matriz *a, Matriz *b){
    Matriz *soma = matriz_construct(a->qtd_linhas,a->qtd_colunas);
    if((a->qtd_linhas != b->qtd_linhas)||(a->qtd_colunas != b->qtd_colunas)){
        printf("Impossivel somar duas matrizes de tamanhos diferentes!\nMatriz A: %dX%d\nMatriz B: %dX%d",
		a->qtd_linhas,a->qtd_colunas,b->qtd_linhas,b->qtd_colunas);
    }else{
        int linha = 0,coluna_a = 0,coluna_b = 0;
        float valor_soma = 0;
        Node *celula_a, *celula_b;
        for(linha = 0;linha< a->qtd_linhas;linha++){
            celula_a = a->linhas[linha];
            celula_b = b->linhas[linha];
            while((celula_a != NULL)||(celula_b != NULL)){
                celula_a == NULL ? coluna_a = a->qtd_colunas : (coluna_a = celula_a->c);
                celula_b == NULL ? coluna_b = b->qtd_colunas : (coluna_b = celula_b->c);
                if(coluna_a > coluna_b){
                    matriz_node_mudar_valor(celula_b->l,celula_b->c,soma,celula_b->value);
                    celula_b = celula_b->next_l;
                }else if(coluna_a < coluna_b){//trocas celulas nas condicionais
                    matriz_node_mudar_valor(celula_a->l,celula_a->c,soma,celula_a->value);
                    celula_a = celula_a->next_l;
                }else{
                    valor_soma = 0;
                    valor_soma = celula_a->value + celula_b->value;
                    matriz_node_mudar_valor(celula_a->l,celula_a->c,soma,valor_soma);
                    celula_a = celula_a->next_l;//tratar o caso de celula_a ou b ser NULL e der segmenataultion fault ao tentar acessar o número de colunas
                    celula_b = celula_b->next_l;//tratar do caso de troca de linha
                }
            }
        }
    }
    return soma;
}//implementada, muito grande 

void matriz_esparsa_print(Matriz *a){
    Node *current;
    int qtd_celulas = 0;
    for(int i = 0; i < a->qtd_linhas; i++){
        current = a->linhas[i];
        while(current != NULL){
            printf("Linha: %d Coluna: %d Valor: %f\n",i,current->c,current->value);
            current = current->next_l;
            qtd_celulas++;
        }
    }
    if(qtd_celulas == 0){
        printf("Matriz nula!\n");
    }
}

Matriz *matriz_multiplicar_escalar(Matriz *a, float num){
    Node *current;
    Matriz *b = matriz_construct(a->qtd_linhas,a->qtd_colunas);
    for(int i = 0; i < a->qtd_linhas; i++){
        current = a->linhas[i];
        while(current != NULL){
            matriz_node_mudar_valor(i,current->c,b,num*(current->value));
            current = current->next_l;
        }
    }
    return b;
}