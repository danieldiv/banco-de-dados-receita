#ifndef RECEITA_SALVA
#define RECEITA_SALVA

#include <iostream>

using namespace std;

class ReceitaSalva {
private:
	string usuario_id;
	string receita_id;
public:
	ReceitaSalva();
	ReceitaSalva(string usuario_id, string receita_id);
	~ReceitaSalva();

	void toString();

	void setUsuarioId(string usuario_id);
	void setReceitaId(string receita_id);

	string getUsuarioId();
	string getReceitaId();
};

#endif