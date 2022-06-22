#ifndef CONTROL_HPP
#define CONTROL_HPP

#include <iostream>
#include <mysql/mysql.h>

#include "ingrediente.hpp"

using namespace std;

class Control {
private:
public:
    Control();
    ~Control();

    void adicionarIngrediente(MYSQL *mysql);
};

#endif