#include <stdio.h>
#include <stdlib.h>
#include <DSGraph.h>

typedef struct NODE_STRUCTURE NO;

//Criação do tipo 'boolean' em C
enum boolean {
    true = 1, false = 0
};
// Permitindo a sua declaração como um tipo qualquer:
typedef  enum boolean  bool;


//Declarações Globais

NO *raiz = NULL;

void criarArvore(NO *pRaiz){
    pRaiz = NULL;
}

int Altura (NO* pNodo)
{
	int Alt_Esq, Alt_Dir;
	if (pNodo == NULL) return 0;
	else
	{
		Alt_Esq = Altura (pNodo->prior);
		Alt_Dir = Altura (pNodo->next);
		if (Alt_Esq > Alt_Dir)
		{
			return (1 + Alt_Esq);
		}
		else
		{
			return (1 + Alt_Dir);
		}
	}
}

int Calcula_FB(NO* pNodo)
{
    if(pNodo == NULL)return 0;
    return (Altura(pNodo->prior)- Altura(pNodo->next));
}

void Seta_FB(NO* pNodo)
{
     if (pNodo!= NULL)
     {
         pNodo->mark=(Altura(pNodo->prior)- Altura(pNodo->next));
		 Seta_FB(pNodo->prior);
		 Seta_FB(pNodo->next);
     }
}


NO* rotacao_direita(NO* N3)
{
    showComment("Arvore AVL: Rotacao a direita no NO %d", N3->value);
    setSleepTime(2);
    show(raiz, 0);

       NO* N2= N3->prior;
       if(N2->next) N3->prior = N2->next;
       else N3->prior=NULL;
       N2->next=N3;
       return N2;
}

NO* rotacao_esquerda(NO* N1)
{
    showComment("Arvore AVL: Rotacao a esquerda no NO %d", N1->value);
    setSleepTime(2);
    show(raiz, 0);

       NO* N2= N1->next;
       if(N2->prior) N1->next= N2->prior;
       else N1->next=NULL;
       N2->prior=N1;
       return N2;
}

NO* rotacao_dupla_direita (NO* N3)
{
    showComment("Arvore AVL: Rotacao dupla a direita no NO %d", N3->value);
    setSleepTime(2);
    show(raiz, 0);

       NO* N1= N3->prior;
       NO* N2= N1->next;

       if(N2->prior) N1->next= N2->prior;
       else N1->next=NULL;

       if(N2->next) N3->prior = N2->next;
       else N3->prior=NULL;

       N2->prior=N1;
       N2->next=N3;

       return N2;
}

NO* rotacao_dupla_esquerda (NO* N1)
{
    showComment("Arvore AVL: Rotacao dupla a esquerda no NO %d", N1->value);
    setSleepTime(2);
    show(raiz, 0);

       NO* N3= N1->next;
       NO* N2= N3->prior;

       if(N2->prior) N1->next= N2->prior;
       else N1->next=NULL;

       if(N2->next) N3->prior = N2->next;
       else N3->prior=NULL;

       N2->prior=N1;
       N2->next=N3;

       return N2;
}

NO* CorrigeAVL(NO* pNodo)
{
	if(pNodo != NULL)
	{
		pNodo->mark=Calcula_FB(pNodo);
		if(pNodo->mark == 2)
		{
			pNodo->prior->mark=Calcula_FB(pNodo->prior);
			if(pNodo->prior->mark > 0)
			{
				pNodo = rotacao_direita(pNodo);
			}
			else
			{
				pNodo =  rotacao_dupla_direita(pNodo);
			}
		}
		else if(pNodo->mark == -2)
		{
			pNodo->next->mark=Calcula_FB(pNodo->next);
			if(pNodo->next->mark < 0)
			{
				pNodo = rotacao_esquerda(pNodo);
			}
			else
			{
				pNodo =  rotacao_dupla_esquerda(pNodo);
			}
		}
		pNodo->prior = CorrigeAVL(pNodo->prior);
		pNodo->next = CorrigeAVL(pNodo->next);
    }
    return pNodo;
}


NO* InsereAVL(NO* pNodo, int ch)
{
	if (pNodo == NULL)
	{
		pNodo =(NO*)malloc(sizeof(NO));
		pNodo->value= ch;
		pNodo->mark= 0;
		pNodo->prior= NULL;
		pNodo->next= NULL;
		return pNodo;
	}
	else
	{
		if(ch < pNodo->value)
		{
			pNodo->prior = InsereAVL(pNodo->prior,ch);
		}
		else
		{
			pNodo->next = InsereAVL(pNodo->next,ch);
		}
	}
	return pNodo;
}


NO* Consulta(NO* pNodo, char ch)
{
    while (pNodo != NULL)
    {
		if(ch == pNodo->value)
		{
			return pNodo;
		}
		else
		{
			if(ch < pNodo->value)
			{
				pNodo=pNodo->prior;
			}
			else
			{
				pNodo=pNodo->next;
			}
		}
	}
	return NULL;
}

NO* RemoveAVL(NO* pNodo)
{
	NO* pNodoAux;
	NO* pNodoAuxPai;

	if((pNodo->prior == NULL) && (pNodo->next == NULL))
	{
        free(pNodo);
    	return NULL;
	}
	else if((pNodo->prior == NULL) && (pNodo->next != NULL))
	{
		pNodoAux=pNodo->next;
        free(pNodo);
    	return pNodoAux;
	}
	else if((pNodo->prior != NULL) && (pNodo->next == NULL))
	{
		pNodoAux=pNodo->prior;
		free(pNodo);
		return pNodoAux;
	}
	else
	{
		if(pNodo->prior->next == NULL)
        {
			pNodoAux=pNodo->prior;
    	    pNodo->prior->next=pNodo->next;
            free(pNodo);
    		return pNodoAux;
        }
        else
        {
    		pNodoAux=pNodo->prior;

    		while (pNodoAux->next != NULL)
    		{
    			pNodoAuxPai=pNodoAux;
                pNodoAux=pNodoAux->next;
    		}

    		if(pNodoAux->prior!=NULL) pNodoAuxPai->next=pNodoAux->prior;
    		else pNodoAuxPai->next=NULL;

            pNodoAux->next=pNodo->next;
    	    pNodoAux->prior=pNodo->prior;

    		free(pNodo);
    		return pNodoAux;
        }
	}

	return NULL;
}

NO* Remove(NO* pNodo, char ch)
{
	NO* pNodoAux=pNodo;
	NO* pNodoPai;
	bool bdir=false;

	if(ch == pNodo->value) return RemoveAVL(pNodoAux);

    while (pNodoAux != NULL)
    {
		if(ch == pNodoAux->value)
		{
			if(bdir) pNodoPai->next= RemoveAVL(pNodoAux);
			else pNodoPai->prior= RemoveAVL(pNodoAux);
			return pNodo;
		}
		else
		{
			if(ch < pNodoAux->value)
			{
				bdir=false;
				pNodoPai=pNodoAux;
				pNodoAux=pNodoAux->prior;
			}
			else
			{
				bdir=true;
				pNodoPai=pNodoAux;
				pNodoAux=pNodoAux->next;
			}
		}
	}
	return pNodo;
}

int main()
{
    init($BINARY_TREE);

    criarArvore(raiz);

    setViewAddress(0);

// ###########################################################################
//
// ÁRVORE AVL - Inserção de Valores
//
// ###########################################################################


    //Insere o Valor 4
    raiz=  InsereAVL(raiz, 4);
    showComment("Arvore AVL: Insere o valor 4.");
    setSleepTime(2);
    show(raiz,0);

    raiz = CorrigeAVL(raiz);
    showComment("Arvore AVL: Arvore Corrigida.");
    setSleepTime(2);
    show(raiz,0);

    Seta_FB(raiz);

    //Insere o Valor 1
    raiz=  InsereAVL(raiz, 1);
    showComment("Arvore AVL: Insere o valor 1.");
    setSleepTime(2);
    show(raiz,0);

    raiz = CorrigeAVL(raiz);
    showComment("Arvore AVL: Arvore Corrigida.");
    setSleepTime(2);
    show(raiz,0);

    Seta_FB(raiz);

    //Insere o Valor 3
    raiz=  InsereAVL(raiz, 3);
    showComment("Arvore AVL: Insere o valor 3.");
    setSleepTime(2);
    show(raiz,0);

    raiz = CorrigeAVL(raiz);
    showComment("Arvore AVL: Arvore Corrigida.");
    setSleepTime(2);
    show(raiz,0);

    Seta_FB(raiz);

    //Insere o Valor 2
    raiz=  InsereAVL(raiz, 2);
    showComment("Arvore AVL: Insere o valor 2.");
    setSleepTime(2);
    show(raiz,0);

    raiz = CorrigeAVL(raiz);
    showComment("Arvore AVL: Arvore Corrigida.");
    setSleepTime(2);
    show(raiz,0);

    Seta_FB(raiz);

    //Insere o Valor 10
    raiz=  InsereAVL(raiz, 10);
    showComment("Arvore AVL: Insere o valor 10.");
    setSleepTime(2);
    show(raiz,0);

    raiz = CorrigeAVL(raiz);
    showComment("Arvore AVL: Arvore Corrigida.");
    setSleepTime(2);
    show(raiz,0);

    Seta_FB(raiz);


    //Insere o Valor 11
    raiz=  InsereAVL(raiz, 11);
    showComment("Arvore AVL: Insere o valor 11.");
    setSleepTime(2);
    show(raiz,0);

    raiz = CorrigeAVL(raiz);
    showComment("Arvore AVL: Arvore Corrigida.");
    setSleepTime(2);
    show(raiz,0);

    Seta_FB(raiz);

    //Insere o Valor 12
    raiz=  InsereAVL(raiz, 12);
    showComment("Arvore AVL: Insere o valor 12.");
    setSleepTime(2);
    show(raiz,0);

    raiz = CorrigeAVL(raiz);
    showComment("Arvore AVL: Arvore Corrigida.");
    setSleepTime(2);
    show(raiz,0);

    Seta_FB(raiz);

// ###########################################################################
//
// ÁRVORE AVL - Remoção de Valores
//
// ###########################################################################

    //Remove o Valor 10
    raiz=  Remove(raiz, 10);
    showComment("Arvore AVL: Remove o valor 10.");
    setSleepTime(2);
    show(raiz,0);

    raiz = CorrigeAVL(raiz);
    showComment("Arvore AVL: Arvore Corrigida.");
    setSleepTime(2);
    show(raiz,0);

    Seta_FB(raiz);

    //Remove o Valor 4
    raiz=  Remove(raiz, 4);
    showComment("Arvore AVL: Remove o valor 4.");
    setSleepTime(2);
    show(raiz,0);

    raiz = CorrigeAVL(raiz);
    showComment("Arvore AVL: Arvore Corrigida.");
    setSleepTime(2);
    show(raiz,0);

    Seta_FB(raiz);

    //Remove o Valor 3
    raiz=  Remove(raiz, 3);
    showComment("Arvore AVL: Remove o valor 3.");
    setSleepTime(2);
    show(raiz,0);

    raiz = CorrigeAVL(raiz);
    showComment("Arvore AVL: Arvore Corrigida.");
    setSleepTime(2);
    show(raiz,0);

    Seta_FB(raiz);


    return 0;
}
