#ifndef _LIST_
#define _LIST_

#include "list.h"

typedef struct Matrix 
{
    List *linhas;
    int qtd_linhas;
    List *colunas;
    int qtd_colunas;
} Matrix;

Matriz *matriz_construct();

void matriz_destroy(Matriz *matriz);
//Não mudado da lista ainda List *list_construct(Node *head, Type_list type);
//Não mudado da lista ainda List void list_delete(List *l);

#endif