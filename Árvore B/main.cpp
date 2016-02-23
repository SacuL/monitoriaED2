#include <iostream>
#include "arvoreB.h"

using namespace std;

int main()
{
    ArvoreB *arb = new ArvoreB;

    arb->inserir(10);
    arb->inserir(11);
    arb->inserir(13);
    arb->inserir(12);
    arb->inserir(1);
    arb->inserir(2);
    arb->inserir(3);
    arb->inserir(4);

    arb->inserir(9);
    arb->inserir(8);
    arb->inserir(7);
    arb->inserir(6);
    arb->inserir(5);
    arb->inserir(14);
    arb->inserir(15);
    arb->inserir(16);

    arb->del(15);

    arb->inserir(20);
    arb->inserir(21);
    arb->inserir(22);
    arb->inserir(23);
    arb->inserir(24);
    arb->inserir(25);
    arb->inserir(26);
    arb->inserir(27);


    arb->del(21);


    arb->imprimeArvore();
    arb->show();

    return 0;
}

