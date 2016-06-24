#include <iostream>
#include <ArvoreR.h>
#include <imprimeEstrutura.h>

using namespace std;

Point* desenhaFiguraA(){

    Point *aux = new Point();
    Point *insAux;
    aux->setXY(5,6);
    insAux = aux;
    aux->setProx(new Point());
    aux = aux->getProx();
    aux->setXY(3,4);
    aux->setProx(new Point());
    aux = aux->getProx();
    aux->setXY(3,8);
    aux->setProx(new Point());
    aux = aux->getProx();
    aux->setXY(1,3);
    aux->setProx(new Point());
    aux = aux->getProx();
    aux->setXY(3,1);
    return insAux;

}
Point* desenhaFiguraB(){

    Point *aux = new Point();
    Point *insAux;
    aux->setXY(6,1);
    insAux = aux;
    aux->setProx(new Point());
    aux = aux->getProx();
    aux->setXY(6,5);
    aux->setProx(new Point());
    aux = aux->getProx();
    aux->setXY(8,5);
    aux->setProx(new Point());
    aux = aux->getProx();
    aux->setXY(8,1);
    return insAux;

}
Point* desenhaFiguraC(){

    Point *aux = new Point();
    Point *insAux;
    aux->setXY(5,1);
    insAux = aux;
    aux->setProx(new Point());
    aux = aux->getProx();
    aux->setXY(6,2);
    aux->setProx(new Point());
    aux = aux->getProx();
    aux->setXY(5,4);
    aux->setProx(new Point());
    aux = aux->getProx();
    aux->setXY(4,2);
    return insAux;

}
Point* desenhaFiguraD(){

    Point *aux = new Point();
    Point *insAux;
    aux->setXY(5,7);
    insAux = aux;
    aux->setProx(new Point());
    aux = aux->getProx();
    aux->setXY(7,7);
    aux->setProx(new Point());
    aux = aux->getProx();
    aux->setXY(8,10);
    aux->setProx(new Point());
    aux = aux->getProx();
    aux->setXY(6,10);
    return insAux;

}
Point* desenhaFiguraE(){

    Point *aux = new Point();
    Point *insAux;
    aux->setXY(9,1);
    insAux = aux;
    aux->setProx(new Point());
    aux = aux->getProx();
    aux->setXY(9,4);
    aux->setProx(new Point());
    aux = aux->getProx();
    aux->setXY(11,1);

    return insAux;

}
Point* desenhaFiguraF(){

    Point *aux = new Point();
    Point *insAux;
    aux->setXY(8,7);
    insAux = aux;
    aux->setProx(new Point());
    aux = aux->getProx();
    aux->setXY(10,9);
    aux->setProx(new Point());
    aux = aux->getProx();
    aux->setXY(12,7);
    return insAux;

}
int main()
{
    ArvoreR *AR = new ArvoreR();
    imprimeEstrutura *imp = new imprimeEstrutura(ARVORE_R);
    imp->setPriArvoreR(AR->getRaiz());
    imp->imprime((char*)"Arvore R");
    Point* aux = desenhaFiguraA();
    Point* rbusca;
    Point p;
    AR->insere(aux);
    aux = desenhaFiguraB();
    AR->insere(aux);
    aux = desenhaFiguraC();
    AR->insere(aux);
    aux = desenhaFiguraD();
    AR->insere(aux);
    aux = desenhaFiguraE();
    AR->insere(aux);
    aux = desenhaFiguraF();
    AR->insere(aux);
    p.setXY(7,4);
    rbusca = AR->busca(p);
    if(rbusca != NULL){

        cout << "Encontrou a MBR: (" << rbusca->getX() << "," << rbusca->getY() <<") - ("
        << rbusca->getProx()->getX() << "," << rbusca->getProx()->getY() << ")"<< endl;

    }else{

        cout << "Nao encontrou"<<endl;

    }
    imp->finalizaImpressao();
    delete AR;
    delete aux;
    return 0;
}
