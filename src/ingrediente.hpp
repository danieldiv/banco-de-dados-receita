#ifndef INGREDIENTE_HPP
#define INGREDIENTE_HPP

#include <iostream>

using namespace std;

class Ingrediente {
private:
    string id;
    string nome;
    string quantidade;
    string unidade;
public:
    Ingrediente();
    Ingrediente(string id, string nome, string quantidade, string unidade);
    ~Ingrediente();

    void toString();

    void setId(string id);
    void setNome(string nome);
    void setQuantidade(string quantidade);
    void setUnidade(string unidade);

    string getId();
    string getNome();
    string getQuantidade();
    string getUnidade();
};


#endif