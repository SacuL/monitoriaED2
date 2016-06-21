#include "ArvoreSPLAY.h"
#include <iostream>

ArvoreSPLAY::ArvoreSPLAY()
{
    raiz = NULL;
}

void ArvoreSPLAY::insere(int valor){
    No* x = insere(raiz, valor);
    raiz = x;
}

No* ArvoreSPLAY::insere(No* p, int valor){
	No *temp1,*temp2,*par;
	if(p == NULL)
	{
        p = new No(valor);
        if(p == NULL)
        {
            std::cout << "Erro ao alocar memoria!\n";
            exit(0);
        }
        return(p);
	}
	//the case 2 says that we must splay newly inserted node to root
	else
	{
        temp2 = p;
        while(temp2 != NULL)
        {
            temp1 = temp2;
            if(temp2->getValor() > valor)
                temp2 = temp2->getAnt();
            else if(temp2->getValor() < valor)
                temp2 = temp2->getProx();
            else
                if(temp2->getValor() == valor)
                    return temp2;
        }
        if(temp1->getValor() > valor)
        {
            par = temp1;//temp1 having the parent address,so that's it
            temp1->setAnt(new No(valor));
            temp1 = temp1->getAnt();
            if(temp1 != NULL)
            {
                temp1->setPai(par);//store the parent address.
            }
            else
            {
                std::cout << "Erro ao alocar memoria!\n";
                exit(0);
            }
        }
        else
        {
            par = temp1;//temp1 having the parent node address.
            temp1->setProx(new No(valor));
            temp1 = temp1->getProx();
            if(temp1 != NULL)
            {
                temp1->setPai(par);//store the parent address
            }
            else
            {
                std::cout << "Erro ao alocar memoria!\n";
                exit(0);
            }
        }
	}
	splay(temp1,p);//temp1 will be new root after splaying
	return (temp1);
}

void ArvoreSPLAY::deletaH(No* p){
    if(p != NULL){
        deletaH(p->getAnt());
        deletaH(p->getProx());
        delete p;
    }
}

// Função que retorna o NÓ sucessor
No* ArvoreSPLAY::sucessor(No *x)
{
    No *temp, *temp2;
    temp = temp2 = x->getProx();
    while(temp != NULL)
    {
        temp2 = temp;
        temp = temp->getAnt();
    }
    return temp2;
}

// Remove valor da arvore
No* ArvoreSPLAY::removerH(No *p, int valor)
{
    No *x,*y;
    No *r;
    No *s;
    r = p;
    x = buscarH(p,valor);
    if(x->getValor() == valor)
    {   //se o no a ser deletado eh folha
        if((x->getAnt() == NULL) && (x->getProx() == NULL))
        {
            y = x->getPai();
            if(x ==(x->getPai()->getProx()))
                y->setProx(NULL);
            else
                y->setAnt(NULL);
            free(x);
        }
        //se o no a ser deletado tem apena filho a esquerda
        else if((x->getAnt() != NULL) && (x->getProx() == NULL))
        {
            if(x == (x->getPai()->getAnt()))
            {
                y = x->getPai();
                x->getAnt()->setPai(y);
                y->setAnt(x->getAnt());
                free(x);
            }
            else
            {
                y = x->getPai();
                x->getAnt()->setPai(y);
                y->setProx(x->getAnt());
                free(x);
            }
        }
        //se o no a ser deletado tem apena filho a direita
        else if((x->getAnt() == NULL) && (x->getProx() != NULL))
        {
            if(x == (x->getPai()->getAnt()))
            {
                y = x->getPai();
                x->getProx()->setPai(y);
                y->setAnt(x->getProx());
                free(x);
            }
            else
            {
                y = x->getPai();
                x->getProx()->setPai(y);
                y->setProx(x->getProx());
                free(x);
            }
        }
        //se o no a ser deletado tem dois filhos
        else if((x->getAnt() != NULL) && (x->getProx() != NULL))
        {
            if(x == (x->getPai()->getAnt()))
            {
                s = sucessor(x);
                if(s != x->getProx())
                {
                    y = s->getPai();
                    if(s->getProx() != NULL)
                    {
                        s->getProx()->setPai(y);
                        y->setAnt(s->getProx());
                    }
                    else y->setAnt(NULL);
                    s->setPai(x->getPai());
                    x->getProx()->setPai(s);
                    x->getAnt()->setPai(s);
                    s->setProx(x->getProx());
                    s->setAnt(x->getAnt());
                    x->getPai()->setAnt(s);
                }
                else
                {
                    y = s;
                    s->setPai(x->getPai());
                    x->getAnt()->setPai(s);
                    s->setAnt(x->getAnt());
                    x->getPai()->setAnt(s);
                }
                free(x);
            }
            else if(x == (x->getPai()->getProx()))
            {
                s = sucessor(x);
                if(s != x->getProx())
                {
                    y = s->getPai();
                    if(s->getProx() != NULL)
                    {
                        s->getProx()->setPai(y);
                        y->setAnt(s->getProx());
                    }
                    else y->setAnt(NULL);
                    s->setPai(x->getPai());
                    x->getProx()->setPai(s);
                    x->getAnt()->setPai(s);
                    s->setProx(x->getProx());
                    s->setAnt(x->getAnt());
                    x->getPai()->setProx(s);
                }
                else
                {
                    y = s;
                    s->setPai(x->getPai());
                    x->getAnt()->setPai(s);
                    s->setAnt(x->getAnt());
                    x->getPai()->setProx(s);
                }
                free(x);
            }

        }
        splay(y,r);
    }
    else
    {
        splay(x,r);
    }
}

void ArvoreSPLAY::remover(int valor){
    raiz = removerH(raiz, valor);
}

//p is a root element of the tree
No* ArvoreSPLAY::buscarH(No *p, int valor)
{
    No *temp1,*temp2;
    if(p != NULL)
    {
        temp1 = p;
        while(temp1 != NULL)
        {
            temp2 = temp1;
            if(temp1->getValor() > valor)
                temp1 = temp1->getAnt();
            else if(temp1->getValor() < valor)
                temp1 = temp1->getProx();
            else
                return temp1;
        }
        return temp2;
    }
    else
    {
        std::cout << "A arvore esta vazia!\n";
        exit(0);
    }
}

No* ArvoreSPLAY::buscar(int valor)
{
    No *x,*r;
    r = raiz;
    x = buscarH(r,valor);
    if(x->getValor() == valor)
    {
        std::cout << "O valor " << valor << " foi encontrado!";
        splay(x,r);
        return x;
    }
    else
    {
        std::cout << "O valor " << valor << " NAO foi encontrado.";
        splay(x,r);
        return NULL;
    }
}

//Função de Rotação para a Direita
No* ArvoreSPLAY::rightRotation(No *p, No* r)
{
    No *x;
    x = p->getAnt();
    p->setAnt(x->getProx());
    if (x->getProx() != NULL){
        x->getProx()->setPai(p);
    }
    x->setProx(p);
    if (p->getPai() != NULL){
        if(p == p->getPai()->getProx()) {
            p->getPai()->setProx(x);
        }
        else{
            p->getPai()->setAnt(x);
        }
    }
    x->setPai(p->getPai());
    p->setPai(x);
    if (p == r)
        return x;
    else
        return r;
}

//Função de Rotação para a Esquerda
No* ArvoreSPLAY::leftRotation(No *p, No* r)
{
    No *x;
    x = p->getProx();
    p->setProx(x->getAnt());
    if (x->getAnt() != NULL) {
        x->getAnt()->setPai(p);
    }
    x->setAnt(p);
    if (p->getPai() != NULL){
        if (p == p->getPai()->getAnt()){
            p->getPai()->setAnt(x);
        }
        else{
            p->getPai()->setProx(x);
        }
    }
    x->setPai(p->getPai());
    p->setPai(x);
    if(p == r)
        return x;
    else
        return r;
}



void ArvoreSPLAY::splay (No *x, No *raiz)
{
        No *p,*g;

        /* Verifica se o nó 'x' é o nó 'raiz' */
        if(x==raiz)
            return;

        /* Faz o Passo 'ZIG' */
        else if(x->getPai()==raiz)
        {

            if(x==x->getPai()->getAnt())
                raiz=rightRotation(raiz,raiz);
            else
                raiz=leftRotation(raiz,raiz);
        }
        else
        {
            p = x->getPai(); /*now points to parent of x*/
            g = p->getPai(); /*now points to parent of x's parent*/

            /* Faz o Passo 'ZIG-ZIG' -> when x is left and x's parent is left */
            if(x == p->getAnt() && p == g->getAnt())
            {
                raiz = rightRotation(g,raiz);
                raiz = rightRotation(p,raiz);
            }
            /* Faz o Passo 'ZIG-ZIG' -> when x is right and x's parent is right */
            else if(x == p->getProx() && p == g->getProx())
            {
                raiz = leftRotation(g,raiz);
                raiz = leftRotation(p,raiz);
            }
            /* Faz o Passo 'ZIG-ZAG' -> when x's is right and x's parent is left*/
            else if(x == p->getProx() && p == g->getAnt())
            {
                raiz = leftRotation(p,raiz);
                raiz = rightRotation(g,raiz);
            }
            /* Faz o Passo 'ZIG-ZAG' -> when x's is left and x's parent is right*/
            else if(x == p->getAnt() && p == g->getProx())
            {
                raiz = rightRotation(p,raiz);
                raiz = leftRotation(g,raiz);
            }
            splay(x, raiz);
        }
}



No** ArvoreSPLAY::getRaiz(){

    return &raiz;

}
ArvoreSPLAY::~ArvoreSPLAY()
{
    deletaH(raiz);
}
