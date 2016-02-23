#include <iostream>
#include <heapBinomial.h>
#include <time.h>
#include <imprimeEstrutura.h>
#include <thread>
using namespace std;

int main(int argc, char* argv[]){

    srand(time(NULL));
    string nomeJanela = "Heap Binomial";
    imprimeEstrutura *imp = new imprimeEstrutura(HEAP_BINOMIAL);
    heapBinomial* hb = new heapBinomial();
    imp->setHeapBinomial(hb);
    imp->imprime((char*)nomeJanela.c_str());
    for(int i = 0; i < 29; i++){

        hb->insere(rand()%100);
        imp->espere(1);

    }
    No_Binomial* mais_prioritario = hb->remover();
    cout << "No mais prioritario removido: " << mais_prioritario->getValor() << endl;
    hb->imprimeHeapConsole();
    imp->finalizaImpressao();
    //cin.get();
    delete hb;
    return 0;
}
