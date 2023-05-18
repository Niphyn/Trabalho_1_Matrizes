#include "list.h"
#include <stdio.h>

List *list_construct(){
    List *l = (List *)calloc(1,sozeof(List));
    l->size = 0;
    l->head = NULL;
}

int list_enpty(List *l){
    if(l->head == NULL){
        return 1;
    }else{
        return 0;
    }
}

void list_destroy(List *l){
    if(list_enpty){
        free (l);
    }else{
        Node *now = l->head,*next;
        for(int i = 0; i < l->size; i++){
            next = now->next_c;
            node_destroy(now);
            now = next;
        }
        free(l);
    }
}