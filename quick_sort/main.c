#include <stdio.h>
#include <stdlib.h>
#include "DSGraph.h"

#define MAX 10
int vetor[MAX];

void quicksort(int x[],int first,int last)
{
    showComment("QuickSort: LP (leftPtr) - V[%d] e RP (rightPtr) - V[%d]", first, last);
    setSleepTime(2);
    show(&vetor,2,&vetor[first],&vetor[last]);

    int pivot,j,temp,i;

    if(first<last)
    {
        pivot=first;

        showComment("QuickSort: pivo escolhido - V[%d] = %d", pivot, vetor[pivot]);
        setSleepTime(2);
        show(&vetor,1,&vetor[pivot]);

        i=first;
        j=last;

        while(i<j)
        {
            while(x[i]<=x[pivot]&&i<last)
            {

                showComment("QuickSort: verifica se LP (V[%d] = %d) eh menor ou igual ao pivo (V[%d] = %d)", i, x[i], pivot, vetor[pivot]);
                setSleepTime(2);
                show(&vetor,2,&x[i],&vetor[pivot]);

                i++;

                showComment("QuickSort: Anda com LP para a direita");
                setSleepTime(2);
                show(&vetor,1,&x[i]);

            }
            while(x[j]>x[pivot])
            {
                showComment("QuickSort: verifica se RP (V[%d] = %d) eh maior que o pivo (V[%d] = %d)", j, x[j], pivot, vetor[pivot]);
                setSleepTime(2);
                show(&vetor,2,&x[j],&vetor[pivot]);

                j--;

                showComment("QuickSort: Anda com RP para a esquerda");
                setSleepTime(2);
                show(&vetor,1,&x[j]);
            }


            if(i<j)
            {
                showComment("QuickSort: indice de LP (V[%d]) < indice de RP V[%d]", i,j);
                setSleepTime(2);
                show(&vetor,2,&x[i], &x[j]);

                temp=x[i];
                x[i]=x[j];
                x[j]=temp;

                showComment("QuickSort: troca valor de LP (V[%d]) com valor de RP V[%d]", i,j);
                setSleepTime(2);
                show(&vetor,2,&x[i], &x[j]);
            }
        }

        showComment("QuickSort: troca o valor do pivo V[%d] com o valor de RP V[%d] (antes)", pivot,j);
        setSleepTime(2);
        show(&vetor,2,&vetor[pivot],&vetor[j]);

        temp=x[pivot];
        x[pivot]=x[j];
        x[j]=temp;

        showComment("QuickSort: troca o valor do pivo V[%d] com o valor de RP V[%d] (depois)", pivot,j);
        setSleepTime(2);
        show(&vetor,2,&vetor[pivot],&vetor[j]);



        showComment("QuickSort: chamada recursiva do QuickSort para a particao de V[%d] ate V[%d]", first,j-1);
        setSleepTime(2);
        show(&vetor,2,&vetor[first],&vetor[j-1]);

        quicksort(x,first,j-1);


        showComment("QuickSort: chamada recursiva do QuickSort para a particao de V[%d] ate V[%d]",j+1,last);
        setSleepTime(2);
        show(&vetor,2,&vetor[j+1],&vetor[last]);

        quicksort(x,j+1,last);

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

    showComment("QuickSort: vetor inicial");
    setSleepTime(2);
    show(&vetor,0);

    setSleepTime(1);

    quicksort(vetor,0, MAX -1);

    showComment("QuickSort: vetor ordenado");
    setSleepTime(10);
    show(&vetor,0);
    terminateDSGraph();

    return 0;
}
