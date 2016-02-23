#ifndef imprimeEstrutura_H
#define imprimeEstrutura_H
#include "No.h"
#define ARVORE_BINARIA 1
#define ARVORE_BINARIA_CONTIGUA 2

using namespace std;
class imprimeEstrutura
{
public:
    ///Funcoes da Estrutura
    imprimeEstrutura(const int TIPO)
    {
        tipo = TIPO;
        inicializou = false;
    };
    void imprime(int argc, char* argv[], char* nomeJanela);
    int alturaArvore();
    void fechaJanela();
    void setPriNoBinario(No* p);
    void setPriNoBinarioCont(int* tree, int ultIndice);
    int* getPriBinarioCont();
    No* getPriBinario();
    ~imprimeEstrutura() {};
private:
    No* priBinario;
    int* priBinarioCont;
    int ultIndiceCont;
    void inicializa(int argc, char* argv[], char* nomeJanela);
    bool inicializou;
    int tipo;

    ///Funcoes do openGL
    static void motion (int x, int y);
    static void mouse (int button, int state, int x, int y);
    static void escreve(char* p, float x, float y);
    static void desenhaNo(float* pos, string valor);
    static void desenhaLinha(float *pos1, float *pos2);
    static void init (void);
    static void keyboard(unsigned char key, int x, int y);
    static void percorreBinariaCont(int* tree, int indiceAtual, int ultIndice, float x, float y, float desX);
    static void percorreBinaria(No* p, float x, float y, float desX);
    static int alturaArvoreBinariaCont(int* tree, int ultIndice);
    static void display();
    int alturaArvoreBinaria(No* p, int nivel);

};

#endif // imprimeEstrutura_H
