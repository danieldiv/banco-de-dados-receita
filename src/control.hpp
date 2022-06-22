#ifndef CONTROL_HPP
#define CONTROL_HPP

#include <iostream>
#include <mysql/mysql.h>

using namespace std;

class Control {
private:
public:
    Control();
    ~Control();

    void adicionarIngrediente(MYSQL *mysql);
    void adicionarUsuario(MYSQL *mysql);
    void adicionarReceita(MYSQL *mysql);
};

#endif