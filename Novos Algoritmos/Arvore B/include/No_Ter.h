#ifndef NO_TER_H
#define NO_TER_H
#include <stdlib.h>

class No_Ter
{
    public:
        No_Ter(){

            esq = NULL;
            dir = NULL;
            meio = NULL;
            chave = false;

        }
        No_Ter *getEsq(){return esq;}
        No_Ter *getDir(){return dir;}
        No_Ter *getMeio(){return meio;}
        char getChar(){return c;}
        bool getChave(){return chave;}
        void setEsq(No_Ter *p){esq = p;}
        void setDir(No_Ter *p){dir = p;}
        void setMeio(No_Ter *p){meio = p;}
        void setChar(char cc){c = cc;}
        void setChave(bool c){chave = c;}
        ~No_Ter(){}
    private:
        No_Ter *esq;
        No_Ter *meio;
        No_Ter *dir;
        char c;
        bool chave;

};

#endif // NO_TER_H
