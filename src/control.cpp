#include "control.hpp"

Control::Control(MYSQL *mysql) { this->mysql = mysql; }

Control::~Control() {}

void Control::adicionarIngrediente() {
    string nome;
    string query;

    cout << "Informe o nome do ingrediente: ";
    cin.ignore();
    getline(cin, nome);

    query.assign("INSERT INTO ingredientes (nome) VALUES ('").append(nome).append("');");

    if (mysql_query(this->mysql, query.c_str()) != 0)
        cout << "Ops... nao foi possivel cadastrar o ingrediente " << nome << "." << endl;
    else
        cout << "O ingrediente " << nome << " foi cadastrado com sucesso" << endl;
}

void Control::adicionarUsuario() {
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

    if (mysql_query(this->mysql, query.c_str()) != 0)
        cout << "Ops... nao foi possivel cadastrar o usuario " << nome << "." << endl;
    else
        cout << "O usuario " << nome << " foi cadastrado com sucesso" << endl;
}

void Control::adicionarReceita(string id_usuario) {
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

    if (mysql_query(this->mysql, query.c_str()) != 0)
        cout << "Ops... nao foi possivel cadastrar a receita " << nome << "." << endl;
    else
        cout << "A receita " << nome << " foi cadastrado com sucesso" << endl;
}

void Control::carregarReceitas() {
    string query = "select * from receitas order by nome";

    mysql_query(this->mysql, query.c_str());
    MYSQL_RES *resultado = mysql_store_result(mysql);
    MYSQL_ROW linha;

    Receita *rec;

    while ((linha = mysql_fetch_row(resultado))) {
        rec = new Receita(linha[0], linha[2], linha[3], linha[4]);

        if (linha[1] != NULL) buscarUsuarioPorId(rec, linha[1]);

        buscarIngredientesDaReceita(rec);
        buscarEtapasDaReceita(rec);

        this->receitas.push_back(*rec);
    }
    for (Receita r : receitas) r.toString();
}

void Control::buscarIngredientesDaReceita(Receita *rec) {
    string query = "select * from vw_receitas_ingredientes where receita_id = ";
    query.append(rec->getId());

    mysql_query(this->mysql, query.c_str());
    MYSQL_RES *resultado = mysql_store_result(mysql);
    MYSQL_ROW linha;

    Ingrediente *ing;
    while ((linha = mysql_fetch_row(resultado))) {
        ing = new Ingrediente(linha[1], linha[2], linha[3], linha[4]);
        rec->setIngredientes(*ing);
    }
}

void Control::buscarUsuarioPorId(Receita *rec, string id) {
    string query = "select id, nome from usuarios where id = ";
    query.append(id);

    mysql_query(this->mysql, query.c_str());
    MYSQL_RES *resultado = mysql_store_result(mysql);
    MYSQL_ROW linha;

    Usuario *usu = new Usuario();

    while ((linha = mysql_fetch_row(resultado))) {
        usu->setId(linha[0]);
        usu->setNome(linha[1]);
        rec->setUsuario(*usu);
    }
}

void Control::buscarEtapasDaReceita(Receita *rec) {
    string query = "select * from receitas_etapas where receita_id = ";
    query.append(rec->getId());

    mysql_query(this->mysql, query.c_str());
    MYSQL_RES *resultado = mysql_store_result(mysql);
    MYSQL_ROW linha;

    while ((linha = mysql_fetch_row(resultado))) {
        Etapa *etapa = new Etapa(linha[0], linha[1], linha[2]);
        buscarPassosDaEtapa(etapa);
        rec->setEtapas(*etapa);
    }
}

void Control::buscarPassosDaEtapa(Etapa *etapa) {
    string query = "select * from receitas_passos where receita_id = ";
    query
        .append(etapa->getCodigoReceita())
        .append(" and ")
        .append("etapa_numero = ").append(etapa->getNumero());

    mysql_query(this->mysql, query.c_str());
    MYSQL_RES *resultado = mysql_store_result(mysql);
    MYSQL_ROW linha;

    while ((linha = mysql_fetch_row(resultado))) {
        Passo passo(linha[2], linha[3]);
        etapa->setPassos(passo);
    }
}