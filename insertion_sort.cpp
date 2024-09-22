#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono> 
#include <iomanip>


using namespace std;

void insertion_sort(vector<float> &v)
{
    int n = v.size();
    for (int i = 1; i < n; i++)
    {
        float key = v[i];
        int j = i - 1;

        while (j >= 0 && v[j] > key)
        {
            v[j + 1] = v[j];
            j = j - 1;
        }
        v[j + 1] = key;
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
        cout << "Cantidad de datos leídos: " << datos.size() << endl;

        if (!datos.empty())
        {
            auto start = chrono::high_resolution_clock::now();
            insertion_sort(datos);
            auto end = chrono::high_resolution_clock::now();

            chrono::duration<float> duracion = end - start;

            cout << "Tiempo de ejecución para " << archivo << ": "
                 << fixed << setprecision(10) << duracion.count() << " segundos" << endl;

            tiempos_output << archivo << " " << duracion.count() << endl;
        }
        ofstream output("insertion_sort_" + archivo);
            for (double i = 0; i < datos.size(); i++)
            {
                output << datos[i] << endl;
            }
            output.close();



    }

    tiempos_output.close();
    return 0;
}