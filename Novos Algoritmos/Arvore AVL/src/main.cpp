#include <iostream>
#include <imprimeEstrutura.h>
#include <AVL.h>

using namespace std;

int main()
{
    string nomeJanela = "Arvore AVL";
    imprimeEstrutura* imp = new imprimeEstrutura(ARVORE_BINARIA);
    AVL* avl = new AVL();
    imp->setPriNoBinario(avl->getRaiz());
    imp->imprime((char*)nomeJanela.c_str());

    imp->espere(1);
    avl->insere(4);

    imp->espere(1);
    avl->insere(1);

    imp->espere(1);
    avl->insere(3);

    imp->espere(1);
    avl->insere(2);

    imp->espere(1);
    avl->insere(10);

    imp->espere(1);
    avl->insere(11);

    imp->espere(1);
    avl->insere(12);

    imp->espere(1);
    avl->remover(10);

    imp->espere(1);
    avl->remover(4);

    imp->espere(1);
    avl->remover(3);

    imp->espere(1);

    imp->finalizaImpressao();
    delete avl;
    delete imp;
    return 0;
}
