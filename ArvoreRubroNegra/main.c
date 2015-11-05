#include <stdio.h>
#include <stdlib.h>
#include "DSGraph.h"

#define MAX 100
typedef struct NODE_STRUCTURE NO;

void rotEsq(NO *);
void rotDir(NO *);
void corrige1(NO *);
void corrige2(NO *);
void corrige3(NO *);
void corrige4(NO *);
void corrige5(NO *);

NO *ptraiz;

NO* avo(NO *n)
{
	if ((n != NULL) && (n->father != NULL))
		return n->father->father;
	else
		return NULL;
}

NO* tio(NO *n)
{
	NO *a = avo(n);
	if (a == NULL)
		return NULL;
	if (n->father == a->prior)
		return a->next;
	else
		return a->prior;
}

void criaArv(int a){
	ptraiz = (NO*)malloc(sizeof(NO));
	ptraiz->father=NULL;
	ptraiz->prior=NULL;
	ptraiz->next=NULL;
	ptraiz->mark = 0;
	ptraiz->value = a;
}

void rotEsq(NO *n){
	NO *Q = n->next;
	if(n->father != NULL){
		if(n->father->next==n) n->father->next=Q;
		if(n->father->prior==n) n->father->prior=Q;
	}
	else ptraiz=Q;

	n->next = Q->prior;
	Q->prior = n;
}

void rotDir(NO *n){
	NO *Q = n->prior;
	if(n->father != NULL){
		if(n->father->next==n) n->father->next=Q;
		if(n->father->prior==n) n->father->prior=Q;
	}
	else ptraiz=Q;

	n->prior = Q->next;
	Q->next = n;
}

void corrige1(NO *n)
{
    showComment("Arvore RUBRO-NEGRA: Caso 1: Se o NO %d eh raiz, ele deve ser PRETO.",n->value);
    setSleepTime(2);
    show(ptraiz,0);

	if (n->father == NULL){
		n->mark = 0;
	}
	else{

		corrige2(n);

	}
}

void corrige2(NO *n)
{
    showComment("Arvore RUBRO-NEGRA: Caso 2: Se o pai do NO %d for PRETO, a Arvore continua valida.",n->value);
    setSleepTime(2);
    show(ptraiz,0);

	if (n->father->mark == 0){
        return;
	}

	else{
		corrige3(n);
	}
}

void corrige3(NO *n)
{
	NO *u = tio(n), *g;

	if ((u != NULL) && (u->mark == 4)) {

        showComment("Arvore RUBRO-NEGRA: Caso 3: Pai e Tio de %d VERMELHOS - passam para PRETO e Avo de %d passa para VERMELHO.",n->value, n->value);
        setSleepTime(2);
        show(ptraiz,0);

		n->father->mark = 0;
		u->mark = 0;
		g = avo(n);
		g->mark = 4;

		corrige1(g);

	} else {
		corrige4(n);
	}
}

void corrige4(NO *n)
{
	NO *g = avo(n);

    showComment("Arvore RUBRO-NEGRA: Caso 4: O pai de %d eh VERMELHO mas o tio de %d eh PRETO.",n->value, n->value);
    setSleepTime(2);
    show(ptraiz,0);

	if ((n == n->father->next) && (n->father == g->prior)) {

        showComment("Arvore RUBRO-NEGRA: Rotacao a Esq. no NO %d.",n->father->value);
        setSleepTime(2);
        show(ptraiz,0);

		rotEsq(n->father);
		n = n->prior;
	} else if ((n == n->father->prior) && (n->father == g->next)) {

        showComment("Arvore RUBRO-NEGRA: Rotacao a Dir. no NO %d.",n->father->value);
        setSleepTime(2);
        show(ptraiz,0);

		rotDir(n->father);
		n = n->next;
	}
	corrige5(n);
}

void corrige5(NO *n)
{
    showComment("Arvore RUBRO-NEGRA: Caso 5:  O pai de %d eh VERMELHO mas o tio de %d eh PRETO.",n->value, n->value);
    setSleepTime(2);
    show(ptraiz,0);

	NO *g = avo(n);
	//if(g==NULL)return;
	n->father->mark = 0;
	g->mark = 4;
	if ((n == n->father->prior) && (n->father == g->prior)) {

        showComment("Arvore RUBRO-NEGRA: Rotacao a Dir. no NO %d.",g->value);
        setSleepTime(2);
        show(ptraiz,0);

		rotDir(g);

	} else {

        showComment("Arvore RUBRO-NEGRA: Rotacao a Dir. no NO %d.",g->value);
        setSleepTime(2);
        show(ptraiz,0);

		rotEsq(g);

	}
}

void insere(int x, NO *pt, NO *father){

	if(pt != NULL){
		if(x < pt->value) insere(x, pt->prior, pt);
		else insere(x, pt->next, pt);
	}
	else{
		NO *novo = (NO*)malloc(sizeof(NO));
		novo->father = father;
		novo->prior=NULL;
		novo->next=NULL;
		novo->mark = 4;
		novo->value = x;
		if(x < father->value) father->prior = novo;
		else father->next = novo;
		free(pt);
		corrige1(novo);
		ptraiz->mark = 0;
	}
}

int main()
{
    int chave;

    init($TREE_BLACK_RED);

    setViewAddress(0);

    chave=4;
    showComment("Arvore RUBRO-NEGRA: Cria a arvore e insere o valor %d.", chave);
    criaArv(chave);
    setSleepTime(2);
    show(ptraiz,0);

    chave=1;
    showComment("Arvore RUBRO-NEGRA: Sera inserido o valor %d.", chave);
    setSleepTime(2);
    show(ptraiz,0);
    insere(chave, ptraiz, NULL);

    chave=5;
    showComment("Arvore RUBRO-NEGRA: Sera inserido o valor %d.", chave);
    setSleepTime(2);
    show(ptraiz,0);
    insere(chave, ptraiz, NULL);

    chave=2;
    showComment("Arvore RUBRO-NEGRA: Sera inserido o valor %d.", chave);
    setSleepTime(2);
    show(ptraiz,0);
    insere(chave, ptraiz, NULL);

    chave=67;
    showComment("Arvore RUBRO-NEGRA: Sera inserido o valor %d.", chave);
    setSleepTime(2);
    show(ptraiz,0);
    insere(chave, ptraiz, NULL);

    chave=6;
    showComment("Arvore RUBRO-NEGRA: Sera inserido o valor %d.", chave);
    setSleepTime(2);
    show(ptraiz,0);
    insere(chave, ptraiz, NULL);

    chave=9;
    showComment("Arvore RUBRO-NEGRA: Sera inserido o valor %d.", chave);
    setSleepTime(2);
    show(ptraiz,0);
    insere(chave, ptraiz, NULL);

    chave=3;
    showComment("Arvore RUBRO-NEGRA: Sera inserido o valor %d.", chave);
    setSleepTime(2);
    show(ptraiz,0);
    insere(chave, ptraiz, NULL);

    showComment("Arvore RUBRO-NEGRA: Arvore Final");
    setSleepTime(10);
    show(ptraiz,0);

    terminateDSGraph();

    return 0;
}
