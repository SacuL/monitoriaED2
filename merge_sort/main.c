#include <stdio.h>
#include <stdlib.h>
#include "DSGraph.h"

#define MAX 10
float A[MAX],B[MAX];

void mergesort(int begin, int end)
{
        int left = 0, right = 0, middle = 0;
        int i = 0;

        if(begin == end)
                return;

        middle = (begin + end)/2;

        showComment("MergeSort: meio = V[%d]", middle);
        setSleepTime(2);
        show(&A,1,&A[middle]);

        showComment("MergeSort: chamada recursiva ao MergeSort, de V[%d] ate V[%d]", begin, middle);
        setSleepTime(2);
        show(&A,2,&A[begin], &A[middle]);
        mergesort(begin,middle);

        showComment("MergeSort: chamada recursiva ao MergeSort, de V[%d] ate V[%d]", middle+1, end);
        setSleepTime(2);
        show(&A,2,&A[middle + 1], &A[end]);
        mergesort(middle + 1,end);

        left = begin;
        right = middle + 1;

        for(i = begin;i <= end;i++)
        {
                        showComment("MergeSort: Verifica o menor elemento: V[%d] e V[%d]",left, right);
                        setSleepTime(2);
                        show(&A,2,&A[left], &A[right]);

                if(right > end || (left <= middle && A[left] <= A[right]))
                {
                        B[i] = A[left];

                        showComment("MergeSort: Segundo vetor recebe o menor na posicao %d",i);
                        setSleepTime(2);
                        show(&B,1,&B[i]);

                        left++;
                }
                else
                {
                        B[i] = A[right];

                        showComment("MergeSort: Segundo vetor recebe o menor na posicao %d",i);
                        setSleepTime(2);
                        show(&B,1,&B[i]);
                        right++;
                }
        }
        for(i = begin;i <= end;i++)
                A[i] = B[i];
}


int main()
{

    //Inicializa a biblioteca grafica com a estrutura a ser apresentada na tela
    init($ARRAY,MAX,1);

    int i = 0;

    setSleepTime(2);

    for(i = 0; i < MAX; i++)
    {
        A[i] = rand()%100;
    }

    showComment("MergeSort: vetor inicial");
    setSleepTime(2);
    show(&A,0);
    setSleepTime(1);

    mergesort(0,MAX-1);

    showComment("MergeSort: vetor ordenado");
    setSleepTime(10);
    show(&A,0);
    terminateDSGraph();

    return 0;
}
