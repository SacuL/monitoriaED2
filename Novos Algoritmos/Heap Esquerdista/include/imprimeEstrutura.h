#ifndef imprimeEstrutura_H
#define imprimeEstrutura_H
#include "No.h"
#include <Lista.h>
#define ARVORE_BINARIA 1
#define ARVORE_BINARIA_CONTIGUA 2
#define GRAFICO_HASHING 3
#define HASHING_LISTA 4
#define LISTA_SIMPLES_ENCADEADA 5
#define VETOR 6

using namespace std;
class imprimeEstrutura
{
public:
    ///Funcoes da Estrutura
    imprimeEstrutura(const int TIPO)
    {
        tipo = TIPO;
    };
    void imprime(int argc, char* argv[], char* nomeJanela, int tempo = -1);
    int alturaArvore();
    static void fechaJanela();
    void setPriNoBinario(No* p);
    void setPriNoBinarioCont(int* tree, int ultIndice);
    void setPriGraficoHashing(int* tabela, int tamTabela);
    void setPriHashingLista(Lista* l, int tamTabela);
    void setPriListaEncadeada(No_Lista* l);
    void setPriVetor(int* i, int tam);
    int* getPriBinarioCont();
    No* getPriBinario();
    ~imprimeEstrutura() {};
private:

    ///Variaveis da estrutura
    No* priBinario;
    int* priBinarioCont;
    int ultIndiceCont;
    int* priGraficoHashing;
    int tamGraficoHashing;
    Lista* priHashingLista;
    int tamHashingLista;
    No_Lista* priListaEncadeada;
    int* priVetor;
    int tamPriVetor;
    void inicializa(int argc, char* argv[], char* nomeJanela);
    int tipo;

    ///Funcoes do openGL
    static void motion (int x, int y);
    static void mouse (int button, int state, int x, int y);
    static void idle(void);
    static void escreve(char* p, float x, float y);
    static void desenhaNo(float* pos, string valor);
    static void desenhaNoLista(float* pos, string valor, float *cor);
    static void desenhaSeta(float* pos1);
    static void desenhaLinha(float *pos1, float *pos2);
    static void desenhaBarra(float *pos1, float *pos2);
    static void desenhaParteGrafico(float altura, float dx, float *pos);
    static void init (void);
    static void keyboard(unsigned char key, int x, int y);
    static void percorreBinariaCont(int* tree, int indiceAtual, int ultIndice, float x, float y, float desX);
    static void percorreBinaria(No* p, float x, float y, float desX);
    static void percorreGraficoHashing(int* p, int tam);
    static void percorreHashingLista(Lista* l, int tam, float *posH);
    static void percorreListaEncadeada(No_Lista* l, float *pos1);
    static void percorreVetor(float *posVetor);
    static int alturaArvoreBinariaCont(int* tree, int ultIndice);
    static int maior(int *vet, int tam);
    static void display();
    int alturaArvoreBinaria(No* p, int nivel);

};

#endif // imprimeEstrutura_H
