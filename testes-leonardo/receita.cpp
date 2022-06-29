#include "receita.hpp"

Receita::Receita(string id, string nome, string rendimento, string tempo/*, string comentarios, string curtidas, string avaliacoes*/) {
    setId(id);
    setNome(nome);
    setRendimento(rendimento);
    setTempo(tempo);
    //leonardo
    /*
    setComentario(comentarios);
    setCurtidas(curtidas);
    setAvaliacoes(avaliacoes);
    */
}

Receita::Receita() {}
Receita::~Receita() {}

void Receita::setIngredientes(Ingrediente ingrediente) { this->ingredientes.push_back(ingrediente); }

void Receita::getIngredientes() {
    if (this->ingredientes.size() != 0)
        for (Ingrediente ing : this->ingredientes) ing.toString();
    else
        cout << "A receita nao possui ingredientes" << endl;
}

void Receita::setEtapas(Etapa etapa) { this->etapas.push_back(etapa); }

void Receita::getEtapas() {
    if (this->etapas.size() != 0)
        for (Etapa etapa : this->etapas) etapa.toString();
    else
        cout << "\nA receita nao possui etapas" << endl;
}

void Receita::setUsuario(Usuario usuario) { this->usuario = usuario; }
Usuario Receita::getUsuario() { return this->usuario; }

void Receita::setId(string id) { this->id = id; }
void Receita::setNome(string nome) { this->nome = nome; }
void Receita::setRendimento(string rendimento) { this->rendimento = rendimento; }
void Receita::setTempo(string tempo) { this->tempo = tempo; }
void Receita::setInfo(string info) { this->info = info; }
//leonardo
/*
void Receita::setComentario(string comentario) { this->comentarios = comentario; }
void Receita::setCurtidas(string curtidas) { this->curtidas = curtidas; }
void Receita::setAvaliacoes(string avaliacoes) { this->avaliacoes = avaliacoes; }
*/
string Receita::getId() { return this->id; }
string Receita::getNome() { return this->nome; }
string Receita::getRendimento() { return this->rendimento; }
string Receita::getTempo() { return this->tempo; }
string Receita::getInfo() { return this->info; }
//leonardo
/*
string Receita::getComentario() { return this->comentarios; }
string Receita::getCurtidas() { return this->curtidas; }
string Receita::getAvaliacoes() { return this->avaliacoes; }
*/
void Receita::toString() {
    cout << endl << "[" << getNome() << "]" << endl << endl
        << "preparo: " << getTempo() << " min | " << "rendimento: " << getRendimento() << getInfo()
        << " | usuario: " << getUsuario().getNome() << endl;

    cout << endl << "[Ingredientes]" << endl << endl;
    getIngredientes();

    cout << endl << "[Modo de preparo]" << endl;
    getEtapas();
    cout << endl << "---------------------------------------------------------------------------" << endl;
}