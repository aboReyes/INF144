/*
*Autor: Diego Axel Lopez Reyes
*Titulo:
*Fecha y Hora:
*/

#include "Bibliotecas/FuncionesAuxiliares.h"

int main(int argc, char **argv) {

    Categoria arrCategorias[MAX_CATEGORIAS]{};
    int cantCategorias=0;

    //Categorias.csv
    leerCategorias("ArchivoDeDatos/Categorias (1).csv",
                    arrCategorias,cantCategorias);

    pruebaCategorias("ArchivoDeReportes/ReporteDePruebaDeCategorias.txt",
                    arrCategorias,cantCategorias,false);

    //Reproducciones.csv

    leerProcesarReproducciones("ArchivoDeDatos/Reproducciones.csv",
                    arrCategorias,cantCategorias);

    pruebaCategorias("ArchivoDeReportes/ReporteDePruebaConReproducciones.txt",
                    arrCategorias,cantCategorias,true);

    calcularPromedioYDuracionesTotales(arrCategorias,cantCategorias);

    emitirReporte("ArchivoDeReportes/ReportePorCategorias.txt",
                    arrCategorias,cantCategorias);

    return 0;
}
