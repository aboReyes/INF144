//
// Created by ASUS on 9/11/2025.
//

#ifndef LAB08_25_1_EMPRESASREGISTRADAS_H
#define LAB08_25_1_EMPRESASREGISTRADAS_H

#include "Fecha.h"

struct EmpresasRegistradas {
    int dni;
    char nombre[200];
    char distrito[100];//Esto es solo UNA cadena

    //Siempre van de la mano, su cadena dinámica con su entero
    char* placas[10];//arreglos de cadenas de caracteres ESTÁTICA//CADENAS DE HASTA UN MAXIMO DE 10 ESPACIOS CADA UNA
    int numPlacas;

    Fecha fechaDeInfraccion;
    Fecha fechaDePago;
    double totalDeMultas;
    double totalPagado;
    double totalAdeudado;
    int cantidadDeFaltas;
};

#endif //LAB08_25_1_EMPRESASREGISTRADAS_H
