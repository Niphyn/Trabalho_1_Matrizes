#include "matriz.h"
#include "list.h"
#include <stdio.h>

Matriz *matriz_construct(){
    Matriz *m = (Matriz *)calloc(1,sizeof(Matriz));
    m->qtd_linhas = 0;
    m->qtd_colunas = 0;
    m->linhas = list_construct();
    m->colunas = list_construct();
    return m;
}

void matriz_destroy(Matriz *m){
    list_destroy(m->colunas);
    list_destroy(m->linhas);
    free(matriz);
}