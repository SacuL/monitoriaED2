#include <iostream>
#include <imprimeEstrutura.h>
#include <heapEsq.h>
#include <time.h>
using namespace std;

int main(int argc, char* argv[])
{

    srand(time(NULL));
    int tempo = 1;
    string nomeJanela = "Heap Esquerdista";
    imprimeEstrutura *Imp = new imprimeEstrutura(ARVORE_BINARIA);
    heapEsq *H = new heapEsq();
    int del;
    for(int i = 0; i < 10; i++)
    {
        cout << "Iteracao " << i << endl;
        H->insere(rand()%60);
        Imp->setPriNoBinario(H->getRaiz());
        Imp->imprime(argc,argv,(char*)nomeJanela.c_str(),tempo);

    }
    Imp->setPriNoBinario(H->getRaiz());
    Imp->imprime(argc,argv,(char*)nomeJanela.c_str());
    cout << "Digite um numero para remover "<<endl;
    cin >> del;
    H->remover(del);
    Imp->setPriNoBinario(H->getRaiz());
    Imp->imprime(argc,argv,(char*)nomeJanela.c_str());
    /*H->insere(10);
    Imp->setPriNoBinario(H->getRaiz());
    Imp->imprime(argc,argv,(char*)nomeJanela.c_str(),tempo);
    H->insere(13);
    Imp->setPriNoBinario(H->getRaiz());
    Imp->imprime(argc,argv,(char*)nomeJanela.c_str(),tempo);
    H->insere(7);
    Imp->setPriNoBinario(H->getRaiz());
    Imp->imprime(argc,argv,(char*)nomeJanela.c_str(),tempo);
    H->insere(1);
    Imp->setPriNoBinario(H->getRaiz());
    Imp->imprime(argc,argv,(char*)nomeJanela.c_str(),tempo);
    H->insere(5);
    Imp->setPriNoBinario(H->getRaiz());
    Imp->imprime(argc,argv,(char*)nomeJanela.c_str(),tempo);
    H->insere(18);
    Imp->setPriNoBinario(H->getRaiz());
    Imp->imprime(argc,argv,(char*)nomeJanela.c_str(),tempo);
    H->insere(15);
    Imp->setPriNoBinario(H->getRaiz());
    Imp->imprime(argc,argv,(char*)nomeJanela.c_str(),tempo);
    H->insere(89);
    Imp->setPriNoBinario(H->getRaiz());
    Imp->imprime(argc,argv,(char*)nomeJanela.c_str(),tempo);
    H->insere(2);
    Imp->setPriNoBinario(H->getRaiz());
    Imp->imprime(argc,argv,(char*)nomeJanela.c_str(),tempo);
    H->insere(15);
    Imp->setPriNoBinario(H->getRaiz());
    Imp->imprime(argc,argv,(char*)nomeJanela.c_str(),tempo);
    H->remover(13);
    H->imprimeHeap();
    Imp->setPriNoBinario(H->getRaiz());
    Imp->imprime(argc,argv,(char*)nomeJanela.c_str());*/
    delete Imp;
    delete H;
    return 0;
}
