#include <stdio.h>
#include <stdlib.h>
#include "DSGraph.h"

#define MAX 10
float vetor[MAX];

void insertionSort()
{
    int i, j, aux;

    for(i = 1; i < MAX; i++)
    {
        j = i;
        setSleepTime(2);
        showComment("InsertionSort: verifica se V[%d] < e V[%d]", j, j-1);
        show(&vetor,2,&vetor[j],&vetor[j - 1]);

        while(vetor[j] < vetor[j - 1])
        {
            aux = vetor[j];
            vetor[j] = vetor[j - 1];
            vetor[j - 1] = aux;

            showComment("InsertionSort: troca V[%d] com V[%d]", j, j-1);
            setSleepTime(2);
            show(&vetor,2,&vetor[j],&vetor[j - 1]);
            j--;

            if(j == 0)break;

            setSleepTime(2);
            showComment("InsertionSort: verifica se V[%d] < e V[%d]", j, j-1);
            show(&vetor,2,&vetor[j],&vetor[j - 1]);
        }
    }
}
int main()
{

    //Inicializa a biblioteca grafica com a estrutura a ser apresentada na tela
    init($ARRAY,MAX,1);

    int i = 0;

    setSleepTime(2);

    for(i = 0; i < MAX; i++)
    {
        vetor[i] = rand()%100;
    }

    showComment("InsertionSort: vetor inicial");
    setSleepTime(2);
    show(&vetor,0);

    setSleepTime(1);
    insertionSort();

    showComment("InsertionSort: vetor ordenado");
    setSleepTime(10);
    show(&vetor,0);

    terminateDSGraph();

    return 0;
}
