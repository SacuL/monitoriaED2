#include "hashingLista.h"

void hashingLista::geraArquivoNumerosAleatorios(int quant, string nomeArquivo)
{

    ofstream numeros;
    numeros.open(nomeArquivo.c_str());
    for(int i = 0; i < quant; i++)
    {

        numeros << rand()%(quant*10) << endl;

    }
    numeros.close();

}
int hashingLista::funcaoHashingNumeros(int chave)
{

    double c = chave*0.618033;
    c = c - (int)c;
    return c*tam;

}
void hashingLista::hashingArquivoNumerico(ifstream *arquivo)
{


    string numero;
    while(arquivo->eof() == 0)
    {

        getline(*arquivo,numero);
        tabela[funcaoHashingNumeros(atoi(numero.c_str()))].push_back(atoi(numero.c_str()));
        numero.clear();

    }
}
void hashingLista::imprimeVetor()
{

    for(int i = 0; i < tam; i++)
    {

        cout << "A posicao do vetor " << i << " esta com os valores:" << endl;
        tabela[i].print();
        cout << endl;

    }

}
hashingLista::hashingLista(int TAM)
{

    tam = TAM;
    tabela = new Lista[TAM];
    for(int i = 0; i < tam; i++)
    {

        tabela[i].push_back(i);

    }

}
hashingLista::~hashingLista()
{

    delete []tabela;

}
Lista* hashingLista::getTabela()
{

    return tabela;

}
int hashingLista::getTamTabela()
{

    return tam;

}
