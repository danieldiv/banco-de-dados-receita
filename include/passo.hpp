#ifndef PASSO_HPP
#define PASSO_HPP

#include <iostream>

using namespace std;

class Passo {
private:
    string sequencia;
    string instrucao;
public:
    Passo();
    Passo(string sequencia, string instrucao);
    ~Passo();

    void toString();

    void setSequencia(string sequencia);
    void setInstrucao(string instrucao);

    string getSequencia();
    string getInstrucao();
};

#endif