#include "heapCont.h"
#include <iostream>

using namespace std;

heapCont::heapCont(const int TIPO)
{
    tamVet = 10;
    heap = new int[tamVet];
    tipo = TIPO;
    ultIndice = -1;
}
int heapCont::busca(int p)
{

    for(int i = 0; i <= ultIndice; i++)
    {

        if(heap[i] == p) return i;

    }
    return -1;

}
void heapCont::insere(int p)
{

    if(ultIndice == -1)
    {

        heap[0] = p;
        ultIndice = 0;

    }
    else
    {

        if(ultIndice + 1 >= tamVet)
        {

            realocaHeap();

        }
        heap[ultIndice + 1] = p;
        ultIndice++;

    }
    constroiHeap(0,ultIndice);


}
void heapCont::constroiHeap(int Iinicio, int Ifinal)
{

    int No = (Ifinal-Iinicio)/2;
    int auxIndice = -1, aux;
    while(No >= 0)
    {

        if(2*No+2 <= Ifinal)
        {

            auxIndice = compara(No,compara(2*No+2,2*No+1));

        }
        else if(2*No+1 <= Ifinal)
        {

            auxIndice = compara(No,2*No+1);

        }
        if((auxIndice != No) && (auxIndice >= 0))
        {

            aux = heap[auxIndice];
            heap[auxIndice] = heap[No];
            heap[No] = aux;
            constroiHeap(No,Ifinal);

        }
        No--;
    }

}
int heapCont::compara(int p, int n)
{

    if(tipo == -1)
    {

        if(heap[p] <= heap[n])
        {

            return p;

        }
        else
        {

            return n;

        }

    }
    else
    {

        if(heap[p] >= heap[n])
        {

            return p;

        }
        else
        {

            return n;

        }

    }

}
void heapCont::realocaHeap(int numVezes)
{

    int* aux = new int[tamVet*numVezes];
    int i;
    for(i = 0; i < tamVet; i++)
    {

        aux[i] = heap[i];

    }
    tamVet = tamVet*numVezes;
    delete []heap;
    heap = aux;

}
void heapCont::removeNo(int p)
{

    int auxIndice = busca(p);

    for(int i = auxIndice; i < ultIndice; i++)
    {

        heap[i] = heap[i+1];

    }
    ultIndice--;
    constroiHeap(0,ultIndice);

}
void heapCont::imprimeHeap(const int tipoImpressao)
{

    cout<<endl<<endl;
    if(tipoImpressao == TREE)
    {

        int No = ultIndice/2;
        if(2*No+1 == ultIndice)
        {

            cout<<"O no "<<heap[No]<<" tem o filho "<<heap[2*No+1]<<endl;
            No--;

        }
        else if(2*No == ultIndice)
        {

            No--;

        }
        while(No >= 0)
        {

            cout<<"O no "<<heap[No]<<" tem os filhos "<<heap[2*No+2]<<" e "<<heap[2*No+1]<<endl;
            No--;

        }

    }
    else if(tipoImpressao == VETOR)
    {

        for(int i = 0; i < ultIndice; i++)
        {

            cout<<heap[i]<<"-";

        }
        cout<<heap[ultIndice]<<endl;

    }
    else
    {

        cout<<"Estrutura nao suportada"<<endl;

    }

}
int* heapCont::getRaiz()
{

    return heap;

}
int heapCont::getUltIndice()
{

    return ultIndice;

}
void heapCont::uniao(int* H, int uInd)
{

    int  j = ultIndice + 1;
    if(ultIndice + uInd >= tamVet)
    {

        realocaHeap(((ultIndice + uInd)/tamVet)+1);

    }
    ultIndice++;
    for(int i = 0; i <=uInd; i++, j++)
    {

        heap[j] = H[i];

    }
    ultIndice = j - 1;
    constroiHeap(0, ultIndice);

}
heapCont::~heapCont()
{
    delete []heap;
}
