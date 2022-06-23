#ifndef CONTROL_HPP
#define CONTROL_HPP

#include <iostream>
#include <mysql/mysql.h>
#include <vector>

#include "receita.hpp"

using namespace std;

class Control {
private:
    vector<Receita> receitas;
public:
    Control();
    ~Control();

    void adicionarIngrediente(MYSQL *mysql);
    void adicionarUsuario(MYSQL *mysql);
    void adicionarReceita(MYSQL *mysql, string id_usuario);

    void carregarReceitas(MYSQL *mysql);
};

#endif