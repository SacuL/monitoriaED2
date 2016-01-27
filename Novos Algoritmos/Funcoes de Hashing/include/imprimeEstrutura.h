#ifndef imprimeEstrutura_H
#define imprimeEstrutura_H
#include "No.h"
#define ARVORE_BINARIA 1
#define ARVORE_BINARIA_CONTIGUA 2
#define GRAFICO_HASHING 3

using namespace std;
class imprimeEstrutura
{
    public:
        ///Funcoes da Estrutura
        imprimeEstrutura(const int TIPO){tipo = TIPO; inicializou = false;};
        void imprime(int argc, char* argv[], char* nomeJanela);
        int alturaArvore();
        void fechaJanela();
        void setPriNoBinario(No* p);
        void setPriNoBinarioCont(int* tree, int ultIndice);
        void setPriGraficoHashing(int* tabela, int tamTabela);
        int* getPriBinarioCont();
        No* getPriBinario();
        ~imprimeEstrutura(){};
    private:

        ///Variaveis da estrutura
        No* priBinario;
        int* priBinarioCont;
        int ultIndiceCont;
        int* priGraficoHashing;
        int tamGraficoHashing;
        void inicializa(int argc, char* argv[], char* nomeJanela);
        bool inicializou;
        int tipo;

        ///Funcoes do openGL
        static void motion (int x, int y);
        static void mouse (int button, int state, int x, int y);
        static void escreve(char* p, float x, float y);
        static void desenhaNo(float* pos, string valor);
        static void desenhaLinha(float *pos1, float *pos2);
        static void desenhaParteGrafico(float altura, float dx, float *pos);
        static void init (void);
        static void keyboard(unsigned char key, int x, int y);
        static void percorreBinariaCont(int* tree, int indiceAtual, int ultIndice, float x, float y, float desX);
        static void percorreBinaria(No* p, float x, float y, float desX);
        static void percorreGraficoHashing(int* p, int tam);
        static int alturaArvoreBinariaCont(int* tree, int ultIndice);
        static int maior(int *vet, int tam);
        static void display();
        int alturaArvoreBinaria(No* p, int nivel);

};

#endif // imprimeEstrutura_H
