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


void ArvoreVermelhoPreta::rotacaoEsquerda(No* x){
    No* y = x->getProx();
    x->setProx(y->getAnt());
    if(y->getAnt() != NULL){
        y->getAnt()->setPai(x);
    }
    y->setPai(x->getPai());
    if(x->getPai() == NULL){
        raiz = y;
    }else{
        if(x == x->getPai()->getAnt()){
            x->getPai()->setAnt(y);
        }else{
            x->getPai()->setProx(y);
        }
    }
    y->setAnt(x);
    x->setPai(y);

//    No* temp = no->getProx();
//    if(no->getPai() != NULL){
//        if(no->getPai()->getProx() == no){
//            no->getPai()->setProx(temp);
//        }
//        if(no->getPai()->getAnt() == no){
//            no->getPai()->setAnt(temp);
//        }
//        temp->setPai(no->getPai());
//    }else{
//        raiz = temp;
//        raiz->setPai(NULL);
//    }
//    no->setProx(temp->getAnt());
//    temp->setAnt(no);
//    no->setPai(temp);
//    if(no->getProx() != NULL){
//        no->getProx()->setPai(no);
//    }
}

void ArvoreVermelhoPreta::rotacaoDireita(No* x){
    No* y = x->getAnt();
    x->setAnt(y->getProx());
    if(y->getProx() != NULL){
        y->getProx()->setPai(x);
    }
    y->setPai(x->getPai());
    if(x->getPai() == NULL){
        raiz = y;
    }else{
        if(x == x->getPai()->getProx()){
            x->getPai()->setProx(y);
        }else{
            x->getPai()->setAnt(y);
        }
    }
    y->setProx(x);
    x->setPai(y);

//    No* temp = no->getAnt();
//    if(no->getPai() != NULL){
//        if(no->getPai()->getProx() == no){
//            no->getPai()->setProx(temp);
//        }
//        if(no->getPai()->getAnt() == no){
//            no->getPai()->setAnt(temp);
//        }
//        temp->setPai(no->getPai());
//    }else{
//        raiz = temp;
//        raiz->setPai(NULL);
//    }
//    no->setAnt(temp->getProx());
//    temp->setProx(no);
//    no->setPai(temp);
//    if(no->getAnt() != NULL){
//        no->getAnt()->setPai(no);
//    }
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


No* ArvoreVermelhoPreta::getSucessor(No* no){
    No* aux = no->getProx();
    while(aux->getAnt() != NULL){
        aux = aux->getAnt();
    }
    return aux;
}

void ArvoreVermelhoPreta::remover(int valor){
    if(raiz == NULL){
        return;
    }
    No* p = raiz;
    No* y = NULL;
    No* q = NULL;
    int achou = 0;
    while( p!= NULL && achou == 0 ){
        if(p->getValor() == valor){
            achou = 1;
        }
        if(achou == 0){
            if(p->getValor() < valor){
                p = p->getProx();
            }else{
                p = p->getAnt();
            }
        }
    }
    if(achou == 0){
        // nao encontrou o valor
        return;
    }else{
        std::cout<<"oskey1"<<endl;
        if(p->getAnt() == NULL || p->getProx() == NULL){
            y = p;
        }else{
            y = getSucessor(p);
        }

        if(y->getAnt() != NULL){

            q = y->getAnt();
        }else{

            q = y->getProx();
//            if(y->getProx() != NULL){
//                q = y->getProx();
//            }else{
//                q = NULL;
//            }
        }std::cout<<"oskey3"<<endl;
        if(q!= NULL){
            q->setPai(y->getPai());
        }
        std::cout<<"oskey4"<<endl;



        if(y->getPai() == NULL){
            raiz = q;
        }else{
            if( y == y->getPai()->getAnt()){
                y->getPai()->setAnt(q);
            }else{
                y->getPai()->setProx(q);
            }
        }
        if( y != p){
            p->setValor(y->getValor());
        }
        if(y->getCor() == PRETO){
            corrigeRemocao(q);
        }


//        if( y != p ){
//            p->setCor(y->getCor());
//            p->setValor(y->getValor());
//        }
//        if(y->getCor() == PRETO){
//            corrigeRemocao(q);
//        }
    }
    std::cout << "DELETOU " << valor << endl;
}

void ArvoreVermelhoPreta::corrigeRemocao(No* x){
    if(x == NULL){
        return;
    }

    std::cout<<"corrigindo "<<x->getValor()<<endl;

    No* w;

    while( x != raiz && x->getCor() == PRETO){
        if (x == x->getPai()->getAnt()) {
            std::cout<<"ok1"<<endl;
            w = x->getPai()->getProx();
            if (w->getCor() == VERMELHO) { //CASO 1
                w->setCor(PRETO);
                x->getPai()->setCor(VERMELHO);
                rotacaoEsquerda(x->getPai());
//                raiz = left_rotate(raiz, x->getPai());
                w = x->getPai()->getProx();
            }
            //CASO 2
            if (w->getAnt()->getCor() == PRETO && w->getProx()->getCor() == PRETO) {
                w->setCor(VERMELHO);
                x = x->getPai();
            } else {
                if (w->getProx()->getCor() == PRETO) { //CASO 3
                    w->getAnt()->setCor(PRETO);
                    w->setCor(VERMELHO);
                    rotacaoDireita(w);
//                    raiz = right_rotate(raiz, w);
                    w = x->getPai()->getProx();
                }
                //CASO 4
                w->setCor(x->getPai()->getCor());
                x->getPai()->setCor(PRETO);
                w->getProx()->setCor(PRETO);
                rotacaoEsquerda(x->getPai());
//                raiz = left_rotate(raiz, x->getPai());
                x = raiz;
            }
        } else {
            std::cout<<"ok2"<<endl;
            w = x->getPai()->getAnt();
            if (w->getCor() == VERMELHO) {
                w->setCor(PRETO);
                x->getPai()->setCor(VERMELHO);
                rotacaoDireita(x->getPai());
//                raiz = right_rotate(raiz, x->getPai());
                w = x->getPai()->getAnt();
            }
            if (w->getProx()->getCor() == PRETO && w->getAnt()->getCor() == PRETO) {
                w->setCor(VERMELHO);
                x = x->getPai();
            } else {
                if (w->getAnt()->getCor() == PRETO) {
                    w->getProx()->setCor(PRETO);
                    w->setCor(VERMELHO);
                    rotacaoEsquerda(w);
//                    raiz = left_rotate(raiz, w);
                    w = x->getPai()->getAnt();
                }
                w->setCor(x->getPai()->getCor());
                x->getPai()->setCor(PRETO);
                w->getAnt()->setCor(PRETO);
                rotacaoDireita(x->getPai());
//                raiz = right_rotate(raiz, x->getPai());
                x = raiz;
            }
        }
    }
    x->setCor(PRETO);

//    if(p == NULL){
//        return;
//    }
//
//    No* s;
//    while (p!= raiz && p->getCor() == PRETO){
//        if(p->getPai()->getAnt() == p){
//            s = p->getPai()->getProx();
//            if(s->getCor() == VERMELHO){
//                s->setCor(PRETO);
//                p->getPai()->setCor(VERMELHO);
//                rotacaoEsquerda(p->getPai());
//                s = p->getPai()->getProx();
//            }
//            if(s->getProx()->getCor() == PRETO && s->getAnt()->getCor() == PRETO){
//                s->setCor(VERMELHO);
//                p = p->getPai();
//            }else{
//                if(s->getAnt()->getCor()==PRETO){
//                    s->getAnt()->setCor(PRETO);
//                    s->setCor(VERMELHO);
//                    rotacaoDireita(s);
//                    s = p->getPai()->getProx();
//                }
//                s->setCor(p->getPai()->getCor());
//                p->getPai()->setCor(PRETO);
//                s->getProx()->setCor(PRETO);
//                rotacaoEsquerda(p->getPai());
//                p = raiz;
//            }
//        }else{
//            s = p->getPai()->getAnt();
//            if(s->getCor() == VERMELHO){
//                s->setCor(PRETO);
//                p->getPai()->setCor(VERMELHO);
//                rotacaoDireita(p->getPai());
//                s = p->getPai()->getAnt();
//            }
//            if(s->getAnt()->getCor() == PRETO && s->getProx()->getCor() == PRETO){
//                s->setCor(VERMELHO);
//                p = p->getPai();
//            }else{
//                if(s->getAnt()->getCor() == PRETO){
//                    s->getProx()->setCor(PRETO);
//                    s->setCor(VERMELHO);
//                    rotacaoEsquerda(s);
//                    s = p->getPai()->getAnt();
//                }
//                s->setCor(p->getPai()->getCor());
//                p->getPai()->setCor(PRETO);
//                s->getAnt()->setCor(PRETO);
//                rotacaoDireita(p->getPai());
//                p = raiz;
//            }
//        }
//
//        p->setCor(PRETO);
//        raiz->setCor(PRETO);
//
//    }
}


No** ArvoreVermelhoPreta::getRaiz(){

    return &raiz;

}
ArvoreVermelhoPreta::~ArvoreVermelhoPreta()
{
    deletaH(raiz);
}
