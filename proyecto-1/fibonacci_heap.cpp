#include <vector>
#include "fibonacci_heap.h"
#include <algorithm>
#include <iostream>

using namespace std;

FibonacciHeap::FibonacciHeap(){
	min = nullptr;
}

FibonacciHeap::~FibonacciHeap(){
	if(min!=nullptr){
		fiNode *temp, *actual;
		actual = min->sig;
		while(actual!=min){
			temp = actual->sig;
			actual->sig = nullptr;
			actual->prev = nullptr;
			actual->padre = nullptr;
			actual->hijo = nullptr;
			delete actual;
			actual = temp;
		}
		min->sig = nullptr;
		min->prev = nullptr;
		min->padre = nullptr;
		min->hijo = nullptr;
		delete min;
	}
}

void FibonacciHeap::insert(const int num){
	fiNode* nuevo = new fiNode;
	nuevo->data = num;
	nuevo->padre = nullptr;
	nuevo->hijo = nullptr;
	nuevo->prev = nuevo;
	nuevo->sig = nuevo;
	if(min==nullptr){
		min = nuevo;
		return;
	}else{
		/*
		Supongamos que tenemos esta lista:
		------------------------
		'-5 <-> 6 <-> 7 <-> 8<-'
		  ^-----------------'
		*/
		fiNode* last = min->prev; //el ultimo nodo es el 8
		last->sig = nuevo; //Antes, el puntero al siguiente nodo del ultimo era el inicio. Ahora, sera el nuevo nodo
		nuevo->prev = last; //Ahora, el puntero al nodo anterior del nuevo nodo, sera el que antes era el ultimo (8)
		min->prev = nuevo; //Antes, el puntero al nodo anterior del primer nodo, era el ultimo nodo. Ahora es el nuevo nodo (que pasa a ser el ultimo)
		nuevo->sig = min; //Finalmente, el nuevo nodo tiene como puntero al siguiente, el primer nodo
		if(nuevo->data < min->data)
			min = nuevo;
		return;
	}
}

int FibonacciHeap::searchMin(){
	if(min == nullptr)
	{
		cout << "no hay elementos el en heap" << endl;
		return -1;
	}
	return min->data;
}

void FibonacciHeap::merge(FibonacciHeap* f2){
	//La idea es tomar el min del nuevo fibonacci heap (f2), e insertarla en la circular doubly linked list 
	//del fibonacci heap actual (this)
	fiNode* min2 = f2->getList();
	fiNode* last2 = min2->prev;

	min->prev->sig = min2;
	last2->sig = min;
	min2->prev = min->prev;
	min->prev = last2;

	auto ppmin = f2->_getList();
	if(min2->data < min->data){
		min = min2;
		(*ppmin) = nullptr;
	}else{
		(*ppmin) = nullptr;
	}
}

struct fiNode* FibonacciHeap::getList(){
	return min;
}

struct fiNode** FibonacciHeap::_getList(){
	auto PPmin = &min;
	return PPmin;
}

void FibonacciHeap::heapify(struct fiNode x){
	/*
		No es necesario implementar delete, pero cuando se borre un elemento, se debe reordenar el Fibonacci Heap
		para que cumpla la propiedad de heap. En este caso, Min-Heap
	*/
}