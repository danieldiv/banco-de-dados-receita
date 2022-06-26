#ifndef RECEITA_HPP
#define RECEITA_HPP

#include <iostream>
#include <vector>

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

    vector<Ingrediente> ingredientes;
    Usuario usuario;
public:
    Receita();
    Receita(string id, string nome, string rendimento, string tempo);
    ~Receita();

    void toString();

    void setIngredientes(Ingrediente ingrediente);
    void getIngredientes();

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