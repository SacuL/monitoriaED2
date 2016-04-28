#ifndef NO_B_H
#define NO_B_H

const int t = 2 ;

const int MAX = 2 * t;
const int MIN = t;


class No_B
{
public:
    //bool folha;
    int tamanho;
    int chave[MAX + 1]; // Para facilitar, os nós permitem uma chave a mais (buffer na posição 0).
    No_B * filho[MAX + 1];
};

#endif // NO_B_H
