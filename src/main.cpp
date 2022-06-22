#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.hpp"
#include "control.hpp"

int menu(Util *util);
void gerenciamento(MYSQL *mysql, Util *util);
int menuGerenciamento();

int main() {
    Util *util = new Util;

    char usuario[] = "aluno";
    char senha[] = "Senh@Alun0";
    char banco[] = "cefet_receitas";
    char host[] = "127.0.0.1";

    MYSQL *mysql = mysql_init(NULL);
    if (util->conexao_banco(mysql, host, usuario, senha, banco) == EXIT_FAILURE) return EXIT_FAILURE;

    int opcao;
    do {
        system("clear");
        opcao = menu(util);

        switch (opcao) {
        case 1:
            printf("\nPesquisar receita por nome\n\n");
            break;
        case 2:
            break;
        case 3:
            util->login(mysql);
            break;
        case 4:
            gerenciamento(mysql, util);
            break;
        case 0:
            printf("Até logo!\n\n");
            mysql_close(mysql);
            delete util;
            return EXIT_SUCCESS;
        default:
            printf("opção invalida...\n");
            break;
        }
        system("read -p \"\nPressione enter para continuar...\" continue");
    } while (opcao != 0);

    return EXIT_SUCCESS;
}

int menu(Util *util) {
    int opcao;

    cout << "MENU " << util->getUser() << endl << endl;
    cout << "[1] Pesquisar receita por nome" << endl;
    cout << "[2] Pesquisar receita por engrediente" << endl;
    cout << "[3] " << ((util->getStatus()) ? "Logout" : "Entrar") << endl;
    if (util->getStatus()) cout << "[4] Gerenciamento" << endl;
    cout << "[0] Sair" << endl << endl;
    cout << ">>> ";

    scanf("%d", &opcao);

    return opcao;
}

void gerenciamento(MYSQL *mysql, Util *util) {
    int op;
    Control *control = new Control;

    do {
        system("clear");
        op = menuGerenciamento();

        switch (op) {
        case 1:
            control->adicionarIngrediente(mysql);
            break;
        case 2:
            util->imprimeDados(mysql, "select * from ingredientes order by nome");
            break;
        case 3:
            control->adicionarUsuario(mysql);
            break;
        case 4:
            util->imprimeDados(mysql, "select * from usuarios");
            break;
        case 0:
            return;
        default:
            cout << "Opcao invalida" << endl;
            break;
        }
        system("read -p \"\nPressione enter para continuar...\" continue");
    } while (op != 0);
}

int menuGerenciamento() {
    int opcao;

    cout << "MENU GERENCIAMENTO" << endl << endl;
    cout << "[1] Cadastrar Ingrediente" << endl;
    cout << "[2] Imprimir Ingredientes" << endl;
    cout << "[3] Cadastrar Usuario" << endl;
    cout << "[4] Imprimir Usuarios" << endl;
    // cout << "[3] Cadastrar Receita" << endl;
    // cout << "[4] Receitas salvas" << endl;
    cout << "[0] Voltar" << endl << endl;
    cout << ">>> ";

    cin >> opcao;

    return opcao;
}