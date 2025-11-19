//
// Created by ASUS on 19/11/2025.
//

#ifndef LAB09_25_2_CATEGORIA_H
#define LAB09_25_2_CATEGORIA_H
#include "Reproduccion.h"

struct Categoria {
    char* codigo;
    char* nombre;
    char* descripcion;
    Reproduccion *reproducciones;
    int numReproducciones;
    //Por las puras estos dos ultimos xd
    double promedioRating;
    int duracionTotal;
};

#endif //LAB09_25_2_CATEGORIA_H
