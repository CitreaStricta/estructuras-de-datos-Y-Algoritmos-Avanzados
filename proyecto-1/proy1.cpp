#include <bits/stdc++.h>
#include "binary_heap.h"
#include "binomial_heap.h"
#include "fibonacci_heap.h"

using namespace std;

int main()
{
    cout << setprecision(10);
    srand(time(NULL));
    int rep = 20;
    double duracion1, duracion2;
    double time;
    int constante = 16383;
    clock_t start;
    for (int n = constante; n <= constante*20; n += constante)
    { // preparacion
        // cout << "datos: " << n << endl;
        // auto binary1 = new BinaryHeap();
        // auto binary2 = new BinaryHeap();
        
        // auto binomial1 = new binomial_heap();
        // auto binomial2 = new binomial_heap();
        
        // auto fibonacci1 = new FibonacciHeap();
        // auto fibonacci2 = new FibonacciHeap();

        auto vecAux1 = vector<int>();
        auto vecAux2 = vector<int>();
        for (int i = 0; i < n; i++)
        {
            int data = rand() % 1000;
            vecAux1.push_back(data);
        }
        
        for (int i = 0; i < n; i++)
        {
            int data = rand() % 1000;
            vecAux2.push_back(data);
        }
        
        for (int i = 0; i < rep; i++)
        {
            auto binary1 = new BinaryHeap();
            auto binary2 = new BinaryHeap();

            auto binomial1 = new binomial_heap();
            auto binomial2 = new binomial_heap();
            int vecSize1 = vecAux1.size();

            for (int j = 0; j < vecSize1; j++)
            {
                binomial1->insert(vecAux1.at(j));
                binary1->insert(vecAux1.at(j));
            }
            auto vecSize2 = vecAux2.size();

            for (int j = 0; j < vecSize2; j++)
            {
                binomial2->insert(vecAux2.at(j));
                binary2->insert(vecAux2.at(j));
            }
            start = clock();
            binary1->merge(*binary2);
            duracion1 += (double)(clock()-start)/CLOCKS_PER_SEC;

            start = clock();
            binomial1->merge(binomial2);
            duracion2 += (double)(clock()-start)/CLOCKS_PER_SEC;

            delete binary1;
            delete binomial1;
            delete binary2;
            delete binomial2;
        }
        //double duracion1 = (double)(clock()-start)/CLOCKS_PER_SEC/rep;

        // cout << "merge binary; " << setprecision(10) << fixed <<  duracion << "; " << endl;

        // start = clock();
        // for (int i = 0; i < rep; i++)
        // {
        //     binomial1->merge(binomial2);
        // }
        // duracion = (double)(clock()-start)/CLOCKS_PER_SEC/rep;

        cout << setprecision(10) << fixed << n << "," <<  duracion1/(double)rep << "," <<  duracion2/(double)rep << endl;
        //n = n+1;

//-----------------------------------------------------------------------------

        // delete binary1;
        // delete binomial1;
        // delete fibonacci1;
        // delete binary2;
        // delete binomial2;
        // delete fibonacci2;
    }
    return 0;
}


/*


La operacion de merge es mas rapida en Binomial Heap que en Binary Heap

La operacion de merge del binomial toma mas tiempo que el binary cuando los datos totales son 2^i-1 (i cualquier numero entero)

*/