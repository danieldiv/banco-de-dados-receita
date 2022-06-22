#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <mysql/mysql.h>

using namespace std;

class Util {
private:
    bool status;
    string user;
public:
    ~Util();
    Util();
    void login(MYSQL *mysql);
    bool checkUsuario(MYSQL *mysql, string usuario, string senha);
    bool checkCredencial(MYSQL *mysql, int codigo, string senha);

    int conexao_banco(MYSQL *mysql, char *host, char *usuario, char *senha, char *banco);
    void imprimeDados(MYSQL *mysql, const char *query);

    void setStatus(bool status);
    bool getStatus();

    void setUser(string user);
    string getUser();
};

#endif