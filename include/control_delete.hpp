#ifndef CTR_DELETE
#define CTR_DELETE

#include <iostream>
#include <mysql/mysql.h>
#include <vector>
#include <map>

#include "receita.hpp"
#include "util.hpp"

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
	void removerIngredientesDaReceita(string receita_id);
	void removerEtapasDaReceita(string receita_id);
	void removerPassosDaEtapa(string receita_id, string etapa_numero);
};

#endif