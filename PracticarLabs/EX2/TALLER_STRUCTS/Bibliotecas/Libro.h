
//
// Created by aml on 21/11/2025.
//

#ifndef LIBRO_H
#define LIBRO_H
#include "UsuarioConElLibro.h"

struct Libro {
    char *codigo;
    char* titulo;
    char* autor;
    int cantidad;
    double precio;
    UsuarioConElLibro *usuarios;
    int cantUsuarios;
};

#endif //LIBRO_H
