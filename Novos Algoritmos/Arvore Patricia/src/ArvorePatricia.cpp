#include <ArvorePatricia.h>

ArvorePatricia::ArvorePatricia(int tamAlfabeto)
{
    raiz = NULL;
    tamAlfa = tamAlfabeto;
}
void ArvorePatricia::inserir(string c){

    if(raiz == NULL){

        raiz = new No_PAT(tamAlfa);
        raiz->setChave(c);

    }else{

        No_PAT* aux = insereRecursivo(c,0,raiz);
        if(aux != raiz){

            if(aux != NULL){

                aux->setFilho(aux->getChave().at(0),raiz);
                aux->clearChave();
                raiz = aux;

            }

        }

    }

}
No_PAT* ArvorePatricia::insereRecursivo(string c, int pos, No_PAT *p){

    if(p->getPosPref() == -1){

        int desv = diferencaStrings(c,p->getChave(),0);
        No_PAT *n = new No_PAT(p->getTamAlfa());
        if(desv >= pos){

            n->setChave(p->getChave());
            p->setFilho(getString(n->getChave(),desv),n);
            p->clearChave();
            n = new No_PAT(tamAlfa);
            n->setChave(c);
            p->setFilho(getString(c,desv),n);
            p->setPosPref(desv);
            return NULL;

        }else{

            No_PAT *aux = new No_PAT(p->getTamAlfa());
            n->setPosPref(desv);
            string auxS;
            auxS.push_back(p->getChave().at(desv));
            n->setChave(auxS);
            aux->setChave(c);
            n->setFilho(getString(c,desv),aux);
            return n;

        }

    }else{

        No_PAT *aux = p->getFilho(getString(c,p->getPosPref()));
        if(aux == NULL){

            aux = new No_PAT(p->getTamAlfa());
            aux->setChave(c);
            p->setFilho(getString(c,p->getPosPref()),aux);
            return NULL;

        }else{

            aux = insereRecursivo(c,p->getPosPref(),aux);
            if(aux != NULL){

                if(aux->getPosPref() < p->getPosPref()){

                    return aux;

                }else{

                    No_PAT *auxF = p->getFilho(getString(c,p->getPosPref()));
                    p->setFilho(getString(c,p->getPosPref()),aux);
                    aux->setFilho(aux->getChave().at(0),auxF);
                    return NULL;

                }

            }


        }

    }
    return NULL;

}
bool ArvorePatricia::buscar(string s){

    if(buscar(s,raiz) != NULL){

        return true;

    }
    return false;

}
int ArvorePatricia::diferencaStrings(string c, string s, unsigned int p){

    if(c.size() <= p || s.size() <= p){

        return -1;

    }else{

        int aux;
        if(c.size() < s.size()){

            aux = c.size();

        }else{

            aux = s.size();

        }
        for(int i = p; i <= aux; i++){

            if(getString(s,i) != getString(c,i)){

                return i;

            }

        }
        return -2;
    }

}
char ArvorePatricia::getString(string s, unsigned int id){

    if(id >= s.size()){

        return '\0';

    }
    return s.at(id);
   /*string::iterator it = s.begin();
    for(unsigned int i = 0; i < id; i++, it++){}
    return *it;*/

}
No_PAT* ArvorePatricia::buscar(string s, No_PAT *p){

    if(p == NULL)return p;
    if(p->getPosPref() == -1){

        if(comparaStrings(p->getChave(),s)){

            return p;

        }else{

            return NULL;

        }

    }else{

        return buscar(s,p->getFilho(getString(s,p->getPosPref())));

    }

}
bool ArvorePatricia::comparaStrings(string s, string c){

    string::iterator itS, itC;
    if(s.size() != c.size()){

        return false;

    }
    for(itS = s.begin(), itC = c.begin(); itS != s.end(); itS++, itC++){

        if(*itS != *itC){

            return false;

        }

    }
    return true;

}
string ArvorePatricia::buscaStringPai(No_PAT* p){

    string aux;
    if(p == NULL){

        return aux;

    }
    aux = p->getChave();
    if(aux.size() > 0){

        return aux;

    }
    for(char c = 'a'; c < p->getTamAlfa(); c++){

        aux = buscaStringPai(p->getFilho(c));
        if(aux.size() > 0){

            return aux;

        }

    }
    return aux;

}
ArvorePatricia::~ArvorePatricia()
{
    delete raiz;
}
