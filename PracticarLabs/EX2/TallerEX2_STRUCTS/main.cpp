
#include "Bibliotecas/FuncionesAuxiliares.h"
#include "Bibliotecas/Libro.h"

int main() {

    Libro *arrLibros=new Libro[MAX_LIBROS]{};
    int cantidadLibros=0;

    Usuario *arrUsuarios=new Usuario[MAX_USUARIOS]{};
    int cantidadUsuarios=0;

    leerLibros("ArchivoDeDatos/Libros.csv",
                arrLibros,cantidadLibros);

    pruebaLibros("ArchivoDeReportes/Inicial.libros.txt",
                arrLibros,cantidadLibros);

    leerUsuarios("ArchivoDeDatos/Usuarios.csv",
                arrUsuarios,cantidadUsuarios);

    return 0;
}
