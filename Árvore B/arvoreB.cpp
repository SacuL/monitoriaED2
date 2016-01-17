#include <iostream>
#include <stdlib.h>
#include "arvoreB.h"

using namespace std;

ArvoreB :: ArvoreB( )
{
    raiz = NULL ;
}
void ArvoreB :: inserir ( int val )
{
    int i ;
    No_B *c, *n ;
    int flag ;
    flag = setval ( val, raiz, &i, &c ) ;
    if ( flag )
    {
        n = new No_B ;
        n -> tamanho = 1 ;
        n -> chave[1] = i ;
        n -> filho[0] = raiz ;
        n -> filho[1] = c ;
        raiz = n ;
    }
}
int ArvoreB :: setval ( int val, No_B *n, int *p, No_B **c )
{
    int k ;
    if ( n == NULL )
    {
        *p = val ;
        *c = NULL ;
        return 1 ;
    }
    else
    {
        if ( buscarNo ( val, n, &k ) )
        {
            cout << endl << "Valor ja existe!" << endl ;

        }
        int retorno = setval ( val, n -> filho[k], p, c );

        if ( retorno )
        {
            if ( n -> tamanho < MAX )
            {
                fillnode ( *p, *c, n, k ) ;
                return 0 ;
            }
            else
            {
                split ( *p, *c, n, k, p, c ) ;
                return 1 ;
            }
        }
        return 0 ;
    }
}
No_B * ArvoreB :: buscar ( int val, No_B *raiz, int *pos )
{
    if ( raiz == NULL )
        return NULL ;
    else
    {
        if ( buscarNo ( val, raiz, pos ) )
            return raiz ;
        else
            return buscar ( val, raiz -> filho[*pos], pos ) ;
    }
}
int ArvoreB :: buscarNo ( int val, No_B *n, int *pos )
{
    if ( val < n -> chave[1] )
    {
        *pos = 0 ;
        return 0 ;
    }
    else
    {
        *pos = n -> tamanho ;
        while ( ( val < n -> chave[*pos] ) && *pos > 1 )
            ( *pos )-- ;
        if ( val == n -> chave[*pos] )
            return 1 ;
        else
            return 0 ;
    }
}
void ArvoreB :: fillnode ( int val, No_B *c, No_B *n, int k )
{
    int i ;
    for ( i = n -> tamanho ; i > k ; i-- )
    {
        n -> chave[i + 1] = n -> chave[i] ;
        n -> filho[i + 1] = n -> filho[i] ;
    }
    n -> chave[k + 1] = val ;
    n -> filho[k + 1] = c ;
    n -> tamanho++ ;
}
void ArvoreB :: split ( int val, No_B *c, No_B *n,
                        int k, int *y, No_B **newnode )
{
    int i, mid ;

    if ( k <= MIN )
        mid = MIN ;
    else
        mid = MIN + 1 ;

    *newnode = new No_B ;

    for ( i = mid + 1 ; i <= MAX ; i++ )
    {
        ( *newnode ) -> chave[i - mid] = n -> chave[i] ;
        ( *newnode ) -> filho[i - mid] = n -> filho[i] ;
    }

    ( *newnode ) -> tamanho = MAX - mid ;
    n -> tamanho = mid ;

    if ( k <= MIN )
        fillnode ( val, c, n, k ) ;
    else
        fillnode ( val, c, *newnode, k - mid ) ;

    *y = n -> chave[n -> tamanho] ;
    ( *newnode ) -> filho[0] = n -> filho[n -> tamanho] ;
    n -> tamanho-- ;
}

// Deleta o valor 'val'
void ArvoreB :: del ( int val )
{
    No_B * temp ;

    if ( ! delhelp ( val, raiz ) )
    {
        cout << endl << "Valor " << val << " nao foi encontrado!" ;
    }
    else
    {
        if ( raiz -> tamanho == 0 )
        {
            temp = raiz ;
            raiz = raiz -> filho[0] ;
            delete temp ;
        }
    }
}

// Auxiliar para deleção
int ArvoreB :: delhelp ( int val, No_B *no )
{
    int i ;
    int flag ;

    if ( no == NULL )
        return 0 ;
    else
    {
        flag = buscarNo ( val, no, &i ) ;
        if ( flag )
        {
            if ( no -> filho[i - 1] )
            {
                copysucc ( no, i ) ;
                flag = delhelp ( no -> chave[i], no -> filho[i] ) ;
                if ( !flag )
                {
                    cout << endl << "Valor " << val << " nao foi encontrado!" ;
                }
            }
            else
                clear ( no, i ) ;
        }
        else
            flag = delhelp ( val, no -> filho[i] ) ;
        if ( no -> filho[i] != NULL )
        {
            if ( no -> filho[i] -> tamanho < MIN )
                restore ( no, i ) ;
        }
        return flag ;
    }
}
// Remove a chave da posição k do nó e anda com as outras chaves
void ArvoreB :: clear ( No_B *no, int k )
{
    int i ;
    for ( i = k + 1 ; i <= no -> tamanho ; i++ )
    {
        no -> chave[i - 1] = no -> chave[i] ;
        no -> filho[i - 1] = no -> filho[i] ;
    }
    no -> tamanho-- ;
}

// Substitui o valor na posicao i pelo seu sucessor
void ArvoreB :: copysucc ( No_B *no, int i )
{
    No_B *temp = no -> filho[i] ;

    while ( temp -> filho[0] )
        temp = temp -> filho[0] ;

    no -> chave[i] = temp -> chave[1] ;
}

// Arruma a árvore (deleção)
void ArvoreB :: restore ( No_B *raiz, int i )
{
    if ( i == 0 )
    {
        if ( raiz -> filho [1] -> tamanho > MIN )
            leftshift ( 1 , raiz ) ;
        else
            merge ( 1, raiz ) ;
    }
    else
    {
        if ( i == raiz -> tamanho )
        {
            if ( raiz -> filho[i - 1] -> tamanho > MIN )
                rightshift ( i, raiz ) ;
            else
                merge ( i, raiz ) ;
        }
        else
        {
            if ( raiz -> filho[i - 1] -> tamanho > MIN )
                rightshift ( i, raiz ) ;
            else
            {
                if ( raiz -> filho[i + 1] -> tamanho > MIN )
                    leftshift ( i + 1 ,raiz) ;
                else
                    merge ( i, raiz ) ;
            }
        }
    }
}
void ArvoreB :: rightshift ( int k , No_B *no)
{
    int i ;
    No_B *temp, *temp2 ;

    temp = no -> filho[k] ;
    temp2 = no -> filho[k-1] ;

    for ( i = temp -> tamanho ; i > 0 ; i-- )
    {
        temp -> chave[i + 1] = temp -> chave[i] ;
        temp -> filho[i + 1] = temp -> filho[i] ;
    }

    temp -> filho[1] = temp -> filho[0] ;
    temp -> tamanho++ ;
    temp -> chave[1] = no -> chave[k] ;
//    temp = raiz -> filho[k - 1] ;
    no -> chave[k] = temp2 -> chave[temp2 -> tamanho] ;
    no -> filho[k] -> filho [0] = temp2 -> filho[temp2 -> tamanho] ;
    temp2 -> tamanho-- ;
}
void ArvoreB :: leftshift ( int k , No_B *no)
{
    No_B *temp ;

    temp = no -> filho[k - 1] ;
    temp -> tamanho++ ;
    temp -> chave[temp -> tamanho] = no -> chave[k] ;
    temp -> filho[temp -> tamanho] = no -> filho[k] -> filho[0] ;
    temp = no -> filho[k] ;
    no -> chave[k] = temp -> chave[1] ;
    temp -> filho[0] = temp -> filho[1] ;
    temp -> tamanho-- ;
    for ( int i = 1 ; i <= temp -> tamanho ; i++ )
    {
        temp -> chave[i] = temp -> chave[i + 1] ;
        temp -> filho[i] = temp -> filho[i + 1] ;
    }
}
void ArvoreB :: merge ( int k , No_B *no)
{

    No_B *temp1, *temp2 ;
    temp1 = no -> filho[k] ;
    temp2 = no -> filho[k - 1] ;
    temp2 -> tamanho++ ;
    temp2 -> chave[temp2 -> tamanho] = no -> chave[k] ;
    temp2 -> filho[temp2 -> tamanho] = temp1 -> filho[0] ;
    int i;
    for ( i = 1 ; i <= temp1 -> tamanho ; i++ )
    {
        temp2 -> tamanho++ ;
        temp2 -> chave[temp2 -> tamanho] = temp1 -> chave[i] ;
        temp2 -> filho[temp2 -> tamanho] = temp1 -> filho[i] ;
    }
    for ( i = k ; i < no -> tamanho ; i++ )
    {
        no -> chave[i] = no -> chave[i + 1] ;
        no -> filho[i] = no -> filho[i + 1] ;
    }
    no -> tamanho-- ;
    delete temp1 ;
}

void ArvoreB :: show( )
{
    display ( raiz ) ;
}
void ArvoreB :: display ( No_B *raiz )
{
    if ( raiz != NULL )
    {
        int i;
        for ( i = 0 ; i < raiz -> tamanho ; i++ )
        {
            display ( raiz -> filho[i] ) ;
            cout << raiz -> chave[i + 1] << "\t" ;
        }
        display ( raiz -> filho[i] ) ;
    }
}
void ArvoreB :: deltree ( No_B *raiz )
{
    if ( raiz != NULL )
    {
        int i;
        for (  i = 0 ; i < raiz -> tamanho ; i++ )
        {
            deltree ( raiz -> filho[i] ) ;
            delete ( raiz -> filho[i] ) ;
        }
        deltree ( raiz -> filho[i] ) ;
        delete ( raiz -> filho[i] ) ;
    }
}

ArvoreB :: ~ArvoreB( )
{
    deltree ( raiz ) ;
}



void ArvoreB :: imprimeArvore()
{
    imprimeNo(raiz);
}


void ArvoreB :: imprimeNo(No_B *no)
{
    cout << endl << "\t===== Imprimindo no de tamanho " << no->tamanho << " =====" << endl << "posicao\t";
    int i;
    for (i = 0 ; i < MAX + 1 ; i++)
    {
        cout << "[" << i << "]\t";
    }
    cout << endl << "chave\t";
    for (i = 0 ; i < MAX + 1 ; i++)
    {
        if(i == 0 )
        {
            cout << "lixo\t";
        }
        else
        {
            cout << no->chave[i] << "\t";
        }
    }
    cout << endl << "filho\t";
    for (i = 0 ; i < MAX + 1 ; i++)
    {
        if(no->filho[i] == NULL)
        {
            cout << "NULL" << "\t";
        }
        else
        {
            cout << "S" << "\t";
        }
    }

    for (i = 0 ; i < no->tamanho + 1 ; i++)
    {
        if(no->filho[i] != NULL)
        {
            imprimeNo(no->filho[i]);
        }
    }
    cout << endl ;

//    cout << endl << "========== Fim da Impressao ==========" << endl << endl;
}
