/*
*Autor: Diego Axel Lopez Reyes
*Titulo:
*Fecha y Hora:
*/

#include "Bibliotecas/FuncionesAuxiliares.h"

int main(int argc, char **argv) {

    //Canales.txt
    //19/06/2022     X5514     xQcOW     2.5
    int arrFechaCanal[MAX_CANALES]{};
    char arrCodeCharCanal[MAX_CANALES]{};
    int arrCodeIntCanal[MAX_CANALES]{};
    double arrRatingCanal[MAX_CANALES]{};
    int nroCanales=0;

    cargarCanales("ArchivoDeDatos/Canales (3).txt",arrFechaCanal,
                    arrCodeCharCanal,arrCodeIntCanal,
                    arrRatingCanal,nroCanales);
    pruebaCanales("ArchivoDeReportes/ReportePruebaCanales.txt",arrFechaCanal,
                    arrCodeCharCanal,arrCodeIntCanal,
                    arrRatingCanal,nroCanales);

    //Etiquetas.txt
    //803100    dropsenabled   01:27
    int arrCodeEtiqueta[MAX_ETIQUETAS]{};
    int arrTiempoDurEtiqueta[MAX_ETIQUETAS]{};
    int nroEtiquetas=0;
    cargarEtiquetas("ArchivoDeDatos/Etiquetas (3).txt",arrCodeEtiqueta,
                    arrTiempoDurEtiqueta,nroEtiquetas);
    pruebaEtiquetas("ArchivoDeReportes/ReportePruebaEtiquetas.txt",arrCodeEtiqueta,
                    arrTiempoDurEtiqueta,nroEtiquetas);

    //EtiquetasEnCanales.txt
    //P7271    113141
    char arrCodeCharEtiquetaCanal[MAX_ETIQUETA_CANAL]{};
    int arrCodeIntEtiquetaCanal[MAX_ETIQUETA_CANAL]{};
    int arrCodeEtiquetaCanal[MAX_ETIQUETA_CANAL]{};
    double arrRatingCanalEtiquetaCanal[MAX_ETIQUETA_CANAL]{};
    int nroEtiquetaCanal=0;
    cargarEtiquetaCanal("ArchivoDeDatos/EtiquetasEnCanales.txt",
                        arrCodeCharEtiquetaCanal,arrCodeIntEtiquetaCanal,
                        arrCodeEtiquetaCanal,nroEtiquetaCanal);
    pruebaEtiquetaCanal("ArchivoDeReportes/ReportePruebaEtiquetaCanal.txt",
                        arrCodeCharEtiquetaCanal,arrCodeIntEtiquetaCanal,
                        arrCodeEtiquetaCanal,nroEtiquetaCanal);

    //ReproduccionesDeEtiquetas.txt
    //28/02/2025  E6696      888106      244
    int arrNroTotalReproCanal[MAX_ETIQUETA_CANAL]{};
    int arrTiempoTotalReproCanal[MAX_ETIQUETA_CANAL]{};

    int arrNroTotalReproCanalGlobal[MAX_ETIQUETAS]{};
    int arrTiempoTotalReproCanalGlobal[MAX_ETIQUETAS]{};
    double arrSumaRatingCanalLigadoEtiqueta[MAX_ETIQUETAS]{};
    double arrIngresoPorReproEtiqueta[MAX_ETIQUETAS]{};
    int arrCantCanalLigadoEtiqueta[MAX_ETIQUETAS]{};


    double tarifaDur=0.75;
    //preguntarTarifa(tarifaDur);

    ordenarEtiquetas(arrCodeEtiqueta,arrTiempoDurEtiqueta,nroEtiquetas);

    procesarReproEtiquetas("ArchivoDeDatos/ReproduccionesDeEtiquetas (3).txt",
                            arrCodeCharCanal,arrCodeIntCanal,
                            arrRatingCanal,nroCanales,
                            arrCodeEtiqueta,arrTiempoDurEtiqueta,nroEtiquetas,
                            arrSumaRatingCanalLigadoEtiqueta,arrCantCanalLigadoEtiqueta,
                            arrCodeCharEtiquetaCanal,arrCodeIntEtiquetaCanal,
                            arrCodeEtiquetaCanal,nroEtiquetaCanal,arrRatingCanalEtiquetaCanal,
                            arrNroTotalReproCanal,arrTiempoTotalReproCanal,
                            arrNroTotalReproCanalGlobal,arrTiempoTotalReproCanalGlobal,arrIngresoPorReproEtiqueta,tarifaDur);


    //Reporte.txt
    //Ordenar
    //GenerarReporte
    generarReporte("ArchivoDeReportes/ReporteTwitch.txt",
                arrCodeCharCanal,arrCodeIntCanal,
                arrRatingCanal,nroCanales,
                arrCodeEtiqueta,arrTiempoDurEtiqueta,nroEtiquetas,
                arrSumaRatingCanalLigadoEtiqueta,arrCantCanalLigadoEtiqueta,
                arrCodeCharEtiquetaCanal,arrCodeIntEtiquetaCanal,
                arrCodeEtiquetaCanal,nroEtiquetaCanal,arrRatingCanalEtiquetaCanal,
                arrNroTotalReproCanal,arrTiempoTotalReproCanal,
                arrNroTotalReproCanalGlobal,arrTiempoTotalReproCanalGlobal,arrIngresoPorReproEtiqueta,tarifaDur);


    return 0;
}
