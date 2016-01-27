#include "hashing.h"
#include <math.h>

void hashing::geraArquivoNumerosAleatorios(int quant, string nomeArquivo)
{

    ofstream numeros;
    int itens[quant*100];
    int k;
    numeros.open(nomeArquivo.c_str());
    for(int i = 0; i < quant; i++)
    {

        k = rand()%(quant*100);
        if(itens[k] != 1)
        {

            numeros <<  k << endl;
            itens[k]=1;
        }
        else i--;

    }
    numeros.close();

}
int hashing::funcaoHashingNumeros(int chave)
{

    double c = chave*0.618033;
    c = c - (int)c;
    return c*tam;

}
void hashing::zeraVetor()
{

    for(int i = 0; i < tam; i++)
    {

        tabela[i] = -1;

    }

}
void hashing::hashingArquivoNumerico(ifstream *arquivo)
{

    string numero;
    int resultado;
    while(arquivo->eof() == 0)
    {

        getline(*arquivo,numero);
        if(preenchidos != tam)
        {
            resultado = funcaoHashingNumeros(atoi(numero.c_str()));
            if(tabela[resultado] == -1)
            {

                tabela[resultado] = atoi(numero.c_str());

            }
            else
            {

                while(tabela[resultado] != -1)
                {

                    resultado += funcaoReHashing(atoi(numero.c_str()));
                    if(resultado >= tam)
                    {

                        resultado = resultado - (tam);

                    }

                }
                tabela[resultado] = atoi(numero.c_str());

            }

            numero.clear();
            preenchidos++;
        }
        else
        {

            cout << "Tabela cheia" << endl;
            return;

        }

    }
}
void hashing::imprimeVetor()
{

    for(int i = 0; i < tam; i++)
    {

        cout << "A posicao do vetor " << i << " esta com o valor " << tabela[i] << endl;

    }

}
hashing::hashing(int TAM)
{

    tam = TAM;
    tabela = new int[TAM];
    zeraVetor();
    preenchidos = 0;

}
hashing::~hashing()
{

    delete []tabela;

}
int hashing::funcaoReHashing(int chave)
{

    return 1;

}
int* hashing::getTabela()
{

    return tabela;

}
int hashing::getTamTabela()
{

    return tam;

}
