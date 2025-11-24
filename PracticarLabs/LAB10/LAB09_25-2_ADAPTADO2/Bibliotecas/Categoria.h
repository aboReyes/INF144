//
// Created by ASUS on 23/11/2025.
//

#ifndef REPASOLAB09_25_2_CATEGORIA_H
#define REPASOLAB09_25_2_CATEGORIA_H
#include "Reproduccion.h"

struct Categoria {
    char *codigo;
    char* nombre;
    char* descripcion;
    Reproduccion *reproducciones;
    int numReproducciones;
    double promedioRating;
    int duracionTotal;
};

#endif //REPASOLAB09_25_2_CATEGORIA_H
