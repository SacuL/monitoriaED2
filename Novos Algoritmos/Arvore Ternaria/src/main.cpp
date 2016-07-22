#include <iostream>
#include <TrieTernaria.h>
#include <string>
#include <imprimeEstrutura.h>

using namespace std;

int main()
{
    string s1 = {"bcd"};
    string s2 = {"adc"};
    string s3 = {"abd"};
    string s4 = {"bda"};
    string s5 = {"abb"};
    string s6 = {"dcb"};
    string s7 = {"ab"};
    string s8 = {"cba"};
    string s9 = {"cb"};
    string s10 = {"cbc"};
    string s11 = {"aaa"};
    string s12 = {"bbb"};
    string nomeJanela = {"Arvore Trie Ternaria"};
    TrieTernaria *trie = new TrieTernaria();
    imprimeEstrutura *imp = new imprimeEstrutura(ARVORE_TRIE_TERNARIA);
    imp->setPriTrieTer(trie->getRaiz());
    imp->imprime((char*)nomeJanela.c_str());
    trie->insere(s1);
    trie->insere(s2);
    trie->insere(s3);
    trie->insere(s4);
    trie->insere(s5);
    trie->insere(s6);
    trie->insere(s7);
    trie->insere(s8);
    trie->insere(s9);
    trie->insere(s10);
    trie->insere(s11);
    trie->insere(s12);
    trie->imprime();

    trie->busca(s4);
    trie->busca(s10);
    trie->busca("bbc");

    imp->finalizaImpressao();
    delete trie;
    delete imp;
    return 0;
}
