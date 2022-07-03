#ifndef CTR_UPDATE_HPP
#define CTR_UPDATE_HPP

#include <iostream>
#include <mysql/mysql.h>
#include <vector>
#include <map>

#include "receita.hpp"
#include "util.hpp"

class ControlUpdate {
private:
	vector<Receita> receitas;
	MYSQL *mysql;
	Util *util;
public:
	ControlUpdate();
	~ControlUpdate();

	MYSQL *getMysql();
	Util *getUtil();

	void setMysql(MYSQL *mysql);
	void setUtil(Util *util);

	void atualizarIngrediente();
	void atualizarUsuario();
	void atualizarReceita();
	void atualizarFoto();
	void atualizarReceitaIngrediente();
	void atualizarReceitaEtapa();
	void atualizarReceitaPassos();
};

#endif