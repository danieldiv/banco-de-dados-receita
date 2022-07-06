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
	int testQuery(string query);

	void removerLinha(string query);
	void construirQueryRemocao(string tabela);
	void removerReceitaDoUsuario();

	void removerReceitaEmCascata();

	void removerIngredientesDaReceita(string receita_id);
	void removerIngredienteDaReceita(string receita_id, string ingrediente_id);

	void removerEtapasDaReceita(string receita_id);
	void removerEtapaDaReceita(string receita_id, string etapa_numero);

	void removerPassosDaEtapa(string receita_id, string etapa_numero);
	void removerPassoDaEtapa(string receita_id, string etapa_numero, string sequencia);

	void removerComentariosDaReceita(string receita_id, string usuario_id);
	void removerComentarioDaReceita(string receita_id, string usuario_id, string data_hora);

	void removerCurtidasDaReceita(string receita_id, string usuario_id);
	void removerCurtidaDaReceita(string receita_id, string usuario_id);

	void removerFotosDaReceita(string receita_id);
	void removerFotoDaReceita(string receita_id, string arquivo);
};

#endif