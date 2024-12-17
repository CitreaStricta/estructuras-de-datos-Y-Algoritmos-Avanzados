#include <sdsl/vectors.hpp>
#include "invertedIndex.hpp"
#include <map>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;
using namespace sdsl;

int main() //g++ -std=c++17 -O3 -DNDEBUG -I ~/include -L ~/lib *.cpp -o a -lsdsl -ldivsufsort -ldivsufsort64
{
    
#pragma region (1) Lee el archivo y guarda las palabras y su ocurrencia, en cada archivo, en un map
    map<string, vector<int>> mapParss;
    fstream file;
    int maxFsToRead = 1000; // cambiar este numero a uno menor para un preprocesado mas corto
    int file_long = 104857600/1000; //50000/1000;
    file.open("english.100MB", ios::in);
    if(file.is_open())
    {
        int f = 0, c = 0;
        string word;
        while(file >> word && f < maxFsToRead)
        {
            //cout << "file: " << f << " palabra: " << word << " caracter: " << c << endl;
            vector<int> v;
            v.push_back(f);
            auto palabraNoEsta = mapParss.insert(make_pair(word, v));

            if(!palabraNoEsta.second && *(palabraNoEsta.first->second.crbegin()) != f)
                palabraNoEsta.first->second.push_back(f);

            c += word.size();
            if(c > file_long)
            {
                c = 0;
                f++;
            }
        }
        file.close();
    }
#pragma endregion

#pragma region (2) parseo de datos a los templates
    invertedIndex<int_vector<>> conIntVector;
    invertedIndex<enc_vector<coder::elias_delta>> conDelta;
    invertedIndex<enc_vector<coder::elias_gamma>> conGama;

    auto itb = mapParss.cbegin();
    auto ite = mapParss.cend();
    while(itb != ite)
    {   
        auto word = itb->first;
        auto vec = itb->second;

        // paso los datos en mapParss a los distintos vectores
        int_vector<> iv;
        iv.resize(vec.size());
        for (int i = 0; i < vec.size(); i++)
            iv[i] = vec.at(i);
        
        enc_vector<coder::elias_delta> evd(vec);
        enc_vector<coder::elias_gamma> evg(vec);

        conIntVector.insert(itb->first, iv);
        conDelta.insert    (itb->first, evd);
        conGama.insert     (itb->first, evg);
        itb++;
    }
#pragma endregion

#pragma region (3) Testing
    string palabra1, palabra2;
    cout <<
    "dame dos palabras iguales para terminar el testing (las palabras igual se buscaran antes de salir)" << endl;
    while(true)
    {
        cout << "dame la primera palabra" << endl;
        cin >> palabra1;
        cout << "dame la segunda palabra" << endl;
        cin >> palabra2;
        auto matchs = conIntVector.interseccion(palabra1, palabra2);

        if (!matchs.empty())
        {
            cout << "match's" << endl;
            for (int i = 0; i < matchs.size(); i++)
                cout << matchs.at(i) << " ";
            cout << endl << endl;
        }
        else cout << "No hay match's" << endl;
        if(palabra1 == palabra2) break;
    }
#pragma endregion

#pragma region (4) Calculo de tiempos
    cout << "inicio de calculo del tiempo" << endl;
    srand(time(NULL));
    double start;
    int rep = 5000000;
    double duracion;

    start = clock();
    for (int i = 0; i < rep; i++)
    {
        conIntVector.interseccion("the", "the");
    }
    duracion = (double)(clock()-start)/CLOCKS_PER_SEC/rep;
    cout << setprecision(20) << fixed << "," <<  duracion/(double)rep << endl;
    
    start = clock();
    for (int i = 0; i < rep; i++)
    {
        conDelta.interseccion("the", "the");
    }
    duracion = (double)(clock()-start)/CLOCKS_PER_SEC/rep;
    cout << setprecision(20) << fixed << "," <<  duracion/(double)rep << endl;

    start = clock();
    for (int i = 0; i < rep; i++)
    {
        conGama.interseccion("the", "the");
    }
    duracion = (double)(clock()-start)/CLOCKS_PER_SEC/rep;
    cout << setprecision(20) << fixed << "," <<  duracion/(double)rep << endl;
#pragma endregion

    return 0;
}