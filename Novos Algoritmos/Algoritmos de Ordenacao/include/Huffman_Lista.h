#ifndef HUFFMAN_LISTA_H
#define HUFFMAN_LISTA_H
#include <No_HUF.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

class Huffman_Lista
{
    public:
        Huffman_Lista();
        No_HUF **getArvore();///retorna o ponteiro para o ponteiro da raiz da arvore
        string codificar(string s);///codifica a string s formando a arvore de huffman, e atualizando o vetor de caracters
        string decodificar(string s);
        void imprimirCodigoChars();///imprime o vetor de codigos  com todos os caracteres
        ~Huffman_Lista();

    private:
        No_HUF* getMenor();///Retorna o nó com menor frequencia
        void retiraLista(No_HUF* n);///Retira o no n da lista
        void insere(char c, int f);///insere o caracter c na lista, se ja existir apenas atualiza sua frequencia
        void geraArvore();///Gera a arvore de huffman a partir da lista encadeada
        string gerarCodigoString(string s);///gera o código de uma string s a partir da arvore
        void gerarCodigos(string s, No_HUF* n);///percorre a arvore de huffman e coleta os codigos de cada caracter
        string codigosLow[26];///caracters minusculos
        string codigosUp[26];///caracters maiusculos
        string codigosAcentos[5];///virgula, ponto, espaco, interrogacao, exclamacao
        void deletaH(No_HUF* n);
        No_HUF *priLista;
        No_HUF *ultLista;
};

#endif // HUFFMAN_LISTA_H
