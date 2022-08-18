#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

class SparseTable {                              // OOP style
private:
  vi A, P2, L2;
  vector<vi> SpT;                                // the Sparse Table
public:
  SparseTable() {}                               // default constructor

  SparseTable(vi &initialA) {                    // pre-processing routine
    A = initialA;
    int n = (int)A.size();
    int L2_n = (int)log2(n)+1;
    P2.assign(L2_n, 0);
    L2.assign(1<<L2_n, 0);
    for (int i = 0; i <= L2_n; ++i) {
      P2[i] = (1<<i);                            // to speed up 2^i
      L2[(1<<i)] = i;                            // to speed up log_2(i)
    }
    for (int i = 2; i < P2[L2_n]; ++i)
      if (L2[i] == 0)
        L2[i] = L2[i-1];                         // to fill in the blanks

    // the initialization phase
    SpT = vector<vi>(L2[n]+1, vi(n));
    for (int j = 0; j < n; ++j)
      SpT[0][j] = j;                             // RMQ of sub array [j..j]

    // the two nested loops below have overall time complexity = O(n log n)
    for (int i = 1; P2[i] <= n; ++i)             // for all i s.t. 2^i <= n
      for (int j = 0; j+P2[i]-1 < n; ++j) {      // for all valid j
        int x = SpT[i-1][j];                     // [j..j+2^(i-1)-1]
        int y = SpT[i-1][j+P2[i-1]];             // [j+2^(i-1)..j+2^i-1]
        SpT[i][j] = A[x] <= A[y] ? x : y;
      }
  }

  int RMQ(int i, int j) {
    int k = L2[j-i+1];                           // 2^k <= (j-i+1)
    int x = SpT[k][i];                           // covers [i..i+2^k-1]
    int y = SpT[k][j-P2[k]+1];                   // covers [j-2^k+1..j]
    return A[x] <= A[y] ? x : y;
  }
};

class SegmentTree {                              // OOP style
private:
  int n;                                         // n = (int)A.size()
  vi A, st, lazy;                                // the arrays

  int l(int p) { return  p<<1; }                 // go to left child
  int r(int p) { return (p<<1)+1; }              // go to right child

  int conquer(int a, int b) {
    if (a == -1) return b;                       // corner case
    if (b == -1) return a;
    return min(a, b);                            // RMQ
  }

  void build(int p, int L, int R) {              // O(n)
    if (L == R)
      st[p] = A[L];                              // base case
    else {
      int m = (L+R)/2;
      build(l(p), L  , m);
      build(r(p), m+1, R);
      st[p] = conquer(st[l(p)], st[r(p)]);
    }
  }

  void propagate(int p, int L, int R) {
    if (lazy[p] != -1) {                         // has a lazy flag
      st[p] = lazy[p];                           // [L..R] has same value
      if (L != R)                                // not a leaf
        lazy[l(p)] = lazy[r(p)] = lazy[p];       // propagate downwards
      else                                       // L == R, a single index
        A[L] = lazy[p];                          // time to update this
      lazy[p] = -1;                              // erase lazy flag
    }
  }

  int RMQ(int p, int L, int R, int i, int j) {   // O(log n)
    propagate(p, L, R);                          // lazy propagation
    if (i > j) return -1;                        // infeasible
    if ((L >= i) && (R <= j)) return st[p];      // found the segment
    int m = (L+R)/2;
    return conquer(RMQ(l(p), L  , m, i          , min(m, j)),
                   RMQ(r(p), m+1, R, max(i, m+1), j        ));
  }

  void update(int p, int L, int R, int i, int j, int val) { // O(log n)
    propagate(p, L, R);                          // lazy propagation
    if (i > j) return;
    if ((L >= i) && (R <= j)) {                  // found the segment
      lazy[p] = val;                             // update this
      propagate(p, L, R);                        // lazy propagation
    }
    else {
      int m = (L+R)/2;
      update(l(p), L  , m, i          , min(m, j), val);
      update(r(p), m+1, R, max(i, m+1), j        , val);
      int lsubtree = (lazy[l(p)] != -1) ? lazy[l(p)] : st[l(p)];
      int rsubtree = (lazy[r(p)] != -1) ? lazy[r(p)] : st[r(p)];
      st[p] = (lsubtree <= rsubtree) ? st[l(p)] : st[r(p)];
    }
  }

public:
  SegmentTree(int sz) : n(sz), st(4*n), lazy(4*n, -1) {}

  SegmentTree(const vi &initialA) : SegmentTree((int)initialA.size()) {
    A = initialA;
    build(1, 0, n-1);
  }

  void update(int i, int j, int val) { update(1, 0, n-1, i, j, val); }

  int RMQ(int i, int j) { return RMQ(1, 0, n-1, i, j); }
};

// int main() {
//   // same example as in Chapter 2: Segment Tree
//   vi A = {18, 17, 13, 19, 15, 11, 20};
//   SparseTable SpT(A);
//   int n = (int)A.size();
//   for (int i = 0; i < n; ++i)
//     for (int j = i; j < n; ++j)
//       printf("RMQ(%d, %d) = %d\n", i, j, SpT.RMQ(i, j));
//   return 0;
// }

int main()
{
  // vi A = {18, 17, 13, 19, 15, 11, 20};
  //SparseTable SpT(A);
  // int n = (int)A.size();
  // for (int i = 0; i < n; ++i)
  //   for (int j = i; j < n; ++j)
  // printf("RMQ(%d, %d) = %d\n", i, j, SpT.RMQ(i, j));

  vi vec;

  srand(time(NULL));
  int random, L, R;
  int rep = 200;
  double time, duracion;
  int nElementosXResultado = 50000;
  int cant_valores_Tabla = 20;
  clock_t start;

  for (int n = nElementosXResultado; n <= nElementosXResultado*cant_valores_Tabla; n += nElementosXResultado)
  {
    // limpio los vectores
    vec.clear();

    // los lleno con valores random
    for (int i = 0; i < n; i++)
    {
      random = rand();
      vec.push_back(random);
    }

    // inicializo dos numeros random que esten dentro del intervalo [0, n-1]
    R = rand() % (vec.size());
    L = rand() % (R+1); // para que L no sea mayor a R

    start = clock();
    for (int i = 0; i < rep; i++)
    {
      SparseTable Prueba_SpT(vec);                                 // Velocidad de buildeo de SpT
    }
    duracion = (double)(clock()-start)/CLOCKS_PER_SEC/rep;

    cout << setprecision(10) << fixed << n << "," <<  duracion/(double)rep << endl;

    SparseTable SpT(vec);
    start = clock();
    for (int i = 0; i < rep; i++)
    {
      SpT.RMQ(L, R);                                            // Velocidad de busqueda de Spt
    }
    duracion = (double)(clock()-start)/CLOCKS_PER_SEC/rep;

    cout << setprecision(10) << fixed << n << "," <<  duracion/(double)rep << endl;

    start = clock();
    for (int i = 0; i < rep; i++)
    { // a lo que le quiero calcular el tiempo
      SegmentTree prueba_st(vec);                               // Velocidad de buildeo de ST
    }
    duracion = (double)(clock()-start)/CLOCKS_PER_SEC/rep;

    cout << setprecision(10) << fixed << n << "," <<  duracion/(double)rep << endl;

    SegmentTree st(vec);
    start = clock();
    for (int i = 0; i < rep; i++)
    {
      st.RMQ(L, R);                                             // Velocidad de buildeo de ST
    }
    duracion = (double)(clock()-start)/CLOCKS_PER_SEC/rep;

    cout << setprecision(10) << fixed << n << "," <<  duracion/(double)rep << endl;
  }
  return 0;
}