/*
*Autor: Diego Axel Lopez Reyes
*Titulo:
*Fecha y Hora:
*/

#include "Bibliotecas/FuncionesAuxiliares.h"

int main(int argc, char **argv) {

    //Ordenar Streams.txt por codigo de stream forma ascendente
    //803100    1:22:25    4003    C1072
    int arrCodeStream[MAX_STREAMS]{};
    int arrDurStream[MAX_STREAMS]{};
    int arrCodeIdiomaStream[MAX_STREAMS]{};
    char arrLetraCatIdiomaStream[MAX_STREAMS]{};
    int arrNumCatIdiomaStream[MAX_STREAMS]{};
    int cantStreams=0;

    cargarStreams("ArchivoDeDatos/Streams (1).txt",
        arrCodeStream,arrDurStream,arrCodeIdiomaStream,
        arrLetraCatIdiomaStream,arrNumCatIdiomaStream,
        cantStreams);

    pruebaStreams("ArchivoDeReportes/ReportePruebaStreams.txt",
        arrCodeStream,arrDurStream,arrCodeIdiomaStream,
        arrLetraCatIdiomaStream,arrNumCatIdiomaStream,
        cantStreams);

    //Canales.txt
    //1/10/2022    A1911    AdmiralBulldog
    //estos se repiten:
    //738184    1/9/2025    15:13:35    3.38    0.628
    //929142    18/8/2025    5:22:57    3.78    0.320

    int arrFechaAntiguaCanal[MAX_STREAMS]{};
    int arrFechaRecienteCanal[MAX_STREAMS]{};
    double arrPromRatingCanal[MAX_STREAMS]{};
    double arrPromDropCanal[MAX_STREAMS]{};
    int arrCantReproCanal[MAX_STREAMS]{};
    int arrTiempoTotalReproCanal[MAX_STREAMS]{};

    procesarCanales("ArchivoDeDatos/Canales (6).txt",
        arrCodeStream,arrDurStream,cantStreams,
        arrFechaAntiguaCanal,arrFechaRecienteCanal,
        arrPromRatingCanal,arrPromDropCanal,
        arrCantReproCanal,arrTiempoTotalReproCanal);

    //ReporteSinOrdenar

    bool esOrdenado;
    reporteStream("ArchivoDeReportes/Reproducciones-Streams.txt",
            arrCodeStream,arrCodeIdiomaStream,
            arrLetraCatIdiomaStream,arrNumCatIdiomaStream,
            arrFechaAntiguaCanal,arrFechaRecienteCanal,
            arrPromRatingCanal,arrPromDropCanal,arrDurStream,
            arrCantReproCanal,arrTiempoTotalReproCanal,
            cantStreams,true);

    //Eliminar los que tienen guiones

    eliminar(arrCodeStream,arrCodeIdiomaStream,
            arrLetraCatIdiomaStream,arrNumCatIdiomaStream,
            arrFechaAntiguaCanal,arrFechaRecienteCanal,
            arrPromRatingCanal,arrPromDropCanal,arrDurStream,
            arrCantReproCanal,arrTiempoTotalReproCanal,
            cantStreams);

    //ReporteConEliminacion
    reporteStream("ArchivoDeReportes/Reproducciones-Streams2.txt",
            arrCodeStream,arrCodeIdiomaStream,
            arrLetraCatIdiomaStream,arrNumCatIdiomaStream,
            arrFechaAntiguaCanal,arrFechaRecienteCanal,
            arrPromRatingCanal,arrPromDropCanal,arrDurStream,
            arrCantReproCanal,arrTiempoTotalReproCanal,
            cantStreams,true);

    //Reporte con eliminacion y ordenacion, sin resumen

    ordenarReporte(arrCodeStream,arrCodeIdiomaStream,
            arrLetraCatIdiomaStream,arrNumCatIdiomaStream,
            arrFechaAntiguaCanal,arrFechaRecienteCanal,
            arrPromRatingCanal,arrPromDropCanal,arrDurStream,
            arrCantReproCanal,arrTiempoTotalReproCanal,
            cantStreams);

    reporteStream("ArchivoDeReportes/Reproducciones-Streams3.txt",
            arrCodeStream,arrCodeIdiomaStream,
            arrLetraCatIdiomaStream,arrNumCatIdiomaStream,
            arrFechaAntiguaCanal,arrFechaRecienteCanal,
            arrPromRatingCanal,arrPromDropCanal,arrDurStream,
            arrCantReproCanal,arrTiempoTotalReproCanal,
            cantStreams,false);

    return 0;
}
