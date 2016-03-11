#include "Huffman_Lista.h"


Huffman_Lista::Huffman_Lista()
{
    priLista = NULL;
    ultLista = NULL;

}
void Huffman_Lista::insere(char c, int f){///insere um caracter sempre no final da lista e se ele ja existir, apenas atualiza sua frequencia

    if(priLista == NULL){

        priLista = new No_HUF();
        priLista->setChar(c);
        priLista->setFreq(f);
        ultLista = priLista;

    }else{

        No_HUF *aux = priLista;
        while(aux != NULL && aux->getChar() != c){aux = aux->getProx();}
        if(aux == NULL){

            ultLista->setProx(new No_HUF());
            ultLista = ultLista->getProx();
            ultLista->setChar(c);
            ultLista->setFreq(f);

        }else{

            aux->setFreq(aux->getFreq()+f);

        }

    }

}
No_HUF* Huffman_Lista::getMenor(){///retorna o no da lista com menor frequencia

    No_HUF *aux = priLista;
    No_HUF *aux2 = priLista;
    if(aux->getProx() == NULL){

        retiraLista(aux);
        return aux;

    }else{

        while(aux != NULL){

            if(aux->getFreq() < aux2->getFreq()){

                aux2 = aux;

            }
            aux = aux->getProx();

        }

    }
    if(aux2 != NULL){

        retiraLista(aux2);

    }
    return aux2;


}
void Huffman_Lista::geraArvore(){///gera a arvore de huffman

    No_HUF *aux;
    while(priLista != NULL){

        aux = new No_HUF();
        aux->setEsq(getMenor());
        aux->setDir(getMenor());
        aux->setFreq(aux->getDir()->getFreq()+aux->getEsq()->getFreq());
        ultLista->setProx(aux);
        ultLista = aux;

    }
    priLista = aux;

}
void Huffman_Lista::retiraLista(No_HUF *n){///retira um no n especificado da lista

    No_HUF* aux = priLista;
    if(n == aux){

        priLista = aux->getProx();

    }else{

        while(aux->getProx() != n){

            aux = aux->getProx();

        }
        aux->setProx(n->getProx());
        if(n->getProx() == NULL){

            ultLista = aux;

        }

    }


}
string Huffman_Lista::codificar(string s){

    string codigo;
    if(priLista == NULL){

        string::iterator it;
        it = s.begin();
        while(it != s.end()){

            insere(*it,1);
            it++;

        }
        geraArvore();
        gerarCodigos(codigo,priLista);
        imprimirCodigoChars();
        return gerarCodigoString(s);

    }else{

        cout << "Huffman estatico já foi criado, impossivel codificar " << s <<endl;

    }
    return codigo;

}
void Huffman_Lista::imprimirCodigoChars(){

    for(int i = 0; i < 26; i++){

        if(codigosLow[i].size() > 0){

            cout << "O codigo do caracter " << (char)(97+i) << " eh " << codigosLow[i] <<endl;

        }

    }
    for(int i = 0; i < 26; i++){

        if(codigosUp[i].size() > 0){

            cout << "O codigo do caracter " << (char)(65+i) << " eh " << codigosUp[i] <<endl;

        }

    }
    for(int i = 0; i < 5; i++){

        if(codigosAcentos[i].size() > 0){

            if(i == 0){

                cout << "O codigo do caracter " << " , " << " eh " << codigosAcentos[i] <<endl;

            }else if(i == 1){

                cout << "O codigo do caracter " << (char)(65+i) << " eh " << codigosAcentos[i] <<endl;

            }else if(i == 2){

                cout << "O codigo do caracter " << " /espaco/ " << " eh " << codigosAcentos[i] <<endl;

            }else if(i == 3){

                cout << "O codigo do caracter " << " ? " << " eh " << codigosAcentos[i] <<endl;

            }else if(i == 4){

                cout << "O codigo do caracter " << " ! " << " eh " << codigosAcentos[i] <<endl;

            }
        }
    }


}
No_HUF** Huffman_Lista::getArvore(){

    return &priLista;

}
void Huffman_Lista::gerarCodigos(string s,No_HUF *n){

    if(n != NULL){

        if(n->getChar() != 0){

            if(n->getChar() >= 97 && n->getChar() <= 122){

                codigosLow[n->getChar() - 97] = s;

            }else if(n->getChar() >= 65 && n->getChar() <=90){

                codigosUp[n->getChar() - 65] = s;

            }else{

                if(n->getChar() == ','){

                    codigosAcentos[0] = s;

                }else if(n->getChar() == '.'){

                    codigosAcentos[1] = s;

                }else if(n->getChar() == ' '){

                    codigosAcentos[2] = s;

                }else if(n->getChar() == '?'){

                    codigosAcentos[3] = s;

                }else if(n->getChar() == '!'){

                    codigosAcentos[4] = s;

                }

            }

       }else{

            if(n->getDir() != NULL){

                s.push_back('1');
                gerarCodigos(s,n->getDir());
                s.erase(s.end()-1);

            }
            if(n->getEsq() != NULL){

                s.push_back('0');
                gerarCodigos(s,n->getEsq());
                s.erase(s.end()-1);


            }

       }

    }

}
string Huffman_Lista::gerarCodigoString(string s){

        string *codigo = new string;
        string::iterator it = s.begin();
        while(it != s.end()){

            if(*it >= 97 && *it <= 122){

                *codigo += codigosLow[*it - 97];

            }else if(*it >= 65 && *it <= 90){

                *codigo += codigosUp[*it - 65];

            }else{

                if(*it == ','){

                    *codigo += codigosAcentos[0];

                }else if(*it == '.'){

                    *codigo += codigosAcentos[1];

                }else if(*it == ' '){

                    *codigo += codigosAcentos[2];

                }else if(*it == '?'){

                    *codigo += codigosAcentos[3];

                }else if(*it == '!'){

                    *codigo += codigosAcentos[4];

                }

            }
        it++;
        }
    return *codigo;
}
string Huffman_Lista::decodificar(string s){

    No_HUF *aux = priLista;
    string::iterator it = s.begin();
    string decodificado;
    while(it != s.end()+1){

        if(aux->getChar() != 0){

            decodificado.push_back(aux->getChar());
            aux = priLista;

        }else{

            if(*it == '1'){

                aux = aux->getDir();

            }else if(*it == '0'){

                aux = aux->getEsq();

            }
            it++;

        }
    }
    return decodificado;

}
void Huffman_Lista::deletaH(No_HUF* n){

    if(n != NULL){

        deletaH(n->getDir());
        deletaH(n->getEsq());
        delete n;

    }


}
Huffman_Lista::~Huffman_Lista()
{
    deletaH(priLista);
}
