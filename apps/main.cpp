#include "util.hpp"
#include "control.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menu(Util *util);
void gerenciamento(MYSQL *mysql, Util *util);
int menuGerenciamento();

int main() {
    Util *util = new Util;

    // printf("%s\n", mysql_get_client_info());

    char usuario[] = "aluno";
    char senha[] = "Senh@Alun0";
    char banco[] = "cefet_receitas";
    char host[] = "127.0.0.1";

    MYSQL *mysql = mysql_init(NULL);
    if (util->conexao_banco(mysql, host, usuario, senha, banco) == EXIT_FAILURE) return EXIT_FAILURE;

    // char nomeReceita[64], nomeIngrediente[64];

    int opcao;
    do {
        if (system("clear") == -1)cout << "erro no system" << endl;
        opcao = menu(util);

        switch (opcao) {
        case 1:
            //leonardo
                //util->login(mysql);
                //deverá entrar com usuário com acesso só as receitas
            // printf("\nPesquisar receita por nome\n\n");
            // printf("Digite o nome da receita: ");
            // scanf(" %[^\n]", nomeReceita);
            // printf("Resultado: \n");
            //procura receita especifica
            // util->imprimeDados(mysql, "select * from receitas");
            break;
        case 2:
            //leonado
                //util->login(mysql);
                //Deverá entrar com usuáio com acesso só aos ingredientes
            // printf("Pesquisar receita por engrediente\n");
            // printf("Digite o ingrediente que deseja: ");
            // scanf(" %[^\n]", nomeIngrediente);
            // printf("Resultado: \n");
            //procura ingrediente especifico
            // util->imprimeDados(mysql, "select * from receitas");
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
            mysql_close(mysql);
            delete util;
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
    Control *control = new Control(mysql);

    do {
        if (system("clear") == -1)cout << "erro no system" << endl;
        op = menuGerenciamento();

        switch (op) {
        case 1:
            control->adicionarIngrediente();
            break;
        case 2:
            util->imprimeDados(mysql, "select * from ingredientes order by nome");
            break;
        case 3:
            control->adicionarUsuario();
            break;
        case 4:
            util->imprimeDados(mysql, "select * from usuarios");
            break;
        case 5:
            control->adicionarReceita(to_string(util->getId()));
            break;
        case 6:
            control->carregarReceitas();
            break;
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
    cout << "[1] Cadastrar Ingrediente" << endl;
    cout << "[2] Imprimir Ingredientes" << endl;
    cout << "[3] Cadastrar Usuario" << endl;
    cout << "[4] Imprimir Usuarios" << endl;
    cout << "[5] Castrar receita" << endl;
    cout << "[6] Imprimir receitas" << endl << endl;

    cout << "[7] Remover ingrediente" << endl;
    cout << "[8] Remover usuario" << endl;
    cout << "[9] Remover receita" << endl;
    cout << "[0] Voltar" << endl << endl;
    cout << ">>> ";

    cin >> opcao;

    return opcao;
}