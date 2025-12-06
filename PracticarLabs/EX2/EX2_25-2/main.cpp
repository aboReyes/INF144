/*
*Autor: Diego Axel Lopez Reyes
*Titulo:
*Fecha y Hora:
*/

#include "Bibliotecas/FuncionesAuxiliares.h"

int main(int argc, char **argv) {

    Transmision *transmisiones=new Transmision[MAX_TRANSMISIONES]{};
    int cantidadTransmisiones=0;

    cargarTransmisiones("ArchivoDeDatos/transmisiones.csv",transmisiones,cantidadTransmisiones);

    cargarStreamers("ArchivoDeDatos/streamers.csv",transmisiones,cantidadTransmisiones);

    cargarComentarios("ArchivoDeDatos/comentarios (1).csv",transmisiones,cantidadTransmisiones);

    emitirReporte("ArchivoDeReportes/ReporteTransmisiones.txt",transmisiones,cantidadTransmisiones);

    return 0;
}
