

#include "Bibliotecas/FuncionesAuxiliares.h"
#include "Bibliotecas/Libro.h"

int main() {

    Libro *arrLibros=new Libro[MAX_LIBROS]{};
    int cantidadLibros=0;

    Usuario *arrUsuarios=new Usuario[MAX_USUARIOS]{};
    int cantidadUsuarios=0;

    leerLibros("ArchivoDeDatos/Libros.csv",
                arrLibros,cantidadLibros);

    pruebaLibros("ArchivoDeReportes/InicialLibros.txt",
                arrLibros,cantidadLibros,false);

    leerUsuarios("ArchivoDeDatos/Usuarios.csv",
                arrUsuarios,cantidadUsuarios);

    pruebaUsuarios("ArchivoDeReportes/InicialUsuarios.txt",
                arrUsuarios,cantidadUsuarios,false);

    actualizarPrestamos("ArchivoDeDatos/PrestamoDeLibros.txt",
                arrLibros,cantidadLibros,arrUsuarios,cantidadUsuarios);

    pruebaLibros("ArchivoDeReportes/LibrosConPrestamo.txt",
                arrLibros,cantidadLibros,true);

    pruebaUsuarios("ArchivoDeReportes/UsuariosConPrestamos.txt",
                arrUsuarios,cantidadUsuarios,true);

    ordenarReporte(arrLibros,cantidadLibros);

    pruebaLibros("ArchivoDeReportes/LibrosOrdenado.txt",
                arrLibros,cantidadLibros,true);

    return 0;
}
