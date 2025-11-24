//
// Created by ASUS on 23/11/2025.
//

#ifndef REPASOLAB09_25_2_NODOCATEGORIA_H
#define REPASOLAB09_25_2_NODOCATEGORIA_H
#include "Categoria.h"

struct NodoCategoria {
    Categoria dato;
    NodoCategoria *siguiente;
};

#endif //REPASOLAB09_25_2_NODOCATEGORIA_H
