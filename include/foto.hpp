#ifndef FOTO_HPP
#define FOTO_HPP

#include <iostream>

using namespace std;

class Foto {
private:
	string arquivo;
public:
	Foto();
	Foto(string arquivo);
	~Foto();

	void setArquivo(string arquivo);
	string getArquivo();

};

#endif