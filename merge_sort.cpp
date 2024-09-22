#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>

using namespace std;

void merge(vector<float> &v, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<float> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
    {
        L[i] = v[l + i];
    }

    for (int i = 0; i < n2; i++)
    {
        R[i] = v[m + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            v[k] = L[i];
            i++;
        }
        else
        {
            v[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        v[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        v[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(vector<float> &v, int l, float r)
{
    if (l >= r)
    {
        return;
    }

    int m = l + (r - l) / 2;

    merge_sort(v, l, m);
    merge_sort(v, m + 1, r);

    merge(v, l, m, r);
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
            merge_sort(datos, 0, datos.size() - 1);
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