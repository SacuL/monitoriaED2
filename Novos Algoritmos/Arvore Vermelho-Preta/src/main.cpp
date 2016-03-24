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

    imp->espere(1);
    avp->insere(4);

    imp->espere(1);
    avp->insere(1);

    imp->espere(1);
    avp->insere(3);

    imp->espere(1);
    avp->insere(2);

    imp->espere(1);
    avp->insere(10);

    imp->espere(1);
    avp->insere(11);

    imp->espere(1);
    avp->insere(12);


    imp->espere(1);

    imp->finalizaImpressao();
    delete avp;
    delete imp;
    return 0;
}
