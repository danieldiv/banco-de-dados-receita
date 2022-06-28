#ifndef CONTROL_HPP
#define CONTROL_HPP

#include <iostream>
#include <mysql/mysql.h>
#include <vector>
#include <map>

#include "receita.hpp"
#include "util.hpp"

using namespace std;

class Control {
private:
    vector<Receita> receitas;
    MYSQL *mysql;
    Util *util;

    // Usuario usuario;
public:
    Control(MYSQL *mysql, Util *util);
    ~Control();

    void adicionarIngrediente();
    void removerIngrediente();

    void adicionarUsuario();
    void adicionarReceita(string id_usuario);

    void carregarReceitas(string nomeReceita);
    void buscarIngredientesDaReceita(Receita *rec);

    void buscarUsuarioPorId(Receita *rec, string id);

    void buscarEtapasDaReceita(Receita *rec);
    void buscarPassosDaEtapa(Etapa *etapa);

    void buscarReceitaPorIngrediente(string ingrediente);
    void buscarReceitaPorId(string id);
};

#endif