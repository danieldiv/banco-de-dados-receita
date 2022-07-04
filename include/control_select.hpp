#ifndef CTR_DELETE_HPP
#define CTR_DELETE_HPP

#include <iostream>
#include <mysql/mysql.h>
#include <vector>
#include <map>

#include "receita.hpp"
#include "util.hpp"

class ControlSelect {
private:
	vector<Receita> receitas;
	MYSQL *mysql;
	Util *util;
public:
	ControlSelect();
	~ControlSelect();

	MYSQL *getMysql();
	Util *getUtil();

	void setMysql(MYSQL *mysql);
	void setUtil(Util *util);

	Usuario buscarUsuarioPorId(string id);

	void carregarReceitas(MYSQL *sql, string nomeReceita);
	void buscarIngredientesDaReceita(Receita *rec);
	void buscarEtapasDaReceita(Receita *rec);
	void buscarPassosDaEtapa(Etapa *etapa);
	void buscarReceitaPorIngrediente(string ingrediente);
	void buscarReceitaPorId(string id);
	void buscarFotosReceita(Receita *rec);
};

#endif