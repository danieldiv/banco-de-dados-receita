#include "ingrediente.hpp"

Ingrediente::~Ingrediente() {}

Ingrediente::Ingrediente(string nome) {
    setNome(nome);
}

Ingrediente::Ingrediente(int id, string nome) {
    setId(id);
    setNome(nome);
}

void Ingrediente::setId(int id) {
    this->id = id;
}

int Ingrediente::getId() {
    return this->id;
}

void Ingrediente::setNome(string nome) {
    this->nome.assign(nome);
}
string Ingrediente::getNome() {
    return this->nome;
}