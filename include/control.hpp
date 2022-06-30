#ifndef CONTROL_HPP
#define CONTROL_HPP

// #include <iostream>
// #include <mysql/mysql.h>
// #include <vector>
// #include <map>

#include "control_delete.hpp"
#include "control_select.hpp"
#include "control_insert.hpp"
#include "control_update.hpp"

using namespace std;

class Control {
private:
    vector<Receita> receitas;
    MYSQL *mysql;
    Util *util;

    ControlDelete ctr_delete;
    ControlSelect ctr_select;
    ControlInsert ctr_insert;
    ControlUpdate ctr_update;
public:
    Control(MYSQL *mysql, Util *util);
    ~Control();

    ControlDelete getControlDelete();
    ControlSelect getControlSelect();
    ControlInsert getControlInsert();
    ControlUpdate getControlUpdate();
};

#endif
