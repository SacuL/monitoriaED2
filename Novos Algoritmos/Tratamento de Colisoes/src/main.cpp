#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "hashingLista.h"
#include "hashing.h"
#include "imprimeEstrutura.h"
#include <time.h>
#include <string>

using namespace std;
void Hlista(int argc, char* argv[])
{

    srand(time(NULL));
    hashingLista *H;
    string nomeJanela = "Tabela de Hashing";
    int tamTabela;
    cout << "Digite o tamanho da tabela de hashing a ser usada" << endl;
    cin >> tamTabela;
    ifstream *arquivo = new ifstream();
    H = new hashingLista(tamTabela);
    imprimeEstrutura *Imp = new imprimeEstrutura(HASHING_LISTA);
    //H->geraArquivoNumerosAleatorios(100,"numeros.txt");
    arquivo->open("numeros.txt");
    H->hashingArquivoNumerico(arquivo);
    H->imprimeVetor();
    arquivo->close();
    Imp->setPriHashingLista(H->getTabela(),H->getTamTabela());
    Imp->imprime(argc,argv,(char*)nomeJanela.c_str());

}
void Hvetor(int argc, char* argv[])
{

    srand(time(NULL));
    hashing *H;
    string nomeJanela = "Tabela de Hashing";
    int tamTabela;
    cout << "Digite o tamanho da tabela de hashing a ser usada" << endl;
    cin >> tamTabela;
    ifstream *arquivo = new ifstream();
    H = new hashing(tamTabela);
    imprimeEstrutura *Imp = new imprimeEstrutura(VETOR);
    //H->geraArquivoNumerosAleatorios(tamTabela,"numeros.txt");
    arquivo->open("numeros.txt");
    H->hashingArquivoNumerico(arquivo);
    H->imprimeVetor();
    arquivo->close();
    Imp->setPriVetor(H->getTabela(),H->getTamTabela());
    Imp->imprime(argc,argv,(char*)nomeJanela.c_str());


}
int main(int argc, char* argv[])
{

inicio:
    int escolha;
    cout << "Qual tipo de estrutura deseja trabalhar?" << endl << "1 - Extensao com lista;" << endl << "2 - ReHashing;" << endl;
    cin >> escolha;
    if(escolha == 1)
    {

        Hlista(argc,argv);

    }
    else if(escolha == 2)
    {

        Hvetor(argc,argv);

    }
    else
    {

        cout << "Estrutura nao conhecida " << endl;
        goto inicio;

    }
    return 0;
}
