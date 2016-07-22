#ifndef ROBINKARP_H_INCLUDED
#define ROBINKARP_H_INCLUDED
#include <string>
#include <cmath>
#include <iostream>
#define N_PRIMO 3


class RobinKarp
{
    public:
        RobinKarp(){
            OFFSET = 0;
        };
        ~RobinKarp(){};
        int busca(std::string padrao, std::string texto);
        void setOFFSET(int OFF){OFFSET=OFF;};

    private:
        int calculaHash(std::string s);
        int OFFSET;

};
#endif // ROBINKARP_H_INCLUDED
