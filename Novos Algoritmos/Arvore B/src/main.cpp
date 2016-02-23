#include <iostream>
#include <imprimeEstrutura.h>
#include <arvoreB.h>
#include <time.h>

using namespace std;

int main()
{
    srand(time(NULL));
    string nomeJanela = "Arvore B";
    imprimeEstrutura *imp = new imprimeEstrutura(ARVORE_B);
    ArvoreB *AB = new ArvoreB();
    imp->setPriArvoreB(AB->getRaiz());
    imp->imprime((char*)nomeJanela.c_str());
    for(int i = 0; i < 20; i++){

        AB->inserir((rand()%1000)+1);

    }
    imp->espere(20);
    imp->fechaJanela();
    delete imp;
    delete AB;
    return 0;
}
