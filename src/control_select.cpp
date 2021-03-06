#include "control_select.hpp"

ControlSelect::ControlSelect() {}
ControlSelect::~ControlSelect() {}

void ControlSelect::setMysql(MYSQL *mysql) { this->mysql = mysql; }
void ControlSelect::setUtil(Util *util) { this->util = util; }

MYSQL *ControlSelect::getMysql() { return this->mysql; }
Util *ControlSelect::getUtil() { return this->util; }

void ControlSelect::carregarUsuarios() {
	string query = "select * from usuarios";
	string query_receitas = "select nome from receitas where id = ";

	mysql_query(getMysql(), query.c_str());
	MYSQL_RES *resultado = mysql_store_result(getMysql());
	MYSQL_RES *resultado_receitas;

	if (mysql_num_rows(resultado) > 0) {
		MYSQL_ROW linha;

		Usuario *usu;
		ReceitaSalva *rec;
		while ((linha = mysql_fetch_row(resultado))) {
			usu = new Usuario(linha[0], linha[1], linha[2], linha[3], linha[4], linha[5], linha[6]);

			query.assign("select * from receitas_salvas where usuario_id = ").append(usu->getId());
			mysql_query(getMysql(), query.c_str());
			resultado_receitas = mysql_store_result(getMysql());

			if (mysql_num_rows(resultado_receitas) > 0) {
				MYSQL_ROW linha_receitas;

				cout << "\n[Receitas salvas]" << endl << endl;
				while ((linha_receitas = mysql_fetch_row(resultado_receitas))) {
					rec = new ReceitaSalva(linha_receitas[0], linha_receitas[1]);
					usu->setReceitas(*rec);

					buscarReceitaPorId(query_receitas, linha_receitas[1], false);
				}
			}
			setUsuario(*usu);
		}
		cout << endl;
		for (Usuario u : this->usuarios) u.toString();
	} else
		cout << "\nNenhum usuario encontrado" << endl;
	this->receitas.clear();
}

void ControlSelect::setUsuario(Usuario usu) { this->usuarios.push_back(usu); }

void ControlSelect::carregarReceitas(MYSQL *sql, string nomeReceita) {
	string query = "select * from receitas";
	query.append(" where nome like '%").append(nomeReceita).append("%'");

	setMysql(sql);

	mysql_query(getMysql(), query.c_str());
	MYSQL_RES *resultado = mysql_store_result(getMysql());

	if (mysql_num_rows(resultado) > 0) {
		MYSQL_ROW linha;
		Receita *rec;

		while ((linha = mysql_fetch_row(resultado))) {
			rec = new Receita(linha[0], linha[2], linha[3], linha[4]);

			if (linha[1] != NULL) rec->setUsuario(buscarUsuarioPorId(linha[1]));

			buscarIngredientesDaReceita(rec);
			buscarEtapasDaReceita(rec);
			buscarFotosReceita(rec);
			buscarCurtidaReceita(rec);
			buscarComentariosReceita(rec);

			this->receitas.push_back(*rec);
		}
		for (Receita r : this->receitas) r.toString();
	} else
		cout << "\nNenhuma receita encontrada" << endl;
	this->receitas.clear();
}

void ControlSelect::buscarIngredientesDaReceita(Receita *rec) {
	string query = "select * from vw_receitas_ingredientes where receita_id = ";
	query.append(rec->getId());

	mysql_query(getMysql(), query.c_str());
	MYSQL_RES *resultado = mysql_store_result(mysql);
	MYSQL_ROW linha;

	Ingrediente *ing;
	while ((linha = mysql_fetch_row(resultado))) {
		ing = new Ingrediente(linha[1], linha[2], linha[3], linha[4]);
		rec->setIngredientes(*ing);
	}
}

Usuario ControlSelect::buscarUsuarioPorId(string id) {
	string query = "select id, nome from usuarios where id = ";
	query.append(id);

	mysql_query(getMysql(), query.c_str());
	MYSQL_RES *resultado = mysql_store_result(mysql);
	MYSQL_ROW linha;

	Usuario *usu = new Usuario();

	while ((linha = mysql_fetch_row(resultado))) {
		usu->setId(linha[0]);
		usu->setNome(linha[1]);

		return *usu;
	}
	return *usu;
}

void ControlSelect::buscarEtapasDaReceita(Receita *rec) {
	string query = "select * from receitas_etapas where receita_id = ";
	query.append(rec->getId());

	mysql_query(getMysql(), query.c_str());
	MYSQL_RES *resultado = mysql_store_result(mysql);
	MYSQL_ROW linha;

	while ((linha = mysql_fetch_row(resultado))) {
		Etapa *etapa = new Etapa(linha[0], linha[1], linha[2]);
		buscarPassosDaEtapa(etapa);
		rec->setEtapas(*etapa);
	}
}

void ControlSelect::buscarPassosDaEtapa(Etapa *etapa) {
	string query = "select * from receitas_passos where receita_id = ";
	query
		.append(etapa->getCodigoReceita())
		.append(" and ")
		.append("etapa_numero = ").append(etapa->getNumero());

	mysql_query(getMysql(), query.c_str());
	MYSQL_RES *resultado = mysql_store_result(mysql);
	MYSQL_ROW linha;

	while ((linha = mysql_fetch_row(resultado))) {
		Passo passo(linha[2], linha[3]);
		etapa->setPassos(passo);
	}
}

void ControlSelect::buscarReceitaPorIngrediente(string ingrediente) {
	string query = "select receita_id from vw_receitas_ingredientes where nome like";
	query.append(" '%").append(ingrediente).append("%' order by receita_id");

	mysql_query(getMysql(), query.c_str());
	MYSQL_RES *resultado = mysql_store_result(mysql);
	MYSQL_ROW linha;

	map<string, int> mapeamento;
	map<string, int>::iterator itr;

	while ((linha = mysql_fetch_row(resultado))) {
		itr = mapeamento.find(linha[0]);
		if (!(itr != mapeamento.end())) mapeamento.insert({ linha[0], 1 });
	}

	if (mapeamento.size() > 0) {
		query.assign("select * from receitas where id = ");
		for (itr = mapeamento.begin(); itr != mapeamento.end(); itr++)
			buscarReceitaPorId(query, itr->first, true);
	} else cout << "\nNenhuma receita encontrada" << endl;
}

void ControlSelect::buscarReceitaPorId(string query, string id, bool controle) {
	// string query = "select * from receitas where id = ";
	query.append(id);

	mysql_query(getMysql(), query.c_str());
	MYSQL_RES *resultado = mysql_store_result(mysql);
	MYSQL_ROW linha;

	Receita *rec;

	while ((linha = mysql_fetch_row(resultado))) {
		if (controle) {
			rec = new Receita(linha[0], linha[2], linha[3], linha[4]);

			if (linha[1] != NULL) rec->setUsuario(buscarUsuarioPorId(linha[1]));

			buscarIngredientesDaReceita(rec);
			buscarEtapasDaReceita(rec);

			this->receitas.push_back(*rec);
		} else {
			cout << linha[0] << endl;
		}
	}
	for (Receita r : this->receitas) r.toString();
	this->receitas.clear();
}

void ControlSelect::buscarFotosReceita(Receita *rec) {
	string query = "select * from receitas_fotos where receita_id = ";
	query.append(rec->getId());

	mysql_query(getMysql(), query.c_str());
	MYSQL_RES *resultado = mysql_store_result(mysql);
	MYSQL_ROW linha;

	Foto *foto;
	while ((linha = mysql_fetch_row(resultado))) {
		foto = new Foto(linha[1]);
		rec->setFoto(*foto);
	}
}

void ControlSelect::buscarCurtidaReceita(Receita *rec) {
	string query = "select usuario_id, estrelas from curtidas where receita_id = ";
	query.append(rec->getId());

	mysql_query(getMysql(), query.c_str());
	MYSQL_RES *resultado = mysql_store_result(mysql);
	MYSQL_ROW linha;

	Curtida *curtida;
	Usuario usu;
	while ((linha = mysql_fetch_row(resultado))) {
		usu = buscarUsuarioPorId(linha[0]);
		curtida = new Curtida(usu.getNome(), linha[1]);
		rec->setCurtida(*curtida);
	}
}

void ControlSelect::buscarComentariosReceita(Receita *rec) {
	string query = "select usuario_id, data_hora, mensagem from comentarios where receita_id = ";
	query.append(rec->getId());

	mysql_query(getMysql(), query.c_str());
	MYSQL_RES *resultado = mysql_store_result(mysql);
	MYSQL_ROW linha;

	Comentario *comentario;
	while ((linha = mysql_fetch_row(resultado))) {
		comentario = new Comentario(linha[0], linha[1], linha[2]);
		rec->setComentarios(*comentario);
	}
}