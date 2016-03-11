#include "TrieTernaria.h"

TrieTernaria::TrieTernaria()
{
    raiz = NULL;
}
bool TrieTernaria::busca(string palavra){
    cout << "Buscando a palavra " << palavra<< "... ";
    bool achou = buscaAux(raiz, palavra);
    if(achou){
        cout << "encontrado!" << endl;
    }else{
        cout << "NAO encontrado!" << endl;
    }
    return achou;
}

bool TrieTernaria::buscaAux(No_Ter* no, string palavra){
    if(no == NULL) return false;
    char caractere = palavra.at(0);

    if(caractere == no->getChar()){
        if(palavra.size() == 1 && no->getChave()){
            return true;
        }else{
            return buscaAux(no->getMeio(),palavra.substr(1,palavra.size()));
        }
    }else{
        if(palavra.size()== 1){
            return false;
        }
        if(caractere > no->getChar()){
            return buscaAux(no->getDir(),palavra);
        }else{
            return buscaAux(no->getEsq(),palavra);
        }
    }
}

void TrieTernaria::insere(string palavra){
    raiz = insereAux(raiz,palavra);
}

No_Ter* TrieTernaria::insereAux(No_Ter* no, string palavra){

    cout << "Inserindo palavra " << palavra << endl;
    char caractere = palavra.at(0);

    if(no == NULL){
        no = new No_Ter();
        no->setChar(caractere);
        cout << "No NULL encontrado! Caractere "<<caractere<<" inserido! " <<endl;
    }

    if(caractere > no->getChar()){
        cout << "Inserindo " << palavra << " na direita! " << endl;
        no->setDir(insereAux(no->getDir(),palavra));
    }else if(caractere < no->getChar()){
        cout << "Inserindo " << palavra << " na esquerda! " << endl;
        no->setEsq(insereAux(no->getEsq(),palavra));
    }else{
        if(palavra.size() == 1){
            cout << "Ultimo caractere! "<< endl;
            no->setChave(true);
        }else{
            cout << "Inserindo " << palavra.substr(1,palavra.size())<< " no meio! "<< endl;
            no->setMeio(insereAux(no->getMeio(),palavra.substr(1,palavra.size())));
        }
    }
    return no;
}

void TrieTernaria::deletaT(No_Ter* n){

    if(n != NULL){

        No_Ter *aux = n;
        while(aux->getEsq() != NULL){aux = aux->getEsq();}
        while(aux != NULL){

            deletaT(aux->getMeio());
            aux = aux->getDir();
        }
        delete n;
    }


}
void TrieTernaria::imprime(){
    imprimeAux(raiz,"");
}

void TrieTernaria::imprimeAux(No_Ter* no, string palavra){
    if(no == NULL) return;
    if(no->getChave()){
        cout << palavra << no->getChar() << endl;
    }
    imprimeAux(no->getEsq(),palavra);
    imprimeAux(no->getMeio(),(palavra+no->getChar()));
    imprimeAux(no->getDir(),palavra);
}

//void TrieTernaria::remove(char *c, int tam){

//    removeT(c,raiz,0,tam);

//}
No_Ter** TrieTernaria::getRaiz(){

    return &raiz;

}
TrieTernaria::~TrieTernaria()
{

//    deletaT(raiz);

}
