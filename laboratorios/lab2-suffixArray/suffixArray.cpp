#include <fstream>
#include "suffixArray.h"

suffixArray::suffixArray()
{
    sufijos = new vector<suffix>();
}

suffixArray::~suffixArray()
{
    delete sufijos;
}

bool suffixArray::generarSufijos(string &txt)
{
    suffix aux;
    auto txtIt = txt.crbegin();
    int largo_texto = txt.size();
    for (int i = 0; i < largo_texto; i++)
    {
        aux.pos = largo_texto - i;
        aux.sfx = *(txtIt + i) + aux.sfx;
        sufijos->push_back(aux);
    }

    return true;
}; // lectura del texto y guardado de sufijos

void suffixArray::save_sufijos_txt()
{
    fstream myfile;
    myfile.open("sufijos.txt", ios::out);
    if (myfile.is_open())
    {
        for (int i = 0; i < sufijos->size(); i++)
        {
            myfile << sufijos->at(i).sfx << "\n";
        }
    }
    myfile.close();
}

bool regla(const suffix &a, const suffix &b)
{
    int cmp = a.sfx.compare(b.sfx);
    return cmp <= 0? 1 : 0;
}

void suffixArray::ordenarSufijos()
{
    sort(sufijos->begin(), sufijos->end(), regla);
}; // ordenar los sufijos en el vector usando un alg. de orden de forma alfabetica

int busBin_LBound(const vector<suffix> *vec, string p, int primer, int ultimo)
{
    int medio;
    string string_medio;

    while(primer < ultimo)
    {
        medio = (ultimo + primer)/2;


        string_medio = vec->at(medio).sfx;

        auto cmp = p.compare(0, p.length(), string_medio, 0, p.length());
        // cmp<0 si el string p va antes de strong_medio
        // cmp = 0 si son equivalentes
        // cmp>0 si p va despues de s_m
        if (cmp == 0)
        { // me sirve y no lo puedo eliminar
            ultimo = medio;
        }
        else
        {
            if (cmp < 0)
            {
                ultimo = medio-1;
            }
            else
            {
                primer = medio+1;
            }
        }
    }
    
    return primer;
}

int busBin_Ubound(const vector<suffix> *vec, string p, int primer, int ultimo)
{
    int medio;
    string string_medio;

    while(primer < ultimo)
    {
        medio = 1 + (ultimo + primer)/2;

        string_medio = vec->at(medio).sfx;

        auto cmp = p.compare(0, p.length(), string_medio, 0, p.length());
        if (cmp == 0)
        { // me sirve y no lo puedo eliminar
            primer = medio;
        }
        else
        {
            if (cmp < 0)
            {
                ultimo = medio-1;
            }
            else
            {
                primer = medio+1;
            }
        }
    }
    
    return primer;
}

int suffixArray::buscarPatron(string patron)
{ // algoritmo a base de busqueda binaria
    return busBin_LBound(sufijos, patron, 0, sufijos->size()-1);
}; // retorna el indice donde el 1er caracter del patron se encuentra

vector<int> suffixArray::buscarInstanciasPatron(string patron)
{
    vector<int> suf_Indices;
    int l = busBin_LBound(sufijos, patron, 0, sufijos->size()-1);
    int u = busBin_Ubound(sufijos, patron, 0, sufijos->size()-1);

    // para la implementacion que estoy haciendo de los Bound, existe el caso de que no se encuentre
    // ningun sufijo pero igual se retorne un rango pero este no tendra ninguno de los sufijos buscados.
    // Ese rango de elementos puede generar un "out_of_range" y lo siguiente lo soluciona.
    // Lo unico que hace es asegurarse de que la cota inferior sea efectivamente un sufijo de
    // los buscados (pudo haber sido la cota superior) y si no, entonces puedo concluir que no hay ningun
    // sufijo de los que estoy buscando.
    if (patron.compare(0, patron.length(), sufijos->at(l).sfx, 0, patron.length() != 0))
    {
        return suf_Indices;
    }
    
    while(l <= u)
    {
        suf_Indices.push_back(sufijos->at(l).pos - 1);
        l++;
    }
    
    return suf_Indices;
};
