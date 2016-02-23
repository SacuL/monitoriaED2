#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;
void randomizaVetor(int* vet, int tam)
{

    for(int i = 0; i < tam; i++)
    {

        vet[i] = rand() % (tam * 2);

    }

}
void imprimeVetor(int* vet, int tam)
{

    int i;
    for(i = 0; i < tam-1; i++)
    {

        cout<<vet[i]<<"-";

    }
    cout<<vet[i];

}
void verificaOrdenado(int *vet, int tam)
{

    for(int i = 0; i < tam - 1; i++)
    {

        if(vet[tam] > vet[tam])
        {

            cout<<endl<<endl<<"Erro: vetor nao esta ordenado!"<<endl;
            return;

        }

    }
    cout << endl <<"Resultado: O vetor esta ordenado!" <<endl;

}

void bubbleSort(int* vetor, int tam)
{

    int j = 0;
    int i = 0;
    int trocou = 0;

    for(i = 0; i<tam; i++)
    {
        for(j = 0 ; j<tam-1; j++)
        {
            if(vetor[j+1] < vetor[j])
            {

                float aux = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1]= aux;
                trocou = 1;

            }

        }
        if (trocou == 0) break;
    }
}

void insertionSort(int* vetor, int tam)
{

    int i, j, aux;

    for(i = 1; i < tam; i++)
    {
        j = i;

        while(vetor[j] < vetor[j - 1])
        {
            aux = vetor[j];
            vetor[j] = vetor[j - 1];
            vetor[j - 1] = aux;

            j--;

            if(j == 0)break;
        }
    }
}

void selectionSort(int* vetor, int tam)
{

    int i, j, min;
    for (i = 0; i < (tam-1); i++)
    {
        min = i;
        for (j = (i+1); j < tam; j++)
        {

            if(vetor[j] < vetor[min])
            {
                min = j;
            }
        }

        if (i != min)
        {
            float swap = vetor[i];
            vetor[i] = vetor[min];
            vetor[min] = swap;

        }
    }
}


void mergeSort(int begin, int end, int* vet, int* vetAux)
{

    int left = 0, right = 0, middle = 0;
    int i = 0;

    if(begin == end)
        return;

    middle = (begin + end)/2;

    mergeSort(begin,middle,vet,vetAux);
    mergeSort(middle + 1,end,vet,vetAux);

    left = begin;
    right = middle + 1;

    for(i = begin; i <= end; i++)
    {

        if(right > end || (left <= middle && vet[left] <= vet[right]))
        {
            vetAux[i] = vet[left];
            left++;
        }
        else
        {
            vetAux[i] = vet[right];
            right++;
        }
    }
    for(i = begin; i <= end; i++)
        vet[i] = vetAux[i];
}
void heapSort(int* vet, int tam)
{

    int aux;
    for(int i=tam-1; i>=0; i--)
    {

        for(int k=(i/2)-1; k>=0; k--)
        {

            if(2*k+2<=i)
            {

                if(vet[2*k+2]>vet[2*k+1])
                {

                    if(vet[2*k+2]>vet[k])
                    {

                        aux=vet[k];
                        vet[k]=vet[2*k+2];
                        vet[2*k+2]=aux;

                    }


                }
                else
                {

                    if(vet[2*k+1]>vet[k])
                    {

                        aux=vet[k];
                        vet[k]=vet[2*k+1];
                        vet[2*k+1]=aux;

                    }

                }

            }
            else
            {

                if(vet[2*k+1]>vet[k])
                {

                    aux=vet[k];
                    vet[k]=vet[2*k+1];
                    vet[2*k+1]=aux;

                }


            }
            aux=vet[0];
            vet[0]=vet[i];
            vet[i]=aux;

        }

    }
    if(vet[0]>vet[1])
    {

        aux=vet[0];
        vet[0]=vet[1];
        vet[1]=aux;

    }

}
void quickSort(int x[],int first,int last)
{

    int pivot,j,temp,i;

    if(first<last)
    {
        pivot=first;
        i=first;
        j=last;

        while(i<j)
        {
            while(x[i]<=x[pivot]&&i<last)
            {

                i++;

            }
            while(x[j]>x[pivot])
            {

                j--;

            }


            if(i<j)
            {

                temp=x[i];
                x[i]=x[j];
                x[j]=temp;

            }
        }
        temp=x[pivot];
        x[pivot]=x[j];
        x[j]=temp;
        quickSort(x,first,j-1);
        quickSort(x,j+1,last);

    }
}
void menu (int* vet, int tam)
{

    int escolha;
    int* vetAux;
    cout <<endl<<endl<<endl;
    cout<< "Escolha o metodo de ordenacao para este vetor: "<<endl;
    cout<< "1 - heapSort;" <<endl<<
        "2 - mergeSort" <<endl<<
        "3 - quickSort" <<endl<<
        "4 - insertionSort" <<endl<<
        "5 - selectionSort" <<endl<<
        "6 - bubbleSort" <<endl << ">> ";
    cin >> escolha;
    switch(escolha)
    {

    case 1:
        heapSort(vet, tam);
        break;
    case 2:
        vetAux = new int[tam];
        mergeSort(0, tam-1 , vet, vetAux);
        delete []vetAux;
        break;
    case 3:
        quickSort(vet, 0, tam-1);
        break;
    case 4:
        insertionSort(vet, tam);
        break;
    case 5:
        selectionSort(vet, tam);
        break;
    case 6:
        bubbleSort(vet, tam);
        break;
    }
    verificaOrdenado(vet,tam);

}
int main()
{
    srand(time(NULL));
    int tam;
    int* vet;
    cout << "Digite o tamanho do vetor " << endl;
    cin >> tam;
    vet = new int[tam];
    randomizaVetor(vet, tam);
    imprimeVetor(vet,tam);
    menu(vet, tam);
    cout<<endl<<endl;
    imprimeVetor(vet,tam);
    cout<<endl;
    delete []vet;
    return 0;
}
