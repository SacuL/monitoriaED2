#ifndef ARVORE_BINARIA_H_INCLUDED
#define ARVORE_BINARIA_H_INCLUDED

#include <No.h>

class ABB
{
    public:
        ABB();
        void inserir(int p);
        void remover(int p);
        No** getRaiz();
        ~ABB();

    private:
        No* raiz;
        No* insereAux(No* p, int ch);
        void removeAux(No* no, No* pai, int valor);
        void deletaH(No* no);
};

#endif // ARVORE_BINARIA_H_INCLUDED
