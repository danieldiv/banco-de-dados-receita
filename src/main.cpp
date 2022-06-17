#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int conexao_banco(MYSQL *mysql, char *host, char *usuario, char *senha, char *banco);
int menu();

int main() {
    char usuario[] = "aluno";
    char senha[] = "Senh@Alun0";
    char banco[] = "cefet_receitas";
    char host[] = "127.0.0.1";

    MYSQL *mysql = mysql_init(NULL);
    if (conexao_banco(mysql, host, usuario, senha, banco) == EXIT_FAILURE) return EXIT_FAILURE;

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
            printf("\nCadastro de Receitas\n\n");
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
    printf("[4] Cadastrar\n");
    printf("[0] Sair\n\n");
    printf(">>> ");

    scanf("%d", &opcao);

    return opcao;
}