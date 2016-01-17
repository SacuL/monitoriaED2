#include <No.h>

#ifndef AVL_H
#define AVL_H

class AVL
{
    public:
        AVL();
        void insere(int p);
        void remover(int p);
        No** getRaiz();
        ~AVL();

    private:
        No *raiz;
        No* rotacao_direita(No* N3);
        No* rotacao_esquerda(No* N1);
        No* rotacao_dupla_direita(No* N3);
        No* rotacao_dupla_esquerda(No* N1);
        No* CorrigeAVL(No* p);
        No* InsereAVL(No* p, int ch);
        No* Consulta(No* p, char ch);
        No* RemoveAVL(No* p);
        No* Remove(No* p, char ch);
        int Altura (No* p);
        int Calcula_FB(No* p);
        void Seta_FB(No* p);
        void deletaH(No* p);
};

#endif // AVL_H
