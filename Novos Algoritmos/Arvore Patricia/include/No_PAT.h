#ifndef NO_PAT_H
#define NO_PAT_H
#include <iostream>

using namespace std;

class No_PAT{

    public:
        No_PAT(int tamAlfabeto){

            posPref = -1;
            tamAlfa = tamAlfabeto;
            filhos = new No_PAT*[tamAlfa+1];
            for(int i = 0; i <= tamAlfa; i++){

                filhos[i] = NULL;

            }
        }
        ~No_PAT(){

            for(int i = 0; i <= tamAlfa; i++){

                if(filhos[i] != NULL){

                    delete filhos[i];

                }

            }

        }
        string getChave(){return chave;}
        void setChave(string c){chave = c;}
        void setPosPref(int p){posPref = p;}
        int getPosPref(){return posPref;}
        int getTamAlfa(){return tamAlfa;}
        void clearChave(){chave.clear();}
        No_PAT *getFilho(char c){

            if(c == '\0'){

                return filhos[tamAlfa];

            }
            return filhos[c-97];

        }
        void setFilho(char c, No_PAT* p){

            if(c == '\0'){

                filhos[tamAlfa] = p;

            }else{

                filhos[c-97] = p;

            }


        }

    private:
        string chave;
        int posPref;
        No_PAT** filhos;
        int tamAlfa;

};

#endif // NO_PAT

