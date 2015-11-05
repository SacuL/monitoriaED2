#include <stdio.h>
#include <stdlib.h>
#include <DSGraph.h>

#define MAX 10
float vetor[MAX];
int trocou=0;

void bubblesort()
{
    int j= 0 ;
    int i=0;

    for(i = 0; i<MAX; i++)
    {
        for(j= 0 ; j<MAX-1; j++)
        {
            showComment("BubbleSort: verificando os valores V[%d] e V[%d]", j, j+1);
            show(&vetor,2,&vetor[j],&vetor[j+1]);
            if(vetor[j+1] < vetor[j])
            {

               float aux = vetor[j];
               vetor[j] = vetor[j+1];
               vetor[j+1]= aux;
               showComment("BubbleSort: alterando valores V[%d] e V[%d]", j, j+1);
               show(&vetor,2,&vetor[j+1],&vetor[j]);
               trocou =1;

           }

        }
        if (trocou == 0) break;
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

    showComment("BubbleSort: vetor inicial");

    show(&vetor,0);
    setSleepTime(1);

    bubblesort();
    showComment("BubbleSort: vetor ordenado");
    setSleepTime(5);
    show(&vetor,0);
    terminateDSGraph();

    return 0;
}
