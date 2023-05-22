#include "matriz.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>

//OBS: quando me refiro a N nas notações com O estou me referindo ao número de elementos não nulos na matriz

Matriz *matriz_construct(int l, int c){
    Matriz *m = (Matriz *)calloc(1,sizeof(Matriz));
    m->qtd_linhas = l;
    m->qtd_colunas = c;
    m->linhas = (Node**)calloc(l,sizeof(Node*));
    m->colunas = (Node**)calloc(c,sizeof(Node*));
    return m;
}//Complexidade do tempo: O(1), pois tem um tempo de execução constante porque não ha loop na função

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
}//Complexidade do tempo: O(1), pois tem um tempo de execução constante porque não ha loop na função

void matriz_read(Matriz *m){
    float v;
    for(int i = 0; i < m->qtd_linhas; i++){
        for(int j = 0; j < m->qtd_colunas; j++){
            scanf("%f",&v);
            matriz_node_mudar_valor(i,j,m,v);
        }
    }
}
/*Complexidade do tempo: O(N^2), pois se trata de dois loops encadeados, ou seja, aumento de +1 iteração no
loop de fora acarretaria em mais n iterações no de dentro*/

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
}
//Complexidade do tempo: O(1), pois tem um tempo de execução constante porque não ha loop na função

void matriz_apaga_celula(Matriz *m, Node *celula){

    Node *prev;

    //Acertar linhas
    prev = node_prev_linha(m->linhas[celula->l],celula);
    if(prev == NULL){
        m->linhas[celula->l] = celula->next_l;
    }else{
        prev->next_l = celula->next_l;
    }
    
    //Acertar colunas   
    prev = node_prev_coluna( m->colunas[celula->c],celula);
    if(prev == NULL){
         m->colunas[celula->c] = celula->next_c;
    }else{
        prev->next_c = celula->next_c;
    }
    node_destroy(celula);
}
//Complexidade do tempo: O(1), pois tem um tempo de execução constante porque não ha loop na função

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
}
//Complexidade do tempo: O(1), pois tem um tempo de execução constante porque não ha loop na função

Node *matriz_node_get(int l, int c, Matriz *matriz){

    Node *current = matriz->linhas[l],*retorno = NULL;

    while(current != NULL){
        if(current->c == c){
            retorno = current;
        }
        current = current->next_l;
    }
    return retorno;
}
/*Complexidade do tempo: O(N), pois se trata de uma busca linear, ou seja, 
quanto mais distante o componente procurado se encontra do head da linha mais demorar*/

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
}
/*Complexidade do tempo: O(N^2), pois se trata de dois loops encadeados, ou seja, aumento de +1 iteração no
loop de fora acarretaria em mais n iterações no de dentro*/

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
}
/*Complexidade do tempo: O(N^2), pois se trata de dois loops encadeados, ou seja, aumento de +1 iteração no
loop de fora acarretaria em mais n iterações no de dentro*/

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
/*Complexidade do tempo: O(N^2), pois se trata de dois loops encadeados, ou seja, aumento de +1 iteração no
loop de fora acarretaria em mais n iterações no de dentro*/

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
/*Complexidade do tempo: O(N^2), pois se trata de dois loops encadeados, ou seja, aumento de +1 iteração no
loop de fora acarretaria em mais n iterações no de dentro*/

Matriz *matriz_multiplicacao_ponto_a_ponto(Matriz *a, Matriz *b){
    Matriz *c = matriz_construct(a->qtd_linhas,a->qtd_colunas);
    if((a->qtd_linhas != b->qtd_linhas)||(a->qtd_colunas != b->qtd_colunas)){
        printf("Impossivel multiplicar ponto a ponto duas matrizes de tamanhos diferentes!\nMatriz A: %dX%d\nMatriz B: %dX%d",
		a->qtd_linhas,a->qtd_colunas,b->qtd_linhas,b->qtd_colunas);
    }else{
        Node *celula_a, *celula_b;
        for(int i = 0; i < a->qtd_linhas; i++){
        celula_a = a->linhas[i];
        celula_b = b->linhas[i];
        while((celula_b != NULL)&&(celula_a != NULL)){
            if(celula_b->c == celula_a->c){
                matriz_node_mudar_valor(i,celula_a->c,c,(celula_a->value)*(celula_b->value));
                celula_a = celula_a->next_l;
                celula_b = celula_b->next_l;
            }else if(celula_b->c > celula_a->c){
                celula_a = celula_a->next_l;
            }else{
                celula_b = celula_b->next_l;
            }
        }
    }
    }
    return c;
}
/*Complexidade do tempo: O(N^2), pois se trata de dois loops encadeados, ou seja, aumento de +1 iteração no
loop de fora acarretaria em mais n iterações no de dentro*/

Matriz *matriz_troca_linhas(int l1, int l2, Matriz *a){
  if((l1 < a->qtd_linhas)&&(l2 < a->qtd_linhas)){
    Node *current;
    Matriz *b = matriz_construct(a->qtd_linhas,a->qtd_colunas);
    for(int i = 0; i < a->qtd_linhas; i++){
        if(i == l1){
            current = a->linhas[l2];
            while(current != NULL){
                matriz_node_mudar_valor(l1,current->c,b,current->value);
                current = current->next_l;
            }
        }else if(i == l2){
            current = a->linhas[l1];
            while(current != NULL){
                matriz_node_mudar_valor(l2,current->c,b,current->value);
                current = current->next_l;
            }
        }else{
            current = a->linhas[i];
            while(current != NULL){
                matriz_node_mudar_valor(i,current->c,b,current->value);
                current = current->next_l;
            }
        }
    }
    return b;
  }else{
    printf("Matriz não tem linhas suficientes\n");
    return NULL;
  }
}
/*Complexidade do tempo: O(N^2), pois se trata de dois loops encadeados, ou seja, aumento de +1 iteração no
loop de fora acarretaria em mais n iterações no de dentro*/

Matriz *matriz_troca_colunas(int c1, int c2, Matriz *a){
    if((c1 < a->qtd_colunas)&&(c2 < a->qtd_colunas)){
    Node *current;
    Matriz *b = matriz_construct(a->qtd_linhas,a->qtd_colunas);
    for(int i = 0; i < a->qtd_colunas; i++){
        if(i == c1){
            current = a->colunas[c2];
            while(current != NULL){
                matriz_node_mudar_valor(current->l,c1,b,current->value);
                current = current->next_c;
            }
        }else if(i == c2){
            current = a->colunas[c1];
            while(current != NULL){
                matriz_node_mudar_valor(current->l,c2,b,current->value);
                current = current->next_c;
            }
        }else{
            current = a->colunas[i];
            while(current != NULL){
                matriz_node_mudar_valor(current->l,i,b,current->value);
                current = current->next_c;
            }
        }
    }
    return b;
   }else{
    printf("Matriz não tem colunas suficientes\n");
    return NULL;
  }
}
/*Complexidade do tempo: O(N^2), pois se trata de dois loops encadeados, ou seja, aumento de +1 iteração no
loop de fora acarretaria em mais n iterações no de dentro*/

Matriz *matriz_multiplicacao(Matriz *a, Matriz *b){
    if(a->qtd_colunas == b->qtd_linhas){
        Node *celula_a, *celula_b;
        float soma = 0;
        int i = 0, j = 0;
        Matriz *c = matriz_construct(a->qtd_linhas,b->qtd_colunas); 
        while(i < a->qtd_linhas){
            soma = 0;
            celula_a = a->linhas[i];
            celula_b = b->colunas[j];
            while((celula_a != NULL)&&(celula_b != NULL)){
                if(celula_a->c == celula_b->l){
                    soma = soma + ((celula_a->value)*(celula_b->value));
                    celula_a = celula_a->next_l;
                    celula_b = celula_b->next_c;
                }else if(celula_a->c < celula_b->l){
                    celula_a = celula_a->next_l;
                }else{
                    celula_b = celula_b->next_c;
                }
            }
            if(soma != 0){
                matriz_node_mudar_valor(i,j,c,soma);
            }
            j++;
            if(j == b->qtd_colunas){
                i++;
                j = 0;
            }
        }
        return c;
    }else{
        printf("Impossível multiplicar a Matriz A pela Matriz B\n");
        return NULL;
    }
}
/*Complexidade do tempo: O(N^3) para matrizes quadradas e O(M*N*O) p/ matrizes com dimensões (M x N) e (N x O),
 pois se trata de três loops encadeados, ou seja, aumento de +1 iteração no loop de fora acarretaria em 
 mais n iterações no de dentro, o que acarretaria em n*m interações no loop mais interno*/

Matriz *matriz_slice(Matriz *a, int l_inicio, int c_inicio, int l_fim, int c_fim){

    if(((l_fim-l_inicio+1) > 0)&&((c_fim-c_inicio + 1)>0)){
        Matriz *b = matriz_construct(l_fim-l_inicio+1,c_fim-c_inicio+1);
        Node *current;
        int i = l_inicio,j = c_inicio;
        while(i<=l_fim){
            current = a->linhas[i];
            if(current != NULL){
                j = current->c;
            }
            while((j<=c_fim)&&(current != NULL)){
                matriz_node_mudar_valor(i-l_inicio,j-c_inicio,b,current->value);
                current = current->next_l;
                if(current != NULL){
                    j = current->c;
                }
            }
            i++;
        }
        return b;
    }else{
        printf("Slice vazio ou negativo, impossível de localizar\n");
        return NULL;
    }
}
/*Complexidade do tempo: O(N^2), pois se trata de dois loops encadeados, ou seja, aumento de +1 iteração no
loop de fora acarretaria em mais n iterações no de dentro*/

Matriz *matriz_transposta(Matriz *a){
    Matriz *b = matriz_construct(a->qtd_colunas,a->qtd_linhas);
    int i = 0;
    Node *current;
    while((current != NULL)||(i < a->qtd_colunas)){
        current = a->colunas[i];
        while(current != NULL){
            matriz_node_mudar_valor(current->c,current->l,b,current->value);
            current = current->next_c;
        }
        i++;
    }
    return b;
}
/*Complexidade do tempo: O(N^2), pois se trata de dois loops encadeados, ou seja, aumento de +1 iteração no
loop de fora acarretaria em mais n iterações no de dentro*/

int Matriz_size(Matriz *m){
    int qtd = 0,i = 0;
    Node *current = NULL;
    while((current != NULL)||(i<m->qtd_linhas)){
        current = m->linhas[i];
        while(current != NULL){
            if(current != NULL){
                qtd++;
            }
            current = current->next_l;
        }
        i++;
    }
    return qtd;
}

void matriz_escrever_binario(FILE *f, Matriz *a){
    if(f != NULL){
        int qtd = Matriz_size(a);
        fwrite(&(a->qtd_linhas),1,sizeof(int),f);
        fwrite(&(a->qtd_colunas),1,sizeof(int),f);
        fwrite(&qtd,1,sizeof(int),f);
        Node *current = NULL;
        int i = 0;
        while((current != NULL)||(i < a->qtd_linhas)){
            current = a->linhas[i];
            while(current != NULL){
                fwrite(&(current->l),1,sizeof(int),f);
                fwrite(&(current->c),1,sizeof(int),f);
                fwrite(&(current->value),1,sizeof(float),f);
                current = current->next_l;
            }
            i++;
        }
    }else{
        printf("Arquivo vazio!\n");
    }
}
/*Complexidade do tempo: O(N^2), pois se trata de dois loops encadeados, ou seja, aumento de +1 iteração no
loop de fora acarretaria em mais n iterações no de dentro*/

Matriz *matriz_ler_binario(FILE *f){
    if(f != NULL){
        int l,c,retorno = 1,qtd;
        float valor;
        fread(&l, 1, sizeof(int), f);
        fread(&c, 1, sizeof(int), f);
        fread(&qtd,1,sizeof(int),f);
        Matriz *a = matriz_construct(l,c);
        for(int i = 0; i<qtd;i++){
            retorno = fread(&l, 1, sizeof(int), f);
            fread(&c, 1, sizeof(int), f);
            fread(&valor,1,sizeof(float),f);
            if(retorno != 0){
                matriz_node_mudar_valor(l,c,a,valor);
            }
        }
        return a;
    }else{
        printf("Arquivo vazio!\n");
        return NULL;
    }
}
/*Complexidade do tempo: O(N^2), pois se trata de dois loops encadeados, ou seja, aumento de +1 iteração no
loop de fora acarretaria em mais n iterações no de dentro*/

void matriz_anular(Matriz *a){
    int i = 0,l,c;
    Node *current,*next;
    while((i < a->qtd_linhas)||(current != NULL)){
        current = a->linhas[i];
        while(current != NULL){
            l = current->l;
            c = current->c;
            next = current->next_l;
            matriz_node_mudar_valor(l,c,a,0);
            current = next;
        }
        i++;
    }
}
/*Complexidade do tempo: O(N^2), pois se trata de dois loops encadeados, ou seja, aumento de +1 iteração no
loop de fora acarretaria em mais n iterações no de dentro*/

float matriz_somar_elementos(Matriz *a){
    int i = 0;
    float soma = 0;
    Node *current;
    while((i < a->qtd_linhas)||(current != NULL)){
        current = a->linhas[i];
        while(current != NULL){
            soma = soma + current->value;
            current = current->next_l;
        }
        i++;
    }
    return soma;
}
/*Complexidade do tempo: O(N^2), pois se trata de dois loops encadeados, ou seja, aumento de +1 iteração no
loop de fora acarretaria em mais n iterações no de dentro*/

Matriz *matriz_covulacao(Matriz *a, Matriz *kernel){
    Matriz *b = matriz_construct(a->qtd_linhas,a->qtd_colunas),
    *submatriz = matriz_construct(kernel->qtd_linhas,kernel->qtd_colunas),*ponto_a_ponto;
    int i = 0, j = 0,l_inicio,c_inicio,c_fim,i_sub,j_sub;
    float soma = 0;
    Node *current_sub;
    if((kernel->qtd_linhas == kernel->qtd_colunas)&&(kernel->qtd_colunas%2 == 1)){
        while(i < a->qtd_linhas){
            for(j = 0; j < a->qtd_colunas; j++){
                l_inicio = i - (kernel->qtd_linhas/2);
                c_inicio = j - (kernel->qtd_colunas/2);
                c_fim = j + (kernel->qtd_colunas/2);
                i_sub = 0;
                j_sub = 0;
                while(i_sub < submatriz->qtd_linhas){
                    if((i_sub + l_inicio >= 0)&&(i_sub + l_inicio < a->qtd_linhas)){
                        current_sub = a->linhas[i_sub + l_inicio];
                        j_sub = current_sub->c;
                        while((j_sub<=c_fim)&&(current_sub != NULL)){
                            if(j_sub >= c_inicio){
                                matriz_node_mudar_valor(i_sub,j_sub-c_inicio,submatriz,current_sub->value);
                            }
                            current_sub = current_sub->next_l;
                            if(current_sub != NULL){
                                j_sub = current_sub->c;
                            }
                        }
                    }
                    i_sub++;
                }
                ponto_a_ponto = matriz_multiplicacao_ponto_a_ponto(submatriz,kernel);
                soma = matriz_somar_elementos(ponto_a_ponto);
                if(soma != 0){
                    matriz_node_mudar_valor(i,j,b,soma);
                }
                matriz_anular(submatriz);
                matriz_destroy(ponto_a_ponto);
            }
            i++;
        }
        matriz_destroy(submatriz);
        return b;
    }else{
        printf("Kernel tem que ser uma matriz quadrada de número impar para conseguir calcular elemento central\n");
        matriz_destroy(submatriz);
        return NULL;
    }
}

/*Complexidade do tempo: O(M*N*O*P) p/ matrizes com dimensões (M x N) e (O x P),
 pois se trata de quatro loops encadeados, ou seja, aumento de +1 iteração no loop de fora acarretaria em 
 mais n iterações no de dentro, o que acarretaria em n*m interações no loop mais interno, e assim por diante*/