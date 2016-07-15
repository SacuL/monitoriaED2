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

        insereRecursivo(c,0,raiz);

    }

}
void ArvorePatricia::insereRecursivo(string c, int pos, No_PAT *p){

    if(p->getPosPref() == -1){

        int aux = diferencaStrings(c,p->getChave(),(unsigned)pos);
        No_PAT *n = new No_PAT(tamAlfa);
        n->setChave(p->getChave());
        p->setFilho(getString(n->getChave(),aux),n);
        n = new No_PAT(tamAlfa);
        n->setChave(c);
        p->setFilho(getString(c,aux),n);
        p->setPosPref(aux);

    }else{

        No_PAT *n = p->getFilho(getString(c,p->getPosPref()));
        if(n != NULL){

            insereRecursivo(c,p->getPosPref(),n);

        }else{

            n = new No_PAT(tamAlfa);
            n->setChave(c);
            p->setFilho(getString(c,p->getPosPref()),n);

        }

    }

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

    string::iterator it = s.begin();
    for(unsigned int i = 0; i < id; i++, it++){}
    return *it;

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
ArvorePatricia::~ArvorePatricia()
{
    delete raiz;
}
