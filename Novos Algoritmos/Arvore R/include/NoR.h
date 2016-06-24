#ifndef POINT_H
#define POINT_H
#include <iostream>

const int d = 2;
const int MAX_R = 2*d;

class Point
{
    public:

        Point(){

            x = 0.0;
            y = 0.0;
            prox = NULL;

        }
        ~Point(){};
        int getX(){return x;}
        int getY(){return y;}
        void setXY(int X, int Y){ x = X; y = Y;}
        void setX(int X){ x = X;}
        void setY(int Y){ y = Y;}
        Point* getProx(){ return prox;}
        void setProx(Point* p){ prox = p;}

    private:

        int x, y;
        Point *prox;

};

#endif

#ifndef NOR_H
#define NOR_H

class NoR
{
    public:

        NoR(){

            listaPontos = NULL;
            idUltFilho = -1;
            MBR = NULL;
            for(int i = 0; i < MAX_R; i++){

                filhos[i] = NULL;

            }
        }
        bool ehFolha(){return idUltFilho == -1;}
        ~NoR(){

            if(MBR != NULL){

                deletePontos(MBR);

            }
            if(listaPontos != NULL){

                deletePontos(listaPontos);

            }

        };

        Point *MBR;
        NoR *filhos[MAX_R];
        int idUltFilho;
        Point *listaPontos;

        private:
        void deletePontos(Point* listaPontos){

            Point* aux;
            while(listaPontos != NULL){

                aux = listaPontos;
                listaPontos = listaPontos->getProx();
                delete aux;

            }

        }


};

#endif
