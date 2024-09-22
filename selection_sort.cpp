#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>

using namespace std;

void selection_sort(vector<float> &v)
{
    size_t n = v.size();
    for (size_t i = 0; i < n - 1; i++)
    {
        size_t min_index = i;
        for (size_t j = i + 1; j < n; j++)
        {
            if (v[j] < v[min_index])
            {
                min_index = j;
            }
        }
        swap(v[i], v[min_index]);
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
            selection_sort(datos);
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
