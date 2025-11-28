//
// Created by aml on 28/11/2025.
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
    bool moroso;
};

#endif //USUARIO_H
