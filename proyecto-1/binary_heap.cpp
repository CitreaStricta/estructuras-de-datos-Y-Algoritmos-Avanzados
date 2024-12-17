#include "binary_heap.h"

using namespace std;

BinaryHeap::BinaryHeap()
{
}

BinaryHeap::~BinaryHeap()
{
}

void BinaryHeap::insert(const int num)
{
    vec.push_back(num);
    //Padre del nodo: (i-1)/2
    int pos = vec.size() - 1;
    while (pos != 0 && vec[pos] < vec[(pos - 1) / 2])
    {
        int aux = vec[pos];
        vec[pos] = vec[(pos - 1) / 2];
        vec[(pos - 1) / 2] = aux;
        pos = (pos - 1) / 2;
    }
}

int BinaryHeap::searchMin()
{
    return vec[0];
}

vector<int> BinaryHeap::getArray()
{
    return vec;
}
/*
void BinaryHeap::merge(BinaryHeap &h1)
{
    vector<int> v1 = this->vec;
    vector<int> v2 = h1.getArray();

    while (!v2.empty())
    {
        this->insert(v2.back());
        v2.pop_back();
    }
}
*/
void BinaryHeap::merge(BinaryHeap &h1)
{
    vector<int> v2 = h1.getArray();

    vec.insert(vec.end(), v2.begin(), v2.end());

    for(int i=vec.size()/2 -1; i>=0; i--){
        heapify(vec, i);
    }

}

void BinaryHeap::heapify(vector<int> &v, int index){
    int n = v.size();
    if(index>=n)
        return;
    int l = 2 * index + 1;
    int r = 2 * index + 2;
    int min;
    if (l < n && v[l] < v[index])
        min = l;
    else
        min = index;
    if (r < n && v[r] < v[min])
        min = r;
 
    if (min != index) {
        swap(v[min], v[index]);
        heapify(v, min);
    }
}