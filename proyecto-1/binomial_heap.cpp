#include "binomial_heap.h"

binomial_heap::binomial_heap()
{
    _arrRoots = new vector<node*>();
}


binomial_heap::~binomial_heap()
{
    node* handlerPtr = nullptr;
    for (int i = 0; i < _arrRoots->size(); i++)
    {
        if (_arrRoots->at(i) != nullptr)
        {
            handlerPtr = _arrRoots->at(i);
            _recursiveDelete(handlerPtr);
            _arrRoots->at(i) = nullptr;
            handlerPtr = nullptr;
        }
    }
    
    delete _arrRoots;
}

void binomial_heap::_recursiveDelete(node* handlerPtr)
{
    node* thisNode = handlerPtr;
    for (int i = 0; i < thisNode->childPtrs->size(); i++)
    { // si no hay punteros en el vector, no entra aqui
        handlerPtr = thisNode->childPtrs->at(i);
        _recursiveDelete(handlerPtr);
        thisNode->childPtrs->at(i) = nullptr; // desreferencio por seguridad
        handlerPtr == nullptr; // desreferencio por seguridad
    }
    delete thisNode->childPtrs; // borro el vector de punteros del nodo
    thisNode->childPtrs = nullptr; // desreferencio el puntero al vector por seguridad
    delete thisNode; // borro el nodo
}

// funcion recursiva para insertar elementos
void binomial_heap::_insertSpecific(int indice, node* handlerPtr)
{
    // si en los punteros a raices no hay un puntero en [indice], lo creo
    if (_arrRoots->size() == indice) _arrRoots->push_back(nullptr);

    // insercion del nuevo nodo en el arreglo de las raices
    // if no hay un nodo en indice. Es decir, si el ptr [indice] en _arrRoots == nullptr
    if (_arrRoots->at(indice) == nullptr)
    {// meto el nodo en ese espacio y retorno
        _arrRoots->at(indice) = handlerPtr;
        handlerPtr = nullptr;
    }
    else
    {// si hay un nodo en ese indice entonces hay que revisar cual tiene el menor valor
        if (_arrRoots->at(indice)->val < handlerPtr->val) // ojo, para los dos casos siguientes (el que sea) sera necesario meterle un puntero de nodo al vector del nodo menor
        {   // si el nodo viejo es menor que el nuevo
            // agrego el nodo nuevo en el vector de punteros del nodo viejo
            _arrRoots->at(indice)->childPtrs->push_back(handlerPtr);
            // hago que handlerPtr apunte al nodo viejo (el con el menor valor)
            handlerPtr = _arrRoots->at(indice);
            // desreferencio el puntero en _arrRoots que estaba apuntando al nodo viejo
            _arrRoots->at(indice) = nullptr;
            // ahora que los punteros estan todos en orden. En handlerPtr se encuentra un binomial tree de orden = k+1.
            // este mismo hace un tiempo atras estaba en el lugar de orden = k. Ahora necesito moverlo al lugar del vector
            // de raices que le corresponde segun su orden.
            _insertSpecific(indice + 1, handlerPtr);
            handlerPtr = nullptr;
        }
        else // nodo nuevo es menor
        {
            // agrego el puntero al nodo viejo al vector de punteros del nodo nuevo
            handlerPtr->childPtrs->push_back(_arrRoots->at(indice));
            // handlerPtr ya esta apuntando al nodo con el menor valor
            // desreferencio el puntero en _arrRoots que estaba apuntando al nodo viejo
            _arrRoots->at(indice) = nullptr;
            // ahora que los punteros estan todos en orden. En handlerPtr se encuentra un binomial tree de orden = k+1.
            // este mismo hace un tiempo atras estaba en el lugar de orden = k. Ahora necesito moverlo al indice del vector
            // de raices que le corresponde segun su orden
            _insertSpecific(indice + 1, handlerPtr);
            handlerPtr = nullptr;
        }
    }
    //return;
}

void binomial_heap::insert(int val)
{
    node* handlerPtr = new node();
    handlerPtr->val = val;
    handlerPtr->childPtrs = new vector<node*>();
    auto it = _arrRoots->begin();
    _insertSpecific(0, handlerPtr);
}

int binomial_heap::find()
{
    auto it = _arrRoots->begin();
    auto itE = _arrRoots->end();
    int min = INT32_MAX;
    // no puedo decir "min = (*it)->val" porque el 1er puntero puede estar apuntando a nullptr
    while (it != itE)
    {
        if ((*it) != nullptr && (*it)->val < min)
        {
            min = (*it)->val;
        }
        it++;
    }
    return min;
}

// merge de los dos heaps en heap1
void binomial_heap::merge(binomial_heap* bin2)
{
    node* handlerPtr = nullptr;
    auto binomial_ToMerge = bin2->_get_PtrToRoots();

    for (int i = 0; i < binomial_ToMerge->size(); i++)
    {// si no entra aqui, no hay elementos para hacer merge
        if (binomial_ToMerge->at(i) != nullptr)
        {
            handlerPtr = binomial_ToMerge->at(i);
            binomial_ToMerge->at(i) = nullptr;
            _insertSpecific(i, handlerPtr);
        }
    }
    
}

void _printTree(vector<node*>* s)
{
    auto itP = s->begin();

    while (itP != s->end())
    {
        cout << (*itP)->val << " ";
        _printTree((*itP)->childPtrs);
        itP++;
    }

}

void _printHeap(vector<node*>* s)
{
    int k = 0;
    auto itP = s->begin();

    while (itP != s->end())
    {
        cout << "arbol con orden " << k << endl;
        if ((*itP) != nullptr)
        {
            cout << (*itP)->val << "  ";
            _printTree((*itP)->childPtrs);
            cout << endl;
        }
        itP++;
        k++;
    }
}

void binomial_heap::printBinomialH()
{
    _printHeap(_arrRoots);
}

vector<node*>* binomial_heap::_get_PtrToRoots()
{
    return _arrRoots;
}