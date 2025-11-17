/*
*Autor: Diego Axel Lopez Reyes
*Titulo:
*Fecha y Hora:
*/

#include "Bibliotecas/FuncionesAuxiliares.h"

int main(int argc, char **argv) {

    //Forma 1: me gusta esta
    Categoria *arrCategorias=new Categoria[MAX_CATEGORIAS]{};
    int cantidadCategorias=0;

    cargarCategorias1("ArchivoDeDatos/Categorias (1).csv",
                    arrCategorias,cantidadCategorias);

    //Forma 2:
    /*Categoria *arrCategorias;
    int cantidadCategorias=0;
    cargarCategorias2("ArchivoDeDatos/Categorias (1).csv",
                    arrCategorias,cantidadCategorias);*/

    /*for (int i=0;i<cantidadCategorias;i++) {
        cout<<setw(3)<<i+1<<")"<<arrCategorias[i].codigo<<" - ";
        cout<<arrCategorias[i].nombre<<endl;
    }*/


    reportePruebaCategorias("ArchivoDeReportes/ReporteDePruebaDeCategorias.txt",
                            arrCategorias,cantidadCategorias,false);

    cargarReproducciones("ArchivoDeDatos/Reproducciones.csv",
                        arrCategorias,cantidadCategorias);

    reportePruebaCategorias("ArchivoDeReportes/ReporteDePruebaConReproducciones.txt",
                            arrCategorias,cantidadCategorias,true);

    calcularTotalesYPromedios(arrCategorias,cantidadCategorias);

    ordenarCategorias(arrCategorias,cantidadCategorias);

    ordenarNombres(arrCategorias,cantidadCategorias);

    emitirReporte("ArchivoDeReportes/ReportePorCategorias.txt",
                    arrCategorias,cantidadCategorias);

    //ordenarRating(arrCategorias,cantidadCategorias);


    emitirReporte2(arrCategorias,cantidadCategorias);

    return 0;
}
