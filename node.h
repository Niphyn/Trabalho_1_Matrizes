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
void node_delete(Node *node);

#endif