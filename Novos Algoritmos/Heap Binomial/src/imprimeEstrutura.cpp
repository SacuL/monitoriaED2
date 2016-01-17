#include <stdio.h>
#include <GL/glut.h>
#include <string>
#include <iostream>
#include <sstream>
#include "No.h"
#include "imprimeEstrutura.h"
#include <math.h>
#include <time.h>
//#define M_PI 3.14159265359
#include <thread>

using namespace std;
No* aux;
bool pause = false;
float pos[] = {10.0,11.0};
float raio = 0.4;
int altura;
int posx = -1;
int posy = -1;
float XYcart = 20.0;
int window;
int tipoEstrutura;
int* graficoHashing;//Ponteiro para a tabela de contagem de colisoes de um hashing
int tamGrafico;//
int* NoCont;//Ponteiro para o vetor da arvore contigua
int ult;//Ultimo indice da arvore contigua
float dx = 0.0, dy = 0.0;
Lista* listaHashing;
int tamListaHashing;
No_Lista* listaEncadeada;
int* vet;
int tamVet;
heapBinomial* Binomial;
No_Binomial* priBinomial;
int auxWait;
int ARGC;
char** ARGV;
char* nomeJanela;
thread *t1;
clock_t inicio;
int wait;

void imprimeEstrutura::inicializa(){

    ///Callbacks OpenGl
   glutInit(&ARGC, ARGV);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
   glutInitWindowSize (1000, 600);
   glutInitWindowPosition (100, 100);
   //glutSetOption(0X01F9,1);
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
void imprimeEstrutura::desenhaNo(float* pos, string valor){

    int numSeg = 32;
    float segmento = 2*M_PI/(float)numSeg;
    float tamanhoValor;
    glColor3f(0.0,0.0,1.0);
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
   if(tipoEstrutura == 1 || tipoEstrutura == 2 || tipoEstrutura == 5 || tipoEstrutura == 4 || tipoEstrutura == 6 || tipoEstrutura == 7){

        glOrtho(0.0, XYcart, 0.0, XYcart*(3.0/5.0), -10.0, 10.0);

   }else if(tipoEstrutura == 3){

        glOrtho(-(tamGrafico*0.05), tamGrafico + tamGrafico*0.05, -maior(graficoHashing, tamGrafico)*0.05, maior(graficoHashing, tamGrafico) + maior(graficoHashing, tamGrafico)*0.05, -10.0, 10.0);

   }
   glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
   glLoadIdentity();

    glEnable(GLUT_MULTISAMPLE);

    if(tipoEstrutura == 1){

        if(aux == NULL){

            cout << "Ponteiro para a raiz da arvore esta vazio, verifique se voce apontou a estrutura para a raiz da arvore a ser imprimida" << endl;

        }else{

            percorreBinaria(aux, pos[0], pos[1], pow(2.0,(altura-2)));

        }

    }else if(tipoEstrutura == 2){

        if(NoCont == NULL){

            cout << "Ponteiro para a raiz da arvore esta vazio, verifique se voce apontou a estrutura para a raiz da arvore a ser imprimida" << endl;

        }else{

            percorreBinariaCont(NoCont, 0, ult, pos[0], pos[1], pow(2.0,(altura-2)));

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
            percorreHeapBinomial(pos1,Binomial->cabeca);

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

    }
}
void imprimeEstrutura::setPriNoBinario(No* p){

    aux = p;
    tipoEstrutura = tipo;
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
        imprimeEstrutura::desenhaLinha(pos2,pos1);

    }if(p->getProx() != NULL){

        pos1[0] = pos2[0] + desX;
        pos1[1] = pos2[1] - desY;
        imprimeEstrutura::desenhaLinha(pos2,pos1);

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
No* imprimeEstrutura::getPriBinario(){

    return priBinario;

}
int imprimeEstrutura::alturaArvore(){

    if(tipo == 1){

        return alturaArvoreBinaria(priBinario,0);

    }else if(tipo == 2){

        cout << "ultimo indice carregado "<<ultIndiceCont <<endl;
        return alturaArvoreBinariaCont(priBinarioCont,ultIndiceCont);

    }else{

        cout<<"Talvez voce selecionou uma estrutura nao suportada quando inicializou a estrutura";
        exit(1);

    }

}
void imprimeEstrutura::setPriNoBinarioCont(int* tree, int ultIndice){

    NoCont = tree;
    ult = ultIndice;
    altura = alturaArvore();

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
            glVertex3f(pos1[0]+1.5,pos1[1]+0.3,0.0);
            glVertex3f(pos1[0]+1.5,pos1[1]-0.3,0.0);
        glEnd();
    glPopMatrix();

}
void imprimeEstrutura::setPriVetor(int* i, int tam){

    vet = i;
    tamVet = tam;

}
void imprimeEstrutura::percorreVetor(float *posVetor){
    int i;
    float cor[] = {0.0, 0.0, 1.0};
    float posH[2];
    posH[0] = posVetor[0] + 2.0;
    posH[1] = posVetor[1];
    stringstream *ss;
    for(i = 0; i < tamVet; i++){

        ss = new stringstream();
        *ss << vet[i];
        if(i+1 < tamVet){

            desenhaBarra(posVetor, posH);

        }
        desenhaNoLista(posVetor, ss->str(),cor);
        glColor3f(0.0, 0.0, 0.0);
        delete ss;
        ss = new stringstream();
        *ss << i;
        escreve((char*)ss->str().c_str(),posVetor[0]-0.3,posVetor[1]+0.5);
        posVetor[0] += 2.0;
        delete ss;

    }

}
void imprimeEstrutura::espera(void){

    while((((clock()-inicio)/CLOCKS_PER_SEC) < wait)||(pause == true)){}
    pause = false;

}
void imprimeEstrutura::setHeapBinomial(heapBinomial* b){

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

    glutPostRedisplay();

}
