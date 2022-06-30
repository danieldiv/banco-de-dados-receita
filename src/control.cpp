#include "control.hpp"

Control::Control(MYSQL *mysql, Util *util) {
    this->mysql = mysql;
    this->util = util;
}

Control::~Control() {}

MYSQL *Control::getMysql() { return this->mysql; }
Util *Control::getUtil() { return this->util; }

void Control::removerLinha(string query) {
    if (mysql_query(getMysql(), query.c_str()) != 0)
        cout << "Nao foi possivel excluir a linha" << endl;
    else {
        if (mysql_affected_rows(getMysql()) != 0)
            cout << "Linha removida com sucesso" << endl;
        else
            cout << "Nenhuma linha afetada" << endl;
    }
}

void Control::construirQueryRemocao(string tabela) {
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

void Control::removerReceitaEmCascata() {
    string query = "select id, nome from receitas";
    getUtil()->imprimeDados(getMysql(), query.c_str());

    string id;

    cout << "\nInforme o codigo da receita para excluir: ";
    cin.ignore();
    getline(cin, id);

    // assumindo que o id exista

    string queryIngredientes = "select * from receitas_ingredientes where receita_id = ";
    queryIngredientes.append(id);

    getUtil()->imprimeDados(getMysql(), queryIngredientes.c_str());

    // buscarIngredientesDaReceita(rec);
    // buscarEtapasDaReceita(rec);
}

void Control::adicionarIngrediente() {
    string nome;
    string query;

    cout << "Informe o nome do ingrediente: ";
    cin.ignore();
    getline(cin, nome);

    query.assign("INSERT INTO ingredientes (nome) VALUES ('").append(nome).append("');");

    if (mysql_query(getMysql(), query.c_str()) != 0)
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

    if (mysql_query(getMysql(), query.c_str()) != 0)
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

    if (mysql_query(getMysql(), query.c_str()) != 0)
        cout << "Ops... nao foi possivel cadastrar a receita " << nome << "." << endl;
    else
        cout << "A receita " << nome << " foi cadastrado com sucesso" << endl;
}

void Control::carregarReceitas(string nomeReceita) {
    string query = "select * from receitas";
    query.append(" where nome like '%").append(nomeReceita).append("%'");

    mysql_query(getMysql(), query.c_str());
    MYSQL_RES *resultado = mysql_store_result(mysql);

    if (mysql_num_rows(resultado) > 0) {
        MYSQL_ROW linha;
        Receita *rec;

        while ((linha = mysql_fetch_row(resultado))) {
            rec = new Receita(linha[0], linha[2], linha[3], linha[4]);

            if (linha[1] != NULL) buscarUsuarioPorId(rec, linha[1]);

            buscarIngredientesDaReceita(rec);
            buscarEtapasDaReceita(rec);

            this->receitas.push_back(*rec);
        }
        for (Receita r : this->receitas) r.toString();
    } else
        cout << "\nNenhuma receita encontrada" << endl;
    this->receitas.clear();
}

void Control::buscarIngredientesDaReceita(Receita *rec) {
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

void Control::buscarUsuarioPorId(Receita *rec, string id) {
    string query = "select id, nome from usuarios where id = ";
    query.append(id);

    mysql_query(getMysql(), query.c_str());
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

    mysql_query(getMysql(), query.c_str());
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

    mysql_query(getMysql(), query.c_str());
    MYSQL_RES *resultado = mysql_store_result(mysql);
    MYSQL_ROW linha;

    while ((linha = mysql_fetch_row(resultado))) {
        Passo passo(linha[2], linha[3]);
        etapa->setPassos(passo);
    }
}

void Control::buscarReceitaPorIngrediente(string ingrediente) {
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
        for (itr = mapeamento.begin(); itr != mapeamento.end(); itr++)
            buscarReceitaPorId(itr->first);
    } else cout << "\nNenhuma receita encontrada" << endl;
}

void Control::buscarReceitaPorId(string id) {
    string query = "select * from receitas where id = ";
    query.append(id);

    mysql_query(getMysql(), query.c_str());
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
    for (Receita r : this->receitas) r.toString();
    this->receitas.clear();
}

void Control::atualizarIngrediente() {
    string id, nome;
    string query = "select * from ingredientes where id = ";

    cout << "Informe o id do ingrediente: ";
    cin.ignore();
    getline(cin, id);
    query.append(id);

    getUtil()->imprimeDados(getMysql(),query.c_str());

    mysql_query(getMysql(), query.c_str());
    MYSQL_RES *resultado = mysql_store_result(this->mysql);
    MYSQL_ROW linha;

    Ingrediente *ing = new Ingrediente();

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