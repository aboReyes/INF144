

#include "Bibliotecas/FuncionesAuxiliares.h"

int main(int argc, char **argv) {

    char idDron[10],idDron2[10];
    solicitarDron(idDron,idDron2);

    Lista primeraLista{};
    crearLista("ArchivoDeDatos/infracciones_drones.csv",primeraLista,idDron);

    Lista segundaLista{};
    crearLista("ArchivoDeDatos/infracciones_drones.csv",segundaLista,idDron2);

    emitirReporte("ArchivoDeReportes/Reporte_drones.txt",primeraLista,idDron,segundaLista,idDron2);

    return 0;
}
