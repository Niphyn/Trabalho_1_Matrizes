#ifndef _NODE_
#define _NODE_

typedef struct Node 
{
    int l;
    int c;
    float value;
    struct Node *next_l;
    struct Node *next_c;
} Node;

Node *node_construct(int l, int c, float value, Node *next_l, Node *next_c);

void node_destroy(Node *node);

Node *node_prev_linha(Node *head_linha, Node *searched);

Node *node_prev_coluna(Node *head_coluna, Node *searched);

#endif