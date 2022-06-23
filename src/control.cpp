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

void Control::carregarReceitas(MYSQL *mysql) {
    string query = "select * from vw_receitas_ingredientes order by receita";

    mysql_query(mysql, query.c_str());
    MYSQL_RES *resultado = mysql_store_result(mysql);
    MYSQL_ROW linha;

    int n_col = mysql_num_fields(resultado);

    Receita *rec;
    Ingrediente *ing;
    Usuario *usu;

    string receita_aux;
    bool controle = true;

    while (linha = mysql_fetch_row(resultado)) {
        rec = new Receita(linha[0], linha[3], linha[4], linha[5]);

        if (linha[1] != NULL) {
            usu = new Usuario(linha[1], linha[2]);
            rec->setUsuario(*usu);
            delete usu;
        }
        if (linha[6] != NULL) rec->setInfo(linha[6]);

        if (linha[7] != NULL) {
            ing = new Ingrediente(linha[7], linha[8], linha[9], linha[10]);
            rec->setIngrediente(*ing);
            delete(ing);
        }
        if (controle) {
            receita_aux = linha[3];
            receitas.push_back(*rec);
            controle = !controle;
        } else {
            if (receita_aux.compare(linha[3]) != 0) {
                receitas.push_back(*rec);
                receita_aux = linha[3];
            }
        }
        delete rec;
    }
    for (Receita r : receitas) {
        r.toString();
    }
}