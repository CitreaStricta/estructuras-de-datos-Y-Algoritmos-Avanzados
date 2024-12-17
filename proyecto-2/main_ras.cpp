#include <iostream>
#include "raster.h"

int main(int argc, char const *argv[]) // compilar con: g++ -std=c++17 -O3 -DNDEBUG -I ~/include -L ~/lib program.cpp -o program -lsdsl -ldivsufsort -ldivsufsort64
{ // ruta a los data sets que se uso /home/vicen/p/edaa/proyectos/dos-dos/data/
    if(argc < 2)
    {
        cout << "Es necesaria la ruta al directorio donde los data sets estan\n" << endl;
        return 0;
    }
    string ruta = argv[1];

    cout << "Data set 8x8" << endl;
    raster ras(8, ruta + "8x8");
    ras.set_int_vector();
    ras.get_Entropy();
    cout << "Entropia de data_set " << "'8x8': " <<  ras.get_Entropy() << endl;
    ras.convert_to_succinct_version();
    ras.creark2Tree();
    ras.matrizDiferencias();

    srand(time(NULL));
    int n;
    int rep = 1000000;
    double time, duracion;
    clock_t start;
    start = clock();
    for (int i = 0; i < rep; i++)
    {
        ras.v_at(3944);
    }
    duracion = (double)(clock()-start)/CLOCKS_PER_SEC/rep;
    cout << "tiempo de busqueda usando el int_vector v: ";
    cout << setprecision(20) << fixed << n << "," << duracion/(double)rep << endl;

    start = clock();
    for (int i = 0; i < rep; i++)
    {
        ras.at(3944);
    }
    duracion = (double)(clock()-start)/CLOCKS_PER_SEC/rep;
    cout << "tiempo de busqueda usando vPrima, el bit map y la operacion rank: ";
    cout << setprecision(20) << fixed << n << "," << duracion/(double)rep << endl;

    
    ras.informe();

    cout << "Data set 128x128" << endl;
    raster ras1(128, ruta + "128x128");
    ras1.set_int_vector();
    ras1.get_Entropy();
    cout << "Entropia de data_set " << "'128x128': " <<  ras1.get_Entropy() << endl;
    ras1.convert_to_succinct_version();
    ras1.creark2Tree();
    ras1.matrizDiferencias();

    for (int i = 0; i < rep; i++)
    {
        ras1.v_at(100000);
    }
    duracion = (double)(clock()-start)/CLOCKS_PER_SEC/rep;
    cout << "tiempo de busqueda usando el int_vector v: ";
    cout << setprecision(20) << fixed << n << "," << duracion/(double)rep << endl;

    start = clock();
    for (int i = 0; i < rep; i++)
    {
        ras1.at(100000);
    }
    duracion = (double)(clock()-start)/CLOCKS_PER_SEC/rep;
    cout << "tiempo de busqueda usando vPrima, el bit map y la operacion rank: ";
    cout << setprecision(20) << fixed << n << "," << duracion/(double)rep << endl;

    ras1.informe();

    cout << "Data set 512x512" << endl;
    raster ras2(512, ruta + "512x512");
    ras2.set_int_vector();
    ras2.get_Entropy();
    cout << "Entropia de data_set " << "'512x512': " <<  ras2.get_Entropy() << endl;
    ras2.convert_to_succinct_version();
    ras2.creark2Tree();
    ras2.matrizDiferencias();

    for (int i = 0; i < rep; i++)
    {
        ras2.v_at(1000000);
    }
    duracion = (double)(clock()-start)/CLOCKS_PER_SEC/rep;
    cout << "tiempo de busqueda usando el int_vector v: ";
    cout << setprecision(20) << fixed << n << "," << duracion/(double)rep << endl;

    start = clock();
    for (int i = 0; i < rep; i++)
    {
        ras2.at(1000000);
    }
    duracion = (double)(clock()-start)/CLOCKS_PER_SEC/rep;
    cout << "tiempo de busqueda usando vPrima, el bit map y la operacion rank: ";
    cout << setprecision(20) << fixed << n << "," << duracion/(double)rep << endl;

    ras2.informe();
// ----------------- experimentos de tiempo -----------------

/* EJEMPLO UTILIZADO PARA ENTENDER EL FUNCIONAMIENTO DE RANK
    int_vector<> v = {3, 3, 3, 2, 1, 5, 5, 5, 7, 7, 7};  //este parte de 0 a n-1
    bit_vector b =   {1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0};  //este parte de 1 a n
    int_vector<> vPrima = {3, 2, 1, 5, 7};               //este parte de 0 a n-1

    sd_vector<> sdb(b);
    sd_vector<>::rank_1_type sdb_rank(&sdb);
    int i;
    cin >> i;
+
    cout << "Rank es: " << sdb_rank(i) << " en v hay: " << v[i - 1] << " que debe ser igual a vPrima que es:  " << vPrima[sdb_rank(i) - 1] << endl;
*/
    return 0;
}
