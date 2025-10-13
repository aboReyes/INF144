/*
*Autor: Diego Axel Lopez Reyes
*Titulo:
*Fecha y Hora: 10:43
*/

#include "Bibliotecas/FuncionesAuxiliares.h"

int main(int argc, char **argv) {
    //Libros.txt
    //9155175	[Diamantes y pedernales]	*Jose Maria Arguedas*	69.02
    int arrCodeLibro[MAX_LIBROS]{};
    double arrPrecioLibro[MAX_LIBROS]{};
    int cantLibros=0;

    leerLibros("ArchivoDeDatos/libros (1).txt",arrCodeLibro,
                arrPrecioLibro,cantLibros);
    /*ordenarLibros(arrCodeLibro,
                arrPrecioLibro,cantLibros);*/
    repPruebaLibros("ArchivoDeReporte/ReportePruebaLibros.txt",arrCodeLibro,
                arrPrecioLibro,cantLibros);

    //Ventas.txt
    //99377    29/04/2024    --> repite:    6398790    92240876    18    ...
    int arrPrimeraFechaVentas[MAX_LIBROS]{};
    int arrUltimaFechaVentas[MAX_LIBROS]{};
    int arrUnidadesVentas[MAX_LIBROS]{};
    int arrPrimerDniVentas[MAX_LIBROS]{};
    int arrUltimoDniVentas[MAX_LIBROS]{};
    double arrPromCalVentas[MAX_LIBROS]{};
    double arrTotalVentas[MAX_LIBROS]{};
    leerProcesarVentas("ArchivoDeDatos/Ventas (1).txt",
                        arrCodeLibro,arrPrecioLibro,
                        arrUnidadesVentas,arrPromCalVentas,
                        arrTotalVentas,arrPrimeraFechaVentas,arrPrimerDniVentas,
                        arrUltimaFechaVentas,arrUltimoDniVentas,cantLibros);
    //Reporte.txt

    //Sin ordenar
    imprimirReporte("ArchivoDeReporte/ReporteVentasPorLibro.txt",arrCodeLibro,
                    arrPrecioLibro,arrUnidadesVentas,arrPromCalVentas,arrTotalVentas,
                    arrPrimeraFechaVentas,arrPrimerDniVentas,arrUltimaFechaVentas,
                    arrUltimoDniVentas,cantLibros);

    //Ordenado :u

    ordenarReporte(arrCodeLibro,arrPrecioLibro,arrUnidadesVentas,
                    arrPromCalVentas,arrTotalVentas,arrPrimeraFechaVentas,
                    arrPrimerDniVentas,arrUltimaFechaVentas,
                    arrUltimoDniVentas,cantLibros);

    imprimirReporte("ArchivoDeReporte/ReporteVentasPorLibroOrdenado.txt",arrCodeLibro,
                    arrPrecioLibro,arrUnidadesVentas,arrPromCalVentas,arrTotalVentas,
                    arrPrimeraFechaVentas,arrPrimerDniVentas,arrUltimaFechaVentas,
                    arrUltimoDniVentas,cantLibros);

    return 0;
}
