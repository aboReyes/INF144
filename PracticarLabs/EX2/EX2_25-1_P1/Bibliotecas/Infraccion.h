//
// Created by ASUS on 30/11/2025.
//

#ifndef EX2_25_1_P1_INFRACCION_H
#define EX2_25_1_P1_INFRACCION_H
#include "Fecha.h"

struct Infraccion {
    Fecha fechaInfraccion;
    char *codigo;
    char *descripcion;
    char *gravedad;
    double monto;
    int dniConductor;
};

#endif //EX2_25_1_P1_INFRACCION_H
