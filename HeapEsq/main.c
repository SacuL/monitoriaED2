#include <stdio.h>
#include <stdlib.h>
#include "DSGraph.h"
#include <math.h>

typedef struct NODE_STRUCTURE No;

No* criaHeapEsq(No* pNodo, int ch){
    pNodo =(No*)malloc(sizeof(No));
    pNodo->valor= ch;
    pNodo->marca= 1;
    pNodo->anterior= NULL;
    pNodo->proximo= NULL;
    return pNodo;
    }

int menor(a, b){
    if (a<b)
        return a;
    else return b;
}

int calculaDist(No* p){
    if(p == NULL) return 0;
    return (1 + menor( calculaDist(p->anterior) , calculaDist(p->proximo)));
}


No* uniaoHeapEsq(No* H1, No* H2){
    if(H1 == NULL) return H2;
    if(H2 == NULL) return H1;
    if(H1->valor < H2->valor){
        No* aux = (No*)malloc(sizeof(No));
        aux = H1;
        H1 = H2;
        H2 = aux;
    }
    if(H1->anterior == NULL)
        H1->anterior = H2;
    else{
        No* H = (No*)malloc(sizeof(No));
        H = H1->proximo;
        H = uniaoHeapEsq(H, H2);
        H1->proximo = H;
        H1->anterior->marca = calculaDist(H1->anterior);
        H1->proximo->marca = calculaDist(H1->proximo);
        if(H1->anterior->marca < H1->proximo->marca){
            No* aux = (No*)malloc(sizeof(No));
            aux = H1->anterior;
            H1->anterior = H1->proximo;
            H1->proximo = aux;
        }

    }
    H1->marca = calculaDist(H1) + 1;
    return H1;
}

No* insere(No* H, int x){
    if(H == NULL) return criaHeapEsq(H, x);
    No* H2 = criaHeapEsq(H2, x);
    H = uniaoHeapEsq(H, H2);
    return H;
}

int removeValor(No* H){
    int x = H->valor;
    H = uniaoHeapEsq(H->anterior, H->proximo);
    return x;
}



int main()
{
    No* raiz = insere(NULL, 4);
    raiz = insere(raiz, 3);
    raiz = insere(raiz, 2);
    raiz = insere(raiz, 1);
    raiz = insere(raiz, 16);
    raiz = insere(raiz, 8);
    raiz = insere(raiz, 7);

    No* raiz2 = insere(NULL, 15);
    raiz2 = insere(raiz2, 8);
    raiz2 = insere(raiz2, 9);
    raiz2 = insere(raiz2, 7);
    raiz2 = insere(raiz2, 5);

    No* result = uniaoHeapEsq(raiz, raiz2);
    printf("%d \n", calculaDist(result));
    printf("%d", result->anterior->proximo->anterior->valor);
}
