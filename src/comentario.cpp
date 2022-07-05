#include "comentario.hpp"

Comentario::Comentario() {}
Comentario::Comentario(string id, string data_hora, string mensagem) {
	setUsuario(id);
	setDataHora(data_hora);
	setMensagem(mensagem);
}

Comentario::~Comentario() {}

void Comentario::setUsuario(string id) { this->usuario = id; }
void Comentario::setDataHora(string dataHora) { this->data_hora = data_hora; }
void Comentario::setMensagem(string mensagem) { this->mensagem = mensagem; }

string Comentario::getUsuario() { return this->usuario; }
string Comentario::getDataHora() { return this->data_hora; }
string Comentario::getMensagem() { return mensagem; }

void Comentario::toString() {
	cout << getUsuario() << " " << getDataHora() << " " << getMensagem() << endl;
}