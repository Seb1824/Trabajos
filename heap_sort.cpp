#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>  
#include <iomanip> 
#include <algorithm>

using namespace std;

void heapify(vector<float> &v, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && v[left] > v[largest])
    {
        largest = left;
    }

    if (right < n && v[right] > v[largest])
    {
        largest = right;
    }

    if (largest != i)
    {
        swap(v[i], v[largest]);
        heapify(v, n, largest);
    }
}

void heap_sort(vector<float> &v)
{
    int n = v.size();

    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(v, n, i);
    }

    for (int i = n - 1; i >= 0; i--)
    {
        swap(v[0], v[i]);
        heapify(v, i, 0);
    }
}

vector<float> leerArchivo(const string &nombreArchivo)
{
    vector<float> v;
    string line;
    ifstream file(nombreArchivo);

    if (file.is_open())
    {
        while (getline(file, line))
        {
            stringstream ss(line);
            float n;
            ss >> n;
            v.push_back(n);
        }
        file.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
    }

    return v;
}

int main()
{
    vector<string> archivos = {"DataGen1.txt", "DataGen05.txt", "DataGen025.txt"};

    ofstream tiempos_output("tiempos_ejecucion.txt");

    for (const string &archivo : archivos)
    {
        vector<float> datos = leerArchivo(archivo);

        if (!datos.empty())
        {
            auto start = chrono::high_resolution_clock::now();
            heap_sort(datos);
            auto end = chrono::high_resolution_clock::now();

            chrono::duration<float> duracion = end - start;

            cout << "Tiempo de ejecución para " << archivo << ": "
                 << fixed << setprecision(10) << duracion.count() << " segundos" << endl;

            tiempos_output << archivo << " " << duracion.count() << endl;
        }
    }

    tiempos_output.close();

    return 0;
}