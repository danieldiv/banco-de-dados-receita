#ifndef CTR_INSERT_HPP
#define CTR_INSERT_HPP

#include <iostream>
#include <mysql/mysql.h>
#include <vector>
#include <map>

#include <time.h>
#include <stdio.h>
#include <string.h>

#include "receita.hpp"
#include "util.hpp"

class ControlInsert {
private:
	vector<Receita> receitas;
	MYSQL *mysql;
	Util *util;
public:
	ControlInsert();
	~ControlInsert();

	MYSQL *getMysql();
	Util *getUtil();
	int testQuery(string query);

	void setMysql(MYSQL *mysql);
	void setUtil(Util *util);

	void adicionarIngrediente();
	void adicionarUsuario();
	void adicionarReceita(string id_usuario);
	void adicionarIngredienteReceitas();
	void adicionarComentarioReceita();
};

#endif