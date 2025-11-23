//
// Created by ASUS on 22/11/2025.
//

#ifndef LAB09_NODOS_NODO_H
#define LAB09_NODOS_NODO_H
#include "Categoria.h"

struct Nodo {
    Categoria dato; //tu tipo de dato
    Nodo *siguiente;
};

#endif //LAB09_NODOS_NODO_H
