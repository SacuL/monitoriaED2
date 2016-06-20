#include <stdio.h>
#include <GL/glut.h>
#include <string>
#include <iostream>
#include <sstream>
#include "imprimeEstrutura.h"
#include <math.h>
#include <time.h>
#define M_PI 3.14159265359
#include <thread>

using namespace std;
No** aux;
bool pause = false;
float pos[] = {10.0,10.0};
float raio = 0.4;
int altura;
int posx = -1;
int posy = -1;
float XYcart = 20.0;
int window;
int tipoEstrutura;
int* graficoHashing;//Ponteiro para a tabela de contagem de colisoes de um hashing
int tamGrafico;//
int** NoCont;//Ponteiro para o vetor da arvore contigua
int* ult;//Ultimo indice da arvore contigua
float dx = 0.0, dy = 0.0;
Lista* listaHashing;
int tamListaHashing;
No_Lista* listaEncadeada;
int **vet;//vetor a ser impresso
int *tamVet;//tamanho do vetor a ser impresso
float **cores;//matriz de cores para serrem usadas em algoritmos de ordenacao
No_Binomial** Binomial;
No_Binomial* priBinomial;
No_B** BTREE;
No_MW** MWTREE;
No_Ter** TERTREE;
No_HUF** HUFTREE;
No_VP** VPTREE;
int auxWait;
int ARGC;
char** ARGV;
char* nomeJanela;
thread *t1;
clock_t inicio;
int wait;
bool full = false;

void imprimeEstrutura::inicializa(){

    ///Callbacks OpenGl
   glutInit(&ARGC, ARGV);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
   glutInitWindowSize (1066, 600);
   glutInitWindowPosition (100, 100);
   glutSetOption(0X01F9,1);
   glutIdleFunc(idle);
   window = glutCreateWindow (nomeJanela);
   init ();
   glutDisplayFunc(display);
   glutMotionFunc(motion);
   glutMouseFunc(mouse);
   glutKeyboardFunc(keyboard);

   glutMainLoop();

}
void imprimeEstrutura::motion (int x, int y){

    pos[0] += (float) ((x - posx)/100.0);
    pos[1] += (float) ((posy - y)/100.0);
    dx += (float) ((x - posx)/20.0);
    dy += (float) ((posy - y)/20.0);
    posx = x;
    posy = y;
    glutPostRedisplay();


}
void imprimeEstrutura::mouse (int button, int state, int x, int y){

    if(button == 3){

        XYcart += 0.5;

    }else if(button == 4){

        XYcart -= 0.5;

    }
    posx = x;
    posy = y;
    glutPostRedisplay();

}
void imprimeEstrutura::escreve(char* p, float x, float y){

    // posicionamos na tela
    glRasterPos2f(x, y);
    // String a ser escrita na tela
    while (*p != '\0') {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,*p++);
    }

}
void imprimeEstrutura::desenhaNo(float* pos, string valor, int cor = DEFAULT){

    int numSeg = 32;
    float segmento = 2*M_PI/(float)numSeg;
    float tamanhoValor;
    if(cor == DEFAULT){

        glColor3f(0.0,0.0,1.0);

    }else{

        if(cor == VERMELHO){

            glColor3f(1.0,0.0,0.0);

        }
        if(cor == PRETO){

            glColor3f(0.0,0.0,0.0);

        }

    }
    glBegin(GL_TRIANGLE_FAN);

        glVertex3f(pos[0],pos[1],0.0);
        for(int i = 0; i <= numSeg; i++){

            glVertex3f(pos[0]+raio*cos(segmento*i),pos[1]+raio*sin(segmento*i),0.0);

        }

    glEnd();
    tamanhoValor = valor.size();
    while(tamanhoValor > 0.9){tamanhoValor = tamanhoValor/10.0;}
    tamanhoValor -= 0.1;
    glColor3f(1.0,1.0,1.0);
    escreve((char*)valor.c_str(),pos[0] - tamanhoValor,pos[1]-0.09);

}
void imprimeEstrutura::desenhaLinha(float *pos1, float *pos2){

    glBegin(GL_LINES);
        glColor3f(0.0,0.0,0.0);
        glVertex3f(pos1[0],pos1[1],0.0);
        glVertex3f(pos2[0],pos2[1],0.0);
    glEnd();

}
void imprimeEstrutura::display(){

   glClear (GL_COLOR_BUFFER_BIT);
   glMatrixMode(GL_PROJECTION);              // Seleciona Matriz de Projeção
   glLoadIdentity();
   if(tipoEstrutura == 3){

        glOrtho(-(tamGrafico*0.05), tamGrafico + tamGrafico*0.05, -maior(graficoHashing, tamGrafico)*0.05, maior(graficoHashing, tamGrafico) + maior(graficoHashing, tamGrafico)*0.05, -10.0, 10.0);

   }else{

        glOrtho(0.0, XYcart, 0.0, XYcart*(9.0/16.0), -10.0, 10.0);

   }
   glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
   glLoadIdentity();

    glEnable(GLUT_MULTISAMPLE);

    if(tipoEstrutura == 1){

        if(aux == NULL){

            cout << "Ponteiro para a raiz da arvore esta vazio, verifique se voce apontou a estrutura para a raiz da arvore a ser imprimida" << endl;

        }else{

            if(*aux != NULL){

                percorreBinaria(*aux, pos[0], pos[1], pow(2.0,(altura-2)));

            }

        }

    }else if(tipoEstrutura == 2){

        if(NoCont == NULL){

            cout << "Ponteiro para a raiz da arvore esta vazio, verifique se voce apontou a estrutura para a raiz da arvore a ser imprimida" << endl;

        }else{

            if(*ult > 0){

                percorreBinariaCont(*NoCont, 0, *ult, pos[0], pos[1], pow(2.0,(altura-2)));

            }

        }

    }else if(tipoEstrutura == 3){

        if(graficoHashing == NULL){

            cout << "Ponteiro para a tabela de hashing esta vazio, verifique se voce apontou a estrutura para a tabela a ser imprimida" << endl;

        }else{

            percorreGraficoHashing(graficoHashing,tamGrafico);

        }

    }else if(tipoEstrutura == 4){

        if(listaHashing == NULL){

            cout << "Ponteiro para lista esta vazio, verifique se voce apontou a estrutura para a lista a ser imprimida" << endl;

        }else{

            float pos1[2];
            pos1[0] = 1.0 + dx;
            pos1[1] = XYcart * ( 3.0 / 5.0 ) - 1.0  + dy;
            percorreHashingLista(listaHashing,tamListaHashing,pos1);

        }


    }else if(tipoEstrutura == 5){

        if(listaEncadeada == NULL){

            cout << "Ponteiro para lista esta vazio, verifique se voce apontou a estrutura para a lista a ser imprimida" << endl;

        }else{

            float pos1[2];
            pos1[0] = 1.0;
            pos1[1] = XYcart*(3.0/10.0);
            percorreListaEncadeada(listaEncadeada,pos1);

        }

    }else if(tipoEstrutura == 6){

        if(vet == NULL){

            cout << "Ponteiro para o vetor esta vazio, verifique se voce apontou a estrutura para o vetor a ser imprimido" << endl;

        }else{

            float pos1[2];
            pos1[0] = 1.0 + dx;
            pos1[1] = XYcart * ( 3.0 / 10.0 )  + dy;
            percorreVetor(pos1);

        }

    }else if(tipoEstrutura == 7){

        if(Binomial == NULL){

            cout << "Ponteiro para heap binomial vazio, verifique se voce apontou a estrutura para a floresta a ser impressa" << endl;

        }else{

            float pos1[2];
            pos1[0] = 1.0 + dx;
            pos1[1] = XYcart * ( 3.0 / 5.5 )  + dy;
            percorreHeapBinomial(pos1,*Binomial);

        }


    }else if(tipoEstrutura == 8){

        if(BTREE == NULL){

            cout << "Ponteiro para a arvore B vazia, verifique se voce apontou a estrutura para a arvore a ser impressa" << endl;

        }else{

            if(*BTREE != NULL){

                float pos1[2];
                pos1[0] = 10.0 + dx;
                pos1[1] = XYcart * ( 3.0 / 5.5 )  + dy;
                percorreB(pos1,*BTREE,altura);

            }

        }


    }else if(tipoEstrutura == 9){

        if(MWTREE == NULL){

            cout << "Ponteiro para a arvore MultiWay vazia, verifique se voce apontou a estrutura para a arvore a ser impressa" << endl;

        }else{

            float pos1[2];
            pos1[0] = 10.0 + dx;
            pos1[1] = XYcart * ( 3.0 / 6.0 )  + dy;
            percorreMultiWay(pos1,*MWTREE,altura);

        }


    }else if(tipoEstrutura == 10){

        if(TERTREE == NULL){

            cout << "Ponteiro para a arvore Ternaria vazia, verifique se voce apontou a estrutura para a arvore a ser impressa" << endl;

        }else{

            float pos1[2];
            pos1[0] = 10.0 + (dx/2);
            pos1[1] = XYcart * ( 3.0 / 6.0 )  + (dy/2);
            percorreTernaria(pos1,*TERTREE,pow(3,altura-1));

        }

    }else if(tipoEstrutura == 11){

        if(HUFTREE == NULL){

            cout << "Ponteiro para a arvore de Huffman vazia, verifique se voce apontou a estrutura para a arvore a ser impressa" << endl;

        }else{

            float pos1[2];
            pos1[0] = 10.0 + (dx/2);
            pos1[1] = XYcart * ( 3.0 / 6.0 )  + (dy/2);
            percorreHuffman(pos1,*HUFTREE,pow(2.0,(altura-2)));

        }

    }else if(tipoEstrutura == 12){

        if(VPTREE == NULL){

            cout << "Ponteiro para a raiz da arvore esta vazio, verifique se voce apontou a estrutura para a raiz da arvore a ser imprimida" << endl;

        }else{

            if(*VPTREE != NULL){

                percorreVermelhoPreta(*VPTREE, pos[0], pos[1], pow(2.0,(altura-2)));

            }

        }

    }else{

        cout << "Tipo de estrutura não reconhecida, verifique os parametros do construtor da função" << endl;

    }
    glutSwapBuffers ();
}
void imprimeEstrutura::init (void){

   glClearColor (1.0, 1.0, 1.0, 1.0);

}
void imprimeEstrutura::keyboard(unsigned char key, int x, int y){
   switch (key){

        case 27:
            glutDestroyWindow(window);
        break;
        case 'p':
            pause = !pause;
        break;
        case 'f':
            full = !full;
            if(full){

                glutFullScreen();

            }else{

                glutReshapeWindow(1066,600);
                glutPositionWindow(100,100);

            }
        break;
        case 'e':
            exit(0);
        break;

    }
}
void imprimeEstrutura::setPriNoBinario(No** p){

    aux = p;
    altura = alturaArvore();


}
void imprimeEstrutura::imprime(char* NMJanela){

    nomeJanela = NMJanela;
    t1 = new thread(inicializa);


}
void imprimeEstrutura::percorreBinaria(No* p, float x, float y, float desX){

    float pos1[2];
    float pos2[2];
    pos2[0] = x;
    pos2[1] = y;
    desX /= 2.0;
    float desY = 2.0;
    ostringstream oss;
    string valor;

    if(p->getAnt() != NULL){

        pos1[0] = pos2[0] - desX;
        pos1[1] = pos2[1] - desY;
        desenhaLinha(pos2,pos1);

    }if(p->getProx() != NULL){

        pos1[0] = pos2[0] + desX;
        pos1[1] = pos2[1] - desY;
        desenhaLinha(pos2,pos1);

    }

    oss << p->getValor();
    valor = oss.str();
    desenhaNo(pos2,valor);
    if(p->getAnt() != NULL){

        pos1[0] = pos2[0] - desX;
        pos1[1] = pos2[1] - desY;
        percorreBinaria(p->getAnt(), pos1[0], pos1[1], desX);

    }if(p->getProx() != NULL){

        pos1[0] = pos2[0] + desX;
        pos1[1] = pos2[1] - desY;
        percorreBinaria(p->getProx(), pos1[0], pos1[1], desX);

    }

}
int imprimeEstrutura::alturaArvoreBinaria(No* p, int nivel){

    int esq, dir;
    if(p == NULL){

        return nivel;

    }else{

        esq = alturaArvoreBinaria(p->getAnt(),nivel+1);
        dir = alturaArvoreBinaria(p->getProx(),nivel+1);
        if(esq > dir){

            return esq;

        }else{

            return dir;

        }

    }
}
void imprimeEstrutura::fechaJanela(){

    glutDestroyWindow(window);

}
int imprimeEstrutura::alturaArvore(){

    if(tipoEstrutura == ARVORE_BINARIA){

        return alturaArvoreBinaria(*aux,0);

    }else if(tipoEstrutura == ARVORE_BINARIA_CONTIGUA){

        return alturaArvoreBinariaCont(*NoCont,*ult);

    }else if(tipoEstrutura == ARVORE_B){

        if(*BTREE != NULL){

            return alturaArvoreB(*BTREE);

        }else{

            return 0;

        }

    }else if(tipoEstrutura == ARVORE_MULTIWAY){

        return alturaArvoreMultiWay(*MWTREE);

    }else if(tipoEstrutura == ARVORE_TRIE_TERNARIA){

        if(*TERTREE != NULL){

            return alturaTrieTernaria(*TERTREE,0);

        }else{

            return 0;

        }

    }else if(tipoEstrutura == ARVORE_HUFFMAN){

        if(*HUFTREE != NULL){

            return alturaHuffman(*HUFTREE,0);

        }else{

            return 0;

        }

    }else if(tipoEstrutura == ARVORE_VERMELHO_PRETA){

        if(*VPTREE != NULL){

            return alturaArvoreVermelhoPreta(*VPTREE,0);

        }else{

            return 0;

        }

    }
    return 0;

}
void imprimeEstrutura::setPriNoBinarioCont(int** tree, int* ultIndice){

    NoCont = tree;
    ult = ultIndice;
    altura = 0;
}
int imprimeEstrutura::alturaArvoreBinariaCont(int* tree, int ultIndice){

    int nivel = 0;
    int i = 0;
    int somatorio = 0;
    if(ultIndice == -1){

        return 0;

    }
    while(somatorio <= ultIndice){

        somatorio += pow(2,i) ;
        nivel++;
        i++;

    }
    return nivel;

}
void imprimeEstrutura::percorreBinariaCont(int* tree, int indiceAtual, int ultIndice, float x, float y, float desX){

    float pos1[2];
    float pos2[2];
    pos2[0] = x;
    pos2[1] = y;
    desX /= 2.0;
    float desY = 2.0;
    ostringstream oss;
    string valor;

    if((2 * indiceAtual) + 1 <= ultIndice){

        pos1[0] = pos2[0] - desX;
        pos1[1] = pos2[1] - desY;
        imprimeEstrutura::desenhaLinha(pos2,pos1);

    }if((2 * indiceAtual) + 2 <= ultIndice){

        pos1[0] = pos2[0] + desX;
        pos1[1] = pos2[1] - desY;
        imprimeEstrutura::desenhaLinha(pos2,pos1);

    }

    oss << tree[indiceAtual];
    valor = oss.str();
    desenhaNo(pos2,valor);
    if((2 * indiceAtual) + 1 <= ultIndice){

        pos1[0] = pos2[0] - desX;
        pos1[1] = pos2[1] - desY;
        percorreBinariaCont(tree,(2 * indiceAtual) + 1, ultIndice, pos1[0], pos1[1], desX);

    }if((2 * indiceAtual) + 2 <= ultIndice){

        pos1[0] = pos2[0] + desX;
        pos1[1] = pos2[1] - desY;
        percorreBinariaCont(tree,(2 * indiceAtual) + 2, ultIndice, pos1[0], pos1[1], desX);

    }

}
void imprimeEstrutura::setPriGraficoHashing(int* tabela, int tamTabela){

    graficoHashing = tabela;
    tamGrafico = tamTabela;

}
void imprimeEstrutura::percorreGraficoHashing(int* p, int tam){

    float pos1[] = {(float)(-tamGrafico*0.05),0.0};
    float pos2[] = {(float)(tamGrafico + tamGrafico*0.05),0.0};
    desenhaLinha(pos1,pos2);
    pos1[1] = -maior(graficoHashing,tamGrafico)*0.05;
    pos1[0] = 0.0;
    pos2[1] = maior(graficoHashing,tamGrafico) + maior(graficoHashing,tamGrafico)*0.05;
    pos2[0] = 0.0;
    desenhaLinha(pos1,pos2);
    ostringstream *oss;
    string valor;
    int MAIOR = maior(graficoHashing, tamGrafico);
    int cont = tamGrafico / 30;
    glColor3f(0.0,1.0,0.0);
    for(int i = 0; i < tamGrafico; i++){

        pos1[0] = (float)i;
        pos1[1] = 0.0;
        desenhaParteGrafico(graficoHashing[i],1.0,pos1);

    }
    glColor3f(1.0,0.0,0.0);
    for(int i = 0; i <= tamGrafico; i++){

        if(tamGrafico < 30){

            oss = new ostringstream();
            *oss << i;
            valor = oss->str();
            escreve((char*)valor.c_str(),(float)i,0.0);
            valor.clear();
            delete oss;

        }else{

            if((tamGrafico / 30) == cont){

                oss = new ostringstream();
                *oss << i;
                valor = oss->str();
                glColor3f(1.0,0.0,0.0);
                escreve((char*)valor.c_str(),(float)i,0.0);
                valor.clear();
                delete oss;
                cont = 0;

            }else{

                cont++;

            }


        }

    }
    cont = MAIOR / 50;
    for(int i = 0; i <= MAIOR; i++){

        if(MAIOR < 50){

            oss = new ostringstream();
            *oss << i;
            valor = oss->str();
            glColor3f(1.0,0.0,0.0);
            escreve((char*)valor.c_str(), 0.0, (float)i);
            valor.clear();
            delete oss;

        }else{

            if((MAIOR / 50) == cont){

                oss = new ostringstream();
                *oss << i;
                valor = oss->str();
                glColor3f(1.0,0.0,0.0);
                escreve((char*)valor.c_str(), 0.0, (float)i);
                valor.clear();
                delete oss;
                cont = 0;

            }else{

                cont++;

            }


        }

    }

}
void imprimeEstrutura::desenhaParteGrafico(float altura, float dx, float *pos){


    glBegin(GL_QUADS);

        glVertex3f(pos[0]+0.1,pos[1],0.0);
        glVertex3f(pos[0]+dx-0.1,pos[1],0.0);
        glVertex3f(pos[0]+dx-0.1,pos[1]+altura,0.0);
        glVertex3f(pos[0]+0.1,pos[1]+altura,0.0);

    glEnd();

}
int imprimeEstrutura::maior(int *vet, int tam){

    int maior = vet[0];
    for(int i = 1; i < tam; i++){

        if(vet[i] > maior){

            maior = vet[i];

        }
    }
    return maior;
}
void imprimeEstrutura::setPriHashingLista(Lista* l, int tamTabela){

    listaHashing = l;
    tamListaHashing = tamTabela;

}
void imprimeEstrutura::setPriListaEncadeada(No_Lista* l){

    listaEncadeada = l;

}
void imprimeEstrutura::desenhaNoLista(float* pos, string valor, float *cor){

    glColor3fv(cor);
    glBegin(GL_QUADS);

        glVertex3f(pos[0]-0.5,pos[1]-0.5, 0.0);
        glVertex3f(pos[0]+0.5,pos[1]-0.5, 0.0);
        glVertex3f(pos[0]+0.5,pos[1]+0.5, 0.0);
        glVertex3f(pos[0]-0.5,pos[1]+0.5, 0.0);

    glEnd();
    glColor3f(1.0, 1.0, 1.0);
    escreve((char*)valor.c_str(),pos[0]-0.3,pos[1]-0.1);

}
void imprimeEstrutura::desenhaSeta(float* pos1){

    glColor3f(0.0,0.0,0.0);
    if(listaHashing != NULL){

        glBegin(GL_LINES);
            glVertex3f(pos1[0],pos1[1], 0.0);
            glVertex3f(pos1[0],pos1[1]-1.5, 0.0);
        glEnd();
        glBegin(GL_TRIANGLES);
            glVertex3f(pos1[0]+0.1,pos1[1]-1.2, 0.0);
            glVertex3f(pos1[0]-0.1,pos1[1]-1.2, 0.0);
            glVertex3f(pos1[0],pos1[1]-1.5, 0.0);
        glEnd();

    }else{

        glBegin(GL_LINES);
            glVertex3f(pos1[0],pos1[1], 0.0);
            glVertex3f(pos1[0],pos1[1]+1.5, 0.0);
        glEnd();
        glBegin(GL_TRIANGLES);
            glVertex3f(pos1[0]+1.2,pos1[1]+0.2, 0.0);
            glVertex3f(pos1[0]+1.2,pos1[1]-0.2, 0.0);
            glVertex3f(pos1[0]+1.5,pos1[1], 0.0);
        glEnd();

    }

}
void imprimeEstrutura::percorreListaEncadeada(No_Lista* l, float *pos1){

    No_Lista* it = l;
    float cor[3];
    cor[0] = 0.0;
    cor[1] = 0.5;
    cor[2] = 0.0;
    stringstream *ss;
    if(listaHashing != NULL){

        ///Destaca a posicao do vetor com verde
        ss = new stringstream();
        *ss << it->info;
        desenhaSeta(pos1);
        desenhaNoLista(pos1,ss->str(),cor);
        delete ss;
        it = it->prox;
        pos1[1] -= 2.0;
        cor[0] = 0.0;
        cor[1] = 0.0;
        cor[2] = 1.0;
        if(it != NULL){

            while(it != NULL){

                ss = new stringstream();
                *ss << it->info;
                if(it->prox != NULL){

                    desenhaSeta(pos1);

                }
                desenhaNoLista(pos1,ss->str(),cor);
                delete ss;
                it = it->prox;
                pos1[1] -= 2.0;

            }

        }

    }else{
        cor[0] = 0.0;
        cor[1] = 0.0;
        cor[2] = 1.0;
        while(it != NULL){

            ss = new stringstream();
            *ss << it->info;
            if(it->prox != NULL){

                desenhaSeta(pos1);

            }
            desenhaNoLista(pos1,ss->str(),cor);
            delete ss;
            it = it->prox;
            pos1[0] += 2.0;

        }

    }


}
void imprimeEstrutura::percorreHashingLista(Lista* l, int tam, float *posH){

    float YY = posH[1];
    float pos2[2];
    int i;
    for(i = 0; i < tam -1; i++){

        posH[0] += 1.5;
        posH[1] = YY;
        glColor3f(0.0,0.0,0.0);
        pos2[0] = posH[0] + 1.5;
        pos2[1] = posH[1];
        desenhaBarra(posH,pos2);
        percorreListaEncadeada(l[i].begin(),posH);


    }
    posH[0] += 1.5;
    posH[1] = YY;
    percorreListaEncadeada(l[i].begin(),posH);

}
void imprimeEstrutura::desenhaBarra(float *pos1, float *pos2){

    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_QUADS);
            glVertex3f(pos1[0],pos1[1]-0.3,0.0);
            glVertex3f(pos1[0],pos1[1]+0.3,0.0);
            glVertex3f(pos2[0],pos2[1]+0.3,0.0);
            glVertex3f(pos2[0],pos2[1]-0.3,0.0);
        glEnd();
    glPopMatrix();

}
void imprimeEstrutura::setPriVetor(int** i, int* tam, float **cor){

    vet = i;
    tamVet = tam;
    cores = cor;

}
void imprimeEstrutura::percorreVetor(float *posVetor){

    int i;
    float cor[] = {0.0, 0.0, 1.0};
    float posH[2];
    posH[1] = posVetor[1];
    stringstream *ss;
    for(i = 0; i < *tamVet; i++){
        posH[0] = posVetor[0] + 1.0;
        if(cores != NULL){

            posH[0] += cores[i][3];

        }
        ss = new stringstream();
        *ss << vet[0][i];
        if(i+1 < *tamVet){

            desenhaBarra(posVetor, posH);

        }
        if(cores != NULL){

            cor[0] = cores[i][0];
            cor[1] = cores[i][1];
            cor[2] = cores[i][2];

        }
        desenhaNoLista(posVetor, ss->str(),cor);
        glColor3f(0.0, 0.0, 0.0);
        delete ss;
        ss = new stringstream();
        *ss << i;
        escreve((char*)ss->str().c_str(),posVetor[0]-0.1,posVetor[1]+0.5);
        posVetor[0] += 1.1;
        if(cores != NULL){

            posVetor[0] += cores[i][3];

        }
        delete ss;

    }

}
void imprimeEstrutura::espera(void){

    while((((clock()-inicio)/CLOCKS_PER_SEC) < wait)||(pause == true)){}
    pause = false;

}
void imprimeEstrutura::setPriHeapBinomial(No_Binomial** b){

    Binomial = b;

}
void imprimeEstrutura::percorreHeapBinomial(float *posHeap, No_Binomial* n){

    percorreHeapBk(posHeap,NULL,n);

}
float imprimeEstrutura::retornaDistanciaHeapBinomial(No_Binomial *n){

    if(n->getGrau() == 0){

        return 1.5;

    }else{

        return (pow(2,n->getGrau()-1))*1.5;

    }

}
void imprimeEstrutura::percorreHeapBk(float *posHeap, float *posPai, No_Binomial* n){

    stringstream *ss = new stringstream;
    float aux[2];
    float aux2[2];
    aux[0] = posHeap[0];
    aux[1] = posHeap[1];
    aux2[0] = posHeap[0];
    aux2[1] = posHeap[1];
    if(n != NULL){

        if(posPai != NULL){

            desenhaLinha(posPai,posHeap);

        }
        if(n->getFilho() != NULL){
            aux2[1] -= 1.5;
            percorreHeapBk(aux2,posHeap,n->getFilho());

        }
        if(n->getIrmao() != NULL){

            posHeap[0] += retornaDistanciaHeapBinomial(n);

            percorreHeapBk(posHeap,posPai,n->getIrmao());

        }
        ///Desenha o no n depois de ter desenhado as linhas
        *ss << n->getValor();
        desenhaNo(aux,ss->str());
        delete ss;

    }


}
void imprimeEstrutura::desenhaLinhasHeapBinomial(float *posHeap, int grau){

    float cont = 0.0;
    float posAux[2];
    while(cont <= grau){

        posAux[0] = posHeap[0] + cont;
        posAux[1] = posHeap[1] - 1.5;
        desenhaLinha(posHeap,posAux);
        cont = cont + 1.5;

    }


}
void imprimeEstrutura::setARGS(int argc, char* argv[]){

    ARGC = argc;
    ARGV = argv;

}
imprimeEstrutura::imprimeEstrutura(const int TIPO){

    cout<<"ImprimeEstrutura"<<endl;
    cout<<"Versao: 1.3 -> 20-06-2016"<<endl<<endl;
    cout<<"Comandos: "<<endl;
    cout<<"'f' -> fullscreen;"<<endl;
    cout<<"'e' -> finaliza aplicacao;"<<endl;
    cout<<"'p' -> pausa a animacao corrente;"<<endl;
    cout<<"'mouse scroll' -> zoom;"<<endl;
    cout<<"'clique e arraste' -> move a estrutura pela janela."<<endl<<endl;
    tipoEstrutura = TIPO;

}
void imprimeEstrutura::finalizaImpressao(){

    t1->join();

}
void imprimeEstrutura::espere(int tempo){

    wait = tempo;
    inicio = clock();
    espera();

}
void imprimeEstrutura::idle(void){

    altura = alturaArvore();
    glutPostRedisplay();

}
void imprimeEstrutura::desenhaNoB(float *posB,int* valores, int tam){

    stringstream *ss;
    float posAux[2];
    glPushMatrix();
        glColor3f(0.8,0.0,0.0);
        glBegin(GL_QUADS);

            glVertex3f(posB[0]-tam/2,posB[1]-0.5,0.0);
            glVertex3f(posB[0]+tam/2,posB[1]-0.5,0.0);
            glVertex3f(posB[0]+tam/2,posB[1]+0.5,0.0);
            glVertex3f(posB[0]-tam/2,posB[1]+0.5,0.0);

        glEnd();

    glPopMatrix();
    posAux[0] = posB[0] - tam/2 + 0.5;
    posAux[1] = posB[1];
    for(int i = 0; i < tam; i++){
        ss = new stringstream;
        *ss << valores[i];
        desenhaNo(posAux,ss->str());
        posAux[0] += 1;
        delete ss;
    }

}
void imprimeEstrutura::percorreB(float* posB, No_B* n, float dist){


    desenhaLinhasB(posB, n, dist);
    desenhaNoB(posB,n->chave,MAX);
    percorreArvoreB(posB, n, dist);

}
void imprimeEstrutura::percorreArvoreB(float *posB, No_B* n, float dist){

    float posAux[2];
    posAux[1] = posB[1] - MAX;
    float distX = pow(MAX+1,dist);
    posAux[0] = posB[0] - distX/2;
    distX /= (float)MAX;
    if(n == NULL) return;
    for(int i = 0; i < MAX + 2; i++){

        if(n->filho[i] != NULL){

            desenhaNoB(posAux,n->filho[i]->chave,MAX);

        }
        posAux[0] += distX;

    }
    posAux[0] = posB[0] - pow(MAX+1,dist)/2;
    for(int i = 0; i < 6; i++){

        percorreArvoreB(posAux, n->filho[i], dist-1);
        posAux[0] += distX;

    }

}
void imprimeEstrutura::setPriArvoreB(No_B **b){

    BTREE = b;

}
int imprimeEstrutura::alturaArvoreB(No_B *b){

    int alt = 0, aux;
    for(int i = 1; b->filho[i] != NULL; i++){

        aux = alturaArvoreB(b->filho[i]);
        if(aux > alt) alt = aux;

    }
    return (alt + 1);
}
void imprimeEstrutura::desenhaLinhasB(float *posB, No_B* n, float dist){

    float posAux[2];
    posAux[1] = posB[1] - MAX;
    float distX = pow(MAX+1,dist);
    posAux[0] = posB[0] - distX/2;
    distX /= (float)MAX;
    if (n == NULL)return;
    for(int i = 0; i < MAX + 2; i++){

        if(n->filho[i] != NULL){

            desenhaLinha(posB,posAux);
            desenhaLinhasB(posAux, n->filho[i], dist-1);

        }
        posAux[0] += distX;

    }
}
void imprimeEstrutura::percorreMultiWay(float *posMW, No_MW* n, float dist){

    float posAux[2];
    float posAuxL[2];
    float distX = pow(n->getTamAlfa(),dist);
    posAux[0] = posMW[0] - distX/2.0;
    distX /= (float)n->getTamAlfa();
    posAux[0] += distX/2.0;
    posAux[1] = posMW[1] - 3;
    desenhaNoMW(posMW,n->getTamAlfa(),n->getChave());
    posAuxL[0] = posMW[0] - n->getTamAlfa()/2.0;
    posAuxL[0] += 0.5;
    posAuxL[1] = posMW[1];
    posAuxL[1] -= 0.25;
    for(int i = 0; i < n->getTamAlfa(); i++){


        if(n->getChar(97 + i) != NULL){

            desenhaLinha(posAuxL,posAux);
            percorreMultiWay(posAux,n->getChar(97 + i),dist-1);

        }
        posAux[0] += distX;
        posAuxL[0] += 1.0;

    }

}
void imprimeEstrutura::setPriArvoreMultiWay(No_MW **m){

    MWTREE = m;

}
void imprimeEstrutura::desenhaNoMW(float *posMW, int tam, bool ehChave){

    float dx = posMW[0] - tam/2.0;
    char p[2];
    float cont = 0.5;
    if(ehChave){

        glColor3f(0.0,1.0,0.0);

    }else{

        glColor3f(0.0,0.0,1.0);

    }
    glBegin(GL_QUADS);

        glVertex3f(posMW[0]-(tam/2.0),posMW[1] - 0.5,0.0);
        glVertex3f(posMW[0]+(tam/2.0),posMW[1] - 0.5,0.0);
        glVertex3f(posMW[0]+(tam/2.0),posMW[1] + 0.7,0.0);
        glVertex3f(posMW[0]-(tam/2.0),posMW[1] + 0.7,0.0);

    glEnd();
    glColor3f(0.0,0.0,0.0);
    for(int i = 0; i <= tam; i++){

        glBegin(GL_QUADS);

            glVertex3f((dx + i) - 0.04, posMW[1] - 0.5, 0.0);
            glVertex3f((dx + i) + 0.04, posMW[1] - 0.5, 0.0);
            glVertex3f((dx + i) + 0.04, posMW[1] + 0.7, 0.0);
            glVertex3f((dx + i) - 0.04, posMW[1] + 0.7, 0.0);

        glEnd();

    }
    glBegin(GL_QUADS);

        glVertex3f(posMW[0] - tam/2.0, posMW[1] - 0.04, 0.0);
        glVertex3f(posMW[0] + tam/2.0, posMW[1] - 0.04, 0.0);
        glVertex3f(posMW[0] + tam/2.0, posMW[1] + 0.04, 0.0);
        glVertex3f(posMW[0] - tam/2.0, posMW[1] + 0.04, 0.0);

    glEnd();
    glBegin(GL_QUADS);

        glVertex3f(posMW[0] - tam/2.0, posMW[1] + 0.62, 0.0);
        glVertex3f(posMW[0] + tam/2.0, posMW[1] + 0.62, 0.0);
        glVertex3f(posMW[0] + tam/2.0, posMW[1] + 0.7, 0.0);
        glVertex3f(posMW[0] - tam/2.0, posMW[1] + 0.7, 0.0);

    glEnd();
    p[1] = '\0';
    glColor3f(1.0,1.0,1.0);
    for(int i = 0; i < tam; i++){

        p[0] = 97 + i;
        escreve(p,dx + cont, posMW[1] + 0.35);
        cont += 1.0;

    }

}
int imprimeEstrutura::alturaArvoreMultiWay(No_MW *n){

    int alt = 0, aux;
    for(int i = 0; i < n->getTamAlfa(); i++){

        if(n->getChar(97 + i) != NULL){

            aux = alturaArvoreMultiWay(n->getChar(97 + i));
            if(aux > alt){

                alt = aux;

            }

        }

    }
    return (alt + 1);

}
void imprimeEstrutura::percorreTernaria(float* posTer, No_Ter *p, float desX){

    float pos1[2];
    float pos2[2];
    pos2[0] = posTer[0];
    pos2[1] = posTer[1];
    desX /= 3.0;
    float desY = 2.0;
    string valor;

    if(p->getEsq() != NULL){

        pos1[0] = pos2[0] - desX;
        pos1[1] = pos2[1] - desY;
        desenhaLinha(pos2,pos1);

    }if(p->getDir() != NULL){

        pos1[0] = pos2[0] + desX;
        pos1[1] = pos2[1] - desY;
        desenhaLinha(pos2,pos1);

    }if(p->getMeio() != NULL){

        pos1[0] = pos2[0];
        pos1[1] = pos2[1] - desY;
        desenhaLinha(pos2,pos1);

    }

    valor.push_back(p->getChar());
    if(p->getChave()){

        desenhaNoCor(pos2,valor,0.0,1.0,0.0);

    }else{

        desenhaNoCor(pos2,valor,0.0,0.0,1.0);

    }
    if(p->getEsq() != NULL){

        pos1[0] = pos2[0] - desX;
        pos1[1] = pos2[1] - desY;
        percorreTernaria(pos1,p->getEsq(), desX);

    }if(p->getDir() != NULL){

        pos1[0] = pos2[0] + desX;
        pos1[1] = pos2[1] - desY;
        percorreTernaria(pos1,p->getDir(), desX);

    }if(p->getMeio() != NULL){

        pos1[0] = pos2[0];
        pos1[1] = pos2[1] - desY;
        percorreTernaria(pos1, p->getMeio(), desX);

    }

}
void imprimeEstrutura::setPriTrieTer(No_Ter** p){

    TERTREE = p;

}
int imprimeEstrutura::alturaTrieTernaria(No_Ter *p, int nivel){


    int esq, dir, meio;
    if(p == NULL){

        return nivel;

    }else{

        esq = alturaTrieTernaria(p->getEsq(),nivel+1);
        dir = alturaTrieTernaria(p->getDir(),nivel+1);
        meio = alturaTrieTernaria(p->getMeio(),nivel+1);
        if(meio > esq && meio > dir)return meio;
        else if(dir > esq && dir > meio)return dir;
        else return esq;

    }

}
void imprimeEstrutura::desenhaNoCor(float* pos, string valor, float red, float green, float blue){

    int numSeg = 32;
    float segmento = 2*M_PI/(float)numSeg;
    float tamanhoValor;
    glColor3f(red,green,blue);
    glBegin(GL_TRIANGLE_FAN);

        glVertex3f(pos[0],pos[1],0.0);
        for(int i = 0; i <= numSeg; i++){

            glVertex3f(pos[0]+raio*cos(segmento*i),pos[1]+raio*sin(segmento*i),0.0);

        }

    glEnd();
    tamanhoValor = valor.size();
    while(tamanhoValor > 0.9){tamanhoValor = tamanhoValor/10.0;}
    tamanhoValor -= 0.1;
    glColor3f(1.0,1.0,1.0);
    escreve((char*)valor.c_str(),pos[0] - tamanhoValor,pos[1]-0.09);

}
void imprimeEstrutura::desenhaLinhasTernaria(float *posTer, No_Ter *n,float dist){

    float posAux[2];
    float posPar[2];
    float distX = pow(3,dist);
    No_Ter* aux;
    aux = n;
    posAux[0] = posTer[0];
    posAux[1] = posTer[1];
    posPar[0] = posTer[0];
    posPar[1] = posTer[1];
    while (aux != NULL){

        desenhaLinha(posPar,posAux);
        posPar[0] = posAux[0];
        if(aux->getMeio() != NULL){

            posAux[1] -= 2.0;
            desenhaLinha(posPar,posAux);
            desenhaLinhasTernaria(posAux,aux->getMeio(),dist-1);
            posAux[1] += 2.0;

        }
        posPar[0] = posAux[0];
        posAux[0] += distX;
        aux = aux->getDir();

    }
    posAux[0] = posTer[0];
    posPar[0] = posTer[0];
    aux = n->getEsq();
    while (aux != NULL){

        posAux[0] -= distX;
        desenhaLinha(posPar,posAux);
        posPar[0] = posAux[0];
        if(aux->getMeio() != NULL){

            posAux[1] -= 2.0;
            desenhaLinha(posPar,posAux);
            desenhaLinhasTernaria(posAux,aux->getMeio(),dist-1);
            posAux[1] += 2.0;

        }
        posPar[0] = posAux[0];
        aux = aux->getEsq();

    }

}
void imprimeEstrutura::setPriHuffmanTree(No_HUF** h){

    HUFTREE = h;

}
void imprimeEstrutura::percorreHuffman(float* posH,No_HUF *h, float desX){

    float pos1[2];
    float pos2[2];
    pos2[0] = posH[0];
    pos2[1] = posH[1];
    desX /= 2.0;
    float desY = 2.0;
    ostringstream oss;
    string valor;

    if(h->getEsq() != NULL){

        pos1[0] = pos2[0] - desX;
        pos1[1] = pos2[1] - desY;
        desenhaLinha(pos2,pos1);

    }if(h->getDir() != NULL){

        pos1[0] = pos2[0] + desX;
        pos1[1] = pos2[1] - desY;
        desenhaLinha(pos2,pos1);

    }

    oss << h->getFreq();
    valor = oss.str();
    if(h->getChar() == 0){

        desenhaNo(pos2,valor);

    }else{

        desenhaNoHuffman(pos2,h->getFreq(),h->getChar());

    }
    if(h->getEsq() != NULL){

        pos1[0] = pos2[0] - desX;
        pos1[1] = pos2[1] - desY;
        percorreHuffman(pos1, h->getEsq(), desX);

    }if(h->getDir() != NULL){

        pos1[0] = pos2[0] + desX;
        pos1[1] = pos2[1] - desY;
        percorreHuffman(pos1, h->getDir(), desX);

    }

}
int imprimeEstrutura::alturaHuffman(No_HUF *h, int nivel){

    int esq, dir;
    if(h == NULL){

        return nivel;

    }else{

        esq = alturaHuffman(h->getEsq(),nivel+1);
        dir = alturaHuffman(h->getDir(),nivel+1);
        if(esq > dir){

            return esq;

        }else{

            return dir;

        }

    }

}
void imprimeEstrutura::desenhaNoHuffman(float *posH, int freq, char c){

    char p[2];
    p[1]='\0';
    glColor3f(0.0,0.5,0.0);
    glBegin(GL_QUADS);

        glVertex3f(posH[0]-raio,posH[1]-2*raio,0.0);
        glVertex3f(posH[0]+raio,posH[1]-2*raio,0.0);
        glVertex3f(posH[0]+raio,posH[1]+2*raio,0.0);
        glVertex3f(posH[0]-raio,posH[1]+2*raio,0.0);

    glEnd();
    glColor3f(1.0,1.0,1.0);
    p[0] = c;
    escreve(p,posH[0],posH[1]+raio);
    ostringstream oss;
    oss << freq;
    escreve((char*)oss.str().c_str(),posH[0],posH[1]-raio);
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_QUADS);

        glVertex3f(posH[0]-raio,posH[1]-(raio/5),0.0);
        glVertex3f(posH[0]+raio,posH[1]-(raio/5),0.0);
        glVertex3f(posH[0]+raio,posH[1]+(raio/5),0.0);
        glVertex3f(posH[0]-raio,posH[1]+(raio/5),0.0);

    glEnd();

}
void imprimeEstrutura::setPriArvoreVermelhoPreta(No_VP** v){

    VPTREE = v;

}
void imprimeEstrutura::percorreVermelhoPreta(No_VP* p, float x, float y, float desX){

    float pos1[2];
    float pos2[2];
    pos2[0] = x;
    pos2[1] = y;
    desX /= 2.0;
    float desY = 2.0;
    ostringstream oss;
    string valor;

    if(p->getAnt() != NULL){

        pos1[0] = pos2[0] - desX;
        pos1[1] = pos2[1] - desY;
        desenhaLinha(pos2,pos1);

    }if(p->getProx() != NULL){

        pos1[0] = pos2[0] + desX;
        pos1[1] = pos2[1] - desY;
        desenhaLinha(pos2,pos1);

    }

    oss << p->getValor();
    valor = oss.str();
    if(p->getCor() == VERMELHO){

        desenhaNo(pos2,valor,VERMELHO);

    }else{

        desenhaNo(pos2,valor,PRETO);

    }
    if(p->getAnt() != NULL){

        pos1[0] = pos2[0] - desX;
        pos1[1] = pos2[1] - desY;
        percorreVermelhoPreta(p->getAnt(), pos1[0], pos1[1], desX);

    }if(p->getProx() != NULL){

        pos1[0] = pos2[0] + desX;
        pos1[1] = pos2[1] - desY;
        percorreVermelhoPreta(p->getProx(), pos1[0], pos1[1], desX);

    }

}
int imprimeEstrutura::alturaArvoreVermelhoPreta(No_VP* p, int nivel){

    int esq, dir;
    if(p == NULL){

        return nivel;

    }else{

        esq = alturaArvoreVermelhoPreta(p->getAnt(),nivel+1);
        dir = alturaArvoreVermelhoPreta(p->getProx(),nivel+1);
        if(esq > dir){

            return esq;

        }else{

            return dir;

        }

    }

}
