#include <iostream>
#include <stdlib.h>
#include <fstream>

#ifndef HASHING_H_INCLUDED
#define HASHING_H_INCLUDED

using namespace std;

class hashing{

public:
    hashing(int TAM);
    void hashingArquivoNumerico(ifstream *arquivo);
    void hashingArquivoString(ifstream *arquivo);
    void zeraVetor();
    int funcaoHashingNumeros(int chave);
    int funcaoHashingStrings(string chave);
    void geraArquivoStringAleatorias(int quant, string nomeArquivo);
    void geraArquivoNumerosAleatorios(int quant, string nomeArquivo);
    int* getTabela();
    int getTamTabela();
    void imprimeVetor();
    ~hashing();
private:
    int* tabela;
    int tam;

};

#endif // HASHING_H_INCLUDED
