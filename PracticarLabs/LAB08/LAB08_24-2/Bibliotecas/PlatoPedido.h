//
// Created by ASUS on 7/11/2025.
//

#ifndef LAB08_24_2_PLATOPEDIDO_H
#define LAB08_24_2_PLATOPEDIDO_H

struct PlatoPedido {
  int codigoPedido;
  char codigoPlato[10];
  char descripcion[100];
  int cantidad;
  double precio;
  double subtotal;
};

#endif //LAB08_24_2_PLATOPEDIDO_H
