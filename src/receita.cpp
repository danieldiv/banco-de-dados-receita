
#include "receita.hpp"

Receita::Receita(string id, string nome, string rendimento, string tempo) {
    setId(id);
    setNome(nome);
    setRendimento(rendimento);
    setTempo(tempo);
}

Receita::Receita() {}
Receita::~Receita() {}

void Receita::setIngrediente(Ingrediente ingrediente) { this->ingrediente = ingrediente; }
Ingrediente Receita::getIngrediente() { return this->ingrediente; }

void Receita::setUsuario(Usuario usuario) { this->usuario = usuario; }
Usuario Receita::getUsuario() { return this->usuario; }

void Receita::setId(string id) { this->id = id; }
void Receita::setNome(string nome) { this->nome = nome; }
void Receita::setRendimento(string rendimento) { this->rendimento = rendimento; }
void Receita::setTempo(string tempo) { this->tempo = tempo; }
void Receita::setInfo(string info) { this->info = info; }

string Receita::getId() { return this->id; }
string Receita::getNome() { return this->nome; }
string Receita::getRendimento() { return this->rendimento; }
string Receita::getTempo() { return this->tempo; }
string Receita::getInfo() { return this->info; }

void Receita::toString() {
    cout
        << "[nome]: " << getNome() << " [rend]: " << getRendimento() << " [tempo]: " << getTempo()
        << " [info]: " << getInfo() << " [usu]: " << getUsuario().getNome();
    getIngrediente().toString();
}