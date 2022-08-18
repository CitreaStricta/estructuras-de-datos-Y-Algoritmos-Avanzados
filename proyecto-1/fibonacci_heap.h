#include <string>
#include <algorithm>
#include <vector>
#ifndef FIBONACCI_HEAP
#define FIBONACCI_HEAP


using namespace std;

struct fiNode{
	int data;
	struct fiNode *sig;
	struct fiNode *prev;
	struct fiNode *hijo;
	struct fiNode *padre;
};

class FibonacciHeap{
	public: 
		FibonacciHeap();
		~FibonacciHeap();
		void insert(const int num);
		int searchMin();
		void merge(FibonacciHeap* f1);
		struct fiNode* getList();
	private:
		void heapify(struct fiNode x);
		fiNode** _getList();
		vector<int> vec;
		struct fiNode* min;
};

#endif