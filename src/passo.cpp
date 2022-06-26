#include "passo.hpp"

Passo::Passo() {}

Passo::Passo(string sequencia, string instrucao) {
    setSequencia(sequencia);
    setInstrucao(instrucao);
}

Passo::~Passo() {}

void Passo::setSequencia(string sequencia) { this->sequencia = sequencia; }
void Passo::setInstrucao(string instrucao) { this->instrucao = instrucao; }

string Passo::getSequencia() { return this->sequencia; }
string Passo::getInstrucao() { return this->instrucao; }

void Passo::toString() {
    cout << "\t" << getSequencia() << ".\t" << getInstrucao() << endl;
}