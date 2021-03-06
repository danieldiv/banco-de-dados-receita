#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <iostream>
#include <vector>

#include "receita_salva.hpp"

using namespace std;

class Usuario {
private:
    string id;
    string nome;
    string telefone;
    string email;
    string cidade;
    string estado;
    string foto;

    vector<ReceitaSalva> receitas;
public:
    Usuario();
    Usuario(string id, string nome);
    Usuario(string id, string nome, string telefone, string email, string cidade, string estado, string foto);
    ~Usuario();

    void toString();

    void setReceitas(ReceitaSalva receita);
    void getReceitas();

    void setId(string id);
    void setNome(string nome);
    void setTelefone(string telefone);
    void setEmail(string email);
    void setCidade(string cidade);
    void setEstado(string estado);
    void setFoto(string foto);

    string getId();
    string getNome();
    string getTelefone();
    string getEmail();
    string getCidade();
    string getEstado();
    string getFoto();
};

#endif