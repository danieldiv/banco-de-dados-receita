#ifndef CURTIDA_HPP
#define CURTIDA_HPP

#include <iostream>

#include "usuario.hpp"

using namespace std;

class Curtida {
private:
	string usu;
	string estrelas;
public:
	Curtida();
	Curtida(string usu, string estrelas);
	~Curtida();

	void toString();

	void setUsuario(string usu);
	string getUsuario();

	void setEstrelas(string estrelas);
	string getEstrelas();
};

#endif