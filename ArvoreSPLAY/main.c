#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <DSGraph.h>

typedef struct NODE_STRUCTURE NO;

//Função que retorna o NÓ sucessor
NO *sucessor(NO *x)
{
        NO *temp,*temp2;
        temp=temp2=x->next;
        while(temp != NULL)
        {
                temp2 = temp;
                temp = temp->prior;
        }
        return temp2;
}

//p is a root element of the tree
NO *lookup(NO *p,int value)
{
        NO *temp1,*temp2;
        if(p != NULL)
        {
                temp1 = p;
                while(temp1 != NULL)
                {
                        temp2 = temp1;
                        if(temp1->value > value)
                                temp1 = temp1->prior;
                        else if(temp1->value < value)
                                temp1 = temp1->next;
                        else
                                        return temp1;
                }
                return temp2;
        }
        else
        {
                printf("NO element in the tree\n");
                exit(0);
        }
}


//Função de Rotação para a Direita
NO *rightrotation(NO *p, NO *raiz)
{
        NO *x;
        x = p->prior;
        p->prior = x->next;
        if (x->next!=NULL) x->next->father = p;
        x->next = p;
        if (p->father!=NULL)
                if(p==p->father->next) p->father->next=x;
                else
                         p->father->prior=x;
        x->father = p->father;
        p->father = x;
        if (p==raiz)
                return x;
        else
                return raiz;
}

//Função de Rotação para a Esquerda
NO *leftrotation(NO *p, NO *raiz)
{
        NO *x;
        x = p->next;
        p->next = x->prior;
        if (x->prior!=NULL) x->prior->father = p;
        x->prior = p;
        if (p->father!=NULL)
                if (p==p->father->prior) p->father->prior=x;
                else
                         p->father->next=x;
        x->father = p->father;
        p->father = x;
        if(p==raiz)
                return x;
        else
                return raiz;
}


//Procedimento SPLAY
void splay (NO *x, NO *raiz)
{
        NO *p,*g;

        /* Verifica se o nó 'x' é o nó 'raiz' */
        if(x==raiz)
                return;

        /* Faz o Passo 'ZIG' */
        else if(x->father==raiz)
        {

                if(x==x->father->prior)
                        raiz=rightrotation(raiz,raiz);
                else
                        raiz=leftrotation(raiz,raiz);
        }
        else
        {
                p=x->father; /*now points to parent of x*/
                g=p->father; /*now points to parent of x's parent*/

                /* Faz o Passo 'ZIG-ZIG' -> when x is left and x's parent is left */
                if(x==p->prior&&p==g->prior)
                {
                        raiz=rightrotation(g,raiz);
                        raiz=rightrotation(p,raiz);
                }
                /* Faz o Passo 'ZIG-ZIG' -> when x is right and x's parent is right */
                else if(x==p->next&&p==g->next)
                {
                        raiz=leftrotation(g,raiz);
                        raiz=leftrotation(p,raiz);
                }
                /* Faz o Passo 'ZIG-ZAG' -> when x's is right and x's parent is left*/
                else if(x==p->next&&p==g->prior)
                {
                        raiz=leftrotation(p,raiz);
                        raiz=rightrotation(g,raiz);
                }
                /* Faz o Passo 'ZIG-ZAG' -> when x's is left and x's parent is right*/
                else if(x==p->prior&&p==g->next)
                {
                        raiz=rightrotation(p,raiz);
                        raiz=leftrotation(g,raiz);
                }
                splay(x, raiz);
        }
}

//Função de inserção de valores na árvore SPLAY
NO *insert(NO *p,int value)
{
        NO *temp1,*temp2,*par,*x;
        if(p == NULL)
        {
                p=(NO*)malloc(sizeof(NO));
                if(p != NULL)
                {
                        p->value = value;
                        p->father = NULL;
                        p->prior = NULL;
                        p->next = NULL;
                }
                else
                {
                        printf("No memory is allocated\n");
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
                                if(temp2->value > value)
                                        temp2 = temp2->prior;
                                else if(temp2->value < value)
                                        temp2 = temp2->next;
                                else
                                        if(temp2->value == value)
                                                return temp2;
                        }
                        if(temp1->value > value)
                        {
                                par = temp1;//temp1 having the parent address,so that's it
                                temp1->prior = (NO *)malloc(sizeof(NO));
                                temp1= temp1->prior;
                                if(temp1 != NULL)
                                {
                                        temp1->value = value;
                                        temp1->father = par;//store the parent address.
                                        temp1->prior = NULL;
                                        temp1->next = NULL;
                                }
                                else
                                {
                                        printf("No memory is allocated\n");
                                        exit(0);
                                }
                        }
                        else
                        {
                                par = temp1;//temp1 having the parent node address.
                                temp1->next = (NO*)malloc(sizeof(NO));
                                temp1 = temp1->next;
                                if(temp1 != NULL)
                                {
                                        temp1->value = value;
                                        temp1->father = par;//store the parent address
                                        temp1->prior = NULL;
                                        temp1->next = NULL;
                                }
                                else
                                {
                                        printf("No memory is allocated\n");
                                        exit(0);
                                }
                        }
        }
        splay(temp1,p);//temp1 will be new root after splaying
        return (temp1);
}

NO *delete(NO *p,int value)
{
        NO *x,*y,*p1;
        NO *raiz;
        NO *s;
        raiz = p;
        x = lookup(p,value);
        if(x->value == value)
        {       //if the deleted element is leaf
                if((x->prior == NULL) && (x->next == NULL))
                {
                        y = x->father;
                        if(x ==(x->father->next))
                                y->next = NULL;
                        else
                                y->prior = NULL;
                        free(x);
                }
                //if deleted element having left child only
                else if((x->prior != NULL) &&(x->next == NULL))
                {
                        if(x == (x->father->prior))
                        {
                                y = x->father;
                                x->prior->father = y;
                                y->prior = x->prior;
                                free(x);
                        }
                        else
                        {
                                y = x->father;
                                x->prior->father = y;
                                y->next = x->prior;
                                free(x);
                        }
                }
                //if deleted element having right child only
                else if((x->prior == NULL) && (x->next != NULL))
                {
                        if(x == (x->father->prior))
                        {
                                y = x->father;
                                x->next->father = y;
                                y->prior = x->next;
                                free(x);
                        }
                        else
                        {
                                y = x->father;
                                x->next->father = y;
                                y->next = x->next;
                                free(x);
                        }
                }
                //if the deleted element having two children
                else if((x->prior != NULL) && (x->next != NULL))
                {
                        if(x == (x->father->prior))
                        {
                                s = sucessor(x);
                                if(s != x->next)
                                {
                                        y = s->father;
                                        if(s->next != NULL)
                                        {
                                                s->next->father = y;
                                                y->prior = s->next;
                                        }
                                        else y->prior = NULL;
                                        s->father = x->father;
                                        x->next->father = s;
                                        x->prior->father = s;
                                        s->next = x->next;
                                        s->prior = x->prior;
                                        x->father->prior = s;
                                }
                                else
                                {
                                        y = s;
                                        s->father = x->father;
                                        x->prior->father = s;
                                        s->prior = x->prior;
                                        x->father->prior = s;
                                }
                                free(x);
                        }
                        else if(x == (x->father->next))
                        {
                                s = sucessor(x);
                                if(s != x->next)
                                {
                                        y = s->father;
                                        if(s->next != NULL)
                                        {
                                                s->next->father = y;
                                                y->prior = s->next;
                                        }
                                        else y->prior = NULL;
                                        s->father = x->father;
                                        x->next->father = s;
                                        x->prior->father = s;
                                        s->next = x->next;
                                        s->prior = x->prior;
                                        x->father->next = s;
                                }
                                else
                                {
                                        y = s;
                                        s->father = x->father;
                                        x->prior->father = s;
                                        s->prior = x->prior;
                                        x->father->next = s;
                                }
                                free(x);
                        }

                }
                splay(y,raiz);
        }
        else
        {
                splay(x,raiz);
        }
}

NO *search(NO *p,int value)
{
        NO *x,*raiz;
        raiz = p;
        x = lookup(p,value);
        if(x->value == value)
        {
                printf("Inside search if\n");
                splay(x,raiz);
        }
        else
        {
                printf("Inside search else\n");
                splay(x,raiz);
        }
}


//Programa Principal

int main()
{

    init($BINARY_TREE);

    setViewAddress(0);

    NO *raiz = NULL; //The root element
    NO *x;//x is which element will come to root.

//    ********************************************************************************************
//    Inserção de elementos na Árvore SPLAY
//    ********************************************************************************************

    // Insere o 1º elemento - 1
    x = insert(raiz,1);
    raiz = x;
    showComment("Arvore SPLAY: Insere o valor 1.");
    setSleepTime(2);
    show(raiz,0);

    // Insere o 2º elemento - 15
    x = insert(raiz,15);
    raiz = x;
    showComment("Arvore SPLAY: Insere o valor 15.");
    setSleepTime(2);
    show(raiz,0);

    // Insere o 3º elemento - 30
    x = insert(raiz,30);
    raiz = x;
    showComment("Arvore SPLAY: Insere o valor 30.");
    setSleepTime(2);
    show(raiz,0);

    // Insere o 4º elemento - 25
    x = insert(raiz,25);
    raiz = x;
    showComment("Arvore SPLAY: Insere o valor 25.");
    setSleepTime(2);
    show(raiz,0);

    // Insere o 5º elemento - 13
    x = insert(raiz,13);
    raiz = x;
    showComment("Arvore SPLAY: Insere o valor 13.");
    setSleepTime(2);
    show(raiz,0);

    // Insere o 6º elemento - 50
    x = insert(raiz,50);
    raiz = x;
    showComment("Arvore SPLAY: Insere o valor 50.");
    setSleepTime(2);
    show(raiz,0);

    // Insere o 7º elemento - 17
    x = insert(raiz,17);
    raiz = x;
    showComment("Arvore SPLAY: Insere o valor 17.");
    setSleepTime(2);
    show(raiz,0);


//    ********************************************************************************************
//    Busca de elementos na Árvore SPLAY
//    ********************************************************************************************

    int chave;

    // Busca o valor - 15
    chave = 15;

    showComment("Arvore SPLAY: Buscando o valor %d.", chave);
    setSleepTime(2);
    show(raiz,0);

    x = lookup(raiz,chave);
    splay(x,raiz);
    raiz = x;

    showComment("Arvore SPLAY: Arvore apos a busca do valor %d.", chave);
    setSleepTime(2);
    show(raiz,0);

    // Busca o valor - 35 //Este valor nao existe na árvore. Colocará o valor mais próxima na raiz
    chave =35;

    showComment("Arvore SPLAY: Buscando o valor %d.", chave);
    setSleepTime(2);
    show(raiz,0);

    x = lookup(raiz,chave);
    splay(x,raiz);
    raiz = x;

    showComment("Arvore SPLAY: Arvore apos a busca do valor %d.", chave);
    setSleepTime(2);
    show(raiz,0);


//    ********************************************************************************************
//    Remoção de elementos na Árvore SPLAY
//    ********************************************************************************************

    // Removendo o valor - 15
    chave =15;

    showComment("Arvore SPLAY: Sera removido o valor %d.", chave);
    setSleepTime(2);
    show(raiz,0);

    raiz = delete(raiz,chave);

    showComment("Arvore SPLAY: Arvore apos a remocao do valor %d.", chave);
    setSleepTime(2);
    show(raiz,0);

    // Removendo o valor - 25
    chave =25;

    showComment("Arvore SPLAY: Sera removido o valor %d.", chave);
    setSleepTime(2);
    show(raiz,0);

    raiz = delete(raiz,chave);

    showComment("Arvore SPLAY: Arvore apos a remocao do valor %d.", chave);
    setSleepTime(2);
    show(raiz,0);

    // Removendo o valor - 13
    chave =13;

    showComment("Arvore SPLAY: Sera removido o valor %d.", chave);
    setSleepTime(2);
    show(raiz,0);

    raiz = delete(raiz,chave);

    showComment("Arvore SPLAY: Arvore apos a remocao do valor %d.", chave);
    setSleepTime(2);
    show(raiz,0);

    terminateDSGraph();

    return 0;
}
