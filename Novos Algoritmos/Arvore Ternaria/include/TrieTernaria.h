#ifndef TRIETERNARIA_H
#define TRIETERNARIA_H
#include <No_Ter.h>
#include <string>
#include <iostream>

using namespace std;

class TrieTernaria
{
    public:
        TrieTernaria();
        void insere(string palavra);
        void imprime();
        bool busca(string palavra);
        void remove(string palavra);
        No_Ter **getRaiz();
        ~TrieTernaria();
    private:
        No_Ter *raiz;
        bool removeT(char *c, No_Ter *n, int idI, int idF);
        void deletaT(No_Ter* n);
        No_Ter* insereAux(No_Ter* no, string palavra);
        void imprimeAux(No_Ter* no, string palavra);
        bool buscaAux(No_Ter* no , string palavra);
};

#endif // TRIETERNARIA_H
