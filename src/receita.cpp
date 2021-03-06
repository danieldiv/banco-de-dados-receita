#include "receita.hpp"

Receita::Receita(string id, string nome, string rendimento, string tempo) {
    setId(id);
    setNome(nome);
    setRendimento(rendimento);
    setTempo(tempo);
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

void Receita::setFoto(Foto foto) { this->fotos.push_back(foto); }
void Receita::getFotos() {
    if (this->fotos.size() != 0)
        for (Foto foto : this->fotos) foto.toString();
    else
        cout << "A receita nao possui fotos" << endl;
}

void Receita::setEtapas(Etapa etapa) { this->etapas.push_back(etapa); }

void Receita::getEtapas() {
    if (this->etapas.size() != 0)
        for (Etapa etapa : this->etapas) etapa.toString();
    else
        cout << "\nA receita nao possui etapas" << endl;
}

void Receita::setCurtida(Curtida curtida) { this->curtidas.push_back(curtida); }

void Receita::getCurtidas() {
    if (this->curtidas.size() != 0)
        for (Curtida curtida : this->curtidas) curtida.toString();
    else
        cout << "A receita nao possui curtidas" << endl;
}

void Receita::setComentarios(Comentario comentario) { this->comentarios.push_back(comentario); }
void Receita::getComentarios() {
    if (this->comentarios.size() != 0)
        for (Comentario comentario : this->comentarios) comentario.toString();
    else
        cout << "A receita nao possui comentarios" << endl;
}

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
    cout << endl << "[" << getNome() << "]" << endl << endl
        << "preparo: " << getTempo() << " min | " << "rendimento: " << getRendimento() << getInfo()
        << " | usuario: " << getUsuario().getNome() << endl;

    cout << endl << "[Ingredientes]" << endl << endl;
    getIngredientes();

    cout << endl << "[Modo de preparo]" << endl;
    getEtapas();

    cout << endl << "[Fotos]" << endl << endl;
    getFotos();

    cout << endl << "[Curtidas]" << endl << endl;
    getCurtidas();

    cout << endl << "[Comentarios]" << endl << endl;
    getComentarios();
    cout << endl << "---------------------------------------------------------------------------" << endl;
}