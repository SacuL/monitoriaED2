#include <iostream>
#include <imprimeEstrutura.h>
#include <ABB.h>

using namespace std;

int main()
{
    string nomeJanela = "Arvore Binaria de Busca";
    imprimeEstrutura* imp = new imprimeEstrutura(ARVORE_BINARIA);
    ABB* abb = new ABB();
    imp->setPriNoBinario(abb->getRaiz());
    imp->imprime((char*)nomeJanela.c_str());

    imp->espere(1);
    abb->inserir(4);

    imp->espere(1);
    abb->inserir(1);

    imp->espere(1);
    abb->inserir(3);

    imp->espere(1);
    abb->inserir(2);

    imp->espere(1);
    abb->inserir(10);

    imp->espere(1);
    abb->inserir(11);

    imp->espere(1);
    abb->inserir(12);

    imp->espere(1);
    abb->remover(10);

    imp->espere(1);
    abb->remover(4);

    imp->espere(1);
    abb->remover(3);

    imp->espere(1);

    abb->inserir(15);
    imp->espere(1);
    abb->inserir(15);
    imp->espere(1);
    abb->inserir(15);
    imp->espere(2);
    abb->remover(15);

    imp->finalizaImpressao();
    delete abb;
    delete imp;
    return 0;
}

