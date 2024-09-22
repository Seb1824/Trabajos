#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>
#include<chrono>
#include<iomanip>

using namespace std;

int particionar(vector<float> &v, float low, float high)
{
    float pivot = v[low + (high - low) / 2]; 
    int i = low - 1;
    int j = high + 1;

    while (true)
    {
        do {
            i++;
        } while (v[i] < pivot);

        do {
            j--;
        } while (v[j] > pivot);

        if (i >= j)
            return j;

        swap(v[i], v[j]);
    }
}

void quick_sort(vector<float> &v, int low, int high)
{
    const int THRESHOLD = 10; 

    if (low < high)
    {
        if (high - low + 1 < THRESHOLD)
        {
            for (int i = low + 1; i <= high; i++)
            {
                float key = v[i];
                int j = i - 1;
                while (j >= low && v[j] > key)
                {
                    v[j + 1] = v[j];
                    j--;
                }
                v[j + 1] = key;
            }
        }
        else
        {
            int pi = particionar(v, low, high);
            quick_sort(v, low, pi);
            quick_sort(v, pi + 1, high);
        }
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
            quick_sort(datos, 0, datos.size() - 1);
            auto end = chrono::high_resolution_clock::now();

            chrono::duration<float> duracion = end - start;

            cout << "Tiempo de ejecución para " << archivo << ": "
                 << fixed << setprecision(10) << duracion.count() << " segundos" << endl;

            tiempos_output << archivo << " " << duracion.count() << endl;

            ofstream output("quick_sort_" + archivo);
            for (float i = 0; i < datos.size(); i++)
            {
                output << datos[i] << endl;
            }
            output.close();
        }
    }

    tiempos_output.close();
    return 0;
}