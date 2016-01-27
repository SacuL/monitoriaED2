#include <iostream>
#include <imprimeEstrutura.h>
#include <heapCont.h>
#include <time.h>
using namespace std;

int main(int argc, char* argv[])
{

    srand(time(NULL));
    string nomeJanela = "Heap Binario Contiguo";
    int numElementos;
    imprimeEstrutura *Imp = new imprimeEstrutura(ARVORE_BINARIA_CONTIGUA);
    heapCont *H = new heapCont(MAX_HEAP);
    heapCont *H2 = new heapCont(MAX_HEAP);
    cout << "Digite o numero de nos a serem randomizados: ";
    cin >> numElementos;
    for(int i = 0; i < numElementos; i++)
    {

        H->insere(rand() % (2 * numElementos));

    }
    for(int i = 0; i < numElementos; i++)
    {

        H2->insere(rand() % (2 * numElementos));

    }
    H->uniao(H2->getRaiz(),H2->getUltIndice());
    H->imprimeHeap();
    Imp->setPriNoBinarioCont(H->getRaiz(),H->getUltIndice());
    Imp->imprime(argc,argv,(char*)nomeJanela.c_str());
    delete Imp;
    delete H;
    delete H2;
    return 0;
}
