#include "heapBinomial.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

heapBinomial::heapBinomial(){
    cabeca = NULL;
}

No_Binomial* heapBinomial::criaNo(int valor){

    No_Binomial* aux = new No_Binomial(valor);

    return aux;
}

void heapBinomial::insere(int valor){

    No_Binomial* novoNo = criaNo(valor);

    cabeca = uniaoHeapsBinomiais(novoNo, cabeca);
}

// Soma duas árvores binomiais adjacentes que pertencem ao heap
No_Binomial* heapBinomial::somaArvoresBinomiais(No_Binomial* a1, No_Binomial* a2){
    if(a1->getGrau() != a2->getGrau()){
        cout << "ERRO: somando duas arvores binomiais de graus distintos!" << endl;
        return NULL;
    }

    No_Binomial* aux;
    // Se a1 > a2 troca (a1 se torna o menor)
    if(a1->getValor() > a2->getValor()){
        aux = a1;
        a1 = a2;
        a2 = aux;
    }

    // Acerta o ponteiro para o resto do heap
    if(a1->getIrmao() == a2){
        a1->setIrmao(a2->getIrmao());
    }
    a2->setIrmao(NULL);

    // Escolhe a raíz mais prioritária e coloca a outra como sua filha
    if(a1->getFilho() == NULL){ // caso k1
        a1->setFilho(a2);
    }else{ // casos kn, n>1
        aux = a1->getFilho();
        while (aux->getIrmao() != NULL){
            aux = aux->getIrmao();
        }
        aux->setIrmao(a2);
    }
    a2->setPai(a1);

    // Acertar o grau
    a1->incrementaGrau();

    return a1;
}

No_Binomial* heapBinomial::intercalacaoHeapsBinomiais(No_Binomial* h1, No_Binomial* h2){
    if(h1 == NULL) return h2;
    if(h2 == NULL) return h1;

    No_Binomial* h;
    if(h1->getGrau() < h2->getGrau()){
        h = h1;
        h1 = h1->getIrmao();
    }else{
        h = h2;
        h2 = h2->getIrmao();
    }
    No_Binomial* aux = h;
    while(h1 != NULL && h2 != NULL){
        if(h1->getGrau() < h2->getGrau()){
            aux->setIrmao(h1);
            h1 = h1->getIrmao();
        }else{
            aux->setIrmao(h2);
            h2 = h2->getIrmao();
        }
        aux = aux->getIrmao();
    }
    if(h1 == NULL){
        aux->setIrmao(h2);
    }else{
        aux->setIrmao(h1);
    }

    return h;
}

void heapBinomial::uniaoHeapsBinomiais(No_Binomial* h){
    cabeca = uniaoHeapsBinomiais(cabeca, h);
}

No_Binomial* heapBinomial::uniaoHeapsBinomiais(No_Binomial* h1, No_Binomial* h2){

    if(h1 == NULL) return h2;
    if(h2 == NULL) return h1;

    No_Binomial* h = intercalacaoHeapsBinomiais(h1, h2);

    No_Binomial* aux = h;
    No_Binomial* a = h;
    No_Binomial* anterior = h;
    while (aux != NULL){
        No_Binomial* b = a->getIrmao();
        if(b != NULL && b->getGrau() == a->getGrau()){
            if(b->getIrmao() != NULL && b->getIrmao()->getGrau() == a->getGrau()){
                anterior = a;
                a = b;
                b = b->getIrmao();
            }
            if(h == a){ // 'a' eh a primeira arvore
                h = somaArvoresBinomiais(a,b);
                aux = h;
                a = h;
                anterior  = h;
            }else{
                aux = somaArvoresBinomiais(a,b);
                anterior->setIrmao(aux);
                a = aux;
            }
        }else{
            anterior = aux;
            aux = aux->getIrmao();
            a = aux;
        }
    }

    return h;

}

void heapBinomial::imprimeHeapConsole(){
    No_Binomial* aux = cabeca;
    cout << "Iniciando impressao do Heap...";
    while(aux!=NULL){
        cout << endl << "-> Arvore de k = " << aux->getGrau() << endl << "--> " << aux->getValor() << " ";
        imprimeArvoreConsole(aux->getFilho());
        aux = aux->getIrmao();
    }
    cout << endl << "Fim da impressao." << endl;
}

// Imprime a arvore binomial de raiz r
void heapBinomial::imprimeArvoreConsole(No_Binomial* r){
    if(r == NULL) return;
    cout << r->getValor() << " ";
    imprimeArvoreConsole(r->getFilho());
    imprimeArvoreConsole(r->getIrmao());
}

// Remove e retorna o no mais prioritário
No_Binomial* heapBinomial::remover(){
    if(cabeca == NULL) return NULL;

    No_Binomial* aux = cabeca;
    No_Binomial* anterior = cabeca;
    No_Binomial* mais_prioritario = aux;
    while (aux->getIrmao() != NULL){
        if(aux->getIrmao()->getValor() < mais_prioritario->getValor()){
            anterior  = aux;
            mais_prioritario = aux->getIrmao();
        }
        aux = aux->getIrmao();
    }

    if(mais_prioritario == cabeca){
        cabeca = uniaoHeapsBinomiais(cabeca->getIrmao(),cabeca->getFilho());
    }else{
        anterior->setIrmao(mais_prioritario->getIrmao());
        cabeca = uniaoHeapsBinomiais(cabeca, mais_prioritario->getFilho());
    }

    return mais_prioritario;
}

No_Binomial* heapBinomial::getCabeca(){
    return cabeca;
}

void heapBinomial::deletaH(No_Binomial* n){
    if(n == NULL) return;
    deletaH(n->getIrmao());
    deletaH(n->getFilho());
    delete n->getFilho();
    delete n->getIrmao();

}

heapBinomial::~heapBinomial(){

    deletaH(cabeca);
    delete cabeca->getFilho();
    delete cabeca->getIrmao();
}

