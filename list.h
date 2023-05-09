#ifndef _LIST_
#define _LIST_

#include "node.h"

typedef enum Type_list {Linha, Coluna};
// 0 = falso, !0 = true; Linha = 0, Linha = 1;

typedef struct List 
{
    struct Node *head;
    int size;
    Type_list type;
} List;

List *list_construct(Node *head, Type_list type);
void list_delete(List *l);

#endif