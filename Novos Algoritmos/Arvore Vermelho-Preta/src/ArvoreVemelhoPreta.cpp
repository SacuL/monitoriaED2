#include "ArvoreVermelhoPreta.h"
#include <iostream>

using namespace std;

ArvoreVermelhoPreta::ArvoreVermelhoPreta()
{
    raiz = NULL;
}
void ArvoreVermelhoPreta::deletaH(No* p){

    if(p != NULL){

        deletaH(p->getAnt());
        deletaH(p->getProx());
        delete p;

    }

}


void ArvoreVermelhoPreta::rotacaoEsquerda(No* no){
    No* temp = no->getProx();
    if(no->getPai() != NULL){
        if(no->getPai()->getProx() == no){
            no->getPai()->setProx(temp);
        }
        if(no->getPai()->getAnt() == no){
            no->getPai()->setAnt(temp);
        }
        temp->setPai(no->getPai());
    }else{
        raiz = temp;
        raiz->setPai(NULL);
    }
    no->setProx(temp->getAnt());
    temp->setAnt(no);
    no->setPai(temp);
    if(no->getProx() != NULL){
        no->getProx()->setPai(no);
    }
}

void ArvoreVermelhoPreta::rotacaoDireita(No* no){
    No* temp = no->getAnt();
    if(no->getPai() != NULL){
        if(no->getPai()->getProx() == no){
            no->getPai()->setProx(temp);
        }
        if(no->getPai()->getAnt() == no){
            no->getPai()->setAnt(temp);
        }
        temp->setPai(no->getPai());
    }else{
        raiz = temp;
        raiz->setPai(NULL);
    }
    no->setAnt(temp->getProx());
    temp->setProx(no);
    no->setPai(temp);
    if(no->getAnt() != NULL){
        no->getAnt()->setPai(no);
    }
}


void ArvoreVermelhoPreta::corrigeCaso1(No* no){
    // Caso 1: Se o NO eh raiz, ele deve ser PRETO
    if(no->getPai() == NULL){
        no->setCor(PRETO);
    }else{
        corrigeCaso2(no);
    }
}

void ArvoreVermelhoPreta::corrigeCaso2(No* no){
    // Caso 2: Se o pai do NO for PRETO, a Arvore continua valida
    if(no->getPai()->getCor() == PRETO){
        return;
    }else{
        corrigeCaso3(no);
    }
}

void ArvoreVermelhoPreta::corrigeCaso3(No* no){
    // Caso 3: Pai e Tio do NO VERMELHOS - passam para PRETO e Avo de NO passa para VERMELHO
    No* tio = no->getTio();

    if(tio != NULL && tio->getCor()==VERMELHO){
        no->getPai()->setCor(PRETO);
        tio->setCor(PRETO);
        No* avo = no->getAvo();
        avo->setCor(VERMELHO);

        corrigeCaso1(avo);
    }else{
        corrigeCaso4(no);
    }
}

void ArvoreVermelhoPreta::corrigeCaso4(No* no){
    // Caso 4: O pai do NO eh VERMELHO mas o tio de NO eh PRETO
    No* avo = no->getAvo();
    No* pai = no->getPai();
    if( (no == pai->getProx()) && (pai == avo->getAnt()) ){
        // Rotacao a esquerda do pai do NO
        rotacaoEsquerda(pai);
        no = no->getAnt();
    }else if( (no == pai->getAnt()) && (pai == avo->getProx()) ){
        // Rotacao a direita do pai do NO
        rotacaoDireita(pai);
        no = no->getProx();
    }
    corrigeCaso5(no);
}

void ArvoreVermelhoPreta::corrigeCaso5(No* no){
    // Caso 5:  O pai do NO eh VERMELHO mas o tio do NO eh PRETO
    No* avo = no->getAvo();
    No* pai = no->getPai();
    pai->setCor(PRETO);
    avo->setCor(VERMELHO);
    if( (no = pai->getAnt()) && (pai == avo->getAnt()) ){
        // Rotacao a direita do avo do NO
        rotacaoDireita(avo);
    }else{
        // Rotacao a esquerda do avo do NO
        rotacaoEsquerda(avo);
    }
}

void ArvoreVermelhoPreta::insereAVP(No* no, No* pai, int valor){

    if(no == NULL){
        No* novo = new No(valor);
        if(pai != NULL){
            novo->setPai(pai);
            if(valor < pai->getValor()){
                pai->setAnt(novo);
            }else{
                pai->setProx(novo);
            }
        }else{
            raiz = novo;
        }
        corrigeCaso1(novo);
    }else{
        if(valor < no->getValor()){
            insereAVP(no->getAnt(),no,valor);
        }else{
            insereAVP(no->getProx(),no,valor);
        }
    }
}


void ArvoreVermelhoPreta::insere(int valor){
    insereAVP(raiz,NULL,valor);
}
void ArvoreVermelhoPreta::remover(int p){

}
No** ArvoreVermelhoPreta::getRaiz(){

    return &raiz;

}
ArvoreVermelhoPreta::~ArvoreVermelhoPreta()
{
    deletaH(raiz);
}
