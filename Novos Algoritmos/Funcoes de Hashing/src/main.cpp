#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "hashing.h"
#include "imprimeEstrutura.h"
#include <time.h>
#include <string>

using namespace std;

int main(int argc, char* argv[]){
    srand(time(NULL));
    hashing *H;
    string nomeJanela = "Tabela de Hashing";
    int tamTabela,c;
    cout << "Digite o tamanho da tabela de hashing a ser usada" << endl;
    cin >> tamTabela;
    cout << "1 - hashing para o arquivo de strings" << endl << "2 - hashing para o arquivo de numeros" << endl;
    cin >> c;
    ifstream *arquivo = new ifstream();
    H = new hashing(tamTabela);
    imprimeEstrutura *Imp = new imprimeEstrutura(GRAFICO_HASHING);
    switch(c){

        case 1:
            arquivo->open("strings.txt");
            H->hashingArquivoString(arquivo);
            break;
        case 2:
            arquivo->open("numeros.txt");
            H->hashingArquivoNumerico(arquivo);


    }
    H->imprimeVetor();
    arquivo->close();
    Imp->setPriGraficoHashing(H->getTabela(),H->getTamTabela());
    Imp->imprime(argc,argv,(char*)nomeJanela.c_str());
    return 0;
}
