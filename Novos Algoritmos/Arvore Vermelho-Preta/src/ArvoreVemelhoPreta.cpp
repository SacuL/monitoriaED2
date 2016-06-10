#include "ArvoreVermelhoPreta.h"
#include <iostream>

using namespace std;

ArvoreVermelhoPreta::ArvoreVermelhoPreta()
{
    raiz = NULL;
}
void ArvoreVermelhoPreta::deletaH(No_VP* p){

    if(p != NULL){

        deletaH(p->getAnt());
        deletaH(p->getProx());
        delete p;

    }

}


void ArvoreVermelhoPreta::rotacaoEsquerda(No_VP* x){
    No_VP* y = x->getProx();
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
}

void ArvoreVermelhoPreta::rotacaoDireita(No_VP* x){
    No_VP* y = x->getAnt();
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
}

void ArvoreVermelhoPreta::corrigeCaso1(No_VP* no){
    // Caso 1: Se o NO eh raiz, ele deve ser PRETO
    if(no->getPai() == NULL){
        no->setCor(PRETO);
    }else{
        corrigeCaso2(no);
    }
}

void ArvoreVermelhoPreta::corrigeCaso2(No_VP* no){
    // Caso 2: Se o pai do NO for PRETO, a Arvore continua valida
    if(no->getPai()->getCor() == PRETO){
        return;
    }else{
        corrigeCaso3(no);
    }
}

void ArvoreVermelhoPreta::corrigeCaso3(No_VP* no){
    // Caso 3: Pai e Tio do NO VERMELHOS - passam para PRETO e Avo de NO passa para VERMELHO
    No_VP* tio = no->getTio();

    if(tio != NULL && tio->getCor()==VERMELHO){
        no->getPai()->setCor(PRETO);
        tio->setCor(PRETO);
        No_VP* avo = no->getAvo();
        avo->setCor(VERMELHO);

        corrigeCaso1(avo);
    }else{
        corrigeCaso4(no);
    }
}

void ArvoreVermelhoPreta::corrigeCaso4(No_VP* no){
    // Caso 4: O pai do NO eh VERMELHO mas o tio de NO eh PRETO
    No_VP* avo = no->getAvo();
    No_VP* pai = no->getPai();
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

void ArvoreVermelhoPreta::corrigeCaso5(No_VP* no){
    // Caso 5:  O pai do NO eh VERMELHO mas o tio do NO eh PRETO
    No_VP* avo = no->getAvo();
    No_VP* pai = no->getPai();
    pai->setCor(PRETO);
    avo->setCor(VERMELHO);
    if( (no == pai->getAnt()) && (pai == avo->getAnt()) ){
        // Rotacao a direita do avo do NO
        rotacaoDireita(avo);
    }else{
        // Rotacao a esquerda do avo do NO
        rotacaoEsquerda(avo);
    }
}

void ArvoreVermelhoPreta::insereAVP(No_VP* no, No_VP* pai, int valor){

    if(no == NULL){
        No_VP* novo = new No_VP(valor);
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

void ArvoreVermelhoPreta::trocaNos(No_VP* noVelho, No_VP* noNovo){
    if(noVelho->getPai() == NULL){
        raiz = noNovo;
    }else{
        if(noVelho == noVelho->getPai()->getAnt()){
            noVelho->getPai()->setAnt(noNovo);
        }else{
            noVelho->getPai()->setProx(noNovo);
        }
    }
    if(noNovo != NULL){
        noNovo->setPai(noVelho->getPai());
    }

}
No_VP* ArvoreVermelhoPreta::getPredecessor(No_VP* no){
    while(no->getProx() != NULL){
        no = no->getProx();
    }
    return no;
}

No_VP* ArvoreVermelhoPreta::getIrmao(No_VP* no){
    if(no == NULL || no->getPai() == NULL){
        cout<<"\n\nERRO NO OU PAI DO NO EH NULL!!"<<endl;
    }
    if(no == no->getPai()->getAnt()){
        return no->getPai()->getProx();
    }else{
        return no->getPai()->getAnt();
    }
}

void ArvoreVermelhoPreta::remover(int valor){
    if(raiz == NULL){
        return;
    }
    No_VP* p = raiz;
    int achou = 0;
    while( p!= NULL  ){
        if(p->getValor() == valor){
            achou = 1;
            break;
        }
        if(p->getValor() < valor){
            p = p->getProx();
        }else{
            p = p->getAnt();
        }
    }
    if(achou == 0){
        // nao encontrou o valor
        return;
    }else{
        cout<<"Iniciando remocao do valor "<<valor<<endl;
        if(p->getAnt() != NULL && p->getProx() != NULL){
            cout << "No a ser removido tem 2 filhos" <<endl;
            No_VP* predecessor = getPredecessor(p->getAnt());
            cout << "Seu predecessor eh o no "<<predecessor->getValor()<<endl;
            cout << "Substituindo o no a ser removido "<<p->getValor()<<" pelo seu predecessor "<<predecessor->getValor()<<endl;
            p->setValor(predecessor->getValor());
            p = predecessor;
            cout << "Agora o no a ser ajustado eh o no "<<p->getValor()<<endl;
        }else{
            cout << "No a ser removido tem 1 ou nenhum filho" <<endl;
        }

        // p deve ser uma folha ou ter apenas 1 filho
        if(p->getAnt() == NULL || p->getProx() == NULL){
        }else{
            cout << "\n\nERRO: P TEM 2 FILHOS!" << endl;
        }
        // pega o unico filho de p, se houver
        No_VP* filho = (p->getProx()==NULL) ? p->getAnt() : p->getProx();
        if(p->getCor() == PRETO){
            if(filho != NULL){
                p->setCor(filho->getCor());
            }else{
                p->setCor(PRETO);
            }
            removerCaso1(p);
        }

        trocaNos(p,filho);

        delete p;

        cout << "DELETOU " << valor << endl;
    }
}

void ArvoreVermelhoPreta::removerCaso1(No_VP* n){
    cout << "Remocao caso 1(no="<<n->getValor()<<"):";
    if(n->getPai()==NULL){
        cout<<" pai eh null. Fim."<<endl;
        return;
    }else{
        cout<<" pai nao eh null. Fim do caso 1."<<endl;
        removerCaso2(n);
    }
}

void ArvoreVermelhoPreta::removerCaso2(No_VP* n){
    cout << "Remocao caso 2(no="<<n->getValor()<<"):";
    No_VP* irmao = getIrmao(n);
    if(irmao->getCor()==VERMELHO){
        cout << "A cor do no " << irmao->getValor() << " eh VERMELHO"<<endl;
    }else{
        cout << "A cor do no " << irmao->getValor() << " eh PRETO"<<endl;
    }
    if(irmao->getCor() == VERMELHO){
        cout<<" irmao vermelho: rotacionar.";
        n->getPai()->setCor(VERMELHO);
        irmao->setCor(PRETO);

        if(n == n->getPai()->getAnt()){
            rotacaoEsquerda(n->getPai());
        }else{
            rotacaoDireita(n->getPai());
        }
    }else{
        cout<<" irmao NAO eh vermelho.";
    }
    cout << " Fim do caso 2."<<endl;
    removerCaso3(n);
}

void ArvoreVermelhoPreta::removerCaso3(No_VP* n){
    cout << "Remocao caso 3(no="<<n->getValor()<<"):";
    No_VP* irmao = getIrmao(n);
    if(irmao == NULL){
        cout<<"\n\nERRO IRMAO IGUAL A NULL"<<endl;
    }
    if(n->getPai()->getCor() == PRETO && irmao->getCor()== PRETO){
        if(irmao->getAnt()==NULL || irmao->getAnt()->getCor() == PRETO){
            if(irmao->getProx()==NULL || irmao->getProx()->getCor() == PRETO){
                cout << " pai, irmao, e filhos do irmao PRETOS:\ncolorir irmao de vermelho e voltar para caso 1 no pai do no atual."<<endl<<"Fim do caso 3."<<endl;
                irmao->setCor(VERMELHO);
                if(irmao->getCor()==VERMELHO){
                    cout << "A cor do no " << irmao->getValor() << " eh VERMELHO"<<endl;
                }else{
                    cout << "A cor do no " << irmao->getValor() << " eh PRETO"<<endl;
                }
                removerCaso1(n->getPai());

                return;
            }
        }
    }
    cout<<" nada a fazer. Fim do caso 3"<<endl;
    removerCaso4(n);
}

void ArvoreVermelhoPreta::removerCaso4(No_VP* n){
    cout << "Remocao caso 4(no="<<n->getValor()<<"):";
    No_VP* irmao = getIrmao(n);
    if(irmao == NULL){
        cout<<"\n\nERRO IRMAO IGUAL A NULL"<<endl;
    }
    if(n->getPai()!= NULL && n->getPai()->getCor() == VERMELHO && irmao->getCor()==PRETO){
        if(irmao->getAnt() == NULL || irmao->getAnt()->getCor() == PRETO){
            if(irmao->getProx() == NULL || irmao->getProx()->getCor() == PRETO){
                cout << " pai VERMELHO, irmao, e filhos do irmao PRETOS:\ncolorir irmao de vermelho e pai de preto."<<endl<<"Fim do caso 4."<<endl;
                irmao->setCor(VERMELHO);
                n->getPai()->setCor(PRETO);
                return;
            }
        }
    }
    cout << " nada a fazer. Fim do caso 4."<<endl;
    removerCaso5(n);

}

void ArvoreVermelhoPreta::removerCaso5(No_VP* n){
    cout << "Remocao caso 5(no="<<n->getValor()<<"):";
    No_VP* irmao = getIrmao(n);
    if(irmao == NULL){
        cout<<"\n\nERRO IRMAO IGUAL A NULL"<<endl;
    }
    if( n == n->getPai()->getAnt() && irmao->getCor() == PRETO
        && (irmao->getAnt() != NULL && irmao->getAnt()->getCor() == VERMELHO)
        && (irmao->getProx() == NULL || irmao->getAnt()->getCor() == PRETO)){
        cout<< " no a esquerda do pai com irmao preto, sobrinho a esquerda vermelho e sobrinho a direita preto:\n"
            << "colorir irmao de vermelho, sobrinho a esquerda de preto e rotacionar o irmao para direita. Fim do caso 5."<<endl;
        irmao->setCor(VERMELHO);
        irmao->getAnt()->setCor(PRETO);
        rotacaoDireita(irmao);
    }else if( n == n->getPai()->getProx() && irmao->getCor() == PRETO
        && (irmao->getProx() != NULL && irmao->getProx()->getCor() == VERMELHO)
        && (irmao->getAnt() == NULL || irmao->getAnt()->getCor() == PRETO)){
        cout<< " no a direita do pai com irmao preto, sobrinho a direita vermelho e sobrinho a esquerda preto:\n"
            << "colorir irmao de vermelho, sobrinho a direita de preto e rotacionar o irmao para esquerda. Fim do caso 5."<<endl;
        irmao->setCor(VERMELHO);
        irmao->getProx()->setCor(PRETO);
        rotacaoEsquerda(irmao);
    }else{
        cout<< " nada a fazer. Fim do caso 5."<<endl;
    }
    removerCaso6(n);
}

void ArvoreVermelhoPreta::removerCaso6(No_VP* n){
    cout << "Remocao caso 6(no="<<n->getValor()<<"):";
    No_VP* irmao = getIrmao(n);
    if(irmao == NULL){
        cout<<"\n\nERRO IRMAO IGUAL A NULL"<<endl;
    }
    cout<<" colorir irmao com a cor do pai e o pai de preto."<<endl;
    irmao->setCor(n->getPai()->getCor());
    n->getPai()->setCor(PRETO);

    if(n == n->getPai()->getAnt()){
        if(irmao->getProx()==NULL){
            cout<<"\n\nERRO SOBRINHO A DIREITA IGUAL A NULL"<<endl;
        }else if (irmao->getProx()->getCor()!=VERMELHO){
            cout<<"\n\nERRO SOBRINHO A DIREITA EH PRETO"<<endl;
        }
        cout<<"No eh filho a esquerda: colorir sobrinho a direita de preto e rotacionar o pai para a esquerda. Fim do caso 6"<<endl;
        irmao->getProx()->setCor(PRETO);
        rotacaoEsquerda(n->getPai());
    }else{
        if(irmao->getAnt()==NULL || irmao->getAnt()->getCor()!=VERMELHO){
            cout<<"\n\nERRO SOBRINHO A ESQUERDA IGUAL A NULL OU PRETO"<<endl;
        }
        cout<<"No eh filho a direita: colorir sobrinho a esquerda de preto e rotacionar o pai para a direita. Fim do caso 6"<<endl;
        irmao->getAnt()->setCor(PRETO);
        rotacaoDireita(n->getPai());
    }
}


No_VP** ArvoreVermelhoPreta::getRaiz(){

    return &raiz;

}
int ArvoreVermelhoPreta::alturaVermelhoPreta(){

    return altura(raiz);

}
int ArvoreVermelhoPreta::altura(No_VP* no){

    if(no ==  NULL){

        return 0;

    }else{
        int esq = 0, dir = 0;

        if(no->getAnt() != NULL && no->getProx() != NULL){

            if(no->getAnt()->getCor() == no->getProx()->getCor()){

                esq = altura(no->getAnt());
                dir = altura(no->getProx());

            }else{

                if(no->getAnt() == VERMELHO){

                    esq = altura(no->getAnt());

                }else{

                    dir = altura(no->getAnt());

                }

            }

        }else{

            esq = altura(no->getAnt());
            dir = altura(no->getProx());

        }


        if(esq > dir){

            return esq+1;

        }else{

            return dir+1;

        }

    }

}
ArvoreVermelhoPreta::~ArvoreVermelhoPreta()
{
    deletaH(raiz);
}
