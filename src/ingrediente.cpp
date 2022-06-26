#include "ingrediente.hpp"

Ingrediente::Ingrediente(string id, string nome, string quantidade, string unidade) {
    setId(id);
    setNome(nome);
    setQuantidade(quantidade);
    setUnidade(unidade);
}

Ingrediente::Ingrediente() {}
Ingrediente::~Ingrediente() {}

void Ingrediente::setId(string id) { this->id = id; }
void Ingrediente::setNome(string nome) { this->nome = nome; }
void Ingrediente::setQuantidade(string quantidade) { this->quantidade = quantidade; }
void Ingrediente::setUnidade(string unidade) { this->unidade = unidade; }

string Ingrediente::getId() { return this->id; }
string Ingrediente::getNome() { return this->nome; }
string Ingrediente::getQuantidade() { return this->quantidade; }
string Ingrediente::getUnidade() { return this->unidade; }

void Ingrediente::toString() {
    cout << "- " << getNome() << " (" << getQuantidade() << " " << getUnidade() << ")" << endl;
}