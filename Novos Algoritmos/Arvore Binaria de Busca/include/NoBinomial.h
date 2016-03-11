#ifndef NO_BINOMIAL_H
#define NO_BINOMIAL_H
#include <stdlib.h>

class No_Binomial
{
    public:

        No_Binomial(int v){
            pai = NULL;
            filho = NULL;
            irmao = NULL;
            valor = v;
            grau = 0;
        };
        ~No_Binomial(){};
        No_Binomial* getPai(){return pai;}
        No_Binomial* getFilho(){return filho;}
        No_Binomial* getIrmao(){return irmao;}
        int getValor(){return valor;}
        int getGrau(){return grau;}
        void setPai(No_Binomial* p){pai = p;}
        void setFilho(No_Binomial* f){filho = f;}
        void setIrmao(No_Binomial* i){irmao = i;}
        void setValor(int v){valor = v;}
        void setGrau(int g){grau = g;}
        void incrementaGrau(){grau++;}
    private:
        No_Binomial* pai;
        No_Binomial* filho;
        No_Binomial* irmao;
        int valor;
        int grau;
};

#endif // NO_H
