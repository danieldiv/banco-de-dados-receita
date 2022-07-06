#include "control.hpp"

Control::Control(MYSQL *mysql, Util *util) {
    this->ctr_delete.setMysql(mysql);
    this->ctr_delete.setUtil(util);

    this->ctr_select.setMysql(mysql);
    this->ctr_select.setUtil(util);

    this->ctr_insert.setMysql(mysql);
    this->ctr_insert.setUtil(util);

    this->ctr_update.setMysql(mysql);
    this->ctr_update.setUtil(util);

    setMysql(mysql);
    setUtil(util);
}

Control::~Control() {}

ControlDelete Control::getControlDelete() { return this->ctr_delete; }
ControlSelect Control::getControlSelect() { return this->ctr_select; }
ControlInsert Control::getControlInsert() { return this->ctr_insert; }
ControlUpdate Control::getControlUpdate() { return this->ctr_update; }

MYSQL *Control::getMysql() { return this->mysql; }
Util *Control::getUtil() { return this->util; }

void Control::setMysql(MYSQL *mysql) { this->mysql = mysql; }
void Control::setUtil(Util *util) { this->util = util; }

void Control::opcoesInsert(int op) {
    if (op == 1)
        getControlInsert().adicionarIngrediente();
    else if (op == 2)
        getControlInsert().adicionarUsuario();
    else if (op == 3)
        getControlInsert().adicionarReceita(to_string(getUtil()->getId()));
    else if (op == 4)
        getControlInsert().adicionarIngredienteReceitas();
    else if (op == 5)
        getControlInsert().adicionarEtapasReceita();
    else if (op == 6)
        getControlInsert().adicionarPassoNaEtapa();
    else if (op == 7)
        getControlInsert().adicionarComentarioReceita();
    else if (op == 8)
        getControlInsert().adicionarCurtidaReceita();
    else if (op == 9)
        getControlInsert().adicionarFotoReceita();
    else if (op == 10)
        getControlInsert().receitaExperimentar(to_string(getUtil()->getId()));
    else if (op == 0)
        return;
    else
        cout << "Opcao invalida" << endl;
}

void Control::opcoesSelect(int op) {
    string query = "select * from ";

    if (op == 1) {
        getUtil()->imprimeDados(getMysql(), query.append("ingredientes").c_str());
    } else if (op == 2) {
        getControlSelect().carregarUsuarios();
    } else if (op == 3) {
        getControlSelect().carregarReceitas(getMysql(), "");
    } else if (op == 4) {
        getUtil()->imprimeDados(getMysql(), query.append("comentarios").c_str());
    } else if (op == 5) {
        getUtil()->imprimeDados(getMysql(), query.append("curtidas").c_str());
    } else if (op == 6) {
        getUtil()->imprimeDados(getMysql(), query.append("receitas_fotos").c_str());
    } else if (op == 0) {
        return;
    } else {
        cout << "Opcao invalida" << endl;
    }
}

void Control::opcoesUpdate(int op) {
    if (op == 1)
        getControlUpdate().atualizarIngrediente();
    else if (op == 2)
        getControlUpdate().atualizarUsuario();
    else if (op == 3)
        getControlUpdate().atualizarReceita();
    else if (op == 4)
        getControlUpdate().atualizarFoto();
    else if (op == 5)
        getControlUpdate().atualizarReceitaIngrediente();
    else if (op == 6)
        getControlUpdate().atualizarReceitaEtapa();
    else if (op == 7)
        getControlUpdate().atualizarReceitaPassos();
    else if (op == 0)
        return;
    else
        cout << "Opcao invalida" << endl;
}

void Control::opcoesDelete(int op) {
    string query;

    if (op == 1) {
        getControlDelete().construirQueryRemocao("ingredientes");
    } else if (op == 2) {
        getControlDelete().construirQueryRemocao("usuarios");
    } else if (op == 3) {
        getControlDelete().removerReceitaEmCascata();
    } else if (op == 4) {
        query.assign("select id, nome from receitas");

        if (getUtil()->imprimeDados(getMysql(), query.c_str())) {
            string receita_id;

            cout << "\nInforme o codigo da receita: ";
            cin.ignore();
            getline(cin, receita_id);

            query.assign("select ingrediente_id, nome from vw_receitas_ingredientes");
            query.append(" where receita_id = ").append(receita_id);

            if (getUtil()->imprimeDados(getMysql(), query.c_str())) {
                string ingrediente_id;

                cout << "\nInforme o codigo do ingrediente: ";
                getline(cin, ingrediente_id);

                getControlDelete().removerIngredienteDaReceita(receita_id, ingrediente_id);
            }
        }
    } else if (op == 5) {
        query.assign("select id, nome from receitas");

        if (getUtil()->imprimeDados(getMysql(), query.c_str())) {
            string receita_id;

            cout << "\nInforme o codigo da receita: ";
            cin.ignore();
            getline(cin, receita_id);

            query.assign("select numero, titulo from receitas_etapas")
                .append(" where receita_id = ").append(receita_id);

            if (getUtil()->imprimeDados(getMysql(), query.c_str())) {
                string etapa_numero;

                cout << "\nInforme o codigo da etapa: ";
                getline(cin, etapa_numero);

                getControlDelete().removerEtapaDaReceita(receita_id, etapa_numero);
            }
        }
    } else if (op == 6) {
        query.assign("select id, nome from receitas");

        if (getUtil()->imprimeDados(getMysql(), query.c_str())) {
            string receita_id;

            cout << "\nInforme o codigo da receita: ";
            cin.ignore();
            getline(cin, receita_id);

            query.assign("select numero, titulo from receitas_etapas")
                .append(" where receita_id = ").append(receita_id);

            if (getUtil()->imprimeDados(getMysql(), query.c_str())) {
                string etapa_numero;

                cout << "\nInforme o codigo da etapa: ";
                getline(cin, etapa_numero);

                query.assign("select sequencia, instrucao from receitas_passos")
                    .append(" where receita_id = ").append(receita_id)
                    .append(" and etapa_numero = ").append(etapa_numero);

                if (getUtil()->imprimeDados(getMysql(), query.c_str())) {
                    string sequencia;

                    cout << "\nInforme o codigo da sequencia: ";
                    getline(cin, sequencia);

                    getControlDelete().removerPassoDaEtapa(receita_id, etapa_numero, sequencia);
                }
            }
        }
    } else if (op == 7) {
        getControlDelete().removerReceitaDoUsuario();
    } else if (op == 0) {
        return;
    } else {
        cout << "Opcao invalida" << endl;
    }
}