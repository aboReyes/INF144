//
// Created by ASUS on 30/11/2025.
//

#ifndef EX2_25_1_P1_CONDUCTOR_H
#define EX2_25_1_P1_CONDUCTOR_H
#include "Infraccion.h"
#include "Vehiculo.h"

struct Conductor {
    int dni;
    char* nombre;
    char* apellido;
    char* licencia;
    Vehiculo vehiculo;
    Infraccion *infracciones;
    int cantidadInfracciones;
};

#endif //EX2_25_1_P1_CONDUCTOR_H
