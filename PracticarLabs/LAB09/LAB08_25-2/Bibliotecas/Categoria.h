//
// Created by ASUS on 12/11/2025.
//

#ifndef LAB08_25_2_CON_DINAMICO_CATEGORIA_H
#define LAB08_25_2_CON_DINAMICO_CATEGORIA_H
#include "Reproduccion.h"

struct Categoria {
    char* codigo;
    char* nombre;
    Reproduccion reproducciones[15];
    int numReproducciones=0;
    double promedioRating=0;
    int duracionTotal=0;
};

#endif //LAB08_25_2_CON_DINAMICO_CATEGORIA_H
