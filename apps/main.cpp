#include "util.hpp"
#include "control.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menu(Util *util);
void gerenciamento(MYSQL *mysql, Util *util);
int menuGerenciamento();
int menuExclusao();

int main() {
    Util *util = new Util;

    // printf("%s\n", mysql_get_client_info());

    char usuario[] = "aluno";
    char senha[] = "Senh@Alun0";
    char banco[] = "cefet_receitas";
    char host[] = "127.0.0.1";

    MYSQL *mysql = mysql_init(NULL);
    if (util->conexao_banco(mysql, host, usuario, senha, banco) == EXIT_FAILURE) return EXIT_FAILURE;

    Control *control = new Control(mysql, util);

    string nomeReceita, nomeIngrediente;

    int opcao;
    do {
        if (system("clear") == -1)cout << "erro no system" << endl;
        opcao = menu(util);

        switch (opcao) {
        case 1:
            cout << "Informe o nome da receita: ";
            cin.ignore();
            getline(cin, nomeReceita);

            if (nomeReceita.length() > 0)
                control->getControlSelect().carregarReceitas(nomeReceita);
            else
                cout << "\nNao foi informada a receita" << endl;
            break;
        case 2:
            cout << "Informe o nome da receita: ";
            cin.ignore();
            getline(cin, nomeIngrediente);

            if (nomeIngrediente.length() > 0)
                control->getControlSelect().buscarReceitaPorIngrediente(nomeIngrediente);
            else
                cout << "\nNao foi informado o ingrediente" << endl;
            break;
        case 3:
            util->login(mysql);
            break;
        case 4:
            if (util->getStatus())
                gerenciamento(mysql, util);
            else
                printf("opção invalida...\n");
            break;
        case 0:
            printf("Até logo!\n\n");

            delete util;
            delete control;
            mysql_close(mysql);

            return EXIT_SUCCESS;
        default:
            printf("opção invalida...\n");
            break;
        }
        if (system("read -p \"\nPressione enter para continuar...\" continue") == -1)cout << "erro no system" << endl;
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

    cin >> opcao;

    return opcao;
}

void gerenciamento(MYSQL *mysql, Util *util) {
    int op;

    Control *control = new Control(mysql, util);

    do {
        if (system("clear") == -1)cout << "erro no system" << endl;
        op = menuGerenciamento();

        switch (op) {
        case 1:
            control->getControlInsert().adicionarIngrediente();
            break;
        case 2:
            util->imprimeDados(mysql, "select * from ingredientes order by nome");
            break;
        case 3:
            control->getControlInsert().adicionarUsuario();
            break;
        case 4:
            util->imprimeDados(mysql, "select * from usuarios");
            break;
        case 5:
            control->getControlInsert().adicionarReceita(to_string(util->getId()));
            break;
        case 6:
            control->getControlSelect().carregarReceitas("");
            break;
        case 7:
            control->getControlDelete().construirQueryRemocao("ingredientes");
            break;
        case 8:
            control->getControlDelete().construirQueryRemocao("usuarios");
            break;
        case 10:
            control->getControlDelete().removerReceitaEmCascata();
            break;
        case 11:
            control->getControlUpdate().atualizarIngrediente();
            break;
        case 12:
            control->getControlInsert().adicionarIngredienteReceitas();
        case 0:
            delete control;
            return;
        default:
            cout << "Opcao invalida" << endl;
            break;
        }
        if (system("read -p \"\nPressione enter para continuar...\" continue") == -1)cout << "erro no system" << endl;
    } while (op != 0);
}

int menuGerenciamento() {
    int opcao;

    cout << "MENU GERENCIAMENTO" << endl << endl;
    cout << "[ 1] Cadastrar Ingrediente" << endl;
    cout << "[ 2] Imprimir Ingredientes" << endl;
    cout << "[ 3] Cadastrar Usuario" << endl;
    cout << "[ 4] Imprimir Usuarios" << endl;
    cout << "[ 5] Castrar Receita" << endl;
    cout << "[ 6] Imprimir Receitas" << endl << endl;

    cout << "[ 7] Remover Ingrediente" << endl;
    cout << "[ 8] Remover Usuario" << endl;
    cout << "[10] Remover Receita em cascata" << endl;

    cout << "[11] Atualizar Ingrediente" << endl;

    cout << "[12] Adicionar ingrediente na receita" << endl;
    cout << "[ 0] Voltar" << endl << endl;
    cout << ">>> ";

    cin >> opcao;

    return opcao;
}