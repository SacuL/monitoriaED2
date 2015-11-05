#include <stdio.h>
#include <stdlib.h>
#include "DSGraph.h"

#define MAX 10
float vetor[MAX];

void selection_sort()
{
  int i, j, min;
  for (i = 0; i < (MAX-1); i++)
   {
    min = i;
        showComment("SelectionSort. Busca do mínimo: valor com pivô = V[%d]",i);
        show(&vetor,1,&vetor[min]);

    for (j = (i+1); j < MAX; j++) {

      showComment("SelectionSort. Busca do mínimo: verifica se V[%d] < V[%d] (pivô)", j, min);
      show(&vetor,2,&vetor[j],&vetor[min]);

      if(vetor[j] < vetor[min]) {
        min = j;
            showComment("SelectionSort: novo pivô = V[%d]",min);
            show(&vetor,1,&vetor[min]);
      }
    }

    //showComment("SelectionSort: verifica se V[%d] != V[%d]", i, min);
    setSleepTime(2);
    //show(&vetor,2,&vetor[i],&vetor[min]);

    if (i != min) {
      float swap = vetor[i];
      vetor[i] = vetor[min];
      vetor[min] = swap;

        showComment("SelectionSort. Ordena: troca  V[%d] com V[%d] (pivô).", i, min);
        show(&vetor,2,&vetor[i],&vetor[min]);
    }
    else{
        showComment("SelectionSort: Ordena: pivô já está em sua posição correta");
        show(&vetor,1,&vetor[i]);
    }
    setSleepTime(1);
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

    showComment("SelectionSort: vetor inicial");
    setSleepTime(2);
    show(&vetor,0);

    setSleepTime(1);
    selection_sort();

    showComment("SelectionSort: vetor ordenado");
    setSleepTime(10);
    show(&vetor,0);
    terminateDSGraph();

    return 0;
}
