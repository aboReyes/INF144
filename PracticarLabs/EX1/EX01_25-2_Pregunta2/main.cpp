//Falta completarlo
#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {

    //Streams.txt
    //803100    1:22:25    4003    C1072
    int arrCodeStream[MAX_STREAMS]{};
    int arrDurStream[MAX_STREAMS]{};
    int arrCodeIdiomaStream[MAX_STREAMS]{};
    char arrCharCatIdiomaStream[MAX_STREAMS]{};
    int arrIntCatIdiomaStream[MAX_STREAMS]{};
    int cantStreams=0;

    cargarStreams("ArchivoDeDatos/Streams.txt",
        arrCodeStream,arrDurStream,arrCodeIdiomaStream,
        arrCharCatIdiomaStream,arrIntCatIdiomaStream,cantStreams);


    //Canales.txt
    //1/10/2022    A1911    AdmiralBulldog
    //a partir de aquí, se repite
    //738184    1/9/2025    15:13:35    3.38    0.628
    //929142    18/8/2025    5:22:57    3.78    0.320

    int arrFechaCanal[MAX_STREAMS]{};
    char arrCodeCharCanal[MAX_STREAMS]{};
    int arrCodeIntCanal[MAX_STREAMS]{};
    int arrFechaAntiguaCanal[MAX_STREAMS]{};
    int arrFechaRecienteCanal[MAX_STREAMS]{};
    double arrRatingPromCanal[MAX_STREAMS]{};
    double arrTasaDropPromCanal[MAX_STREAMS]{};
    int arrDurStreamCanal[MAX_STREAMS]{};

    procesarCanales("ArchivoDeDatos/Canales.txt",arrCodeStream,
                    arrFechaCanal,arrCodeCharCanal,arrCodeIntCanal,
                    arrFechaAntiguaCanal,arrFechaRecienteCanal,
                    arrRatingPromCanal,arrTasaDropPromCanal,
                    arrDurStreamCanal,cantStreams);


    //Reporte sin ordenar

    reporteStreams("ArchivoDeReportes/Reproducciones-Streams.txt",
                    arrCodeStream,arrCodeIdiomaStream,
                    arrCharCatIdiomaStream,arrIntCatIdiomaStream,
                    arrFechaAntiguaCanal,arrFechaRecienteCanal,
                    arrRatingPromCanal,arrTasaDropPromCanal,
                    arrDurStreamCanal,cantStreams);

    return 0;
}
