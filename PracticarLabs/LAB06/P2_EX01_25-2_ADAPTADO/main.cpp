/*
*Autor: Diego Axel Lopez Reyes
*Descripcion: Generaremos un reporte en base a los archivos txt seleccionados
*donde usaremos la busqueda binaria e insertar ordenador, las cuales son herramientas
*fundamentales para el manejo de arreglos y la correcta impresion de dicho reporte
*/

#include "Bibliotecas/FuncionesAuxiliares.h"

int main(int argc, char **argv) {

    //Streams.txt
    //803100    1:22:25    4003    C1072
    int arrCodeStream[MAX_STREAMS]{};
    int arrDurStream[MAX_STREAMS]{};
    int arrCodeIdioma[MAX_STREAMS]{};
    char arrCodeCharCatIdioma[MAX_STREAMS]{};
    int arrCodeIntCatIdioma[MAX_STREAMS]{};
    int cantStreams=0;

    cargarStreams("ArchivosDeDatos/Streams (2).txt",
        arrCodeStream,arrDurStream,arrCodeIdioma,
        arrCodeCharCatIdioma,arrCodeIntCatIdioma,cantStreams);

    pruebaStreams("ArchivosDeReporte/Prueba-Streams.txt",
        arrCodeStream,arrDurStream,arrCodeIdioma,
        arrCodeCharCatIdioma,arrCodeIntCatIdioma,cantStreams);


    //Canales.txt
    //1/10/2022    A1911    AdmiralBulldog
    //738184    1/9/2025    15:13:35    3.38    0.628
    //929142    18/8/2025    5:22:57    3.78    0.320

    int arrFechaAntiguaCanal[MAX_STREAMS]{};
    int arrFechaRecienteCanal[MAX_STREAMS]{};
    double arrPromRatingCanal[MAX_STREAMS]{};
    double arrPromDropCanal[MAX_STREAMS]{};
    int arrCantReproCanal[MAX_STREAMS]{};
    int arrTiempoTotalReproCanal[MAX_STREAMS]{};

    procesarCanales("ArchivosDeDatos/Canales (7).txt",
        arrCodeStream,arrDurStream,cantStreams,
        arrFechaAntiguaCanal,arrFechaRecienteCanal,
        arrPromDropCanal,arrPromRatingCanal,
        arrCantReproCanal,arrTiempoTotalReproCanal);


    //Reporte1

    imprimirReporte("ArchivosDeReporte/Reproducciones-Streams.txt",
        arrCodeStream,arrDurStream,arrCodeIdioma,
        arrCodeCharCatIdioma,arrCodeIntCatIdioma,cantStreams,
        arrFechaAntiguaCanal,arrFechaRecienteCanal,
        arrPromDropCanal,arrPromRatingCanal,
        arrCantReproCanal,arrTiempoTotalReproCanal,false);


    //Reporte2 ordenado

    ordenarReporte(arrCodeStream,arrDurStream,arrCodeIdioma,
        arrCodeCharCatIdioma,arrCodeIntCatIdioma,cantStreams,
        arrFechaAntiguaCanal,arrFechaRecienteCanal,
        arrPromDropCanal,arrPromRatingCanal,
        arrCantReproCanal,arrTiempoTotalReproCanal);

    imprimirReporte("ArchivosDeReporte/Reproducciones-Streams-Ordenado.txt",
        arrCodeStream,arrDurStream,arrCodeIdioma,
        arrCodeCharCatIdioma,arrCodeIntCatIdioma,cantStreams,
        arrFechaAntiguaCanal,arrFechaRecienteCanal,
        arrPromDropCanal,arrPromRatingCanal,
        arrCantReproCanal,arrTiempoTotalReproCanal,true);

    //Reporte 3 eliminar

    eliminar(arrCodeStream,arrDurStream,arrCodeIdioma,
        arrCodeCharCatIdioma,arrCodeIntCatIdioma,cantStreams,
        arrFechaAntiguaCanal,arrFechaRecienteCanal,
        arrPromDropCanal,arrPromRatingCanal,
        arrCantReproCanal,arrTiempoTotalReproCanal);

    imprimirReporte("ArchivosDeReporte/Reproducciones-Streams-Eliminado.txt",
        arrCodeStream,arrDurStream,arrCodeIdioma,
        arrCodeCharCatIdioma,arrCodeIntCatIdioma,cantStreams,
        arrFechaAntiguaCanal,arrFechaRecienteCanal,
        arrPromDropCanal,arrPromRatingCanal,
        arrCantReproCanal,arrTiempoTotalReproCanal,true);


    return 0;
}
