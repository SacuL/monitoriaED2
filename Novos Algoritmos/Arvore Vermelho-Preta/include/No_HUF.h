#ifndef NO_HUF_H
#define NO_HUF_H
#include <stdlib.h>

class No_HUF
{
    public:

        No_HUF(){esq = NULL; dir = NULL; prox = NULL; caracter = 0;}
        ~No_HUF(){};
        char getChar(){return caracter;}
        No_HUF *getEsq(){return esq;}
        No_HUF *getDir(){return dir;}
        No_HUF *getProx(){return prox;}
        int getFreq(){return freq;}
        void setEsq(No_HUF *n){esq = n;}
        void setDir(No_HUF *n){dir = n;}
        void setProx(No_HUF *n){prox = n;}
        void setChar(char c){caracter = c;}
        void setFreq(int f){freq = f;}

    private:
        char caracter;
        int freq;
        No_HUF *esq;
        No_HUF *dir;
        No_HUF *prox;
};

#endif // NO_HUF_H
