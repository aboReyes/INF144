//
// Created by ASUS on 7/11/2025.
//

#ifndef LAB08_24_2_CLIENTE_H
#define LAB08_24_2_CLIENTE_H

#include "Distrito.h"
#include "PlatoPedido.h"

struct Cliente {
  int dni;
  char nombre[100];
  Distrito distrito;
  PlatoPedido pedidos[30];
  int cantidadDePedidos;
  double montoTotal;
};

#endif //LAB08_24_2_CLIENTE_H
