#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;


void insertionSort(vector<int>& arr, int inicio, int fin)
{
    for (int i = inicio + 1; i <= fin; i++)
    {
        int actual = arr[i];
        int j = i - 1;

        while (j >= inicio && arr[j] > actual)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = actual;
    }
}


void merge(vector<int>& arr, int inicio, int medio, int fin)
{
    vector<int> izquierda;
    vector<int> derecha;

    for (int i = inicio; i <= medio; i++)
    {
        izquierda.push_back(arr[i]);
    }

    for (int i = medio + 1; i <= fin; i++)
    {
        derecha.push_back(arr[i]);
    }

    int i = 0;
    int j = 0;
    int posicion = inicio;

    while (i < izquierda.size() && j < derecha.size())
    {
        if (izquierda[i] <= derecha[j])
        {
            arr[posicion] = izquierda[i];
            i++;
        }
        else
        {
            arr[posicion] = derecha[j];
            j++;
        }

        posicion++;
    }

    while (i < izquierda.size())
    {
        arr[posicion] = izquierda[i];
        i++;
        posicion++;
    }

    while (j < derecha.size())
    {
        arr[posicion] = derecha[j];
        j++;
        posicion++;
    }
}

void mergeSortHibrido(vector<int>& arr, int inicio, int fin, int k)
{

    if (fin - inicio + 1 <= k)
    {
        insertionSort(arr, inicio, fin);
        return;
    }

    int medio = inicio + (fin - inicio) / 2;

    mergeSortHibrido(arr, inicio, medio, k);

    mergeSortHibrido(arr, medio + 1, fin, k);

    merge(arr, inicio, medio, fin);
}


int main()
{
    const int n = 1000000;

    int valoresK[] = {1, 2, 4, 8, 16, 32, 64, 128};

    vector<int> datos(n);

    random_device rd;
    mt19937 generador(rd());

    uniform_int_distribution<int> distribucion(1, 1000000);

    for (int i = 0; i < n; i++)
    {
        datos[i] = distribucion(generador);
    }

    ofstream archivo("resultados.csv");

    if (!archivo)
    {
        cout << "Error al crear el archivo resultados.csv" << endl;
        return 1;
    }

    archivo << "k,tiempo_microsegundos" << endl;

    cout << "MERGE SORT HIBRIDO" << endl;
    cout << "Elementos: " << n << endl;
    cout << endl;

    cout << "k\tTiempo (microsegundos)" << endl;
    cout << "--------------------------------" << endl;


    for (int k : valoresK)
    {

        vector<int> arreglo = datos;

        auto inicio = high_resolution_clock::now();

        mergeSortHibrido(arreglo, 0, n - 1, k);

        auto fin = high_resolution_clock::now();

        auto duracion =
            duration_cast<microseconds>(fin - inicio);


        long long tiempo = duracion.count();

        cout << k << "\t"
             << tiempo << " us" << endl;

        archivo << k << "," << tiempo << endl;
    }

    archivo.close();


    cout << endl;
    cout << "Los resultados fueron guardados en:" << endl;
    cout << "resultados.csv" << endl;


    return 0;
}