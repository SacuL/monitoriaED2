#include "RobinKarp.h"

using namespace std;

int RobinKarp::calculaHash(string s){
    int res = 0;
    for(int i = 0 ; i < s.size() ; i++){
        res = res + (s.at(i)-OFFSET) * pow(N_PRIMO,i);
    }
    return res;
}

int RobinKarp::busca(string padrao, string texto)
{
    int tamanhoPadrao = padrao.size();
    if( texto.size() < tamanhoPadrao) return -1;

    int hashPadrao = calculaHash(padrao);

    int posAtual = 0;
    int hashAtual = calculaHash(texto.substr(posAtual,tamanhoPadrao));

    do{
        if(hashAtual == hashPadrao){
            if(padrao == texto.substr(posAtual,tamanhoPadrao)){
                return posAtual;
            }
        }

        if ((posAtual + tamanhoPadrao) >= texto.size()) return -1;

        hashAtual = hashAtual - (texto.at(posAtual)-OFFSET);
        hashAtual = hashAtual / N_PRIMO;
        posAtual++;
        hashAtual = hashAtual + (texto.at(posAtual + tamanhoPadrao - 1)-OFFSET) * pow(N_PRIMO,tamanhoPadrao-1); ;
    }
    while (true);
}
