//
// Created by DIEGO on 05/12/2025.
//

#ifndef P1_TRANSMISION_H
#define P1_TRANSMISION_H
#include "Comentario.h"
#include "Streamer.h"

struct Transmision {
    int id_transmision;
    Streamer streamer;
    Comentario *comentarios;
    int cantidad_comentarios;
    int fecha;
    int duracion;
};

#endif //P1_TRANSMISION_H
