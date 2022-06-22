#include "control.hpp"

Control::Control() {}

Control::~Control() {}

void Control::adicionarIngrediente(MYSQL *mysql) {
    string nome;
    string query;

    cout << "Informe o nome do ingrediente: ";
    cin.ignore();
    getline(cin, nome);

    query.assign("INSERT INTO ingredientes (nome) VALUES ('").append(nome).append("');");

    if (mysql_query(mysql, query.c_str()) != 0)
        cout << "Ops... nao foi possivel cadastrar o ingrediente " << nome << "." << endl;
    else
        cout << "O ingrediente " << nome << " foi cadastrado com sucesso" << endl;
}

void Control::adicionarUsuario(MYSQL *mysql) {
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

    query.assign("INSERT INTO usuarios (nome, telefone, email, cidade, estado, foto) VALUES ")
        .append("('").append(nome).append("','")
        .append(telefone).append("','")
        .append(email).append("','")
        .append(cidade).append("','")
        .append(estado).append("','")
        .append(foto).append("');");

    if (mysql_query(mysql, query.c_str()) != 0)
        cout << "Ops... nao foi possivel cadastrar o usuario " << nome << "." << endl;
    else
        cout << "O usuario " << nome << " foi cadastrado com sucesso" << endl;
}

void Control::adicionarReceita(MYSQL *mysql, string id_usuario) {
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

    query.assign("INSERT INTO receitas (usuario_id, nome, rendimento, tempo) VALUES ")
        .append("(").append(id_usuario).append(",'")
        .append(nome).append("','")
        .append(rendimento).append("','")
        .append(tempo).append("');");

    if (mysql_query(mysql, query.c_str()) != 0)
        cout << "Ops... nao foi possivel cadastrar a receita " << nome << "." << endl;
    else
        cout << "A receita " << nome << " foi cadastrado com sucesso" << endl;
}