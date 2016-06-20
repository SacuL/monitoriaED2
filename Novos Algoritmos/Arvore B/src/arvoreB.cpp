#include <iostream>
#include <stdlib.h>
#include "arvoreB.h"

using namespace std;

ArvoreB :: ArvoreB( )
{
    raiz = NULL ;
}
ArvoreB :: ~ArvoreB( )
{

    deletaArvore(raiz);

}
void ArvoreB::deletaArvore(No_B* n){

    if(n == NULL)return;
    for(int i = 0; i <= n->tamanho; i++){

        deletaArvore(n->filho[i]);
        delete n->filho[i];

    }

}
No_B** ArvoreB::getRaiz(){

    return &raiz;

}
void ArvoreB::inserir(int valor){

    if(raiz == NULL){///Verifica se a arvore esta vazia, se sim, apenas cria a raiz

        raiz = new No_B();
        insereNo(raiz, valor);

    }else{///Caso contrario, chama a insercao

        insereRecursivo(raiz,valor);
        if(raiz->chave[MAX] != 0){///Verifica se a raiz esta em overflow, se estiver faz o split

            No_B* novoNo;
            No_B* auxRaiz = new No_B();
            int s = split(raiz, &novoNo);
            auxRaiz->filho[0] = raiz;
            auxRaiz->filho[1] = novoNo;
            auxRaiz->chave[0] = s;
            auxRaiz->tamanho++;
            raiz = auxRaiz;

        }

    }

}
void ArvoreB::insereNo(No_B* no, int valor){///Insere no 'no' o valor da variavel 'valor'

    int k = 0;
    while(k < no->tamanho && no->chave[k] < valor){///Encontra a posicao do vetor de chaves que 'valor' sera inserido

        k++;

    }
    for(int i = no->tamanho-1; i >= k; i--){///Desloca todos os valores a direita de k uma posicao, incluindo k, liberando espaco para valor ser inserido em k

        no->chave[i+1] = no->chave[i];

    }
    for(int i = no->tamanho; i >= k; i--){///Desloca todos os filhos a direita de k uma posicao, incluindo k, liberando espaco para outro filho ser inserido em k

        no->filho[i+1] = no->filho[i];

    }
    no->chave[k] = valor;
    no->tamanho++;
}
void ArvoreB::insereRecursivo(No_B* no, int valor){

    int k = 0;
    while(k < no->tamanho){///Encontra a posicao do vetor de chaves que 'valor' sera inserido

            if(no->chave[k] < valor)k++;
            else break;

    }
    if(no->filho[k]== NULL){///Verifica se o no eh folha, se for, insere, caso contrario continua descendo na arvore

        insereNo(no,valor);

    }else{

        insereRecursivo(no->filho[k], valor);
        if(no->filho[k]->chave[MAX] != 0){///Verifica se houve overflow na insersao

            No_B* novoNo;///No que sera criado no split
            int s = split(no->filho[k],&novoNo);///Valor de retorno do split, ou seja, o valor que será adicionado no 'no'
            insereNo(no,s);
            no->filho[no->getPos(s)] = no->filho[no->getPos(s)+1];///Coloco o ponteiro para o filho 'n' usado no split na posicao correta
            no->filho[no->getPos(s)+1] = novoNo;///Adiciona o 'novoNo' criado como filho maior de 's'

        }

    }

}
int ArvoreB::split(No_B* n, No_B** novoNo){///Reparte os valores de 'n' para o 'novoNo' e retorna o valor mediano;


    *novoNo = new No_B();

    int MID = MIN;///Encontro o valor mediano no No 'n'
    int k = 0;
    int sobressalente;

    for(int i = MID+1; i <= MAX; i++){///Transfiro os valores a direita de MID para o novo No.

        (*novoNo)->chave[k] = n->chave[i];
        n->chave[i] = 0;
        (*novoNo)->filho[k] = n->filho[i];
        n->filho[i] = NULL;
        (*novoNo)->tamanho++;
        n->tamanho--;
        k++;

    }

    (*novoNo)->filho[k] = n->filho[MAX+1];
    n->filho[MAX+1] = NULL;
    sobressalente = n->chave[MID];///Guardo o No que ira subir para o pai
    n->chave[MID] = 0;
    n->tamanho--;

    return sobressalente;///Retorno o No sobressalente da funcao split

}
No_B* ArvoreB::buscar(int valor, No_B* n){

    No_B* aux;
    if(n == NULL){

        return NULL;

    }else{///Verifica se o valor esta no No 'n', se estiver, retona a posicao de memoria de 'n', caso nao esteja, verifica nos seus filhos

        if(n->getPos(valor) != -1){

            return n;

        }

    }
    for(int i = 0; i <= n->tamanho; i++){///Verifica se encontra o valor nos filhos de 'n'

        aux = buscar(valor,n->filho[i]);
        if(aux != NULL){

            return aux;

        }

    }
    return NULL;

}
bool ArvoreB::buscar(int valor){

    if(buscar(valor,raiz) != NULL){

        return true;

    }
    return false;
}
