#ifndef _LIST_
#define _LIST_

#include "node.h"

typedef struct List 
{
    struct Node *head;
    int size;
} List;

List *list_construct();
void list_destroy(List *l);

#endif