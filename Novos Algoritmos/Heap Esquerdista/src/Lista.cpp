#include "Lista.h"
#include <stdlib.h>
#include <cstring>
#include <iostream>



Lista::Lista()
{
    pri = NULL;
    ult = NULL;
    tam = 0;
}
void Lista::push_back(int p)
{

    No_Lista* aux = new No_Lista();
    aux->info = p;

    if(pri == NULL)
    {

        pri = aux;
        ult = pri;

    }
    else
    {

        ult->prox = aux;
        ult = ult->prox;

    }
    tam++;

}
void Lista::erase(int p)
{

    No_Lista* it = busca(p);
    No_Lista* aux;
    if(pri != NULL)
    {

        if(pri->info == p)
        {

            it = pri->prox;
            delete pri;
            pri = it;
            tam--;

        }
        return;

    }
    else
    {

        return;

    }
    if(it->prox != NULL)
    {

        if(it->prox->prox == NULL)
        {

            ult = it;

        }
        aux = it->prox->prox;
        delete it->prox;
        it->prox = aux;
        tam--;

    }


}
No_Lista* Lista::busca(int p)
{

    No_Lista* it = begin();
    while(it->prox != NULL)
    {

        if(it->prox->info == p)
        {

            return it;

        }
        it = it->prox;

    }
    return it;
}
No_Lista* Lista::search(int p)
{

    if(pri == NULL)return NULL;
    else if(pri->info == p) return pri;
    No_Lista *aux = busca(p);
    if(aux->prox != NULL)
    {

        return aux->prox;

    }
    return NULL;

}
No_Lista* Lista::begin()
{

    return pri;

}
void Lista::clear()
{

    No_Lista* aux;
    No_Lista* it = begin();

    while(it != NULL)
    {

        aux = it->prox;
        delete it;
        it = aux;
        tam--;

    }

}
int Lista::size()
{

    return tam;

}
void Lista::push_front(int p)
{

    No_Lista *aux = new No_Lista();
    aux->info = p;
    aux->prox = pri;
    pri = aux;
    tam++;

}
void Lista::print()
{

    No_Lista* it = begin();
    if(pri != NULL)
    {

        while(it->prox != NULL)
        {

            cout << it->info << "-";
            it = it->prox;

        }
        cout << it->info;

    }
}
Lista::~Lista()
{
    clear();
}
