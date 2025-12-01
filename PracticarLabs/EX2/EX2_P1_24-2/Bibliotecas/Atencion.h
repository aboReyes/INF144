//
// Created by ASUS on 30/11/2025.
//

#ifndef EX2_24_2_P1_ATENCION_H
#define EX2_24_2_P1_ATENCION_H
#include "Comentario.h"
#include "Plato.h"

struct Atencion {
    int codigo;
    Plato *platosAtendidos;
    int cantidadPlatos;
    double totalVenta;
    int hora;
    Comentario *comentarios;
    int cantidadComentarios;
};

#endif //EX2_24_2_P1_ATENCION_H
