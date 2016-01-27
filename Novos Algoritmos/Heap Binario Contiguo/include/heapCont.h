#ifndef HEAPCONT_H
#define HEAPCONT_H
#define MAX_HEAP  1
#define MIN_HEAP -1
#define VETOR 2
#define TREE 3

class heapCont
{
    public:
        heapCont(const int tipo);
        int busca(int p);//Retorna o indice do NO p buscado, se for -1, NO nao existe
        void insere(int p);//Insere um No p no heap
        void removeNo(int p);//Remove um NO p do heap
        void imprimeHeap(const int tipoImpressao = VETOR);//Imprime o vetor em forma de heap
        int* getRaiz();//Retorna o ponteiro para o vetor heap
        int getUltIndice();//Retorna o indice do ultimo no do vetor heap
        void uniao(int* H, int uInd);//Faz a uniao entre os heap deste objeto e o heap correspondente do vetor H
        ~heapCont();

    private:
        int* heap;//Vetor que será usado para armazenar o heap
        void realocaHeap(int numVezes = 2);//Caso o espaco do vetor acabar, ele realoca o heap com o dobro do tamanho
        void constroiHeap(int Iinicio, int Ifinal);//Verifica as proprieades do heap
        int compara(int p, int n);//Retorna o indice do valor correspondente a comparacao, se for MAX_HEAP retorna
        //o maior, se for o MIN_HEAP retorna o menor, p e n sao indices do vetor heap
        int ultIndice;//Ultimo indice do vetor que corresponde a parte do heap
        int tamVet;//Tamanho do vetor
        int tipo;//Tipo do heap, se será MAX_HEAP ou MIN_HEAP
};

#endif // HEAPCONT_H
