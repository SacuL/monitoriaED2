#include <imprimeEstrutura.h>
#include "RobinKarp.h"
#include <fstream>
#include <string>

string leArquivo(string caminho)
{
    ifstream arquivo(caminho);
    string linha;
    string conteudo;
    while (getline(arquivo, linha))
    {
        conteudo += linha;
        conteudo.push_back('\n');
    }
    arquivo.close();

    return conteudo;
}

int main()
{
    RobinKarp *rk = new RobinKarp();


    string livro = leArquivo("pg25690.txt");
    string padraoLivro = "reclamada";
    int resultadoLivro = rk->busca(padraoLivro,livro);
    cout << "Buscando padrao \"" << padraoLivro <<"\"... ";
    if(resultadoLivro == -1){
        cout << "Nao foi encontrado!\n";
    }else{
        cout << "Achou na posicao " << resultadoLivro << endl;
        cout << "\"" << livro.substr(resultadoLivro,padraoLivro.size()) << "\"" << endl;
    }

    string padrao = "jsndkj askjd";
    string texto = "tejxto com vjsajsndkj askrias cojsisas okajsndkj asdasndj asjd asojdbajsndkj askjd ";
    int resultado = rk->busca(padrao,texto);
    cout << "Buscando padrao \"" << padrao <<"\"... ";
    if(resultado == -1){
        cout << "Nao foi encontrado!\n";
    }else{
        cout << "Achou na posicao " << resultado << endl;
        cout << "\"" << texto.substr(resultado,padrao.size()) << "\"" << endl;
    }


    int k = 0;
    cin >>k;
    return 0;
}
