#ifndef BINOMIAL_HEAP
#define BINOMIAL_HEAP
#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;

struct node
{
    int val;
    vector<node*>* childPtrs;
};

class binomial_heap
{
private:
    vector<node*>* _arrRoots;
    void _insertSpecific(int, node*);
    void _recursiveDelete(node*);
public:
    binomial_heap();
    ~binomial_heap();
    void insert(int);
    int find();
    void merge(binomial_heap*);
    void printBinomialH();
    vector<node*>* _get_PtrToRoots();
};

#endif