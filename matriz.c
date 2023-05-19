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
            printf("%d %d\n",i,j);
        }
    }
}//implementada

void matriz_node_mudar_valor(int l, int c, Matriz *matriz, float valor){

    Node *celula = matriz_node_get(l,c,matriz);

    if(celula != NULL){
        celula->value = valor;
    }else{
        celula = node_construct(l,c,valor,NULL,NULL);
        matriz_inserir_celula(matriz,celula);
    }
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
                    printf("0 ");
                }
            }else{
                printf("0 ");
            }
        }
        printf("\n");
    }
}//implementada

Matriz *matriz_soma(Matriz *a, Matriz *b){
    Matriz *soma = NULL;
    if((a->qtd_linhas != b->qtd_linhas)||(a->qtd_colunas != b->qtd_colunas)){
        printf("Impossivel somar duas matrizes de tamanhos diferentes!\nRetornando um ponteiro NULL!!
        \nMatriz A Linha: %d Coluna: %d\nMatriz B Linha: %d Coluna: %d",a->qtd_linhas,a->qtd_colunas,b->qtd_linhas,b->qtd_colunas);
    }else{
        int linha = 0,coluna_a = 0,coluna_b = 0;
        float valor_soma = 0;
        soma = matriz_construct(a->qtd_linhas,a->qtd_colunas);
        Node *celula_a, *celula_b;
        for(linha = 0;linha< a->qtd_linhas;linha++){
            celula_a = a->linhas[linha];
            celula_b = b->linhas[linha];
            while((celula_a != NULL)||(celula_b != NULL)){
                co >= 0 ? numero++ : numero--;
                if(celula_a->c > celula_b->c){
                    matriz_node_mudar_valor(celula_b->l,celula_b->c,soma,celula_b->value);
                    celula_b = celula_b->next_l;
                }else if(celula_a->c > celula_b->c){
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
}