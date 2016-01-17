#ifndef NO_LISTA_H
#define NO_LISTA_H
#include <stdlib.h>
#include <string>

using namespace std;

class No_Lista
{
public:
    No_Lista()
    {
        prox = NULL;
    };
    int info;
    No_Lista* prox;
    ~No_Lista() {};

};

#endif // NO_LISTA_H
