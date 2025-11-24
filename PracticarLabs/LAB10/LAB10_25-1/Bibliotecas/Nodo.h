//
// Created by ASUS on 24/11/2025.
//

#ifndef LAB10_25_1_NODO_H
#define LAB10_25_1_NODO_H
#include "Cuenta.h"

struct Nodo {
    Cuenta cuenta; //mi dato
    Nodo *siguiente;
};

#endif //LAB10_25_1_NODO_H
