#include "ABB.h"

ABB::ABB()
{
    raiz = NULL;
}

No* ABB::insereAux(No* no, int valor)
{
    if (no == NULL)
    {
        no = new No();;
        no->setValor(valor);
        return no;
    }
    else
    {
        if(valor < no->getValor())
        {
            no->setEsquerda(insereAux(no->getEsquerda(),valor));
        }
        else
        {
            no->setDireita(insereAux(no->getDireita(),valor));
        }
    }
    return no;
}

void ABB::removeAux(No* no, No* pai, int valor)
{
    if (no == NULL) return;

    if (no->getValor() == valor)
    {
        // se o no atual tem 1 ou nenhum filho
        if(no->getEsquerda() == NULL || no->getDireita() == NULL){
            No* aux = NULL;
            // faz aux apontar para o unico filho de no
            if(no->getDireita()!=NULL){
                aux = no->getDireita();
            }else{
                aux = no->getEsquerda();
            }

            // faz o pai apontar para o filho do no atual
            if(pai != NULL){
                if(pai->getEsquerda()== no){
                    pai->setEsquerda(aux);
                }else{
                    pai->setDireita(aux);
                }
            }else{
                raiz = aux;
            }

            // remove o no
            delete no;

        }else { // o no tem 2 filhos
            // encontra  o sucessor (menor valor da subarvore a direita)
            No* sucessor = no->getDireita();
            while(sucessor->getEsquerda()!=NULL){
                sucessor = sucessor->getEsquerda();
            }
            no->setValor(sucessor->getValor());
            // remover o no do sucessor
            removeAux(no->getDireita(),no,sucessor->getValor());
        }
    }
    else
    {
        if(valor < no->getValor())
        {
            removeAux(no->getEsquerda(),no,valor);
        }
        else
        {
            removeAux(no->getDireita(),no,valor);
        }
    }
}


void ABB::remover(int valor)
{
    removeAux(raiz, NULL, valor);
}

void ABB::inserir(int valor)
{
    raiz = insereAux(raiz, valor);
}

No** ABB::getRaiz()
{

    return &raiz;

}

void ABB::deletaH(No* no)
{
    if(no != NULL)
    {
        deletaH(no->getEsquerda());
        deletaH(no->getDireita());
        delete no;
    }
}

ABB::~ABB()
{
    deletaH(raiz);
}

