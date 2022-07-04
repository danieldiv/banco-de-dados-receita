#include "curtida.hpp"

Curtida::Curtida() {}
Curtida::Curtida(string usu, string estrelas) {
	setUsuario(usu);
	setEstrelas(estrelas);
}
Curtida::~Curtida() {}

void Curtida::setUsuario(string usu) { this->usu = usu; }
string Curtida::getUsuario() { return this->usu; }

void Curtida::setEstrelas(string estrelas) { this->estrelas = estrelas; }
string Curtida::getEstrelas() { return this->estrelas; }

void Curtida::toString() {
	cout << getUsuario() << " - " << getEstrelas() << endl;
}