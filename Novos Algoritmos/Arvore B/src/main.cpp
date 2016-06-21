#include <iostream>
#include <imprimeEstrutura.h>
#include <arvoreB.h>
#include <time.h>

using namespace std;

int main()
{
    //srand(time(NULL));
    string nomeJanela = "Arvore B";
    int valor;
    imprimeEstrutura *imp = new imprimeEstrutura(ARVORE_B);
    ArvoreB *AB = new ArvoreB();
    imp->setPriArvoreB(AB->getRaiz());
    imp->imprime((char*)nomeJanela.c_str());
    for(int i = 0; i < 15; i++){

        valor = (rand()%1000)+1;
        AB->inserir(valor);
        imp->espere(1);
        cout << "Inserindo o valor " << valor << endl;

    }
    imp->finalizaImpressao();
    delete imp;
    delete AB;
    return 0;
}
