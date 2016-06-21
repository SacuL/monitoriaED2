#include <iostream>
#include <imprimeEstrutura.h>
#include <ArvoreVermelhoPreta.h>
#include <time.h>

using namespace std;

int main()
{
    srand(time(NULL));
    string nomeJanela = "Arvore Vermelho Preta";
    imprimeEstrutura* imp = new imprimeEstrutura(ARVORE_VERMELHO_PRETA);
    ArvoreVermelhoPreta* avp = new ArvoreVermelhoPreta();
    imp->setPriArvoreVermelhoPreta(avp->getRaiz());
    imp->imprime((char*)nomeJanela.c_str());

    for(int i = 0; i < 15; i++)
    {
        avp->insere(rand() % 100);
        imp->espere(1);
    }
    cout << avp->alturaVermelhoPreta() << endl;
    imp->finalizaImpressao();
    delete avp;
    delete imp;
    return 0;
}

