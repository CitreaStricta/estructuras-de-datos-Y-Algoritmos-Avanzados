#include <string>
#include <queue>
#include <map>
#include <fstream>
#include <iostream>
using namespace std;

struct node
{
    string str;
    int frec;
    node* child0;
    node* child1;

};

// resive un puntero a la raiz del arbol, un puntero a un int que cuenta los bits totales
// y un int que funciona como un contador de recurciones.
// Como lo unico que requiero es la cantidad de bits que se usaron para codificar la regla
// solo necesito un contador de recursiones para saber cuandos bits tiene la codificacion del caracter
// y no si es un 0 o un 1.
// esta funcion tambien ejecuta los delete de cada nodo del arbol al terminar de usarlo
void compressedFile_Size(node *top, long long int *bTotales, int* nTotales, int bits)
{
    node* lChild = top->child0;
    node* rChild = top->child1;
    while (lChild != nullptr && rChild != nullptr)
    {
        // accedo al hijo izquierdo
        compressedFile_Size(lChild, bTotales, nTotales, bits + 1);
        top->child0 = nullptr;
        // accedo al hijo derecho 
        compressedFile_Size(rChild, bTotales, nTotales, bits + 1);
        top->child1 = nullptr;
        delete top;
        *nTotales += 1;
        return;
    }
    // si llega aqui => estamos en una hoja

    *bTotales += (top->frec)*bits;
    *nTotales += 1;
    delete top;
}

void make_tree(priority_queue<pair<int, node*>>* pq)
{
    // necesito un while pq sea mayor a 1, continuar
    node* nNode = nullptr;
    int newFrec = 0;
    pair<int, node*> pair0;
    pair<int, node*> pair1;
    
    while(pq->size() > 1)
    {
        nNode = new node();
        nNode->child0 = nNode->child1 = nullptr;
        
        // tomo hijo 0 y lo apunto con child0 del nNode
        pair0 = pq->top();
        newFrec = pair0.first;
        nNode->child0 = pair0.second;
        nNode->str = pair0.second->str;
        pq->pop();
        // tomo hijo 1 y lo apunto con child1 del nNode
        pair1 = pq->top();
        newFrec += pair1.first;
        nNode->child1 = pair1.second;
        nNode->str += pair1.second->str;
        pq->pop();
        // guardo el nNode en la pq y le doi una nueva frecuencia igual a newFrec

        nNode->frec = newFrec;
        pq->push(make_pair(newFrec, nNode));
        nNode = nullptr;
        newFrec = 0;
    }
}

void make_mHeap(map<string, int>* map_of_frec, priority_queue<pair<int, node*>>* pq)
{
    node* nNodo = nullptr;
    auto itb = map_of_frec->begin();
    auto ite = map_of_frec->end();
    int frec;
    while(itb != ite)
    {
        // preparar el nodo a pushear
        nNodo = new node();
        nNodo->str = itb->first;
        nNodo->child0 = nNodo->child1 = nullptr;
        frec = itb->second;
        nNodo->frec = -frec;
        pq->push(make_pair(-frec, nNodo));
        nNodo = nullptr;
        itb++;
    }
}

// una funcion que devuelva el preso en bits del archivo y guarde en un mapa las palabras o caracteres con sus frecuencias 
long long int preprocess(map<string, int>* map_of_frec, char* f, int t)
{
    long long int fileSize_inBits = 0;
    char c;
    string word;
    
    ifstream file;
    file.open(f, ios::out);
    if (file.is_open())
    {
        if (t == 0)
        { // si se quiere comprimir por palabras
            while(file >> word)
            {
                fileSize_inBits += word.length() * 8;
                // leo un caracter, lo guardo en el mapa y le aumento su frecuencia
                auto par_notIn = map_of_frec->insert(make_pair(word, 1));
                if(!par_notIn.second)
                { // si el par ya existia aumento su frecuencia
                    par_notIn.first->second++;
                }
            }
            file.close();
            return fileSize_inBits;
        }
        else
        { // si se quiere comprimir por caracteres
            while(file.get(c))
            {
                fileSize_inBits += 8;
                // leo un caracter, lo guardo en el mapa y le aumento su frecuencia
                auto par_notIn = map_of_frec->insert(make_pair(string(1, c), 1));
                if(!par_notIn.second)// si el par ya existia aumento su frecuencia
                    par_notIn.first->second++;
            }
            file.close();
            return fileSize_inBits;
        }
    }
    return -1;
}

void fake_compress(char* f, char* t)
{
    int type;
    t++;
    char x = *t;
    
    (x == 'w') ? type = 0: type = 1;
    
    map<string, int>* map_of_frec = new map<string, int>();
    long long int fileSize_inBits = preprocess(map_of_frec, f, type);

    auto pq = new priority_queue<pair<int, node*>>();

    make_mHeap(map_of_frec, pq);

    make_tree(pq);
    node* n = pq->top().second;

    long long int bitsTotales = 0;
    long long int *ptrBT = &bitsTotales;
    
    int nodosTotales = 0;
    int *ptrNT = &nodosTotales;

    compressedFile_Size(pq->top().second, ptrBT, ptrNT, 0);
    pq->pop();
    cout <<
    "el archivo comprimido pesa: " << -bitsTotales << " bits\n" <<
    "  El archivo original pesa: " << fileSize_inBits << " bits\n" <<
    "Ratio de compresion: " << ((long double)-bitsTotales/(long double)fileSize_inBits)*100 << "%\n" <<
    "Nodos totales: " << nodosTotales <<
    endl;

    delete pq;
    delete map_of_frec;
}

int main(int argc, char *argv[])
{

    fake_compress(argv[2], argv[1]);

    return 0;
}