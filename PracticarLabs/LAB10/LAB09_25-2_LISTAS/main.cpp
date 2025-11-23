
#include "Bibliotecas/FuncionesAuxiliares.h"

int main(int argc, char **argv) {

    //depende el IDE, se puede quitar el "=nullptr", CLion god y lo asigna
    //en caso no lo coloques
    Nodo *listaCategoria=nullptr;

    /*//CASO INSERCION AL FINAL (FIRST IN, FIRST OUT)
    leerCategorias("ArchivoDeDatos/Categorias (3).csv",
                    listaCategoria,false,true,false);

    pruebaCategorias("ArchivoDeReportes/PruebaCategoriasFinal.txt",
                    listaCategoria);



    //CASO INSERCION AL INICIO (LAST IN, FIRST OUT)
    leerCategorias("ArchivoDeDatos/Categorias (3).csv",
                    listaCategoria,true,false,false);

    pruebaCategorias("ArchivoDeReportes/PruebaCategoriasInicio.txt",
                    listaCategoria);*/



    //CASO INSERCION ORDENADA
    leerCategorias("ArchivoDeDatos/Categorias (3).csv",
                    listaCategoria,false,false,true);

    pruebaCategorias("ArchivoDeReportes/PruebaCategoriasOrdenada.txt",
                    listaCategoria);

    //ACTUALIZAR (PARA LLENAR CAMPOS FALTANTES)

    actualizarLista("ArchivoDeDatos/StreamsReproducidos (1).csv",listaCategoria);


    //ACTUALIZAR COMENTARIOS

    actualizarComentarios("ArchivoDeDatos/ComentariosAlCanal (1).csv",listaCategoria);


    //reporteFinal

    generarReporte("ArchivoDeReportes/ReporteFinal.txt",listaCategoria);

    return 0;
}
