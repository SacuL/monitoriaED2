#include <iostream>
#include <imprimeEstrutura.h>
#include <ArvoreSPLAY.h>

using namespace std;

int main()
{
    string nomeJanela = "Arvore SPLAY";
    imprimeEstrutura* imp = new imprimeEstrutura(ARVORE_BINARIA);
    ArvoreSPLAY* splay = new ArvoreSPLAY();
    imp->setPriNoBinario(splay->getRaiz());
    imp->imprime((char*)nomeJanela.c_str());

    imp->espere(1);
    splay->insere(4);

    imp->espere(1);
    splay->insere(1);

    imp->espere(1);
    splay->insere(3);

    imp->espere(1);
    splay->insere(2);

    imp->espere(1);
    splay->insere(10);

    imp->espere(1);
    splay->insere(11);

    imp->espere(1);
    splay->insere(12);

    imp->espere(1);
    splay->remover(10);

    imp->espere(1);
    splay->remover(4);

    imp->espere(1);
    splay->remover(3);

    imp->espere(1);

    imp->finalizaImpressao();
    delete splay;
    delete imp;
    return 0;
}
