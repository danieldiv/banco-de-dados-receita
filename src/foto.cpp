#include "foto.hpp"

Foto::Foto() {}

Foto::Foto(string arquivo) {
	setArquivo(arquivo);
}

Foto::~Foto() {}

void Foto::setArquivo(string arquivo) { this->arquivo = arquivo; }
string Foto::getArquivo() { return this->arquivo; }