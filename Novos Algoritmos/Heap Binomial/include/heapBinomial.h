#ifndef HEAPBINOMIAL_H
#define HEAPBINOMIAL_H
#include "NoBinomial.h"

class heapBinomial
{
    public:
        No_Binomial* cabeca;

        void insere(int x);
        void uniaoHeapsBinomiais(No_Binomial* h);
        void imprimeHeapConsole();
        void imprimeArvoreConsole(No_Binomial* n);
        No_Binomial* remover();
        heapBinomial();
        ~heapBinomial();
    private:
        No_Binomial* criaNo(int ch);
        No_Binomial* getCabeca();
        No_Binomial* somaArvoresBinomiais(No_Binomial* a1, No_Binomial* a2);
        No_Binomial* intercalacaoHeapsBinomiais(No_Binomial* h1, No_Binomial* h2);
        No_Binomial* uniaoHeapsBinomiais(No_Binomial* h1, No_Binomial* h2);
        void deletaH(No_Binomial* n);

};

#endif // HEAPBINOMIAL_H
