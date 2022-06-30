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
		cout << "Ops... nao foi possivel atualizar o ingrdiente " << nome << "." << endl;
	else
		cout << "A ingrediente " << nome << " foi atualizado com sucesso" << endl;
}
