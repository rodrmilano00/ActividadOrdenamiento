// ActividadOrdenamiento
// Created by luis1 on 07/09/2026.
// A01254706
//

#include "Busqueda.h"

//implementacion de busqueda lineal
int busquedaLineal(const std::vector<int> &datos, int objetivo) {
    const int n = datos.size();

    for (int i = 0; i < n; i++) {
        if (datos[i] == objetivo) {
            return i;
        }
    }
    return -1;
}

//implementacion de bsuqueda binaria
int busquedaBinaria(const std::vector<int> &datos, int objetivo) {
    int izquierda = 0;
    int derecha = 0;

    while (izquierda <= derecha) {
        const int centro = derecha + (derecha - izquierda) / 2;

        if (datos[centro] == objetivo) {
            return centro;
        } else if (datos[centro] < objetivo) {
            izquierda = centro + 1;
        } else {
            derecha = centro - 1;
        }
    }
    return -1;
}

//implementacion de busquedatrinaria
int busquedaTrinaria(const std::vector<int> &datos, int objetivo) {
    int izquierda = 0;
    int derecha = datos.size() - 1;

    while (izquierda <= derecha) {
        //se divide el espacio de busqueda en 3 partes iguales
        const int tercio = (derecha - izquierda) / 3;
        const int corteIzq = izquierda + tercio;
        const int corteDer = derecha - tercio;

        if (datos[corteIzq] == objetivo) {
            return corteIzq;
        }
        if (datos[corteDer] == objetivo) {
            return corteDer;
        }

        if (objetivo < datos[corteIzq]) {
            derecha = corteIzq - 1;
        } else if (objetivo > datos[corteDer]) {
            izquierda = corteIzq + 1;
        } else {
            izquierda = corteIzq + 1;
            derecha = corteDer - 1;
        }
    }
    return -1;
}

