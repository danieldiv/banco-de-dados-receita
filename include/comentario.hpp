#ifndef COMENTARIO_HPP
#define COMENTARIO_HPP

#include <iostream>

using namespace std;

class Comentario {
private:
	string usuario;
	string data_hora;
	string mensagem;
public:
	Comentario();
	Comentario(string id, string data_hora, string mensagem);
	~Comentario();

	void setUsuario(string id);
	void setDataHora(string dataHora);
	void setMensagem(string mensagem);

	string getUsuario();
	string getDataHora();
	string getMensagem();

	void toString();
};

#endif