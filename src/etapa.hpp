#ifndef ETAPA_HPP
#define ETAPA_HPP

#include <iostream>
#include <vector>

#include "passo.hpp"

using namespace std;

class Etapa {
private:
    string codigo_receita;
    string numero;
    string titulo;

    vector<Passo> passos;
public:
    Etapa();
    Etapa(string codigo, string numero, string titulo);
    ~Etapa();

    void toString();

    void setPassos(Passo passo);
    void getPassos();

    void setNumero(string numero);
    void setTitulo(string titulo);
    void setCodigoReceita(string codigo);

    string getNumero();
    string getTitulo();
    string getCodigoReceita();
};

#endif