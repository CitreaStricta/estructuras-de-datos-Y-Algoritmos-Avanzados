#ifndef BINARY_HEAP
#define BINARY_HEAP
#include <vector>
using namespace std;

class BinaryHeap{
    public:
        BinaryHeap();
        ~BinaryHeap();
        void insert (const int num);
        int searchMin();
		vector<int> getArray();
        void merge (BinaryHeap &h1);
    private:
        void heapify(vector<int> &v, int index);
        vector<int> vec;		
};

#endif