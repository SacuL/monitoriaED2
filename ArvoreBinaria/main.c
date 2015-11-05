#include <stdio.h>
#include <stdlib.h>
#include "DSGraph.h"


#define MAX 100
typedef struct NODE_STRUCTURE NO;


void criarArvore(NO *pRaiz){
    pRaiz = NULL;
}


NO *inserir(NO *pRaiz, int numero){
    if(pRaiz == NULL){
        pRaiz = (NO *) malloc(sizeof(NO));
        pRaiz->next = NULL;
        pRaiz->prior = NULL;
        pRaiz->value = numero;
        return pRaiz;
    }
    else
    {
        if(numero < pRaiz->value)
           pRaiz->prior = inserir(pRaiz->prior, numero);
        if(numero > pRaiz->value)
           pRaiz->next = inserir(pRaiz->next, numero);
    }

  return pRaiz;
}



int contarNos(NO *pRaiz){
   if(pRaiz == NULL)
        return 0;
   else
        return 1 + contarNos(pRaiz->prior) + contarNos(pRaiz->next);
}


int maior(int a, int b){
    if(a > b)
        return a;
    else
        return b;
}

int altura(NO *pRaiz){
   if((pRaiz == NULL) || (pRaiz->prior == NULL && pRaiz->next == NULL))
       return 0;
   else
       return 1 + maior(altura(pRaiz->prior), altura(pRaiz->next));
}


//verifica se a arvore está vazia
int vazia(NO* a){
    return a == NULL;
}

NO *remover(int valor, NO *Arvore)
{
    NO *Aux,*Temp;
    if (Arvore->value==valor)
    {
        if((Arvore->prior!=NULL && Arvore->next!=NULL) || (Arvore->prior!=NULL && Arvore->next==NULL))
        {
            Aux=Arvore->prior; /* Guarda o endereco do no que sobe */
            Temp=Aux;

            /* Desce até a folha mais a direita do no que sobe */
            while (Temp->next!=NULL)
            {
                Temp=Temp->next;
            }

            Temp->next=Arvore->next;
        }
        else if (Arvore->next!=NULL && Arvore->prior==NULL)
            Aux=Arvore->next; /* Guarda o no que sobe */
        else
            Aux=NULL; /* Para o caso de eliminacao de uma folha. */

        free(Arvore);

        return Aux;
    }
    else
    {
        if (Arvore->value > valor)
            Arvore->prior=remover(valor,Arvore->prior);
        if (Arvore->value < valor)
            Arvore->next=remover(valor,Arvore->next);

        return Arvore;
    }
}



int main()
{

    init($BINARY_TREE);

    NO *raiz = NULL;

    criarArvore(raiz);

    setViewAddress(0);

    raiz=  inserir(raiz, 4);
    showComment("Arvore Binaria: Insere o valor 4.");
    setSleepTime(2);
    show(raiz,0);

    raiz=  inserir(raiz, 2);
    showComment("Arvore Binaria: Insere o valor 2.");
    setSleepTime(2);
    show(raiz,0);

    raiz=  inserir(raiz, 0);
    showComment("Arvore Binaria: Insere o valor 0.");
    setSleepTime(2);
    show(raiz,0);

    raiz=  inserir(raiz, 1);
    showComment("Arvore Binaria: Insere o valor 1.");
    setSleepTime(2);
    show(raiz,0);

    raiz=  inserir(raiz, 5);
    showComment("Arvore Binaria: Insere o valor 5.");
    setSleepTime(2);
    show(raiz,0);

    raiz=  inserir(raiz, 7);
    showComment("Arvore Binaria: Insere o valor 7.");
    setSleepTime(2);
    show(raiz,0);

    //Remoção de nós
    raiz=remover(2,raiz);
    showComment("Arvore Binaria: Remove o valor 2.");
    setSleepTime(2);
    show(raiz,0);

    raiz=remover(4, raiz);
    showComment("Arvore Binaria: Remove o valor 4.");
    setSleepTime(2);
    show(raiz,0);

    raiz=remover(7, raiz);
    showComment("Arvore Binaria: Remove o valor 7.");
    setSleepTime(2);
    show(raiz,0);

    raiz=remover(0, raiz);
    showComment("Arvore Binaria: Remove o valor 0.");
    setSleepTime(2);
    show(raiz,0);

    terminateDSGraph();

    return 0;
}
