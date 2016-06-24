#ifndef imprimeEstrutura_H
#define imprimeEstrutura_H
#include <No.h>
#include <Lista.h>
#include <NoBinomial.h>
#include <No_B.h>
#include <No_MW.h>
#include <No_Ter.h>
#include <No_HUF.h>
#include <No_VP.h>
#include <NoR.h>
#define PRETO 1
#define VERMELHO 0
#define DEFAULT -1
#define ARVORE_BINARIA 1
#define ARVORE_BINARIA_CONTIGUA 2
#define GRAFICO_HASHING 3
#define HASHING_LISTA 4
#define LISTA_SIMPLES_ENCADEADA 5
#define VETOR 6
#define HEAP_BINOMIAL 7
#define ARVORE_B 8
#define ARVORE_MULTIWAY 9
#define ARVORE_TRIE_TERNARIA 10
#define ARVORE_HUFFMAN 11
#define ARVORE_VERMELHO_PRETA 12
#define ARVORE_R 13

using namespace std;
class imprimeEstrutura
{
    public:
        ///Funcoes da Estrutura
        imprimeEstrutura(const int TIPO);
        void imprime(char* nomeJanela);
        static void fechaJanela();
        void setPriNoBinario(No** p);
        void setPriNoBinarioCont(int** tree, int* ultIndice);
        void setPriGraficoHashing(int* tabela, int tamTabela);
        void setPriHashingLista(Lista* l, int tamTabela);
        void setPriListaEncadeada(No_Lista* l);
        void setPriVetor(int** i, int* tam, float **cores);
        void setPriHeapBinomial(No_Binomial** b);
        void setPriArvoreB(No_B **b);
        void setPriArvoreMultiWay(No_MW **m);
        void setPriTrieTer(No_Ter** p);
        void setPriHuffmanTree(No_HUF** h);
        void setPriArvoreVermelhoPreta(No_VP** v);
        void setPriArvoreR(NoR** r);
        void setARGS(int argc, char* argv[]);
        int* getPriBinarioCont();
        void finalizaImpressao();
        static void espere(int tempo);
        ~imprimeEstrutura(){};
    private:

        int tipo;

        ///Funcoes do openGL
        static void inicializa();
        static void motion (int x, int y);
        static void mouse (int button, int state, int x, int y);
        static void espera(void);
        static void idle(void);
        static void escreve(char* p, float x, float y);
        static void desenhaNo(float* pos, string valor, int cor);
        static void desenhaNoLista(float* pos, string valor, float *cor);
        static void desenhaSeta(float* pos1);
        static void desenhaLinha(float *pos1, float *pos2);
        static void desenhaBarra(float *pos1, float *pos2);
        static void desenhaParteGrafico(float altura, float dx, float *pos);
        static void desenhaNoB(float *posB, int* valores, int tam);
        static void desenhaNoMW(float *posMW, int tam, bool ehChave);
        static void desenhaNoR(float *posR, NoR* n);
        static void desenhaNoCor(float* pos, string valor, float red, float green, float blue);
        static void init (void);
        static void keyboard(unsigned char key, int x, int y);
        static void percorreBinariaCont(int* tree, int indiceAtual, int ultIndice, float x, float y, float desX);
        static void percorreBinaria(No* p, float x, float y, float desX);
        static void percorreGraficoHashing(int* p, int tam);
        static void percorreHashingLista(Lista* l, int tam, float *posH);
        static void percorreListaEncadeada(No_Lista* l, float *pos1);
        static void percorreVetor(float *posVetor);
        static void percorreHeapBinomial(float *posHeap, No_Binomial* n);
        static void percorreHeapBk(float *posHeap, float *posPai, No_Binomial* n);
        static void percorreB(float *posB, No_B* n, float dist);
        static void percorreMultiWay(float *posMw, No_MW* n, float dist);
        static void percorreTernaria(float *posTer, No_Ter* n, float dist);
        static void percorreArvoreB(float *posB, No_B* n, float dist);
        static void percorreHuffman(float *posH, No_HUF* h, float dist);
        static void percorreVermelhoPreta(No_VP* p, float x, float y, float desX);
        static void percorreR(float *pos1,NoR *n,float dist);
        static void desenhaLinhasR(float *pos1,NoR *n,float dist);
        static void desenhaLinhasB(float *posB, No_B* n, float dist);
        static void desenhaLinhasHeapBinomial(float *posHeap, int grau);
        static void desenhaLinhasTernaria(float *posTer, No_Ter *n, float dist);
        static float retornaDistanciaHeapBinomial(No_Binomial *n);
        static int alturaArvoreBinariaCont(int* tree, int ultIndice);
        static int alturaArvoreB(No_B*);
        static int alturaArvoreMultiWay(No_MW *n);
        static int alturaTrieTernaria(No_Ter *n, int nivel);
        static int alturaHuffman(No_HUF* h, int nivel);
        static void desenhaNoHuffman(float *posH,int freq, char c);
        static int maior(int *vet, int tam);
        static void display();
        static int alturaArvore();
        static int alturaArvoreBinaria(No* p, int nivel);
        static int alturaArvoreVermelhoPreta(No_VP* p, int nivel);
        static int alturaArvoreR(NoR* n);
        static string converteMBR(Point* n);

};

#endif // imprimeEstrutura_H

