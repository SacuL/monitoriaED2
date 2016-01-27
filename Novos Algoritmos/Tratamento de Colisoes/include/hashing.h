#include <iostream>
#include <stdlib.h>
#include <fstream>

#ifndef HASHING_H_INCLUDED
#define HASHING_H_INCLUDED

using namespace std;

class hashing
{

public:
    hashing(int TAM);
    void hashingArquivoNumerico(ifstream *arquivo);
    void zeraVetor();
    int funcaoHashingNumeros(int chave);
    int funcaoReHashing(int chave);
    void geraArquivoNumerosAleatorios(int quant, string nomeArquivo);
    int* getTabela();
    int getTamTabela();
    void imprimeVetor();
    ~hashing();
private:
    int* tabela;
    int tam;
    int preenchidos;

};

#endif // HASHING_H_INCLUDED
