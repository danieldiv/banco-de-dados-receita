#include "receita_salva.hpp"

ReceitaSalva::ReceitaSalva() {}
ReceitaSalva::ReceitaSalva(string usuario_id, string receita_id) {
	setUsuarioId(usuario_id);
	setReceitaId(receita_id);
}
ReceitaSalva::~ReceitaSalva() {}

void ReceitaSalva::toString() {}

void ReceitaSalva::setUsuarioId(string usuario_id) { this->usuario_id = usuario_id; }
void ReceitaSalva::setReceitaId(string receita_id) { this->receita_id = receita_id; }

string ReceitaSalva::getUsuarioId() { return this->usuario_id; }
string ReceitaSalva::getReceitaId() { return this->receita_id; }