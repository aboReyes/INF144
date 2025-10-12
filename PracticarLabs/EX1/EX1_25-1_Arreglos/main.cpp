/*
*Autor: Diego Axel Lopez Reyes
*Titulo:
*Fecha y Hora:
*/

#include "Bibliotecas/FuncionesAuxiliares.h"

int main(int argc, char **argv) {
    //TablaDeInfracciones.txt
    //G2007   425.23      No conducir ...
    char arrLetraInfraccion[MAX_TABLA_INFRACCIONES]{};
    int arrNumInfraccion[MAX_TABLA_INFRACCIONES]{};
    double arrMultaInfraccion[MAX_TABLA_INFRACCIONES]{};
    int cantInfraccion=0;

    leerTablaInfracciones("ArchivoDeDatos/TablaDeInfracciones (2).txt",
                            arrLetraInfraccion,arrNumInfraccion,
                            arrMultaInfraccion,cantInfraccion);
    pruebaTablaInfracciones("ArchivoDeReportes/ReportePruebaTablaInfra.txt",
                            arrLetraInfraccion,arrNumInfraccion,
                            arrMultaInfraccion,cantInfraccion);

    //InfraccionesCometidas.txt
    //1/12/2020   G760-721      G2022
    char arrLetraPlacaInfraCom[MAX_INFRA_COMETIDAS]{};
    int arrNum1PlacaInfraCom[MAX_INFRA_COMETIDAS]{};
    int arrNum2PlacaInfraCom[MAX_INFRA_COMETIDAS]{};
    int arrCantMultasPagadasInfraCom[MAX_INFRA_COMETIDAS]{};
    double arrTotalMultasPagadasInfraCom[MAX_INFRA_COMETIDAS]{};
    int arrCantMultasPendInfraCom[MAX_INFRA_COMETIDAS]{};
    double arrTotalMultasPendInfraCom[MAX_INFRA_COMETIDAS]{};
    int arrFechaMasAntiguaInfraCom[MAX_INFRA_COMETIDAS]{};
    int cantPlacas=0;

    leerInfraccionesCometidas("ArchivoDeDatos/InfraccionesCometidas (3).txt",
                            arrLetraInfraccion,arrNumInfraccion,
                            arrMultaInfraccion,cantInfraccion,
                            arrLetraPlacaInfraCom,arrNum1PlacaInfraCom,
                            arrNum2PlacaInfraCom,arrCantMultasPagadasInfraCom,
                            arrTotalMultasPagadasInfraCom,arrCantMultasPendInfraCom,
                            arrTotalMultasPendInfraCom,arrFechaMasAntiguaInfraCom,
                            cantPlacas);

    ordenarPlacas(arrLetraInfraccion,arrNumInfraccion,
                    arrMultaInfraccion,
                    arrLetraPlacaInfraCom,arrNum1PlacaInfraCom,
                    arrNum2PlacaInfraCom,arrCantMultasPagadasInfraCom,
                    arrTotalMultasPagadasInfraCom,arrCantMultasPendInfraCom,
                    arrTotalMultasPendInfraCom,arrFechaMasAntiguaInfraCom,
                    cantPlacas);

    generarReporte("ArchivoDeReportes/ReporteInfracciones.txt",
                    arrLetraPlacaInfraCom,arrNum1PlacaInfraCom,
                    arrNum2PlacaInfraCom,arrCantMultasPagadasInfraCom,
                    arrTotalMultasPagadasInfraCom,arrCantMultasPendInfraCom,
                    arrTotalMultasPendInfraCom,arrFechaMasAntiguaInfraCom,
                    cantPlacas);
    return 0;
}
