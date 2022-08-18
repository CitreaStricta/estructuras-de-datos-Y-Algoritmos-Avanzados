#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>
#include "suffixArray.h"

using namespace std;

vector<int> pathernMashing_bf(string txt, string patron)
{
    vector<int> suf_IndicesFB;
    for (int i = 0; i < txt.length(); i++) // O(n)
    {
        if (patron.compare(0, patron.length(), txt, i, patron.length()) == 0) // O(nm)
        {
            suf_IndicesFB.push_back(i);
        }
    }

    return suf_IndicesFB;
}

int main()
{ // zona de pruebas
    string patron = "zscr";
    string texto;

    // cin >> texto;
    // suffixArray *temp = new suffixArray();
    // temp->generarSufijos(texto);
    // temp->ordenarSufijos();
    // temp->save_sufijos_txt();
    // temp->buscarInstanciasPatron(patron);
    // pathernMashing_bf(texto, patron);
    // delete temp;
    // return 0;

    texto.erase();
    patron.erase();

    // zona de experimentos

    // n fijo
    for (int i = 0; i < 10000; i++)
    {
        texto = texto + (char)(97 + rand() % 26);
    }


    srand(time(NULL));
    int rep = 200;

    double time;
    int constante = 2;
    clock_t start;
    for (int n = constante; n <= constante*20; n += constante)
    { // preparacion para calcular tiempo

        vector<int> vec1, vec2;
        //n creciente
        for (int i = 0; i < constante; i++)
        {
            texto = texto + (char)(97 + rand() % 26);
        }

        cout << "texto: " << texto << endl;

        // patron (y su largo) random
        int random = 1 + rand() % 10;
        patron.erase();
        for (int i = 0; i < n; i++)
        {
            patron = patron + (char)(97 + rand() % 26);
        }

        // cout << "patron: " << patron << endl;
        
        suffixArray *temp = new suffixArray();
        temp->generarSufijos(texto);
        temp->ordenarSufijos();

        //cout << "n++ y patron (y largo) random; " << endl;

// experimento 1
        start = clock();
        for (int i = 0; i < rep; i++)
        { // a lo que le quiero calcular el tiempo
            vec1 = temp->buscarInstanciasPatron(patron);
        }
        double duracion = (double)(clock()-start)/CLOCKS_PER_SEC/rep;

// experimento 2

        start = clock();
        for (int i = 0; i < rep; i++)
        {
            vec2 = pathernMashing_bf(texto, patron);
        }
        double duracion2 = (double)(clock()-start)/CLOCKS_PER_SEC/rep;

        //cout << "fuerza bruta; " << n << "; " << duracion << endl;

        cout << n << "; " << duracion << "; " << duracion2 << "; " << endl;
        delete temp;
    }
    return 0;
}