#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>

using namespace std;

int busquedaSecuencial(const vector<int> &vec, int p)
{
    for (int i = 0; i < vec.size(); i++) // O(n)
    {
        if (vec.at(i) == p)
        {
            return i;
        }
    }
    return -1;
}

int busquedaBinaria(const vector<int> &vec, int p, int primer, int ultimo)
{
    int medio;
    int elemento_medio;

    while(primer <= ultimo) // O(log(n))
    {
        medio = primer + floor(ultimo - primer)/2;

        elemento_medio = vec.at(medio);

        if (elemento_medio == p)
        {
            return medio;
        }
        else
        { // es el elemento que estamos revisando menor o mayor al buscado?
            if (elemento_medio < p)
            { // es menor que el buscado (nos vamos al subarreglo derecho)
                primer = medio + 1;
            }
            else
            { // es mayor que el buscado (nos vamos al subarreglo izquierdo)
                ultimo = medio - 1;
            }
        }
    }
    return -1;
}

int busquedaDoblada(const vector<int> &vec, int p)
{
    //La implementacion de la busqueda se optimiza mas si se revisa el primer elemento por separado
    if (vec.at(0) == p)
    {
        return 0;
    }
    
    int ultimo = vec.size() - 1;
    int salto = 1;

    // para evitar que se salte mucho mas alla del ultimo elemento del vector
    // y para detenerce al sobrepasar el numero buscado
    while(salto < ultimo && vec.at(salto) < p) // O(log(n))
    { // "Salto" dentro del vector hasta haber pasado el elemento buscado
        salto *= 2;
    }

     // si el salto 
    if (salto > ultimo)
    {  // SE PASO DEL ULTIMO ELEMENTO DEL VECTOR:
        if (vec.at(ultimo) == p)
        { // reviso el ultimo.
            return ultimo;
        }
        else
        { // Y si no es, uso b_binaria en el subarreglo
            return busquedaBinaria(vec, p, salto/2, ultimo); // O(log(n))
        }
    }
    else
    { // no se paso del ultimo elemento del vector:
        if(vec.at(salto) == p)
        {// reviso el elemento al que salte
            return salto;
        }
        else
        { // Y si no es, uso b_binaria en el subarreglo
            return busquedaBinaria(vec, p, salto/2, salto); // O(log(n))
        }
    }
    
}

int main()
{
    int rep = 300;
    double time;
    double duracion;
    clock_t start;

    for (int n = 50000; n <= 1000000; n += 50000)
    {

        vector<int> vlocal(n, 1); // llena el vector con n unos (1)

        //vlocal[0] = 0; // coloco un 0 en el primer elemento
        //vlocal.push_back(2); // coloco un 2 en el ultimo elemento
        //vlocal.push_back(3); // coloco un 3 en el ultimo elemento para que
                               // la busqueda doblada no encuentre el 2 en la primera pasada

        int num_buscado = 2;

// calculo de busqueda secuencial

        start = clock();
        for (int i = 0; i < rep; i++)
        {// hacemos la busqueda
            busquedaSecuencial(vlocal, num_buscado);
        }
        duracion = (double)(clock()-start)/CLOCKS_PER_SEC/rep;

        cout
        << "busqueda secuencial; " << n << "; " << duracion << endl;

// calculo de busqueda binaria

        start = clock();
        for (int i = 0; i < rep; i++)
        {// hacemos la busqueda
            busquedaBinaria(vlocal, num_buscado, 0, n-1);
        }
        
        duracion = (double)(clock()-start)/CLOCKS_PER_SEC/rep;

        cout << "busqueda binaria; " << n << "; " << duracion << endl;

// calculo de busqueda doblada

        start = clock();
        for (int i = 0; i < rep; i++)
        {// hacemos la busqueda
            busquedaDoblada(vlocal, num_buscado);
        }
        
        duracion = (double)(clock()-start)/CLOCKS_PER_SEC/rep;

        cout << "busqueda doblada; " << n << "; " << duracion << endl;

    }
}