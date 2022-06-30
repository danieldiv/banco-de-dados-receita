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

    string queryIngredientes = "select receita_id, ingrediente_id from receitas_ingredientes where receita_id = ";
    queryIngredientes.append(id);

    // getUtil()->imprimeDados(getMysql(), queryIngredientes.c_str());

    // buscarIngredientesDaReceita(rec);
    // buscarEtapasDaReceita(rec);

    mysql_query(getMysql(), queryIngredientes.c_str());
    MYSQL_RES *resultado = mysql_store_result(mysql);
    MYSQL_ROW linha;

    if (resultado == NULL) {
        cout << "Query invalida" << endl;
    } else if (mysql_affected_rows(mysql) == 0) {
        cout << "Nao possui ingredientes nesta receita" << endl;
    }

    while ((linha = mysql_fetch_row(resultado))) {
        query.assign("delete from receitas_ingredientes where receita_id = ")
            .append(id).append(" and ingrediente_id = ").append(linha[1]);
        // cout << "query: " << query << endl;
        removerLinha(query);
    }

    string queryEtapas = "select receita_id, numero from receitas_etapas where receita_id = ";
    queryEtapas.append(id);

    // getUtil()->imprimeDados(getMysql(), queryEtapas.c_str());

    mysql_query(getMysql(), queryEtapas.c_str());
    resultado = mysql_store_result(mysql);

    if (resultado == NULL) {
        cout << "Query invalida" << endl;
    } else if (mysql_affected_rows(mysql) == 0) {
        cout << "Nao possui etapas nesta receita" << endl;
    }

    while ((linha = mysql_fetch_row(resultado))) {
        // query.assign("delete from receitas_ingredientes where receita_id = ")
        //     .append(id).append(" and numero = ").append(linha[1]);
        // cout << "query: " << query << endl;
        // removerLinha(query);

        string queryPassosDaEtapa = "select receita_id, etapa_numero, sequencia from receitas_passos where receita_id = ";
        queryPassosDaEtapa.append(id).append(" and etapa_numero = ").append(linha[1]);

        // getUtil()->imprimeDados(getMysql(), queryEtapas.c_str());

        mysql_query(getMysql(), queryPassosDaEtapa.c_str());
        MYSQL_RES *resultado2 = mysql_store_result(mysql);
        MYSQL_ROW linha2;

        // cout << "query etapas: " << queryEtapas << endl;
        // cout << "query passos:" << queryPassosDaEtapa << endl;

        while ((linha2 = mysql_fetch_row(resultado2))) {
            queryPassosDaEtapa.assign("delete from receitas_passos where receita_id = ")
                .append(id).append(" and etapa_numero = ").append(linha2[1])
                .append(" and sequencia = ").append(linha2[2]);
            removerLinha(queryPassosDaEtapa);
        }
        queryEtapas.assign("delete from receitas_etapas where receita_id = ")
            .append(id).append(" and numero = ").append(linha[1]);
        // cout << "query: " << queryEtapas << endl;
        removerLinha(queryEtapas);
    }
    query.assign("delete from receitas where id = ").append(id);
    removerLinha(query);
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


/*
[Thomás]:

- Dando erro ao cadastrar
* Arrumar como é passado o id da Receita,
* Se der certo criar opção de adicionar mais ingredientes à receita
*/
void Control::adicionarIngredienteReceitas() {
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

    query.assign("INSERT INTO receitas_ingredientes(receita_id, ingrediente_id, quantidade, unidade) VALUES ")
        .append("(").append(id_receita).append(",")
        .append(id_ingrediente).append(",")
        .append(quantidade).append(",'")
        .append(unidade).append("')");

    if (mysql_query(getMysql(), query.c_str()) != 0)
        cout << "Ops... nao foi possivel cadastrar ingrediente à receita." << endl;
    else
        cout << "O ingrediente foi cadastrado na receita com sucesso" << endl;
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

            if (linha[1] != NULL) rec->setUsuario(buscarUsuarioPorId(linha[1]));

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

Usuario Control::buscarUsuarioPorId(string id) {
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
        // rec->setUsuario(*usu);
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

        if (linha[1] != NULL) rec->setUsuario(buscarUsuarioPorId(linha[1]));

        buscarIngredientesDaReceita(rec);
        buscarEtapasDaReceita(rec);

        this->receitas.push_back(*rec);
    }
    for (Receita r : this->receitas) r.toString();
    this->receitas.clear();
}
