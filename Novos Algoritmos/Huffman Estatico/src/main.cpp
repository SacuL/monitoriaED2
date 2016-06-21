#include <iostream>
#include <Huffman_Lista.h>
#include <string>
#include <imprimeEstrutura.h>
#include <time.h>

using namespace std;

int main()
{
    imprimeEstrutura *imp = new imprimeEstrutura(ARVORE_HUFFMAN);
    Huffman_Lista *H = new Huffman_Lista;
    string s = {"Paralelepipedo!"};
    string c = H->codificar(s);
    cout << "Codigo gerado de " << s << " eh " << c <<endl;
    string d = H->decodificar(c);
    cout << "String decodificada de " << c << " eh " << d << endl;
    imp->setPriHuffmanTree(H->getArvore());
    imp->imprime((char*)"Arvore de Huffman");
    imp->finalizaImpressao();
    delete H;
    delete imp;
    return 0;
}
