#include "control.hpp"

Control::Control(MYSQL *mysql, Util *util) {
    this->ctr_delete.setMysql(mysql);
    this->ctr_delete.setUtil(util);

    this->ctr_select.setMysql(mysql);
    this->ctr_select.setUtil(util);

    this->ctr_insert.setMysql(mysql);
    this->ctr_insert.setUtil(util);

    this->ctr_update.setMysql(mysql);
    this->ctr_update.setUtil(util);
}

Control::~Control() {}

ControlDelete Control::getControlDelete() { return this->ctr_delete; }
ControlSelect Control::getControlSelect() { return this->ctr_select; };
ControlInsert Control::getControlInsert() { return this->ctr_insert; }
ControlUpdate Control::getControlUpdate() { return this->ctr_update; }