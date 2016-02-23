#include "hashing.h"
#include <math.h>

void hashing::geraArquivoNumerosAleatorios(int quant, string nomeArquivo){

    ofstream numeros;
    numeros.open(nomeArquivo.c_str());
    for(int i = 0; i < quant; i++){

        numeros << rand()%(quant*1000) << endl;

    }
    numeros.close();

}
void hashing::geraArquivoStringAleatorias(int quant, string nomeArquivo){

    ofstream strings;
    string saida;
    int tamanhoString;
    char c[52];
    strings.open(nomeArquivo.c_str());
    int j = 0;
    for(int i = 65; i <91; i++){

        c[j] = i;
        j++;

    }
    for(int i = 97; i <123; i++){

        c[j] = i;
        j++;

    }
    for(int i = 0; i < quant; i++){

        tamanhoString = rand()%100;
        if(tamanhoString == 0){

            tamanhoString += 1;

        }
        for(int k = 0; k < tamanhoString; k++){

            saida.push_back(c[rand()%52]);

        }
        strings <<saida<< endl;
        saida.clear();

    }
    strings.close();

}
int hashing::funcaoHashingNumeros(int chave){

    /*double c = chave*0.618033;
    c = c - (int)c;
    return c*tam;*/
    chave = chave%9871;
    return chave%tam;

}
void hashing::zeraVetor(){

    for(int i = 0; i < tam; i++){

        tabela[i] = 0;

    }

}
void hashing::hashingArquivoNumerico(ifstream *arquivo){


    string numero;
    while(arquivo->eof() == 0){

        getline(*arquivo,numero);
        tabela[funcaoHashingNumeros(atoi(numero.c_str()))]++;
        numero.clear();

    }
}
void hashing::imprimeVetor(){

    for(int i = 0; i < tam; i++){

        cout << "A posicao do vetor " << i << " esta com o valor " << tabela[i] << endl;

    }

}
void hashing::hashingArquivoString(ifstream *arquivo){

    string entrada;
    while(arquivo->eof() == 0){

        getline(*arquivo,entrada);
        tabela[funcaoHashingStrings(entrada)]++;
        entrada.clear();

    }

}
int hashing::funcaoHashingStrings(string chave){

    string::iterator it;
    it = chave.begin();
    int saida;
    while(it != chave.end()){

        saida += *it;
        it++;

    }
    return fabs(saida%tam);
}
hashing::hashing(int TAM){

    tam = TAM;
    tabela = new int[TAM];
    zeraVetor();

}
hashing::~hashing(){

    delete []tabela;

}
int* hashing::getTabela(){

    return tabela;

}
int hashing::getTamTabela(){

    return tam;

}
