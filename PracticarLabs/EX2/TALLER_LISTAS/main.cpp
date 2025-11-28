
#include "Bibliotecas/FuncionesAuxiliares.h"


int main() {

    NodoUsuario * listaUsuarios=nullptr;
    cargarUsuarios("ArchivoDeDatos/Usuarios.csv",listaUsuarios);

    pruebaUsuarios("ArchivoDeReportes/UsuarioInicial.txt",listaUsuarios);

    //actualizarPrestamo("ArchivoDeDatos/PrestamoDeLibros.txt",listaUsuarios);


    return 0;
}
