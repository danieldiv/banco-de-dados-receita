#ifndef RECEITA_HPP
#define RECEITA_HPP

#include <iostream>

#include "ingrediente.hpp"
#include "usuario.hpp"

using namespace std;

class Receita {
private:
    string id;
    string nome;
    string rendimento;
    string tempo;
    string info;

    Ingrediente ingrediente;
    Usuario usuario;
public:
    Receita();
    Receita(string id, string nome, string rendimento, string tempo);
    ~Receita();

    void toString();

    void setIngrediente(Ingrediente ingrediente);
    Ingrediente getIngrediente();

    void setUsuario(Usuario usuario);
    Usuario getUsuario();

    void setId(string id);
    void setNome(string nome);
    void setRendimento(string rendimento);
    void setTempo(string tempo);
    void setInfo(string info);

    string getId();
    string getNome();
    string getRendimento();
    string getTempo();
    string getInfo();
};

#endif