#ifndef ARVOREB_H_INCLUDED
#define ARVOREB_H_INCLUDED
#include <No_B.h>

/*
Árvore B
Adaptado de: http://electrofriends.com/source-codes/software-programs/cpp-programs/cpp-data-structure/c-program-to-implement-b-trees/
*/

class ArvoreB
{
private :
    No_B *raiz ;
    void zeraNo(No_B* b);
public :
    ArvoreB( ) ;
    void inserir ( int val ) ;
    int setval ( int val, No_B *n, int *p, No_B **c ) ;
    static No_B * buscar ( int val, No_B *raiz, int *pos ) ;
    static int buscarNo ( int val, No_B *n, int *pos ) ;
    void fillnode ( int val, No_B *c, No_B *n, int k ) ;
    void split ( int val, No_B *c, No_B *n,
                 int k, int *y, No_B **newnode ) ;
    void del ( int val ) ;
    int delhelp ( int val, No_B *raiz ) ;
    void clear ( No_B *raiz, int k ) ;
    void copysucc ( No_B *raiz, int i ) ;
    void restore ( No_B *raiz, int i ) ;
    void rightshift ( int k ,No_B *no) ;
    void leftshift ( int k ,No_B *no) ;
    void merge ( int k ,No_B *no) ;
    void show( ) ;
    static void display ( No_B *raiz ) ;
    static void deltree ( No_B *raiz ) ;
    static void imprimeNo ( No_B *raiz );
    void imprimeArvore();
    No_B** getRaiz();

    ~ArvoreB( ) ;
} ;




#endif // ARVOREB_H_INCLUDED
