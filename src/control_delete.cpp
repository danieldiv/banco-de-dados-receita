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

/**
 * @brief construirQueryRemocao tenta realizar a remocao de alguma
 * linha da tabela passando o id
 *
 * @param tabela
 */
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

/**
 * @brief removerReceitaEmCascata remove os itens relacionados a receita
 * para depois remover a receita
 */
void ControlDelete::removerReceitaEmCascata() {
	string query = "select id, nome from receitas";
	getUtil()->imprimeDados(getMysql(), query.c_str());

	string id;

	cout << "\nInforme o codigo da receita para excluir: ";
	cin.ignore();
	getline(cin, id);

	removerIngredientesDaReceita(id);
	removerEtapasDaReceita(id);

	query.assign("delete from receitas where id = ").append(id);
	removerLinha(query);
}

void ControlDelete::removerIngredientesDaReceita(string receita_id) {
	cout << endl << "REMOCAO DE INGREDIENTES DA RECEITA" << endl << endl;

	string query = "select receita_id, ingrediente_id from receitas_ingredientes where receita_id = ";
	query.append(receita_id);

	mysql_query(getMysql(), query.c_str());
	MYSQL_RES *resultado = mysql_store_result(mysql);
	MYSQL_ROW linha;

	if (resultado == NULL) {
		cout << "Query invalida" << endl;
		return;
	} else if (mysql_affected_rows(mysql) == 0) {
		cout << "Nao possui ingredientes nesta receita" << endl;
		return;
	}

	while ((linha = mysql_fetch_row(resultado))) {
		query.assign("delete from receitas_ingredientes where receita_id = ")
			.append(receita_id).append(" and ingrediente_id = ").append(linha[1]);
		removerLinha(query);
	}
}

void ControlDelete::removerEtapasDaReceita(string receita_id) {
	cout << endl << "REMOCAO DE ETAPAS DA RECEITA" << endl << endl;

	string queryEtapas = "select receita_id, numero from receitas_etapas where receita_id = ";
	queryEtapas.append(receita_id);

	mysql_query(getMysql(), queryEtapas.c_str());
	MYSQL_RES *resultado = mysql_store_result(mysql);

	if (resultado == NULL) {
		cout << "Query invalida" << endl;
		return;
	} else if (mysql_affected_rows(mysql) == 0) {
		cout << "Nao possui etapas nesta receita" << endl;
		return;
	}
	MYSQL_ROW linha;

	while ((linha = mysql_fetch_row(resultado))) {
		removerPassosDaEtapa(receita_id, linha[1]);

		queryEtapas.assign("delete from receitas_etapas where receita_id = ")
			.append(receita_id).append(" and numero = ").append(linha[1]);
		removerLinha(queryEtapas);
	}
}

void ControlDelete::removerPassosDaEtapa(string receita_id, string etapa_numero) {
	cout << endl << "REMOCAO DE PASSOS DA ETAPA" << endl << endl;

	string query = "select receita_id, etapa_numero, sequencia from receitas_passos where receita_id = ";
	query.append(receita_id).append(" and etapa_numero = ").append(etapa_numero);

	mysql_query(getMysql(), query.c_str());
	MYSQL_RES *resultado2 = mysql_store_result(mysql);
	MYSQL_ROW linha2;

	while ((linha2 = mysql_fetch_row(resultado2))) {
		query.assign("delete from receitas_passos where receita_id = ")
			.append(receita_id).append(" and etapa_numero = ").append(etapa_numero)
			.append(" and sequencia = ").append(linha2[2]);
		removerLinha(query);
	}
}