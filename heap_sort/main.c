#include <stdio.h>
#include <stdlib.h>
#include "DSGraph.h"

#define MAX 10
float vetor[MAX];


void heapsort(float a[], int n)
{
    int i = n/2, pai, filho;

    float t;

    for (;;)
    {
        if (i > 0)
        {
            i--;
            t = a[i];
        }
        else
        {
            n--;
            if (n == 0)
                return;
            t = a[n];

            showComment("HeapSort: O primeiro elemento (maior elemento) vai para a seu posicao correta.");
            setSleepTime(2);
            show(&vetor,2, &a[0], &a[n]);

            a[n] = a[0];

            setSleepTime(2);
            show(&vetor,2, &a[0], &a[n]);
        }

        pai = i;
        filho = i*2 + 1;

            showComment("HeapSort: Indice Raiz: V[%d]",pai);
            setSleepTime(2);
            show(&vetor,1,&vetor[i]);


            showComment("HeapSort: Indice Raiz: V[%d] e Filho 1: V[%d]",pai,filho);
            setSleepTime(2);
            show(&vetor,2, &a[pai], &a[filho]);

        while (filho < n)
        {
            if ((filho + 1 < n)  &&  (a[filho + 1] > a[filho])){

                filho++;

                showComment("HeapSort: Indice Raiz: V[%d] e Filho 2: V[%d]",pai,filho);
                setSleepTime(2);
                show(&vetor,2, &a[pai], &a[filho]);
            }
            if (a[filho] > t)
            {

                showComment("Filho V[%d] maior que pai V[%d] -> filho ira receber o valor do pai.",filho, pai);
                setSleepTime(2);
                show(&vetor,2, &a[pai], &a[filho]);

                a[pai] = a[filho];

                pai = filho;
                filho = pai*2 + 1;


            }
            else
                break;
        }
        a[pai] = t;
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

    showComment("HeapSort: vetor inicial");
    setSleepTime(2);
    show(&vetor,0);

    setSleepTime(1);
    heapsort(vetor ,MAX );

    showComment("HeapSort: vetor ordenado");
    setSleepTime(10);
    show(&vetor,0);
    terminateDSGraph();

    return 0;
}
