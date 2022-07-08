#include "control_update.hpp"

ControlUpdate::ControlUpdate() {}
ControlUpdate::~ControlUpdate() {}

void ControlUpdate::setMysql(MYSQL *mysql) { this->mysql = mysql; }
void ControlUpdate::setUtil(Util *util) { this->util = util; }

MYSQL *ControlUpdate::getMysql() { return this->mysql; }
Util *ControlUpdate::getUtil() { return this->util; }

void ControlUpdate::atualizarIngrediente() {
	string id, nome;
	string query = "select * from ingredientes";
	getUtil()->imprimeDados(getMysql(), query.c_str());

	cout << "\nInforme o id do ingrediente: ";
	cin.ignore();
	getline(cin, id);
	id = getUtil()->testSqlInjection(getMysql(), id);
	query.append(id);

	cout << "Informe o novo nome do ingrediente: ";
	getline(cin, nome);
	nome = getUtil()->testSqlInjection(getMysql(), nome);

	query.assign("UPDATE ingredientes set nome = ")
		.append("'").append(nome).append("'")
		.append(" where id = ").append(id);

	if (mysql_query(getMysql(), query.c_str()) != 0)
		cout << "Ops... nao foi possivel atualizar o ingrediente " << nome << "." << endl;
	else
		cout << "O ingrediente " << nome << " foi atualizado com sucesso" << endl;
}

void ControlUpdate::atualizarUsuario() {
	string id, nome, telefone, email, cidade, estado, foto;
	string query = "select * from usuarios";
	getUtil()->imprimeDados(getMysql(), query.c_str());

	cout << "\nInforme o id do usuario: ";
	cin.ignore();
	getline(cin, id);
	id = getUtil()->testSqlInjection(getMysql(), id);

	query.append(id);

	cout << "Informe o nome do usuario: ";
	getline(cin, nome);
	nome = getUtil()->testSqlInjection(getMysql(), nome);

	cout << "Informe o telefone do usuario: ";
	getline(cin, telefone);
	telefone = getUtil()->testSqlInjection(getMysql(), telefone);

	cout << "Informe o email do usuario: ";
	getline(cin, email);
	email = getUtil()->testSqlInjection(getMysql(), email);

	cout << "Informe o cidade do usuario: ";
	getline(cin, cidade);
	cidade = getUtil()->testSqlInjection(getMysql(), cidade);

	cout << "Informe o estado do usuario: ";
	getline(cin, estado);
	estado = getUtil()->testSqlInjection(getMysql(), estado);

	cout << "Informe o foto do usuario: ";
	getline(cin, foto);
	foto = getUtil()->testSqlInjection(getMysql(), foto);

	query.assign("UPDATE usuarios set nome = ")
		.append("'").append(nome).append("'")
		.append(", telefone = ")
		.append("'").append(telefone).append("'")
		.append(", email = ")
		.append("'").append(email).append("'")
		.append(", cidade = ")
		.append("'").append(cidade).append("'")
		.append(", estado = ")
		.append("'").append(estado).append("'")
		.append(", foto = ")
		.append("'").append(foto).append("'")
		.append(" where id = ").append(id);

	if (mysql_query(getMysql(), query.c_str()) != 0)
		cout << "Ops... nao foi possivel atualizar o usuario " << nome << "." << endl;
	else
		cout << "O ususario " << nome << " foi atualizado com sucesso" << endl;
}

void ControlUpdate::atualizarReceita() {
	string id, nome, rendimento, tempo, info, email;
	string query = "select * from receitas";
	getUtil()->imprimeDados(getMysql(), query.c_str());

	cout << "\nInforme o id da receita: ";
	cin.ignore();
	getline(cin, id);
	id = getUtil()->testSqlInjection(getMysql(), id);
	query.append(id);

	cout << "Informe o nome da receita: ";
	getline(cin, nome);
	nome = getUtil()->testSqlInjection(getMysql(), nome);

	cout << "Informe o rendimento da receita: ";
	getline(cin, rendimento);
	rendimento = getUtil()->testSqlInjection(getMysql(), rendimento);

	cout << "Informe o tempo da receita: ";
	getline(cin, tempo);
	tempo = getUtil()->testSqlInjection(getMysql(), tempo);

	cout << "Informe o info da receita: ";
	getline(cin, info);
	info = getUtil()->testSqlInjection(getMysql(), info);

	query.assign("UPDATE receitas set nome = ")
		.append("'").append(nome).append("'")
		.append(", rendimento = ")
		.append("'").append(rendimento).append("'")
		.append(", tempo = ")
		.append("'").append(tempo).append("'")
		.append(", info = ")
		.append("'").append(info).append("'")
		.append(" where id = ").append(id);

	if (mysql_query(getMysql(), query.c_str()) != 0)
		cout << "Ops... nao foi possivel atualizar a receita " << nome << "." << endl;
	else
		cout << "A receita " << nome << " foi atualizada com sucesso" << endl;
}

void ControlUpdate::atualizarFoto() {
	string receita_id, arquivo, novo_arquivo;
	string query = "select * from receitas_fotos";
	getUtil()->imprimeDados(getMysql(), query.c_str());

	cout << "\nInforme o id da receita: ";
	cin.ignore();
	getline(cin, receita_id);
	receita_id = getUtil()->testSqlInjection(getMysql(), receita_id);

	cout << "Informe a foto da receita: ";
	getline(cin, arquivo);
	arquivo = getUtil()->testSqlInjection(getMysql(), arquivo);

	cout << "Informe a novo foto da receita: ";
	getline(cin, novo_arquivo);
	novo_arquivo = getUtil()->testSqlInjection(getMysql(), novo_arquivo);

	query.assign("UPDATE receitas_fotos set arquivo = ")
		.append("'").append(novo_arquivo).append("'")
		.append(" where receita_id = ").append(receita_id)
		.append(" and arquivo = '").append(arquivo).append("'");

	if (mysql_query(getMysql(), query.c_str()) != 0) {
		cout << "Nao fossivel atualizar o nome da foto da receita" << endl;
	} else
		cout << "A foto da receita foi atualizada com sucesso" << endl;
}

void ControlUpdate::atualizarReceitaIngrediente() {
	string receita_id, ingrediente_id, quantidade, unidade;
	string query = "select id, nome from receitas";
	getUtil()->imprimeDados(getMysql(), query.c_str());

	cout << "\nInforme o id da receita: ";
	cin.ignore();
	getline(cin, receita_id);
	receita_id = getUtil()->testSqlInjection(getMysql(), receita_id);

	query.assign("select * from receitas_ingredientes where receita_id = ").append(receita_id);
	getUtil()->imprimeDados(getMysql(), query.c_str());

	cout << "\nInforme o id do ingrediente: ";
	getline(cin, ingrediente_id);
	ingrediente_id = getUtil()->testSqlInjection(getMysql(), ingrediente_id);

	cout << "Informe quantidade do ingrediente: ";
	getline(cin, quantidade);
	quantidade = getUtil()->testSqlInjection(getMysql(), quantidade);

	cout << "Informe unidade do ingrediente: ";
	getline(cin, unidade);
	unidade = getUtil()->testSqlInjection(getMysql(), unidade);

	query.assign("UPDATE receitas_ingredientes set quantidade = ")
		.append(quantidade).append(", unidade = '").append(unidade).append("'")
		.append(" where receita_id = ").append(receita_id)
		.append(" and ingrediente_id =").append(ingrediente_id);
	cout << "query: " << query << endl;

	if (mysql_query(getMysql(), query.c_str()) != 0)
		cout << "Ops... nao foi possivel atualizar as informacoes do ingrediente." << endl;
	else
		cout << "O ingrediente da receita foi atualizado com sucesso" << endl;
}

void ControlUpdate::atualizarReceitaEtapa() {
	string receita_id, numero, novo_numero, titulo;
	string query = "select id, nome from receitas";
	getUtil()->imprimeDados(getMysql(), query.c_str());

	cout << "\nInforme o id da receita: ";
	cin.ignore();
	getline(cin, receita_id);
	receita_id = getUtil()->testSqlInjection(getMysql(), receita_id);

	query.assign("select numero, titulo from receitas_etapas where receita_id = ").append(receita_id);
	getUtil()->imprimeDados(getMysql(), query.c_str());

	cout << "\nInforme o numero da etapa: ";
	getline(cin, numero);
	numero = getUtil()->testSqlInjection(getMysql(), numero);

	cout << "Informe o titulo da etapa: ";
	getline(cin, titulo);
	titulo = getUtil()->testSqlInjection(getMysql(), titulo);

	query.assign("UPDATE receitas_etapas set titulo = ")
		.append("'").append(titulo).append("'")
		.append(" where receita_id = ").append(receita_id)
		.append(" and numero = ").append(numero);
	cout << "query: " << query << endl;

	if (mysql_query(getMysql(), query.c_str()) != 0)
		cout << "Ops... nao foi possivel atualizar a etapa da receita." << endl;
	else
		cout << "A etapa " << numero << " foi atualizada com sucesso" << endl;
}

void ControlUpdate::atualizarReceitaPassos() {
	string receita_id, etapa_numero, sequencia, nova_sequencia, introducao;
	string query = "select * from receitas";
	getUtil()->imprimeDados(getMysql(), query.c_str());

	cout << "\nInforme o id da receita: ";
	cin.ignore();
	getline(cin, receita_id);
	receita_id = getUtil()->testSqlInjection(getMysql(), receita_id);

	query.assign("select * from receitas_etapas where receita_id = ").append(receita_id);
	getUtil()->imprimeDados(getMysql(), query.c_str());

	cout << "\nInforme o numero da etapa: ";
	getline(cin, etapa_numero);
	etapa_numero = getUtil()->testSqlInjection(getMysql(), etapa_numero);

	query.assign("select * from receitas_passos where receita_id = ")
		.append(receita_id).append(" and etapa_numero = ")
		.append(etapa_numero);
	getUtil()->imprimeDados(getMysql(), query.c_str());

	cout << "Informe a sequencia do passo: ";
	getline(cin, sequencia);
	sequencia = getUtil()->testSqlInjection(getMysql(), sequencia);

	cout << "Informe a nova sequencia do passo: ";
	getline(cin, nova_sequencia);
	nova_sequencia = getUtil()->testSqlInjection(getMysql(), nova_sequencia);

	cout << "Informe uma introducao do passo: ";
	getline(cin, introducao);
	introducao = getUtil()->testSqlInjection(getMysql(), introducao);

	query.assign("UPDATE receitas_passos set ")
		.append("sequencia = ")
		.append("").append(nova_sequencia).append("")
		.append(", instrucao = ")
		.append("'").append(introducao).append("'")
		.append(" where receita_id = ").append(receita_id)
		.append(" and etapa_numero = ").append(etapa_numero)
		.append(" and sequencia = ").append(sequencia);

	if (mysql_query(getMysql(), query.c_str()) != 0)
		cout << "Ops... nao foi possivel atualizar o passo da etapa." << endl;
	else
		cout << "O passo da etapa foi atualizado com sucesso" << endl;
}