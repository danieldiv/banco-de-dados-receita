#include "util.hpp"

Util::~Util() {}

Util::Util() { setStatus(false); }

void Util::login(MYSQL *mysql) {
    if (getStatus()) {
        setStatus(false);
        setUser("");
        cout << "Logout com sucesso" << endl;
    } else {
        string user = "admin";
        string password = "123456";

        cin.ignore();

        // cout << "Usuario: ";
        // getline(cin, user);

        // cout << "Senha: ";
        // getline(cin, password);
        if (!(checkUsuario(mysql, user, password))) {
            cout << "\nUsuario ou senha invalida" << endl;
        } else {
            setUser(user);
            setStatus(true);
            cout << "\nBem vindo " << getUser() << endl;
        }
    }
}

bool Util::checkUsuario(MYSQL *mysql, string usuario, string senha) {
    string query = "select id, nome from usuarios";

    int codigo;
    string nome;

    mysql_query(mysql, query.c_str());
    MYSQL_RES *resultado = mysql_store_result(mysql);
    MYSQL_ROW linha;


    while ((linha = mysql_fetch_row(resultado))) {
        codigo = stoi(linha[0]);
        nome = linha[1];

        if (nome.compare(usuario) == 0) {
            if (checkCredencial(mysql, codigo, senha)) {
                setId(codigo);
                return true;
            }
            return false;
        }
    }
    return false;
}

bool Util::checkCredencial(MYSQL *mysql, int codigo, string senha) {
    string query = "select * from credenciais";

    string codigo_credencial;
    string senha_credencial;

    mysql_query(mysql, query.c_str());
    MYSQL_RES *resultado = mysql_store_result(mysql);
    MYSQL_ROW linha;

    while ((linha = mysql_fetch_row(resultado))) {
        codigo_credencial = linha[0];
        senha_credencial = linha[1];

        if (codigo_credencial.compare(to_string(codigo)) == 0)
            if (senha.compare(senha_credencial) == 0)  return true;
    }
    return false;
}

int Util::conexao_banco(MYSQL *mysql, char *host, char *usuario, char *senha, char *banco) {
    if (mysql == NULL) {
        printf("Não foi possível carregar o cliente MySQL\n");
        return EXIT_FAILURE;
    }
    if (mysql_real_connect(mysql, host, usuario, senha, banco, 0, NULL, 0) == NULL) {
        printf("Não foi possível conectar ao SGBD\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

bool Util::imprimeDados(MYSQL *mysql, const char *query) {
    mysql_query(mysql, query);
    MYSQL_RES *resultado = mysql_store_result(mysql);
    MYSQL_ROW linha;

    if (resultado == NULL) {
        cout << "Query invalida" << endl;
        return false;
    } else if (mysql_affected_rows(mysql) == 0) {
        cout << "Empty set" << endl;
        return false;
    }

    int n_col = mysql_num_fields(resultado);
    int aux_nCol;

    while ((linha = mysql_fetch_row(resultado))) {
        aux_nCol = 0;

        while (aux_nCol < n_col) {
            if (linha[aux_nCol] != NULL) printf("(%s)\t", linha[aux_nCol]);
            aux_nCol++;
        }
        cout << endl;
    }
    return true;
}

string Util::getDataAtual() {
    time_t now;
    struct tm *tm_now;
    char texto[20];

    time(&now);
    tm_now = localtime(&now);
    strftime(texto, sizeof(texto), "%Y/%m/%d %H:%M:%S", tm_now);

    string str = texto;

    return str;
}

void Util::setStatus(bool status) {
    this->status = status;
}

bool Util::getStatus() {
    return this->status;
}

void Util::setUser(string user) {
    this->user.assign(user);
}

string Util::getUser() {
    return this->user;
}

void Util::setId(long id) {
    this->id = id;
}

long Util::getId() {
    return this->id;
}