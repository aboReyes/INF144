//
// Created by ASUS on 16/11/2025.
//

#ifndef LAB09_25_1_INFRACCIONCOMETIDA_H
#define LAB09_25_1_INFRACCIONCOMETIDA_H

#include "Fecha.h"
#include "TablaDeInfracciones.h"
struct InfraccionCometida {
    Fecha fechaDeInfraccion;
    char *placa;
    //dado que se redunda multa descripcion y el codigo,
    //se puede optimizar colocando el struct de su campos
    TablaDeInfracciones infraccion;
    bool multaPagada;
    Fecha fechaDePago;
};

#endif //LAB09_25_1_INFRACCIONCOMETIDA_H
