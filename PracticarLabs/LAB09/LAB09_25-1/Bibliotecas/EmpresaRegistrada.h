//
// Created by ASUS on 16/11/2025.
//

#ifndef LAB09_25_1_EMPRESAREGISTRADA_H
#define LAB09_25_1_EMPRESAREGISTRADA_H

#include "InfraccionCometida.h"

struct EmpresaRegistrada {
    int dni;
    char* nombre;
    char* distrito;

    char* placas[10];
    int numPlacas=0;

    InfraccionCometida *infracciones; //acá aparece new struct :c
    int cantidadDeInfracciones=0;

    double totalPagado;
    double totalAdeudado;
};

#endif //LAB09_25_1_EMPRESAREGISTRADA_H
