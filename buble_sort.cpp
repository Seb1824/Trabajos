
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

void bubbleSort(vector<float>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
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

int main ()
{
    vector<string> archivos = {"DataGen1.txt", "DataGen05.txt", "DataGen025.txt"};

    ofstream tiempos_output("tiempos_ejecucion.txt");

    for (const string &archivo : archivos)
    {
        vector<float> datos = leerArchivo(archivo);

        if (!datos.empty())
        {
            auto start = chrono::high_resolution_clock::now();
            bubbleSort(datos);
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