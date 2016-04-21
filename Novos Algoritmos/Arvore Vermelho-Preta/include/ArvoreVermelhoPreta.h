#include <No.h>

#ifndef ArvoreVermelhoPreta_H
#define ArvoreVermelhoPreta_H

class ArvoreVermelhoPreta
{
    public:
        ArvoreVermelhoPreta();
        void insere(int valor);
        void remover(int p);
        No** getRaiz();
        ~ArvoreVermelhoPreta();

    private:
        No* raiz;
        void insereAVP(No* no,No* pai, int valor);
        void deletaH(No* p);
        void corrigeCaso1(No* no);
        void corrigeCaso2(No* no);
        void corrigeCaso3(No* no);
        void corrigeCaso4(No* no);
        void corrigeCaso5(No* no);
        void rotacaoEsquerda(No* no);
        void rotacaoDireita(No* no);
        void removerCaso1(No* n);
        void removerCaso2(No* n);
        void removerCaso3(No* n);
        void removerCaso4(No* n);
        void removerCaso5(No* n);
        void removerCaso6(No* n);
        No* getPredecessor(No* no);
        No* getIrmao(No* no);
        void trocaNos(No* noVelho, No* noNovo);


};

#endif // ArvoreVermelhoPreta_H
