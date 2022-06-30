#ifndef CTR_DELETE
#define CTR_DELETE

#include <iostream>
#include <mysql/mysql.h>
#include <vector>
#include <map>

#include "receita.hpp"
#include "util.hpp"
#include "teste.hpp"

class ControlDelete {
private:
	vector<Receita> receitas;
	MYSQL *mysql;
	Util *util;
public:
	ControlDelete();
	~ControlDelete();

	MYSQL *getMysql();
	Util *getUtil();

	void setMysql(MYSQL *mysql);
	void setUtil(Util *util);

	void removerLinha(string query);
	void construirQueryRemocao(string tabela);

	void removerReceitaEmCascata();
	void removerIngredientesDaReceita(Receita *rec);
	void removerEtapasDaReceita(Receita *rec);
	void removerPassosDaEtapa(Etapa *etapa);
};

#endif