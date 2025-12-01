//
// Created by ASUS on 30/11/2025.
//

#ifndef EX2_24_2_P1_COMENTARIO_H
#define EX2_24_2_P1_COMENTARIO_H
#include "Palabra.h"

struct Comentario {
    char* texto;
    char* preProcesado;
    Palabra palabras[20];
    int cantidadPalabras;
    int polaridadTotal;
};

#endif //EX2_24_2_P1_COMENTARIO_H
