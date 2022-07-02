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
	query.append(id);

	cout << "Informe o novo nome do ingrediente: ";
	getline(cin, nome);

	query.assign("UPDATE ingredientes set nome = ")
		.append("'").append(nome).append("'")
		.append(" where id = ").append(id);

	if (mysql_query(getMysql(), query.c_str()) != 0)
		cout << "Ops... nao foi possivel atualizar o ingrediente " << nome << "." << endl;
	else
		cout << "A ingrediente " << nome << " foi atualizado com sucesso" << endl;
}

void ControlUpdate::atualizarUsuario() {
	string id, nome, telefone, email, cidade, estado, foto;
	string query = "select * from usuarios";
	getUtil()->imprimeDados(getMysql(), query.c_str());

	cout << "\nInforme o id do usuario: ";
	cin.ignore();
	getline(cin, id);
	query.append(id);

	cout << "Informe o nome do usuario: ";
	getline(cin, nome);

	cout << "Informe o telefone do usuario: ";
	getline(cin, telefone);

	cout << "Informe o email do usuario: ";
	getline(cin, email);

	cout << "Informe o cidade do usuario: ";
	getline(cin, cidade);

	cout << "Informe o estado do usuario: ";
	getline(cin, estado);

	cout << "Informe o foto do usuario: ";
	getline(cin, foto);

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
	string query = "select * from usuarios";
	getUtil()->imprimeDados(getMysql(), query.c_str());

	cout << "\nInforme o id da receita: ";
	cin.ignore();
	getline(cin, id);
	query.append(id);

	cout << "Informe o nome da receita: ";
	getline(cin, nome);

	cout << "Informe o rendimento da receita: ";
	getline(cin, rendimento);

	cout << "Informe o tempo da receita: ";
	getline(cin, email);

	cout << "Informe o info da receita: ";
	getline(cin, info);

	query.assign("UPDATE usuarios set nome = ")
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

void ControlUpdate::atualizarFoto() {}
void ControlUpdate::atualiozarReceitaIngrediente() {}
void ControlUpdate::atualizarReceitaEtapa() {}
void ControlUpdate::atualizarReceitaPassos() {}