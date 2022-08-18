#ifndef INVERTEDINDEX
#define INVERTEDINDEX

#include <iostream>

using namespace std;

template <typename tipoLista>
class invertedIndex
{
private:
    map<string, tipoLista> idxMap;
public:
    invertedIndex();
    ~invertedIndex();
    void insert(const string s, const tipoLista);
    vector<int> interseccion(const string &s1, const string &s2);
};

template <typename tipoLista>
invertedIndex<tipoLista>::invertedIndex(){};

template <typename tipoLista>
invertedIndex<tipoLista>::~invertedIndex(){};


template <typename tipoLista>
void invertedIndex<tipoLista>::insert(const string s, const tipoLista ts)
{
    idxMap.insert(make_pair(s, ts));
};

// Entregame dos palabras s1 y s2 y te dare un vector con los matchs
template <typename tipoLista>
vector<int> invertedIndex<tipoLista>::interseccion(const string &s1, const string &s2)
{
    vector<int> ocurrencias;
    auto mapE = idxMap.end();
    auto w1 = idxMap.find(s1);
    auto w2 = idxMap.find(s2);

    if(w1 == mapE || w2 == mapE)
    {
        cout << "una o mas de las palabras no aparece en los archivos\n" << endl;
        return ocurrencias;
    }
    
    // cout << w1->first << " " << w2->first <<  endl;
    auto vecw1 = w1->second;
    auto vecw2 = w2->second;
    int sizeofw1 = vecw1.size();
    int sizeofw2 = vecw2.size();
    
    for (int i = 0, j = 0; i < sizeofw1 && j < sizeofw2;)
    {
        //cout 
        //<< vecw1[i] << " " << i << " " << sizeofw1 << " " << vecw2[j] << " " << j << " " << sizeofw2 << endl;
        
        if(vecw1[i] == vecw2[j])
        {
            ocurrencias.push_back(vecw1[i]); // ambos valores son iguales. Pude haber guardado vecw2[j]
            i++;
            j++;
        }
        else
            if (vecw1[i] < vecw2[j])
                i++;
            else
                j++;
    }
    return ocurrencias;
};
#endif