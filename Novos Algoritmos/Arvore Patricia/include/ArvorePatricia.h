#ifndef ARVOREPATRICIA_H
#define ARVOREPATRICIA_H
#include <No_PAT.h>

class ArvorePatricia
{
    public:
        ArvorePatricia(int tamAlfabeto);
        void inserir(string c);
        bool buscar(string s);
        bool comparaStrings(string s, string c);
        No_PAT** getRaiz(){return &raiz;}
        int diferencaStrings(string c, string s, unsigned int p);
        char getString(string s, unsigned int id);
        ~ArvorePatricia();

    private:
        No_PAT* insereRecursivo(string c,int pos, No_PAT *p);
        string buscaStringPai(No_PAT* p);
        No_PAT *buscar(string s, No_PAT *p);
        int tamAlfa;
        No_PAT *raiz;
};

#endif // ARVOREPATRICIA_H
