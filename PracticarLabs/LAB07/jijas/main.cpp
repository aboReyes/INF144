/*
*Autor: Diego Axel Lopez Reyes
*Titulo:
*Fecha y Hora:
*/

//me dio flojera hacer un procesamiento para cada nombre, entonces solo cambie el cant y si funcó :u
#include "Bibliotecas/FuncionesAuxiliares.h"

int main(int argc, char **argv) {

    char* arrNombres[MAX_NOMBRES]{};
    int cantNombres1 = 0;

    //Formato1

    cargarArchivos("ArchivoDeDatos/nombresPracticar.txt",
                    arrNombres,cantNombres1,
                    true,false,false,false);

    imprimirReporte("ArchivoDeReportes/Reporte1.txt",
                        arrNombres,cantNombres1);
    //Formato1+Formato2
    int cantNombres2 = 0;
    cargarArchivos("ArchivoDeDatos/nombresPracticar.txt",
                    arrNombres,cantNombres2,
                    false,true,false,false);

    imprimirReporte("ArchivoDeReportes/Reporte2.txt",
                    arrNombres,cantNombres2);

    //Formato3
    int cantNombres3 = 0;
    cargarArchivos("ArchivoDeDatos/nombresPracticar.txt",
                    arrNombres,cantNombres3,
                    false,false,true,false);

    imprimirReporte("ArchivoDeReportes/Reporte3.txt",
                    arrNombres,cantNombres3);

    //Formato4
    int cantNombres4=0;

    cargarArchivos("ArchivoDeDatos/nombresPracticar.txt",
                    arrNombres,cantNombres4,
                    false,false,false,true);

    imprimirReporte("ArchivoDeReportes/Reporte4.txt",
                    arrNombres,cantNombres4);

    return 0;
}
