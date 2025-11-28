//
// Created by aml on 28/11/2025.
//

#ifndef NODOUSUARIO_H
#define NODOUSUARIO_H
#include "Usuario.h"

struct NodoUsuario {
    Usuario usuario;
    NodoUsuario* siguiente;
};

#endif //NODOUSUARIO_H
