/*
 *Nombre: Diego Axel López Reyes
 *Descripcion: Se realizará un reporte de ventas por libros en base a los datos
 *proprocionados por el txt (libros,clientes,ventas), donde se filtrará las fechas
 *emitidas por el usuario, se mostrarán las librerias y ventas por cada libro y
 *finalizando se mostrará un resumen por cada libro y uno final recopilando todos los datos
 */

//viene para el parcial //archivos y archivos con arreglos

#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {

    crearReporte("ArchivosDeDatos/libros.txt",
                "ArchivosDeDatos/Ventas.txt",
                "ArchivosDeDatos/Clientes.txt",
                "ArchivosDeReportes/ReporteDeVentas.txt");
    return 0;
}
