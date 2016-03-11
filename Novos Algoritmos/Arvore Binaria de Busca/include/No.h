#ifndef NO_H
#define NO_H
#include <stdlib.h>

class No
{
    public:

        No(){
            direita = NULL;
            esquerda = NULL;
        };
        ~No(){};
        No* getDireita(){return direita;}
        No* getEsquerda(){return esquerda;}
        int getValor(){return valor;}
        void setDireita(No* p){direita = p;}
        void setEsquerda(No* a){esquerda = a;}
        void setValor(int v){valor = v;}
    private:
        No* direita;
        No* esquerda;
        int valor;
};

#endif // NO_H
