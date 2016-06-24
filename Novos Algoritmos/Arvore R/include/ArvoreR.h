#ifndef ARVORER_H
#define ARVORER_H
#include <NoR.h>
#include <iostream>

using namespace std;

class ArvoreR
{
    public:
        ArvoreR();
        void insere(Point *listaObjeto);///Insere um objeto na arvore R
        Point* busca(Point p);///Busca um ponto 'p' na arvore e retorna qual MBR ele pertence
        NoR** getRaiz();
        ~ArvoreR();

    private:

        void insereRecursivo(Point *MBR, Point *listaPontos, NoR *n);///Usado para descer na arvore, localizar o local correto para a insercao do objeto e 'consertar' a arvore
        void split(NoR *n, NoR **novoNo);///Reparte as MBR's do No 'n' com o 'novoNo'
        void addFilho(NoR* pai, NoR* filho);///Adiciona ao pai o respectivo filho
        float calcArea(Point* MBR);///Calcula a area de uma MBR
        float calcArea(Point* MBR1, Point* MBR2);///Calcula a area da soma de duas MBR's
        Point* criaMBR(Point* listaP1, Point* listaP2);///Cria uma MBR baseada em uma ou duas listas de pontos
        Point* buscaRecursiva(Point p, NoR* n);///Auxiliar para a funcao publicade busca
        bool pertenceMBR(Point p, Point* MBR);///Verifica se um ponto p pertence a MBR
        void deletaArvore(NoR* n);///Auxiliar para o destrutor
        NoR* raiz;
};

#endif // ARVORER_H
