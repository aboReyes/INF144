
#include "Bibliotecas/FuncionesAuxiliares.h"
int main(int argc, char **argv) {

    Categoria *arrCategoria = new Categoria[MAX_CATEGORIAS]{};
    int cantidadCategorias = 0;

    leerCategorias("ArchivoDeDatos/Categorias (2).csv",
                    arrCategoria,cantidadCategorias);

    pruebaCategorias("ArchivoDeReportes/ReporteDePruebaDeCategorias.txt",
                    arrCategoria,cantidadCategorias,false,false);

    leerStreamsReproducidos("ArchivoDeDatos/StreamsReproducidos.csv",
                    arrCategoria,cantidadCategorias);

    pruebaCategorias("ArchivoDeReportes/ReporteDePruebaConReproducciones.txt",
                    arrCategoria,cantidadCategorias,true,false);

    ordenarDatos(arrCategoria,cantidadCategorias);

    pruebaCategorias("ArchivoDeReportes/ReporteDePruebaOrdenado.txt",
                    arrCategoria,cantidadCategorias,true,false);

    leerComentarios("ArchivoDeDatos/ComentariosAlCanal.csv",
                    arrCategoria,cantidadCategorias);

    pruebaCategorias("ArchivoDeReportes/ReporteDePruebaConComentarios.txt",
                    arrCategoria,cantidadCategorias,true,true);

    return 0;
}
