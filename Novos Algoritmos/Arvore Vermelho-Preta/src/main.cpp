#include <iostream>
#include <imprimeEstrutura.h>
#include <ArvoreVermelhoPreta.h>

using namespace std;

int main()
{

    string nomeJanela = "Arvore Vermelho Preta";
    imprimeEstrutura* imp = new imprimeEstrutura(ARVORE_VERMELHO_PRETA);
    ArvoreVermelhoPreta* avp = new ArvoreVermelhoPreta();
    imp->setPriNoBinario(avp->getRaiz());
    imp->imprime((char*)nomeJanela.c_str());

    for(int i = 0; i < 15; i++)
    {
        avp->insere(rand() % 100);
        imp->espere(1);
    }

    imp->finalizaImpressao();
    delete avp;
    delete imp;
    return 0;
}

