#include "control_delete.hpp"

ControlDelete::ControlDelete() {}
ControlDelete::~ControlDelete() {}

void ControlDelete::setMysql(MYSQL *mysql) { this->mysql = mysql; }
void ControlDelete::setUtil(Util *util) { this->util = util; }

MYSQL *ControlDelete::getMysql() { return this->mysql; }
Util *ControlDelete::getUtil() { return this->util; }

void ControlDelete::removerLinha(string query) {
	if (mysql_query(getMysql(), query.c_str()) != 0)
		cout << "Nao foi possivel excluir a linha" << endl;
	else {
		if (mysql_affected_rows(getMysql()) != 0)
			cout << "Linha removida com sucesso" << endl;
		else
			cout << "Nenhuma linha afetada" << endl;
	}
}

void ControlDelete::construirQueryRemocao(string tabela) {
	string query = "select * from ";
	query.append(tabela);

	getUtil()->imprimeDados(getMysql(), query.c_str());

	string id;

	cout << "\nInforme o codigo da tabela (" << tabela << ") para excluir: ";
	cin.ignore();
	getline(cin, id);

	query.assign("delete from ").append(tabela).append(" where id = ").append(id);
	removerLinha(query);
}

void ControlDelete::removerReceitaEmCascata() {
	string query = "select id, nome from receitas";
	getUtil()->imprimeDados(getMysql(), query.c_str());

	string id;

	cout << "\nInforme o codigo da receita para excluir: ";
	cin.ignore();
	getline(cin, id);

	// assumindo que o id exista

	string queryIngredientes = "select receita_id, ingrediente_id from receitas_ingredientes where receita_id = ";
	queryIngredientes.append(id);

	// getUtil()->imprimeDados(getMysql(), queryIngredientes.c_str());

	// buscarIngredientesDaReceita(rec);
	// buscarEtapasDaReceita(rec);

	mysql_query(getMysql(), queryIngredientes.c_str());
	MYSQL_RES *resultado = mysql_store_result(mysql);
	MYSQL_ROW linha;

	if (resultado == NULL) {
		cout << "Query invalida" << endl;
	} else if (mysql_affected_rows(mysql) == 0) {
		cout << "Nao possui ingredientes nesta receita" << endl;
	}

	while ((linha = mysql_fetch_row(resultado))) {
		query.assign("delete from receitas_ingredientes where receita_id = ")
			.append(id).append(" and ingrediente_id = ").append(linha[1]);
		// cout << "query: " << query << endl;
		removerLinha(query);
	}

	string queryEtapas = "select receita_id, numero from receitas_etapas where receita_id = ";
	queryEtapas.append(id);

	// getUtil()->imprimeDados(getMysql(), queryEtapas.c_str());

	mysql_query(getMysql(), queryEtapas.c_str());
	resultado = mysql_store_result(mysql);

	if (resultado == NULL) {
		cout << "Query invalida" << endl;
	} else if (mysql_affected_rows(mysql) == 0) {
		cout << "Nao possui etapas nesta receita" << endl;
	}

	while ((linha = mysql_fetch_row(resultado))) {
		// query.assign("delete from receitas_ingredientes where receita_id = ")
		//     .append(id).append(" and numero = ").append(linha[1]);
		// cout << "query: " << query << endl;
		// removerLinha(query);

		string queryPassosDaEtapa = "select receita_id, etapa_numero, sequencia from receitas_passos where receita_id = ";
		queryPassosDaEtapa.append(id).append(" and etapa_numero = ").append(linha[1]);

		// getUtil()->imprimeDados(getMysql(), queryEtapas.c_str());

		mysql_query(getMysql(), queryPassosDaEtapa.c_str());
		MYSQL_RES *resultado2 = mysql_store_result(mysql);
		MYSQL_ROW linha2;

		// cout << "query etapas: " << queryEtapas << endl;
		// cout << "query passos:" << queryPassosDaEtapa << endl;

		while ((linha2 = mysql_fetch_row(resultado2))) {
			queryPassosDaEtapa.assign("delete from receitas_passos where receita_id = ")
				.append(id).append(" and etapa_numero = ").append(linha2[1])
				.append(" and sequencia = ").append(linha2[2]);
			removerLinha(queryPassosDaEtapa);
		}
		queryEtapas.assign("delete from receitas_etapas where receita_id = ")
			.append(id).append(" and numero = ").append(linha[1]);
		// cout << "query: " << queryEtapas << endl;
		removerLinha(queryEtapas);
	}
	query.assign("delete from receitas where id = ").append(id);
	removerLinha(query);
}