#include "control_delete.hpp"

ControlDelete::ControlDelete() {}
ControlDelete::~ControlDelete() {}

void ControlDelete::setMysql(MYSQL *mysql) { this->mysql = mysql; }
void ControlDelete::setUtil(Util *util) { this->util = util; }

MYSQL *ControlDelete::getMysql() { return this->mysql; }
Util *ControlDelete::getUtil() { return this->util; }

/**
 * @brief testeQuery testa a query informada
 * nao esta funcionando bem
 * @param query
 * @return int -1 = query invalida
 * 				1 = query executada com sucesso
 * 				0 = nenhuma linha afetada
 */
int ControlDelete::testQuery(string query) {
	if (mysql_query(getMysql(), query.c_str()) != 0) return -1;
	else if (mysql_affected_rows(getMysql()) != 0) return 1;
	return 0;
}

void ControlDelete::removerLinha(string query) {
	int res = testQuery(query);

	if (res == -1) cout << "Nao foi possivel excluir a linha" << endl;
	else {
		if (res == 1) cout << "Linha removida com sucesso" << endl;
		else cout << "Nenhuma linha afetada" << endl;
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

	if (getUtil()->imprimeDados(getMysql(), query.c_str())) {

		string id;

		cout << "\nInforme o codigo da receita para excluir: ";
		cin.ignore();
		getline(cin, id);

		query.assign("select id from receitas where id = ").append(id);

		mysql_query(getMysql(), query.c_str());

		if (mysql_store_result(getMysql()) == NULL) {
			cout << "Query invalida" << endl;
			return;
		} else if (mysql_affected_rows(getMysql()) == 0) {
			cout << "Receita nao encontrada" << endl;
			return;
		}
		removerIngredientesDaReceita(id);
		removerEtapasDaReceita(id);
		removerFotosDaReceita(id);
		removerCurtidaDaReceita(id, to_string(getUtil()->getId()));
		removerComentariosDaReceita(id, to_string(getUtil()->getId()));

		query.assign("delete from receitas where id = ").append(id);
		removerLinha(query);
	}
}

void ControlDelete::removerIngredientesDaReceita(string receita_id) {
	string query = "select receita_id, ingrediente_id from receitas_ingredientes where receita_id = ";
	query.append(receita_id);

	mysql_query(getMysql(), query.c_str());
	MYSQL_RES *resultado = mysql_store_result(getMysql());
	MYSQL_ROW linha;

	if (resultado == NULL) {
		cout << "Query invalida" << endl;
		return;
	} else if (mysql_affected_rows(getMysql()) == 0) {
		cout << "Nao possui ingredientes nesta receita" << endl;
		return;
	}

	while ((linha = mysql_fetch_row(resultado)))
		removerIngredienteDaReceita(receita_id, linha[1]);
}

void ControlDelete::removerIngredienteDaReceita(string receita_id, string ingrediente_id) {
	string query = "delete from receitas_ingredientes where receita_id = ";
	query.append(receita_id).append(" and ingrediente_id = ").append(ingrediente_id);
	removerLinha(query);
}

void ControlDelete::removerEtapasDaReceita(string receita_id) {
	string queryEtapas = "select receita_id, numero from receitas_etapas where receita_id = ";
	queryEtapas.append(receita_id);

	mysql_query(getMysql(), queryEtapas.c_str());
	MYSQL_RES *resultado = mysql_store_result(getMysql());

	if (resultado == NULL) {
		cout << "Query invalida" << endl;
		return;
	} else if (mysql_affected_rows(getMysql()) == 0) {
		cout << "Nao possui etapas nesta receita" << endl;
		return;
	}
	MYSQL_ROW linha;

	while ((linha = mysql_fetch_row(resultado)))
		removerEtapaDaReceita(receita_id, linha[1]);
}

void ControlDelete::removerEtapaDaReceita(string receita_id, string etapa_numero) {
	removerPassosDaEtapa(receita_id, etapa_numero);

	string query = "delete from receitas_etapas where receita_id = ";
	query.append(receita_id).append(" and numero = ").append(etapa_numero);
	removerLinha(query);
}

void ControlDelete::removerPassosDaEtapa(string receita_id, string etapa_numero) {
	string query = "select receita_id, etapa_numero, sequencia from receitas_passos where receita_id = ";
	query.append(receita_id).append(" and etapa_numero = ").append(etapa_numero);

	mysql_query(getMysql(), query.c_str());
	MYSQL_RES *resultado = mysql_store_result(getMysql());

	if (resultado == NULL) {
		cout << "Query invalida" << endl;
		return;
	} else if (mysql_affected_rows(getMysql()) == 0) {
		cout << "Nao possui passos na estapa desta receita" << endl;
		return;
	}
	MYSQL_ROW linha;

	while ((linha = mysql_fetch_row(resultado)))
		removerPassoDaEtapa(receita_id, etapa_numero, linha[2]);
}

void ControlDelete::removerPassoDaEtapa(string receita_id, string etapa_numero, string sequencia) {
	string query = "delete from receitas_passos where receita_id = ";
	query.append(receita_id).append(" and etapa_numero = ").append(etapa_numero)
		.append(" and sequencia = ").append(sequencia);
	removerLinha(query);
}

void ControlDelete::removerComentariosDaReceita(string receita_id, string usuario_id) {
	string query = "select usuario_id, receita_id, data_hora from comentarios";
	query.append(" where usuario_id = ").append(usuario_id)
		.append(" and receita_id = ").append(receita_id);

	mysql_query(getMysql(), query.c_str());
	MYSQL_RES *resultado = mysql_store_result(getMysql());

	if (resultado == NULL) {
		cout << "Query invalida" << endl;
		return;
	} else if (mysql_affected_rows(getMysql()) == 0) {
		cout << "Nao possui comentarios na receita" << endl;
		return;
	}
	MYSQL_ROW linha;

	while ((linha = mysql_fetch_row(resultado)))
		removerComentarioDaReceita(receita_id, usuario_id, linha[2]);
}

void ControlDelete::removerComentarioDaReceita(string receita_id, string usuario_id, string data_hora) {
	string query = "delete from comentarios where receita_id = ";
	query.append(receita_id).append(" and usuario_id = ").append(usuario_id)
		.append(" and data_hora = ").append("'").append(data_hora).append("'");
	removerLinha(query);
}

void ControlDelete::removerCurtidasDaReceita(string receita_id, string usuario_id) {
	string query = "select usuario_id, receita_id from curtidas";
	query.append(" where usuario_id = ").append(usuario_id)
		.append(" and receita_id = ").append(receita_id);

	mysql_query(getMysql(), query.c_str());
	MYSQL_RES *resultado = mysql_store_result(getMysql());

	if (resultado == NULL) {
		cout << "Query invalida" << endl;
		return;
	} else if (mysql_affected_rows(getMysql()) == 0) {
		cout << "Nao possui curtidas na receita" << endl;
		return;
	}
	MYSQL_ROW linha;

	while ((linha = mysql_fetch_row(resultado)))
		removerCurtidaDaReceita(receita_id, usuario_id);
}

void ControlDelete::removerCurtidaDaReceita(string receita_id, string usuario_id) {
	string query = "delete from curtidas where receita_id = ";
	query.append(receita_id).append(" and usuario_id = ").append(usuario_id);
	removerLinha(query);
}

void ControlDelete::removerFotosDaReceita(string receita_id) {
	string query = "select * from receitas_fotos";
	query.append(" where receita_id = ").append(receita_id);

	mysql_query(getMysql(), query.c_str());
	MYSQL_RES *resultado = mysql_store_result(getMysql());

	if (resultado == NULL) {
		cout << "Query invalida" << endl;
		return;
	} else if (mysql_affected_rows(getMysql()) == 0) {
		cout << "Nao possui fotos na receita" << endl;
		return;
	}
	MYSQL_ROW linha;

	while ((linha = mysql_fetch_row(resultado)))
		removerFotoDaReceita(receita_id, linha[1]);
}

void ControlDelete::removerFotoDaReceita(string receita_id, string arquivo) {
	string query = "delete from receitas_fotos where receita_id = ";
	query.append(receita_id).append(" and arquivo = ")
		.append("'").append(arquivo).append("'");
	removerLinha(query);
}

void ControlDelete::removerReceitaDoUsuario() {
	string query = "select id, nome from usuarios";

	if (getUtil()->imprimeDados(getMysql(), query.c_str())) {
		string usuario_id;

		cin.ignore();
		cout << "Informe o codigo do usuario: ";
		getline(cin, usuario_id);

		query.assign("select r.id, r.nome from receitas_salvas rs")
			.append(" left outer join receitas r on r.id = rs.receita_id")
			.append(" where rs.usuario_id = ").append(usuario_id);

		if (getUtil()->imprimeDados(getMysql(), query.c_str())) {
			string receita_id;
			cout << "Informe o codigo da receita: ";
			getline(cin, receita_id);

			query.assign("delete from receitas_salvas where receita_id = ")
				.append(receita_id).append(" and usuario_id = ")
				.append(to_string(getUtil()->getId()));
			removerLinha(query);
		}
	}
}