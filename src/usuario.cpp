#include "usuario.hpp"

Usuario::Usuario(string id, string nome) {
    setId(id);
    setNome(nome);
}
Usuario::Usuario(string id, string nome, string telefone, string email, string cidade, string estado, string foto) {
    setId(id);
    setNome(nome);
    setTelefone(telefone);
    setEmail(email);
    setCidade(cidade);
    setEstado(estado);
    setFoto(foto);
}

Usuario::Usuario() {}
Usuario::~Usuario() {}

void Usuario::setReceitas(ReceitaSalva receita) { this->receitas.push_back(receita); }
void Usuario::getReceitas() {
    if (this->receitas.size() != 0)
        for (ReceitaSalva receita : this->receitas) {
            cout << receita.getUsuarioId() << " " << receita.getReceitaId() << endl;
        } else
            cout << "A receita nao possui receitas" << endl;
}

void Usuario::setId(string id) { this->id = id; }
void Usuario::setNome(string nome) { this->nome = nome; }
void Usuario::setTelefone(string telefone) { this->telefone = telefone; }
void Usuario::setEmail(string email) { this->email = email; }
void Usuario::setCidade(string cidade) { this->cidade = cidade; }
void Usuario::setEstado(string estado) { this->estado = estado; }
void Usuario::setFoto(string foto) { this->foto = foto; }

string Usuario::getNome() { return this->nome; }
string Usuario::getId() { return this->id; }
string Usuario::getTelefone() { return this->telefone; }
string Usuario::getEmail() { return this->email; }
string Usuario::getCidade() { return this->cidade; }
string Usuario::getEstado() { return this->estado; }
string Usuario::getFoto() { return this->foto; }

void Usuario::toString() {
    cout << getId() << " " << getNome() << " " << getTelefone() << " " << getEmail()
        << " " << getCidade() << " " << getEstado() << " " << getFoto() << " " << endl;

    // cout << "\n[Receitas salvas]" << endl << endl;
    // getReceitas();
}