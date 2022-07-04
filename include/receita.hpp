#ifndef RECEITA_HPP
#define RECEITA_HPP

#include <iostream>
#include <vector>

#include "usuario.hpp"
#include "ingrediente.hpp"
#include "etapa.hpp"
#include "foto.hpp"
#include "curtida.hpp"

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
    vector<Foto> fotos;
    vector<Curtida> curtidas;
public:
    Receita();
    Receita(string id, string nome, string rendimento, string tempo);
    ~Receita();

    void toString();

    void setIngredientes(Ingrediente ingrediente);
    void getIngredientes();

    void setFoto(Foto foto);
    void getFotos();

    void setCurtida(Curtida curtida);
    void getCurtidas();

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