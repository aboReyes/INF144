//
// Created by aml on 21/11/2025.
//

#ifndef USUARIO_H
#define USUARIO_H
#include "LibroEnSuPoder.h"

struct Usuario {
    int dni;
    char* nombre;
    char categoria;
    double calificacion;
    LibroEnSuPoder *libros;
    int cantLibros;
};

#endif //USUARIO_H
