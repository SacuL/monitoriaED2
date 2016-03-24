#ifndef NO_H
#define NO_H
#include <stdlib.h>
#define VERMELHO 0
#define PRETO 1

class No
{
    public:

        No(int v){
            pai = NULL;
            proximo = NULL;
            anterior = NULL;
            cor = VERMELHO;
            valor = v;
        };
        ~No(){};
        No* getProx(){return proximo;}
        No* getAnt(){return anterior;}
        No* getPai(){return pai;}
        int getValor(){return valor;}
        int getCor(){return cor;}
        void setProx(No* p){proximo = p;}
        void setAnt(No* a){anterior = a;}
        void setPai(No* pa){pai = pa;}
        void setValor(int v){valor = v;}
        void setCor(int c){cor = c;}
        No* getAvo(){
            if(pai != NULL){
                return pai->getPai();
            }
            return NULL;
        };
        No* getTio(){
            No* avo = getAvo();
            if(avo == NULL){
                return NULL;
            }
            if(pai == avo->getAnt()){
                return avo->getProx();
            }else{
                return avo->getAnt();
            }
        };

    private:
        No* proximo;
        No* anterior;
        No* pai;
        int valor;
        int cor;

};

#endif // NO_H
