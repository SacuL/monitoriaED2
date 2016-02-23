#include <iostream>
#include <stdlib.h>
#include <fstream>

#ifndef HASHING_LISTA_H_INCLUDED
#define HASHING_LISTA_H_INCLUDED
#include <Lista.h>

using namespace std;

class hashingLista{

public:
    hashingLista(int TAM);
    void hashingArquivoNumerico(ifstream *arquivo);
    int funcaoHashingNumeros(int chave);
    void geraArquivoNumerosAleatorios(int quant, string nomeArquivo);
    Lista* getTabela();
    int getTamTabela();
    void imprimeVetor();
    ~hashingLista();
private:
    Lista* tabela;
    int tam;

};

#endif // HASHING_H_INCLUDED
