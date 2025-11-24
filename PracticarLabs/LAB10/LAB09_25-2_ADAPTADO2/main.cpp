
#include "Bibliotecas/FuncionesAuxiliares.h"

int main(int argc, char **argv) {

    NodoCategoria *listaCategoria =nullptr;

    crearListaCategoria("ArchivoDeDatos/Categorias (3).csv",listaCategoria);

    actualizarReproducciones("ArchivoDeDatos/StreamsReproducidos (1).csv",listaCategoria);

    actualizarComentarios("ArchivoDeDatos/ComentariosAlCanal (1).csv",listaCategoria);

    //decidí calcular totales para que tenga sentido el orden de eliminar
    calcularTotales(listaCategoria);

    emitirReporte("ArchivoDeReportes/ReportePorCategorias.txt",listaCategoria);

    //consideré eliminar si cuenta con un rating menor a 3
    eliminarPorRating(listaCategoria);

    emitirReporte("ArchivoDeReportes/ReportePorCategoriasCasoEliminacion.txt",listaCategoria);



    return 0;
}
