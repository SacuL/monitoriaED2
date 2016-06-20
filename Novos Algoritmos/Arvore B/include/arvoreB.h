#ifndef ARVOREB_H_INCLUDED
#define ARVOREB_H_INCLUDED
#include <No_B.h>


class ArvoreB
{
private :
    No_B *raiz ;
    void insereNo(No_B* no, int valor);
    void insereRecursivo(No_B* no, int valor);
    int split(No_B* n, No_B** novoNo);
    void deletaArvore(No_B* n);
    No_B* buscar(int valor, No_B* n);


public :

    void inserir(int valor);
    void remover(int valor);
    bool buscar(int valor);
    ArvoreB();
    No_B** getRaiz();
    ~ArvoreB() ;
} ;




#endif // ARVOREB_H_INCLUDED
