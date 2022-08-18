#ifndef SUFFIX_ARRAY
#define SUFFIX_ARRAY

#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>

using namespace std;

struct suffix
{
    int pos;
    string sfx; // im srry. I fale you. No time to redo
};

class suffixArray
{
private:
    vector<suffix> *sufijos;

public:
    suffixArray();
    ~suffixArray();
    bool generarSufijos(string &file_name); // tectura de txt y guardar sus sufijos
    void save_sufijos_txt();
    void ordenarSufijos(); // ordenar los sufijos en el vector usando un alg. de orden de forma alfabetica
    int buscarPatron(string patron); // retorna un numero indicativo del lugar donde el 1er caracter se encuentra
    vector<int> buscarInstanciasPatron(string patron);
};

#endif