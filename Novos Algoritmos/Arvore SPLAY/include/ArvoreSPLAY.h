#include <No.h>

#ifndef ARVORESPLAY_H
#define ARVORESPLAY_H

class ArvoreSPLAY
{
    public:
        ArvoreSPLAY();
        void insere(int valor);
        No* buscar(int valor);
        void remover(int valor);
        No** getRaiz();
        ~ArvoreSPLAY();

    private:
        No* raiz;
        No* removerH(No *p, int valor);
        No* sucessor(No* x);
        No* buscarH(No* p, int valor);
        No* rightRotation(No *p, No* r);
        No* leftRotation(No *p, No* r);
        No* insere(No* no, int valor);
        void splay (No *x, No *raiz);
        void deletaH(No* p);
};

#endif // ArvoreSPLAY_H
