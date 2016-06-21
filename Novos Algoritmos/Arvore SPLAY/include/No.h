#ifndef NO_H
#define NO_H
#include <stdlib.h>

class No
{
    public:

        No(int v){
            pai = NULL;
            proximo = NULL;
            anterior = NULL;
            valor = v;
        };
        ~No(){};
        No* getProx(){return proximo;}
        No* getAnt(){return anterior;}
        No* getPai(){return pai;}
        int getValor(){return valor;}
        void setProx(No* p){proximo = p;}
        void setAnt(No* a){anterior = a;}
        void setValor(int v){valor = v;}
        void setPai(No* p){pai = p;}
    private:
        No* proximo;
        No* anterior;
        No* pai;
        int valor;

};

#endif // NO_H
