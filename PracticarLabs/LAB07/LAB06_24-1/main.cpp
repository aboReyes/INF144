/*
*Autor: Diego Axel Lopez Reyes
*Titulo:
*Fecha y Hora:
*/


#include "Bibliotecas/FuncionesAuxiliares.h"

int main(int argc, char **argv) {
    //Facultades.txt
    //FACULTAD_DE_DERECHO   400111
    char *facultad[MAX_FACULTADES]{};
    int arrCodeFacultad[MAX_FACULTADES]{};
    int cantFacultades=0;

    cargarFacultades("ArchivoDeDatos/Facultades.txt",
                    facultad,arrCodeFacultad,cantFacultades);

    int codigoFacultad;
    preguntarFacultad(codigoFacultad);

    //Calificaciones.txt
    //DER614   5.75
    //se repite:
    //20238549   16
    //20205830   17

    int arrCodigoAlumnos[MAX_CALIFICACIONES]{};
    int arrNumCursos[MAX_CALIFICACIONES]{};
    double arrSumaPonderada[MAX_CALIFICACIONES]{};
    double arrNumCreditos[MAX_CALIFICACIONES]{};
    int cantCalificaciones=0;
    //Prom ponderado = sumaPonderada / numCreditos

    cargarCalificaciones("ArchivoDeDatos/Calificaciones.txt",
                        arrCodigoAlumnos,arrNumCursos,
                        arrSumaPonderada,arrNumCreditos,
                        cantCalificaciones);

    //Reporte

    //Alumnos.txt
    //20227341     DIAZ/ANTEZANO/MAGALI-SILVANA   200451

    generarReporte("ArchivoDeDatos/Alumnos.txt",
                    "ArchivoDeReportes/ReporteTP.txt",
                    codigoFacultad,arrCodeFacultad,facultad,
                    arrCodigoAlumnos,arrNumCursos,
                    arrSumaPonderada,arrNumCreditos,
                    cantCalificaciones,
                    cantFacultades);

    return 0;
}
