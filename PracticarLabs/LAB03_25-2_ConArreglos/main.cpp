/*
*Autor: Diego Axel Lopez Reyes
*Titulo:
*Fecha y Hora:
*/

#include "Biblioteca/ArchivosAuxiliares.h"

int main(int argc, char **argv) {

    //Etiquetas.txt
    int arrCodigoEtiqueta[MAX_ETIQUETAS]{};
    int arrDurEtiqueta[MAX_ETIQUETAS]{};
    int nroEtiquetas=0;

    cargarEtiquetas("ArchivoDeDatos/Etiquetas (1).txt",arrCodigoEtiqueta,
                    arrDurEtiqueta,nroEtiquetas);
    imprimirReportePruebaEtiquetas("ArchivoDeReportes/ReportePruebaEtiquetas.txt",arrCodigoEtiqueta,
                    arrDurEtiqueta,nroEtiquetas);

    //arreglo de Repro Etiquetas.txt
    //28/02/2025  E6696      888106      244
    int arrFechaReproEtiquetas[MAX_REPRODUCCIONES]{};
    char arrCodeCharStreamer[MAX_REPRODUCCIONES]{};
    int arrCodeIntStreamer[MAX_REPRODUCCIONES]{};
    int arrCodigoEtiquetaRepro[MAX_REPRODUCCIONES]{};
    int arrCantReproducciones[MAX_REPRODUCCIONES]{};
    int nroReproducciones=0;

    cargarReproEtiquetas("ArchivoDeDatos/ReproduccionesDeEtiquetas (1).txt",arrFechaReproEtiquetas,
                        arrCodeCharStreamer,arrCodeIntStreamer,arrCantReproducciones,arrCodigoEtiquetaRepro,nroReproducciones);
    imprimirReportePruebaReproEtiquetas("ArchivoDeReportes/ReportePruebaReproEtiquetastxt",arrFechaReproEtiquetas,
                        arrCodeCharStreamer,arrCodeIntStreamer,arrCodigoEtiquetaRepro,arrCantReproducciones,nroReproducciones);

    //reporte

    double tarifaDur=0.78;
    /*cout<<"Ingrese tarifa: ";
    cin>>tarifaDur;*/
    crearReporte("ArchivoDeDatos/Canales (1).txt","ArchivoDeReportes/ReporteTwitch.txt",
                arrCodigoEtiqueta,arrDurEtiqueta,nroEtiquetas,
                arrFechaReproEtiquetas,arrCodeCharStreamer,arrCodeIntStreamer,
                arrCantReproducciones,arrCodigoEtiquetaRepro,nroReproducciones,tarifaDur);

    return 0;
}
