/*
*Autor: Diego Axel Lopez Reyes
*Titulo:
*Fecha y Hora: 
*/

//No esta bien el procedimiento segun las indicaciones pero salió xd

#include "Bibliotecas/FuncionesAuxiliares.h"

int main(int argc, char **argv) {

    //TablaDeInfracciones.txt
    //2007   425.23      No conducir po...
    int arrCodigoInfraccion[MAX_TABLA_INFRA]{};
    double arrMultasInfraccion[MAX_TABLA_INFRA]{};
    //char *arrDescripcionInfraccion[MAX_TABLA_INFRA]{}; no se puede
    int cantInfracciones=0;

    cargarInfracciones("ArchivoDeDatos/TablaDeInfracciones (4).txt",
                        arrCodigoInfraccion,arrMultasInfraccion,
                        cantInfracciones);

    //InfraccionesCometidas.txt
    int arrDni[MAX_INFRA_COM]{};
    int arrMasMultaAntigua[MAX_INFRA_COM]{};
    int arrUltimaPendiente[MAX_INFRA_COM]{};
    double arrTotalMultas[MAX_INFRA_COM]{};
    double arrTotalPagadas[MAX_INFRA_COM]{};
    double arrTotalPendientes[MAX_INFRA_COM]{};
    char *arrPlacasEmpresa[MAX_INFRA_COM]{};
    int cantInfraCom=0;

    cargarInfraCom("ArchivoDeDatos/InfraccionesCometidas (5).txt",
                   "ArchivoDeReportes/PlacasRegistradas.txt",
                   arrCodigoInfraccion,arrMultasInfraccion,cantInfracciones,
                   arrDni,arrMasMultaAntigua,arrUltimaPendiente,
                   arrTotalMultas,arrTotalPagadas,arrTotalPendientes,
                   arrPlacasEmpresa,cantInfraCom);


    //Reporte


    crearReporte("ArchivoDeReportes/PlacasRegistradas.txt",
                "ArchivoDeReportes/ReporteDeMultas.txt",
                arrDni,arrMasMultaAntigua,arrUltimaPendiente,arrPlacasEmpresa,
                arrTotalMultas,arrTotalPagadas,cantInfraCom);

    return 0;
}
