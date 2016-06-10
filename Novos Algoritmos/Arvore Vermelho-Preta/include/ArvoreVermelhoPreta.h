#include "No_VP.h"

#ifndef ArvoreVermelhoPreta_H
#define ArvoreVermelhoPreta_H

class ArvoreVermelhoPreta
{
    public:
        ArvoreVermelhoPreta();
        void insere(int valor);
        void remover(int p);
        No_VP** getRaiz();
        ~ArvoreVermelhoPreta();

    private:
        No_VP* raiz;
        void insereAVP(No_VP* no,No_VP* pai, int valor);
        void deletaH(No_VP* p);
        void corrigeCaso1(No_VP* no);
        void corrigeCaso2(No_VP* no);
        void corrigeCaso3(No_VP* no);
        void corrigeCaso4(No_VP* no);
        void corrigeCaso5(No_VP* no);
        void rotacaoEsquerda(No_VP* no);
        void rotacaoDireita(No_VP* no);
        void removerCaso1(No_VP* n);
        void removerCaso2(No_VP* n);
        void removerCaso3(No_VP* n);
        void removerCaso4(No_VP* n);
        void removerCaso5(No_VP* n);
        void removerCaso6(No_VP* n);
        No_VP* getPredecessor(No_VP* no);
        No_VP* getIrmao(No_VP* no);
        void trocaNos(No_VP* noVelho, No_VP* noNovo);


};

#endif // ArvoreVermelhoPreta_H
