#ifndef NO_B_H
#define NO_B_H

const int t = 2 ;

const int MAX = 2 * t;
const int MIN = t;


class No_B
{
public:
    No_B(){

        for(int i = 0; i <= MAX; i++){

            chave[i] = 0;
            filho[i] = NULL;

        }
        filho[MAX+1] = NULL;
        tamanho = 0;

    }
    ~No_B(){}
    int getPos(int valor){

        for(int i = 0; i < tamanho; i++){

            if(chave[i] == valor) return i;

        }
        return -1;

    }///Retorna a posicao do 'valor' no vetor chave.
    int tamanho;
    int chave[MAX + 1]; /// Para facilitar, os nós permitem uma chave a mais (buffer na posição MAX).
    No_B * filho[MAX + 2];
};

#endif // NO_B_H
