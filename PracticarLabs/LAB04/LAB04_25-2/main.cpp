/*
*Autor: Diego Axel Lopez Reyes
*Titulo:
*Fecha y Hora: 
*/

#include "Bibliotecas/FuncionesAuxiliares.h"
int main(int argc, char **argv) {

    //tarifa (usar hardcode)
    double tarifaDurEtiquetas=0.78;
    //preguntarTarifa(tarifaDurEtiquetas);

    //Canales.txt
    //19/06/2022    X5514      xQcOW      2.5      632180
    int arrFechaCanal[MAX_CANALES]{};
    char arrCodeCharCanal[MAX_CANALES]{};
    int arrCodeIntCanal[MAX_CANALES]{};
    double arrRatingCanal[MAX_CANALES]{};
    int nroCanales=0;

    cargarCanales("ArchivosDeDatos/Canales (2).txt",arrFechaCanal,
                    arrCodeCharCanal,arrCodeIntCanal,arrRatingCanal,nroCanales);
    pruebaCanales("ArchivosDeReporte/ReportePruebaCanales.txt",arrFechaCanal,
                    arrCodeCharCanal,arrCodeIntCanal,arrRatingCanal,nroCanales);

    //Etiquetas.txt
    //803100    dropsenabled   01:27
    int arrCodeEtiqueta[MAX_ETIQUETAS]{};
    int arrTiempoDurEtiqueta[MAX_ETIQUETAS]{};
    int nroEtiquetas=0;

    cargarEtiquetas("ArchivosDeDatos/Etiquetas (2).txt",
                    arrCodeEtiqueta,arrTiempoDurEtiqueta,nroEtiquetas);
    pruebaEtiquetas("ArchivosDeReporte/ReportePruebaEtiquetas.txt",
                    arrCodeEtiqueta,arrTiempoDurEtiqueta,nroEtiquetas);

    //ReproduccionesDeEtiquetas.txt
    //28/02/2025  E6696      888106      244
    int arrNroTotalReproCanales[MAX_CANALES]{};
    int arrTiempoTotalReproCanales[MAX_CANALES]{};
    int arrCantTotalReproEtiquetas[MAX_ETIQUETAS]{};
    int arrTiempoTotalReproEtiquetas[MAX_ETIQUETAS]{};

    procesarReproducciones("ArchivosDeDatos/ReproduccionesDeEtiquetas (2).txt",arrFechaCanal,
                            arrCodeCharCanal,arrCodeIntCanal,arrRatingCanal,nroCanales,
                            arrCodeEtiqueta,arrTiempoDurEtiqueta,nroEtiquetas,
                            arrNroTotalReproCanales,arrTiempoTotalReproCanales,arrCantTotalReproEtiquetas,
                            arrTiempoTotalReproEtiquetas,tarifaDurEtiquetas);

    //ReporteFinal.txt

    generarReporte("ArchivosDeReporte/ReporteTPTwitch.txt",arrFechaCanal,
                            arrCodeCharCanal,arrCodeIntCanal,arrRatingCanal,nroCanales,
                            arrCodeEtiqueta,arrTiempoDurEtiqueta,nroEtiquetas,
                            arrNroTotalReproCanales,arrTiempoTotalReproCanales,arrCantTotalReproEtiquetas,
                            arrTiempoTotalReproEtiquetas,tarifaDurEtiquetas);


    return 0;
}
