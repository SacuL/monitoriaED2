#include <iostream>
#include <Trie_MultiWay.h>
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
    string nomeJanela = {"Arvore Trie MultiWay"};
    Trie_MultiWay* trie = new Trie_MultiWay(4);
    imprimeEstrutura *imp = new imprimeEstrutura(ARVORE_MULTIWAY);
    imp->setPriArvoreMultiWay(trie->getRaiz());
    imp->imprime((char*)nomeJanela.c_str());
    trie->insere((char*)s1.c_str(),s1.size());
    imp->espere(2);
    trie->insere((char*)s2.c_str(),s2.size());
    imp->espere(2);
    trie->insere((char*)s3.c_str(),s3.size());
    imp->espere(2);
    trie->insere((char*)s4.c_str(),s4.size());
    imp->espere(2);
    trie->insere((char*)s5.c_str(),s5.size());
    imp->espere(2);
    trie->insere((char*)s6.c_str(),s6.size());
    imp->espere(2);
    trie->insere((char*)s7.c_str(),s7.size());
    imp->espere(2);
    trie->insere((char*)s8.c_str(),s8.size());
    imp->espere(2);
    trie->insere((char*)s9.c_str(),s9.size());
    imp->espere(2);
    trie->insere((char*)s10.c_str(),s10.size());
    imp->espere(2);
    trie->insere((char*)s11.c_str(),s11.size());
    imp->espere(2);
    trie->insere((char*)s12.c_str(),s12.size());
    imp->espere(2);
    trie->imprime();
    cout << "Pesquisando " << s3 << endl;
    if(trie->busca((char*)s3.c_str(), s3.size())){

        cout << "String existe" << endl;

    }else{

        cout << "String nao existe" << endl;

    }
    trie->remove((char*)s1.c_str(),s1.size());
    cout << "Deletou " << s1 << endl;
    trie->remove((char*)s12.c_str(),s12.size());
    cout << "Deletou " << s12 << endl;
    cout << "Altura da arvore " << trie->alturaMW() <<endl;
    imp->finalizaImpressao();
    delete trie;
    delete imp;
    return 0;
}
