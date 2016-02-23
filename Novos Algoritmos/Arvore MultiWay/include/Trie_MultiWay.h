#ifndef TRIE_MULTIWAY_H
#define TRIE_MULTIWAY_H
#include <No_MW.h>

class Trie_MultiWay
{
    public:
        Trie_MultiWay(int tamAlfabeto);
        void insere(char* c, int tam);
        void imprime();
        void remove(char* c, int tam);
        bool busca(char* c, int tam);
        No_MW** getRaiz();
        ~Trie_MultiWay();
    private:
        No_MW* raiz;
        int alfabeto;
        bool verificaString(char* c, int tam);
        void imprimeMW(string s, No_MW* n);
        void removeMW(No_MW *n, char* c, int idI, int idF);
        void deleteH(No_MW *n);

};

#endif // TRIE_MULTIWAY_H
