#ifndef CONTROL_HPP
#define CONTROL_HPP

#include <iostream>
#include <mysql/mysql.h>
#include <vector>
#include <map>

#include "receita.hpp"
#include "util.hpp"

using namespace std;

class Control {
private:
    vector<Receita> receitas;
    MYSQL *mysql;
    Util *util;
public:
    Control(MYSQL *mysql, Util *util);
    ~Control();

    MYSQL *getMysql();
    Util *getUtil();

    void removerLinha(string query);
    void construirQueryRemocao(string tabela);

    void adicionarIngrediente();

    void adicionarUsuario();
    void buscarUsuarioPorId(Receita *rec, string id);

    void adicionarReceita(string id_usuario);
    void carregarReceitas(string nomeReceita);
    void buscarIngredientesDaReceita(Receita *rec);
    void buscarEtapasDaReceita(Receita *rec);
    void buscarPassosDaEtapa(Etapa *etapa);
    void buscarReceitaPorIngrediente(string ingrediente);
    void buscarReceitaPorId(string id);

    void removerReceitaEmCascata();
    void removerIngredientesDaReceita(Receita *rec);
    void removerEtapasDaReceita(Receita *rec);
    void removerPassosDaEtapa(Etapa *etapa);

    void atualizarIngrediente();
};

#endif