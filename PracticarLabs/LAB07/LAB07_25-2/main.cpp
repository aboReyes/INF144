/*
*Autor: Diego Axel Lopez Reyes
*Titulo:
*Fecha y Hora:
*/

#include "Bibliotecas/FuncionesAuxiliares.h"

int main(int argc, char **argv) {
    //categorias.txt
    //UM163F47   just_chatting
    char *arrCodigoCategoria[MAX_CATEGORIAS]{};
    char *arrNombreCategoria[MAX_CATEGORIAS]{};
    int cantCategorias = 0;

    cargarCategorias("ArchivoDeDatos/Categorias (4).txt",
                    arrCodigoCategoria,arrNombreCategoria,cantCategorias);

    probarCategorias("ArchivoDeReportes/Reporte-Prueba-Categorias.txt",
                    arrCodigoCategoria,arrNombreCategoria,cantCategorias);

    //Reproducciones (4).txt
    //31/8/2025  Sardoche    ZT132U54    4.410    0.715    1:41:48
    int arrFechaStream[MAX_REPRO_STREAM]{};
    char* arrNombreCanalStream[MAX_REPRO_STREAM]{};
    char* arrCodigoCanalStream[MAX_REPRO_STREAM]{};
    double arrRatingStream[MAX_REPRO_STREAM]{};
    double arrDropStream[MAX_REPRO_STREAM]{};
    int arrDurStream[MAX_REPRO_STREAM]{};
    int cantStreams=0;

    cargarReproStreams("ArchivoDeDatos/Reproducciones (4).txt",
                        arrFechaStream,arrNombreCanalStream,arrCodigoCanalStream,
                        arrRatingStream,arrDropStream,arrDurStream,cantStreams);

    pruebaReproStreams("ArchivoDeReportes/ReporteDePruebaDeStreamsReproducidos.txt",
                        arrFechaStream,arrNombreCanalStream,arrCodigoCanalStream,
                        arrRatingStream,arrDropStream,arrDurStream,cantStreams);

    /*char categoria[]="xxx_yyyy_zzz";
    char nombreArchivo[200]{};
    char enlace[200]{};
    generarArchivoEnlace(categoria,nombreArchivo,enlace);*/


    procesarReporte(arrCodigoCategoria,arrNombreCategoria,cantCategorias,
                    arrFechaStream,arrNombreCanalStream,arrCodigoCanalStream,
                    arrRatingStream,arrDropStream,arrDurStream,cantStreams);

    return 0;
}
