#ifndef INGREDIENTE_HPP
#define INGREDIENTE_HPP

#include <iostream>

using namespace std;

class Ingrediente {
private:
    int id;
    string nome;
public:
    Ingrediente(string nome);
    Ingrediente(int id, string nome);
    ~Ingrediente();

    void setId(int id);
    int getId();

    void setNome(string nome);
    string getNome();
};

#endif