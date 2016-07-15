#include <iostream>
#include <ArvorePatricia.h>
#include <imprimeEstrutura.h>

using namespace std;

int main()
{
    ArvorePatricia *AP = new ArvorePatricia(4);
    imprimeEstrutura *imp = new imprimeEstrutura(ARVORE_PATRICIA);
    imp->setPriArvorePatricia(AP->getRaiz());
    imp->imprime((char*)"Arvore PATRICIA");
    AP->inserir("abcd");
    AP->inserir("bcd");
    AP->inserir("abdc");
    AP->inserir("abbb");
    AP->inserir("bcdc");
    if(AP->buscar("bcd")){

        cout << "Existe a string na arvore" << endl;

    }else{

        cout << "Nao existe a string na arvore" << endl;

    }
    imp->finalizaImpressao();
    delete AP;
    return 0;
}
