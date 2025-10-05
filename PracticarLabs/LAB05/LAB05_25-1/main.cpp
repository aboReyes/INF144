/*
*Autor: Diego Axel Lopez Reyes
*Titulo:
*Fecha y Hora: 
*
*/

#include "Bibliotecas/FuncionesAuxiliares.h"

int main(int argc, char **argv) {
    //EmpresasRegistradas.txt
    //79672079      contreras/chang/johana-cinthia    Chorrillos
    int arrDniRepreEmpresa[MAX_EMPRESAS]{};
    int nroRepreEmpresa=0;
    int arrCantLevesEmpresas[MAX_EMPRESAS]{};
    double arrMontoLevesEmpresas[MAX_EMPRESAS]{};
    int arrCantGravesEmpresas[MAX_EMPRESAS]{};
    double arrMontoGravesEmpresas[MAX_EMPRESAS]{};
    int arrCantMuyGravesEmpresas[MAX_EMPRESAS]{};
    double arrMontoMuyGravesEmpresas[MAX_EMPRESAS]{};
    cargarRepresentantesEmpresas("ArchivosDeDatos/EmpresasRegistradas (1).txt",
                                arrDniRepreEmpresa, nroRepreEmpresa);
    //ordenarRepresentantesEmpresas(arrDniRepreEmpresa,nroRepreEmpresa); ya no me sirve :c

    //TablaDeInfracciones.txt
    //G2007   425.23      No conducir ...
    char arrCodeCharInfraccion[MAX_MULTAS]{};
    int arrCodeIntInfraccion[MAX_MULTAS]{};
    double arrMultaInfraccion[MAX_MULTAS]{};
    int nroMultas=0;
    int arrCantMultasInfraccion[MAX_MULTAS]{};
    double arrTotalMultasInfraccion[MAX_MULTAS]{};
    cargarMultasInfraccion("ArchivosDeDatos/TablaDeInfracciones (1).txt",arrCodeCharInfraccion,
                            arrCodeIntInfraccion, arrMultaInfraccion, nroMultas);

    //PlacasRegistradas.txt
    //12443643   M421-807
    int arrDniRegistroPlaca[MAX_PLACAS]{};
    char arrCodeCharPlaca[MAX_PLACAS]{};
    int arrCodeIntPlaca[MAX_PLACAS]{};
    int nroPlacas=0;
    cargarPlacas("ArchivosDeDatos/PlacasRegistradas.txt",arrDniRegistroPlaca,
                arrCodeCharPlaca,arrCodeIntPlaca,nroPlacas);


    //InfraccionesCometidas.txt
    //1/12/2020   G760-721      G2022
    procesarInfraccionesCometidas("ArchivosDeDatos/InfraccionesCometidas (2).txt",arrDniRepreEmpresa, nroRepreEmpresa,
                                arrCodeCharInfraccion,arrCodeIntInfraccion, arrMultaInfraccion, nroMultas,
                                arrDniRegistroPlaca,arrCodeCharPlaca,arrCodeIntPlaca,nroPlacas,
                                arrCantLevesEmpresas,arrCantGravesEmpresas,arrCantMuyGravesEmpresas,
                                arrMontoLevesEmpresas,arrMontoGravesEmpresas,arrMontoMuyGravesEmpresas,
                                arrCantMultasInfraccion,arrTotalMultasInfraccion);

    //Reporte.txt
    ordenarReporte(arrDniRepreEmpresa, nroRepreEmpresa,
                    arrCantLevesEmpresas,arrCantGravesEmpresas,arrCantMuyGravesEmpresas,
                    arrMontoLevesEmpresas,arrMontoGravesEmpresas,arrMontoMuyGravesEmpresas,
                    arrCodeCharInfraccion,arrCodeIntInfraccion,arrMultaInfraccion,nroMultas,
                    arrCantMultasInfraccion,arrTotalMultasInfraccion);

    generarReporte("ArchivosDeReportes/Reporte.txt",arrDniRepreEmpresa, nroRepreEmpresa,
                    arrCantLevesEmpresas,arrCantGravesEmpresas,arrCantMuyGravesEmpresas,
                    arrMontoLevesEmpresas,arrMontoGravesEmpresas,arrMontoMuyGravesEmpresas,
                    arrCodeCharInfraccion,arrCodeIntInfraccion,arrMultaInfraccion,nroMultas,
                    arrCantMultasInfraccion,arrTotalMultasInfraccion);

    return 0;
}
