// ActividadOrdenamiento
// Created by luis1 on 07/09/2026.
// A01254706
/*
 *Comparando el desempeño de la BusquedaLineal, BusquedaBinaria y BusquedaTrinaria
*Metodología:
*  1. Para cada tamaño de entrada n se genera un vector<int> de n elementos
*     aleatorios y se ordena de forma ascendente. La generación y el ordenamiento NO se incluyen en
*     el tiempo reportado.
*  2. Se seleccionan 30 índices aleatorios del vector y se busca el valor
*     almacenado en cada uno de ellos.
*  3. Para cada una de las 30 búsquedas se mide el tiempo empleado
*     por la función de búsqueda, usando
*     chrono::high_resolution_clock.
*  4. Se calcula el promedio de las 30 mediciones para cada combinación
*     (algoritmo, tamaño de entrada) y se reporta en microsegundos (us).
*  5. Los mismos 30 índices se reutilizan para los tres algoritmos en un
*     mismo tamaño de entrada.
*
*/

#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <random>
#include <vector>

#include "Busqueda.h"
using namespace std;

int nBusquedas = 30;
int semillaAleatoria = 42;

//generacion del vector con datos aleatorios (rng)
vector<int> genVectorOrdenado(size_t n, mt19937 &rng) {
    vector<int> v(n);
    uniform_int_distribution<int> dist(0, 2000000000);

    for (size_t i = 0; i < n; i++) {
        v[i] = dist(rng);
    }
    sort(v.begin(), v.end());
    return v;
}

//selecciona numero de busquedas con indices aleatorios
vector<int> indicesBusqueda(size_t n, mt19937 &rng) {
    uniform_int_distribution<size_t> dist(0, n - 1);
    vector<int> indices(nBusquedas);
    for (int i = 0; i < nBusquedas; i++) {
        indices[i] = dist(rng);
    }
    return indices;
}

//template con el numero de busquedas y devuelve el tiempo promedio empleado del tipo de busquedas
template<typename FuncionBusqueda>
double medirTiempoPromedio(vector<int>& datos, vector<int>& objetivos, FuncionBusqueda funcion) {
    double sumaTiempo = 0.0;

    for (int objetivo:objetivos) {
        auto start = chrono::high_resolution_clock::now();
        int resultado = funcion(datos, objetivo);
        auto end = chrono::high_resolution_clock::now();

        if (resultado == -1) {
            cerr<<"No se encontró el elemento .\n";
        }

        chrono::duration<double, micro> duration = end - start;
        sumaTiempo += duration.count();
    }

    return sumaTiempo / nBusquedas;
}

int main() {
    const vector<size_t> tamanos = {100000, 1000000, 10000000, 100000000};
    mt19937 rng(semillaAleatoria);

    struct Resultado {
        size_t n;
        double tiempoLineal;
        double tiempoBinaria;
        double tiempoTrinaria;
    };
    vector<Resultado> resultados;

    cout<<fixed<<setprecision(4);
    cout<<"Tamano\t\tLineal(us)\t\tBinaria(us)\t\tTrinaria(us)\n";

    for (size_t n:tamanos) {
        vector<int> datos = genVectorOrdenado(n, rng);
        vector<int> objetivos = indicesBusqueda(n, rng);

        //convertir indices a valores reales
        vector<int> valoresObjetivo(nBusquedas);
        for (int i = 0; i < nBusquedas; i++) {
            valoresObjetivo[i] = datos[objetivos[i]];
        }

        const double tLineal = medirTiempoPromedio(datos, valoresObjetivo, busquedaLineal);
        const double tBinaria = medirTiempoPromedio(datos, valoresObjetivo, busquedaBinaria);
        const double tTrinaria = medirTiempoPromedio(datos, valoresObjetivo, busquedaTrinaria);

        resultados.push_back({n, tLineal, tBinaria, tTrinaria});

        cout<<n<<"\t"<<tLineal<<"\t\t"<<tBinaria<<"\t\t"<<tTrinaria<<"\n";
    }

    //generacion de CSV
    ofstream csv("resultados.csv");
    csv<<"TamanoEntrada, BusquedaLineal_us, BusquedaBinaria_us, BusquedaTrinaria_us\n";
    csv<<fixed<<setprecision(4);

    for (const auto& resultado:resultados) {
        csv<<resultado.n<<","<<resultado.tiempoLineal<<","<<resultado.tiempoBinaria<<","<<resultado.tiempoTrinaria<<"\n";
    }
    csv.close();

    cout<<"Resultados guardados con exito";
    return 0;
}

