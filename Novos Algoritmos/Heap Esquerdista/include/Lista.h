#ifndef LISTA_H
#define LISTA_H
#include "No_Lista.h"


class Lista
{
public:
    Lista();
    void push_back(int p);
    void push_front(int p);
    void erase(int p);
    No_Lista* search(int p);
    No_Lista* begin();
    void clear();
    int size();
    void print();
    ~Lista();
private:
    No_Lista* pri;
    No_Lista* ult;
    No_Lista* busca(int p);
    int tam;
};

#endif // LISTA_H
