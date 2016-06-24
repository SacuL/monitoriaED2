#include "ArvoreR.h"

ArvoreR::ArvoreR()
{
    raiz = NULL;
}
void ArvoreR::insere(Point *listaObjeto){

    if(raiz == NULL){

        raiz = new NoR();
        NoR *aux = new NoR();
        aux->listaPontos = listaObjeto;
        aux->MBR = criaMBR(listaObjeto,NULL);
        addFilho(raiz,aux);
        raiz->MBR = aux->MBR;

    }else{

        insereRecursivo(criaMBR(listaObjeto,NULL),listaObjeto,raiz);
        if(raiz->idUltFilho == MAX_R-1){

            NoR *novoNo;
            NoR *auxRaiz = new NoR();
            split(raiz, &novoNo);
            addFilho(auxRaiz,raiz);
            addFilho(auxRaiz,novoNo);
            raiz = auxRaiz;
            raiz->MBR = criaMBR(raiz->filhos[0]->MBR, raiz->filhos[1]->MBR);


        }

    }

}
void ArvoreR::insereRecursivo(Point *MBR, Point *listaPontos, NoR *n){

    if(n->filhos[0]->ehFolha()){///Verifica se esta em um No folha, se estiver, insere o objeto 'listaPontos' como filho do No 'n'

        Point* auxMBR = NULL;
        NoR *aux = new NoR();
        aux->listaPontos = listaPontos;
        aux->MBR = criaMBR(listaPontos, NULL);
        addFilho(n, aux);
        for(int i = 0; i <= n->idUltFilho; i++){///Corrige a MBR de 'n'

            auxMBR = criaMBR(auxMBR,n->filhos[i]->MBR);

        }
        n->MBR = auxMBR;

    }else{///Se 'n' nao for folha, busco o filho mais adequado para descer na arvore

        int idPos = 0;
        float areaMin = calcArea(MBR,n->filhos[0]->MBR) - calcArea(n->filhos[0]->MBR, NULL);
        float areaAux;
        Point* auxMBR = NULL;
        for(int i = 1; i <= n->idUltFilho; i++){///Verifica qual posicao tem a menor adicao na area da MBR

            areaAux = calcArea(MBR,n->filhos[i]->MBR);
            areaAux = areaAux - calcArea(MBR,n->filhos[i]->MBR);
            if(areaAux < areaMin){

                areaMin = areaAux;
                idPos = i;

            }

        }
        insereRecursivo(MBR,listaPontos,n->filhos[idPos]);///Desce na arvore
        if(n->filhos[idPos]->idUltFilho+1 == MAX_R){///Verifica se por onde o algoritmo desceu na arvore deu overflow, se caso deu, faz um split do filho com overflow

            NoR* novoNo;
            split(n->filhos[idPos], &novoNo);
            addFilho(n, novoNo);

        }
        for(int i = 0; i <= n->idUltFilho; i++){///Corrige a MBR de 'n'

            auxMBR = criaMBR(auxMBR,n->filhos[i]->MBR);

        }
        delete n->MBR;
        n->MBR = auxMBR;

    }

}
void ArvoreR::addFilho(NoR* pai, NoR* filho){

    pai->idUltFilho++;
    pai->filhos[pai->idUltFilho] = filho;

}
Point* ArvoreR::criaMBR(Point* listaP1, Point* listaP2){

    float xMin, xMax, yMin, yMax;

    if(listaP1 == NULL && listaP2 == NULL)return NULL;
    else{

        Point* aux;
        if(listaP1 != NULL){

            xMin = listaP1->getX();
            xMax = listaP1->getX();
            yMin = listaP1->getY();
            yMax = listaP1->getY();

            aux = listaP1->getProx();
            while(aux != NULL){

                if(aux->getX() > xMax){

                    xMax = aux->getX();

                }else if(aux->getX() < xMin){

                    xMin = aux->getX();

                }
                if(aux->getY() > yMax){

                    yMax = aux->getY();

                }else if(aux->getY() < yMin){

                    yMin = aux->getY();

                }

                aux = aux->getProx();

            }

        }if(listaP2 != NULL){

            if(listaP1 == NULL){

                xMin = listaP2->getX();
                xMax = listaP2->getX();
                yMin = listaP2->getY();
                yMax = listaP2->getY();

            }
            aux = listaP2->getProx();
            while(aux != NULL){

                if(aux->getX() > xMax){

                    xMax = aux->getX();

                }else if(aux->getX() < xMin){

                    xMin = aux->getX();

                }
                if(aux->getY() > yMax){

                    yMax = aux->getY();

                }else if(aux->getY() < yMin){

                    yMin = aux->getY();

                }

                aux = aux->getProx();
            }

        }


        aux = new Point();
        aux->setXY(xMin,yMin);
        aux->setProx(new Point());
        aux->getProx()->setXY(xMax,yMax);
        return aux;

    }

}
float ArvoreR::calcArea(Point* MBR){

    return (MBR->getProx()->getX()-MBR->getX())*(MBR->getProx()->getY() - MBR->getY());

}
float ArvoreR::calcArea(Point* MBR1, Point* MBR2){

    Point* auxMBR = criaMBR(MBR1,MBR2);
    float area = calcArea(auxMBR);
    delete auxMBR;
    return area;

}
 void ArvoreR::split(NoR *n, NoR **novoNo){

    int MID = MAX_R/2;///Encontro a posicao do meio do vetor de filhos;
    int k=0;///Flag para percorrer o vetor de filhos do 'novoNo'

    *novoNo = new NoR();

    for(int i = MID; i < MAX_R; i++){

        (*novoNo)->filhos[k] = n->filhos[i];
        (*novoNo)->idUltFilho++;
        n->filhos[i] = NULL;
        k++;

    }
    if(MAX_R != 1){

        n->idUltFilho = MID-1;

    }else{

        n->idUltFilho = 0;

    }
    Point* auxMBR = NULL;
    for(int i = 0; i <= n->idUltFilho; i++){///Corrige a MBR do no 'n'

         auxMBR = criaMBR(auxMBR,n->filhos[i]->MBR);

    }
    n->MBR = auxMBR;
    auxMBR = NULL;
    for(int i = 0; i <= (*novoNo)->idUltFilho; i++){///Corrige a MBR do no 'novoNo'

         auxMBR = criaMBR(auxMBR,(*novoNo)->filhos[i]->MBR);

    }
    (*novoNo)->MBR = auxMBR;

 }
 NoR** ArvoreR::getRaiz(){

    return &raiz;

 }
 Point* ArvoreR::busca(Point p){

    return buscaRecursiva(p,raiz);

 }
 Point* ArvoreR::buscaRecursiva(Point p, NoR* n){

    Point* aux = NULL;
    for(int i = 0; i <= n->idUltFilho; i++){

        if(pertenceMBR(p,n->filhos[i]->MBR)){

            if(n->filhos[0]->ehFolha()){

                return n->filhos[i]->MBR;

            }else{

                aux = buscaRecursiva(p,n->filhos[i]);
                if(aux != NULL){

                    return aux;

                }
            }

        }

    }
    return NULL;

 }
 bool ArvoreR::pertenceMBR(Point p, Point* MBR){

    if(p.getX() >= MBR->getX() && p.getY() >= MBR->getY()){

        if(p.getX() <= MBR->getProx()->getX() && p.getY() <= MBR->getProx()->getY()){

            return true;

        }

    }
    return false;

 }
 void ArvoreR::deletaArvore(NoR* n){

    if(n == NULL)return;

    for(int i = 0; i <= n->idUltFilho; i++){

        deletaArvore(n->filhos[i]);

    }
    delete n;

 }
ArvoreR::~ArvoreR()
{
    deletaArvore(raiz);

}
