//
// Created by ASUS on 16/11/2025.
//

#ifndef LAB08_25_2_AGAIN_CATEGORIA_H
#define LAB08_25_2_AGAIN_CATEGORIA_H
#include "Reproduccion.h"

struct Categoria {
    char* codigo;
    char* nombre;
    Reproduccion* reproducciones;
    int numReproducciones;
    double promedioRating;
    int duracionTotal;
};

#endif //LAB08_25_2_AGAIN_CATEGORIA_H
