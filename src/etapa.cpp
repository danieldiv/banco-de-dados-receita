#include "etapa.hpp"

Etapa::Etapa() {}

Etapa::Etapa(string codigo, string numero, string titulo) {
    setCodigoReceita(codigo);
    setNumero(numero);
    setTitulo(titulo);
}

Etapa::~Etapa() {}

void Etapa::setPassos(Passo passo) { this->passos.push_back(passo); }

void Etapa::getPassos() {
    if (this->passos.size() != 0)
        for (Passo passo : this->passos) passo.toString();
    else
        cout << "\tA etapa nao possui passos" << endl;
}

void Etapa::setNumero(string numero) { this->numero = numero; }
void Etapa::setTitulo(string titulo) { this->titulo = titulo; }
void Etapa::setCodigoReceita(string codigo) { this->codigo_receita = codigo; }

string Etapa::getNumero() { return this->numero; }
string Etapa::getTitulo() { return this->titulo; }
string Etapa::getCodigoReceita() { return this->codigo_receita; }

void Etapa::toString() {
    cout << "\n\tEtapa " << getNumero() << ": " << getTitulo() << endl;
    getPassos();
}