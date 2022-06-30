#include "control_insert.hpp"

ControlInsert::ControlInsert() {}
ControlInsert::~ControlInsert() {}

void ControlInsert::setMysql(MYSQL *mysql) { this->mysql = mysql; }
void ControlInsert::setUtil(Util *util) { this->util = util; }

MYSQL *ControlInsert::getMysql() { return this->mysql; }
Util *ControlInsert::getUtil() { return this->util; }

void ControlInsert::adicionarIngrediente() {
	string nome;
	string query;

	cout << "Informe o nome do ingrediente: ";
	cin.ignore();
	getline(cin, nome);

	query.assign("insert INTO ingredientes (nome) VALUES ('").append(nome).append("');");

	if (mysql_query(getMysql(), query.c_str()) != 0)
		cout << "Ops... nao foi possivel cadastrar o ingrediente " << nome << "." << endl;
	else
		cout << "O ingrediente " << nome << " foi cadastrado com sucesso" << endl;
}

void ControlInsert::adicionarUsuario() {
	string nome;
	string telefone;
	string email;
	string cidade;
	string estado;
	string foto;

	string query;

	cout << "Informe o nome do Usuario: ";
	cin.ignore();
	getline(cin, nome);

	cout << "Informe o telefone: ";
	getline(cin, telefone);

	cout << "Informe o email: ";
	getline(cin, email);

	cout << "Informe a cidade: ";
	getline(cin, cidade);

	cout << "Informe o estado: ";
	getline(cin, estado);

	cout << "Informe a foto: ";
	getline(cin, foto);

	query.assign("insert INTO usuarios (nome, telefone, email, cidade, estado, foto) VALUES ")
		.append("('").append(nome).append("','")
		.append(telefone).append("','")
		.append(email).append("','")
		.append(cidade).append("','")
		.append(estado).append("','")
		.append(foto).append("');");

	if (mysql_query(getMysql(), query.c_str()) != 0)
		cout << "Ops... nao foi possivel cadastrar o usuario " << nome << "." << endl;
	else
		cout << "O usuario " << nome << " foi cadastrado com sucesso" << endl;
}

void ControlInsert::adicionarReceita(string id_usuario) {
	string nome;
	string rendimento;
	string tempo;

	string query;

	cout << "Informe o nome da receita: ";
	cin.ignore();
	getline(cin, nome);

	cout << "Informe o rendimento: ";
	getline(cin, rendimento);

	cout << "Informe o tempo: ";
	getline(cin, tempo);

	query.assign("insert INTO receitas (usuario_id, nome, rendimento, tempo) VALUES ")
		.append("(").append(id_usuario).append(",'")
		.append(nome).append("','")
		.append(rendimento).append("','")
		.append(tempo).append("');");

	if (mysql_query(getMysql(), query.c_str()) != 0)
		cout << "Ops... nao foi possivel cadastrar a receita " << nome << "." << endl;
	else
		cout << "A receita " << nome << " foi cadastrado com sucesso" << endl;

}


/*
[Thomás]:

- Dando erro ao cadastrar
* Arrumar como é passado o id da Receita,
* Se der certo criar opção de adicionar mais ingredientes à receita
*/
void ControlInsert::adicionarIngredienteReceitas() {
	string query = "select id, nome from receitas";
	getUtil()->imprimeDados(getMysql(), query.c_str());

	string id_ingrediente;
	string id_receita;
	string quantidade;
	string unidade;

	cout << "\nInforme id da receita: ";
	cin.ignore();
	getline(cin, id_receita);

	query.assign("select * from receitas where id = ").append(id_receita);

	mysql_query(getMysql(), query.c_str());
	MYSQL_RES *resultado = mysql_store_result(mysql);

	if (resultado == NULL) {
		cout << "Query invalida" << endl;
		return;
	} else if (mysql_affected_rows(mysql) == 0) {
		cout << "Empty set" << endl;
		return;
	}

	cout << endl << "[Adicionando Ingredientes à receita]" << endl << endl;

	query = "select * from ingredientes";
	getUtil()->imprimeDados(getMysql(), query.c_str());

	cout << "\nInforme o id do ingrediente: ";
	// cin.ignore();
	getline(cin, id_ingrediente);

	query.assign("select * from ingredientes where id = ").append(id_ingrediente);

	mysql_query(getMysql(), query.c_str());
	resultado = mysql_store_result(mysql);

	// verifica se a query eh invalida ou se encontrou o id informado
	if (resultado == NULL) {
		cout << "Query invalida" << endl;
		return;
	} else if (mysql_affected_rows(mysql) == 0) {
		cout << "Ingrediente nao encontrado" << endl;
		return;
	}

	cout << "Informe a quantidade: ";
	getline(cin, quantidade);

	cout << "Informe a unidade: ";
	getline(cin, unidade);

	query.assign("insert INTO receitas_ingredientes(receita_id, ingrediente_id, quantidade, unidade) VALUES ")
		.append("(").append(id_receita).append(",")
		.append(id_ingrediente).append(",")
		.append(quantidade).append(",'")
		.append(unidade).append("')");

	if (mysql_query(getMysql(), query.c_str()) != 0)
		cout << "Ops... nao foi possivel cadastrar ingrediente à receita." << endl;
	else
		cout << "O ingrediente foi cadastrado na receita com sucesso" << endl;
}