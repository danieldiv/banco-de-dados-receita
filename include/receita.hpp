#ifndef RECEITA_HPP
#define RECEITA_HPP

#include <iostream>
#include <vector>

#include "usuario.hpp"
#include "ingrediente.hpp"
#include "etapa.hpp"

using namespace std;

class Receita {
private:
    string id;
    string nome;
    string rendimento;
    string tempo;
    string info;

    Usuario usuario;

    vector<Ingrediente> ingredientes;
    vector<Etapa> etapas;
public:
    Receita();
    Receita(string id, string nome, string rendimento, string tempo);
    ~Receita();

    void toString();

    void setIngredientes(Ingrediente ingrediente);
    void getIngredientes();

    void setUsuario(Usuario usuario);
    Usuario getUsuario();

    void setEtapas(Etapa etapa);
    void getEtapas();

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