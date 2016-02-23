#ifndef HEAPESQ_H
#define HEAPESQ_H
#include "No.h"

class heapEsq
{
public:
    heapEsq();
    No* criaHeapEsq(int ch);
    void insere(int x);
    No* uniaoHeapEsq(No* H1, No* H2);
    void imprimeHeap();
    void remover(int x);
    No* getRaiz();
    ~heapEsq();
private:
    No* H;
    int menor(int a, int b);
    int calculaDist(No* p);
    void deletaH(No* H1);
    void imprime(No* H1);
    No* buscaPai(No* H1, int x);

};

#endif // HEAPESQ_H
