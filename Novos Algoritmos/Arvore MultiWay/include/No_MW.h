#ifndef NO_MW_H
#define NO_MW_H
#include <iostream>

using namespace std;

class No_MW
{
    public:
        No_MW(int tamAlfabeto){

            chave = false;
            chars = new No_MW*[tamAlfabeto];
            for(int i = 0 ; i < tamAlfabeto ; i ++){
                chars[i] = NULL;
            }
            tamAlfa = tamAlfabeto;
        }
        bool getChave(){return chave;}
        void setChave(bool c){chave = c;}
        No_MW* setChar(char c){

            if(chars[c - 97] != NULL){

                return chars[c - 97];

            }else{

                chars[c - 97] = new No_MW(tamAlfa);
                return chars[c - 97];

            }


        }No_MW* getChar(char c){

            return chars[c - 97];

        }
        bool ehNULL(){

            for(int i = 0; i < tamAlfa; i++){

                if(chars[i] == NULL){

                    return false;

                }

            }
            return true;

        }
        int getTamAlfa(){return tamAlfa;}
        ~No_MW(){

            for(int i = 0; i < tamAlfa; i++){

                if(chars[i] != NULL){

                    delete chars[i];

                }

            }
            delete []chars;

        }
    private:
        No_MW** chars;
        bool chave;
        int tamAlfa;
};

#endif // NO_MW_H
