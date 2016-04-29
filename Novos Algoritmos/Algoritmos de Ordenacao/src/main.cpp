#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <imprimeEstrutura.h>

using namespace std;
void trocaCor(float **cores, int id, float R, float G, float B){

    cores[id][0] = R;
    cores[id][1] = G;
    cores[id][2] = B;


}
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

        if(vet[i] > vet[i+1])
        {

            cout<<endl<<endl<<"Erro: vetor nao esta ordenado!"<<endl;
            return;

        }

    }
    cout << endl <<"Resultado: O vetor esta ordenado!" <<endl;

}

void bubbleSort(int* vetor, int tam, float **cor, void (espera)(int))
{

    int j = 0;
    int i = 0;
    int trocou = 0;

    for(i = 0; i<tam; i++)
    {
        for(j = 0 ; j<tam-1; j++)
        {

            trocaCor(cor,j,1.0,0.8,0.0);
            trocaCor(cor,j+1,1.0,0.8,0.0);
            espera(1);
            if(vetor[j+1] < vetor[j])
            {
                trocaCor(cor,j,0.0,1.0,0.0);
                trocaCor(cor,j+1,0.0,1.0,0.0);
                float aux = vetor[j];
                espera(1);
                vetor[j] = vetor[j+1];
                vetor[j+1]= aux;
                espera(1);
                trocou = 1;

            }
            trocaCor(cor,j,0.0,0.0,1.0);
            trocaCor(cor,j+1,0.0,0.0,1.0);

        }
        if (trocou == 0) break;
    }
}

void insertionSort(int* vetor, int tam, float **cor, void (espera)(int))
{

    int i, j, aux;

    for(i = 1; i < tam; i++)
    {
        j = i;
        trocaCor(cor,i,1.0,0.0,0.0);
        while(vetor[j] < vetor[j - 1])
        {
            if(j != i)trocaCor(cor,j,1.0,0.8,0.0);
            trocaCor(cor,j-1,1.0,0.8,0.0);
            espera(2);

            aux = vetor[j];
            vetor[j] = vetor[j - 1];
            vetor[j - 1] = aux;

            if(j != i)trocaCor(cor,j,0.0,0.0,1.0);
            trocaCor(cor,j-1,0.0,0.0,1.0);

            j--;

            if(j == 0)break;
        }
        trocaCor(cor,i,0.0,0.0,1.0);
    }
}

void selectionSort(int* vetor, int tam, float **cor, void (espera)(int))
{

    int i, j, min;
    for (i = 0; i < (tam-1); i++)
    {
        min = i;
        trocaCor(cor,i,1.0,0.0,0.0);
        for (j = (i+1); j < tam; j++)
        {

            trocaCor(cor,j,1.0,0.8,0.0);
            espera(1);
            if(vetor[j] < vetor[min])
            {
                if(min != i)trocaCor(cor,min,0.0,0.0,1.0);
                trocaCor(cor,j,0.0,1.0,0.0);
                espera(1);
                min = j;

            }else{

                trocaCor(cor,j,0.0,0.0,1.0);

            }


        }
        if (i != min)
        {
            trocaCor(cor,i,0.0,0.7,0.7);
            trocaCor(cor,min,0.0,0.7,0.7);
            espera(1);
            float swap = vetor[i];
            vetor[i] = vetor[min];
            vetor[min] = swap;
            trocaCor(cor,i,0.0,0.0,1.0);
            trocaCor(cor,min,0.0,0.0,1.0);

        }

    }
}


void mergeSort(int begin, int end, int* vet, int* vetAux, float **cor, void (espera)(int))
{

    int left = 0, right = 0, middle = 0;
    int i = 0;
    if(begin == end)
        return;

    middle = (begin + end)/2;

    cor[middle][3] = 1;
    espera(1);
    mergeSort(begin,middle,vet,vetAux,cor,espera);
    mergeSort(middle + 1,end,vet,vetAux,cor,espera);
    cor[middle][3] = 0;

    left = begin;
    right = middle + 1;

    trocaCor(cor,begin,0.0,0.5,0.0);
    trocaCor(cor,end,0.0,0.5,0.0);
    if(end-begin > 1)trocaCor(cor,middle,0.8,0.8,0.0);
    espera(1);

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
    for(i = begin; i <= end; i++){
        vet[i] = vetAux[i];
    }
    if(end-begin > 1)trocaCor(cor,middle,0.0,0.0,1.0);
    trocaCor(cor,begin,0.0,0.0,1.0);
    trocaCor(cor,end,0.0,0.0,1.0);

}
void heapSort(int* vet, int tam, float **cor, void (espera)(int))
{

    int aux;
    int auxVal;
    while(tam > 1){

        for(int i = (tam/2)-1; i >=0; i--){

            trocaCor(cor,i,1.0,0.3,0.0);
            espera(1);
            aux = 2*i+1;
            if(((2*i+2) < tam)&&(vet[2*i+2] > vet[aux])){

                aux = 2*i+2;

            }

            if((2*i+2) < tam)trocaCor(cor,2*i+2,1.0,0.8,0.0);
            trocaCor(cor,2*i+1,1.0,0.8,0.0);
            espera(1);

            if(vet[aux] > vet[i]){

                trocaCor(cor,i,0.0,1.0,0.5);
                trocaCor(cor,aux,0.0,1.0,0.5);
                espera(1);

                auxVal = vet[aux];
                vet[aux] = vet[i];
                vet[i] = auxVal;

                trocaCor(cor,i,0.0,1.0,0.0);
                trocaCor(cor,aux,0.0,1.0,0.0);
                espera(1);

            }

            if((2*i+2) < tam)trocaCor(cor,2*i+2,0.0,0.0,1.0);
            trocaCor(cor,2*i+1,0.0,0.0,1.0);
            trocaCor(cor,i,0.0,0.0,1.0);
        }
        trocaCor(cor,0,0.0,1.0,0.0);
        trocaCor(cor,tam-1,0.0,1.0,0.0);
        espera(1);

        auxVal = vet[0];
        vet[0] = vet[tam-1];
        vet[tam-1] = auxVal;

        trocaCor(cor,0,0.0,0.0,1.0);
        trocaCor(cor,tam-1,0.0,0.0,1.0);
        tam--;

    }

}
void quickSort(int x[],int first,int last, float **cor, void (espera)(int))
{

    int pivot,j,temp,i;

    if(first<last)
    {
        pivot=first;
        i=first;
        j=last;

        trocaCor(cor,pivot,1.0,0.0,0.0);

        while(i<j)
        {
            while(x[i]<=x[pivot]&&i<last)
            {

                if(i != first)trocaCor(cor,i,0.0,0.0,1.0);

                i++;

                trocaCor(cor,i,1.0,0.8,0.0);
                espera(1);

            }
            while(x[j]>x[pivot])
            {

                trocaCor(cor,j,0.0,0.0,1.0);

                j--;

                trocaCor(cor,j,1.0,0.8,0.0);
                espera(1);

            }


            if(i<j)
            {

                trocaCor(cor,i,0.0,1.0,0.0);
                trocaCor(cor,j,0.0,1.0,0.0);
                espera(1);

                temp=x[i];
                x[i]=x[j];
                x[j]=temp;

                trocaCor(cor,i,1.0,0.8,0.0);
                trocaCor(cor,j,1.0,0.8,0.0);

            }
        }

        trocaCor(cor,pivot,0.0,0.0,1.0);
        trocaCor(cor,j,0.0,0.0,1.0);
        espera(1);

        temp=x[pivot];
        x[pivot]=x[j];
        x[j]=temp;

        trocaCor(cor,pivot,0.0,0.0,1.0);
        trocaCor(cor,i,0.0,0.0,1.0);
        trocaCor(cor,j,0.0,0.0,1.0);

        quickSort(x,first,j-1,cor,espera);
        quickSort(x,j+1,last,cor,espera);

    }
}
void menu (int* vet, int tam, float** cor, void (espera)(int))
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
        heapSort(vet, tam,cor,espera);
        break;
    case 2:
        vetAux = new int[tam];
        mergeSort(0, tam-1 , vet, vetAux,cor,espera);
        delete []vetAux;
        break;
    case 3:
        quickSort(vet, 0, tam-1,cor,espera);
        break;
    case 4:
        insertionSort(vet, tam,cor,espera);
        break;
    case 5:
        selectionSort(vet, tam,cor,espera);
        break;
    case 6:
        bubbleSort(vet, tam, cor, espera);
        break;
    }
    verificaOrdenado(vet,tam);

}
float** inicializaMatrizCores(int tam){

    float **cores;
    cores = new float*[tam];
    for(int i = 0; i < tam; i++){

        cores[i] = new float[4];
        cores[i][0] = 0.0;
        cores[i][1] = 0.0;
        cores[i][2] = 1.0;
        cores[i][3] = 0.0;

    }
    return cores;

}
int main()
{
    srand(time(NULL));
    int tam;
    int* vet;
    float **cores;
    imprimeEstrutura *imp = new imprimeEstrutura(VETOR);
    cout << "Digite o tamanho do vetor " << endl;
    cin >> tam;
    vet = new int[tam];
    cores = inicializaMatrizCores(tam);
    imp->setPriVetor(&vet,&tam, cores);
    imp->imprime("Algoritmos de Ordenacao");
    randomizaVetor(vet, tam);
    imprimeVetor(vet,tam);
    menu(vet, tam, cores, imprimeEstrutura::espere);
    cout<<endl<<endl;
    imprimeVetor(vet,tam);
    cout<<endl;
    imp->finalizaImpressao();
    delete []vet;
    return 0;
}
