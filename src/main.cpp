#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#include "ingrediente.hpp"
#include <string.h>
#include <stdbool.h>

int conexao_banco(MYSQL *mysql, char *host, char *usuario, char *senha, char *banco);
int menu();
int menuTeste();
void imprimeDados(MYSQL *mysql, const char *query);

bool login(MYSQL *mysql, string usuario, string senha);
bool checkCredencial(MYSQL *mysql, int codigo, string senha);

int main() {
    char usuario[] = "aluno";
    char senha[] = "Senh@Alun0";
    char banco[] = "cefet_receitas";
    char host[] = "127.0.0.1";

    MYSQL *mysql = mysql_init(NULL);
    if (conexao_banco(mysql, host, usuario, senha, banco) == EXIT_FAILURE) return EXIT_FAILURE;

    string user = "admin";
    string password = "123456";

    if (!(login(mysql, user, password))) {
        cout << "Usuario ou senha invalida" << endl;
    } else {
        cout << "senha correta" << endl;
    }

    return EXIT_SUCCESS;

    int opcao;
    do {
        system("clear");
        opcao = menu();

        if (opcao == 1) {
            printf("\nPesquisar receita por nome\n\n");
        } else if (opcao == 2) {
            /*printf("\nPesquisa de Receita por engrediente\n\n");
            mysql_query(conexao, "SELECT * FROM contatos");
            MYSQL_RES* resultado = mysql_store_result(conexao);
            int n_col = mysql_num_fields(resultado);
            MYSQL_ROW linha;
            while (linha = mysql_fetch_row(resultado)){
                printf("(%s)-(%s)-(%s)-(%s)\n",linha[0],linha[1],linha[2],linha[3]);
            }*/
        } else if (opcao == 3) {
            printf("\nEntrar\n\n");
        } else if (opcao == 4) {
            system("clear");

            char nome[100];
            int op2 = menuTeste();
            cout << endl;

            if (op2 == 1) {
                printf("\nCadastro de Ingrediente\n\n");

                cout << "Informe o nome do ingrediente: ";
                cin.ignore();
                scanf(" %[^\n]", nome);

                char query[200];

                sprintf(query, "INSERT INTO ingredientes (nome) VALUES ('%s')", nome);

                if (mysql_query(mysql, query) != 0)
                    cout << "Ops... nao foi possivel cadastrar o ingrediente " << nome << "." << endl;
                else
                    cout << "O ingrediente " << nome << " foi cadastrado com sucesso" << endl;

            } else if (op2 == 2) {
                string query;
                query.assign("SELECT * FROM ingredientes");
                imprimeDados(mysql, query.c_str());
            } else {
                cout << "Opcao invalida!" << endl;
            }
            // printf("\nCadastro de Receitas\n\n");
            /*printf("Nome: ");
            char nome[65];
            scanf(" %[^\n]", nome);
            printf("Telefone: ");
            char telefone[65];
            scanf(" %[^\n]", telefone);
            printf("E-mail: ");
            char email[65];
            scanf(" %[^\n]", email);
            char query[1024];
            sprintf(query, "INSERT INTO contatos (nome, telefone, email) VALUES ('%s', '%s', '%s')",
            nome, telefone, email);
            if(mysql_query(conexao, query) != 0){
                printf("Oops... não conseguir cadastrar seu contato.\n");
            }*/
        } else if (opcao == 0) {
            printf("Até logo!\n\n");

            mysql_close(mysql);
            return EXIT_SUCCESS;
        } else {
            printf("opção escolhida não é válida...\n");
        }
        system("read -p \"\nPressione enter para continuar...\" continue");
    } while (opcao != 0);

    return EXIT_SUCCESS;
}

int conexao_banco(MYSQL *mysql, char *host, char *usuario, char *senha, char *banco) {
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

int menu() {
    int opcao;

    printf("MENU\n\n");
    printf("[1] Pesquisar receita por nome\n");
    printf("[2] Pesquisar receita por engrediente\n");
    printf("[3] Entrar\n");
    printf("[4] Cadastrar teste\n");
    printf("[0] Sair\n\n");
    printf(">>> ");

    scanf("%d", &opcao);

    return opcao;
}

int menuTeste() {
    int opcao;

    cout << "MENU CADASTRO" << endl << endl;
    cout << "[1] Cadastrar Ingrediente" << endl;
    cout << "[2] Buscar Ingredientes" << endl << endl;
    printf(">>> ");

    cin >> opcao;

    return opcao;
}

void imprimeDados(MYSQL *mysql, const char *query) {
    mysql_query(mysql, query);
    MYSQL_RES *resultado = mysql_store_result(mysql);
    MYSQL_ROW linha;

    int n_col = mysql_num_fields(resultado);
    int aux_nCol;

    while (linha = mysql_fetch_row(resultado)) {
        aux_nCol = 0;

        while (aux_nCol < n_col) {
            if (linha[aux_nCol] != NULL) cout << "(" << linha[aux_nCol] << ")\t";
            aux_nCol++;
        }
        cout << endl;
    }
}

bool login(MYSQL *mysql, string usuario, string senha) {
    string query = "select id, nome from usuarios";

    int codigo;
    string nome;

    mysql_query(mysql, query.c_str());
    MYSQL_RES *resultado = mysql_store_result(mysql);
    MYSQL_ROW linha;

    while (linha = mysql_fetch_row(resultado)) {
        codigo = stoi(linha[0]);
        nome = linha[1];

        cout << codigo << " " << nome << endl;

        if (nome.compare(usuario) == 0) {
            if (checkCredencial(mysql, codigo, senha)) return true;
            return false;
        }
    }
    return false;
}

bool checkCredencial(MYSQL *mysql, int codigo, string senha) {
    string query = "select * from credenciais";

    int codigo_credencial;
    string senha_credencial;

    mysql_query(mysql, query.c_str());
    MYSQL_RES *resultado = mysql_store_result(mysql);
    MYSQL_ROW linha;

    while (linha = mysql_fetch_row(resultado)) {
        codigo_credencial = stoi(linha[0]);
        senha_credencial = linha[1];

        if (senha.compare(senha_credencial) == 0)  return true;
    }
    return false;
}