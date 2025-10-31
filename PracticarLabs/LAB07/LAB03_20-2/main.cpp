/*
*Autor: Diego Axel Lopez Reyes
*Titulo:
*Fecha y Hora:
*/

#include "FuncionesAuxiliares.h"

int main(int argc, char **argv) {

    //Productos.txt
    //362085    96    ENALAPRIL T/30 10MG
    int arrCodeProducto[MAX_PRODUCTOS]{};
    int arrStockProducto[MAX_PRODUCTOS]{};
    char* arrDescProd[MAX_PRODUCTOS];
    int cantProductos = 0;

    //Con libreria Cstring
    /*cargarProductosConCstring("ArchivoDeDatos/Productos.txt",
                    arrCodeProducto,arrStockProducto,
                    arrDescProd,cantProductos);*/

    //Sin libreria Cstring
    cargarProductosSinCstring("ArchivoDeDatos/Productos.txt",
                    arrCodeProducto,arrStockProducto,
                    arrDescProd,cantProductos);

    pruebaProductos("ArchivoDeReportes/Reporte-Prueba-Productos.txt",
                    arrCodeProducto,arrStockProducto,
                    arrDescProd,cantProductos);

    //prueba rapida, a coomparacion de prueba productos que es un mini reporte
    /*for (int i=0;i<cantProductos;i++) {
        cout <<i+1<<") "<<arrCodeProducto[i]<<" - "<<arrStockProducto[i]<<" - "<< arrDescProd[i]<<endl;
    }*/

    //Movimientos.txt [Productos Con Déficit (actualizacion)]
    //750   63640178   (P o R)
    //605093   24
    //835103   37
    //538466   20
    //307965   36
    //313114   36
    int arrCodeProductoDef[MAX_PRODUCTOS]{};
    int arrStockProductoDef[MAX_PRODUCTOS]{};
    char *arrDescProdDef[MAX_PRODUCTOS]{};
    int cantProductosDef = 0;

    procesarMovimientos("ArchivoDeDatos/Movimientos.txt",
                        arrCodeProducto,arrStockProducto,
                        arrDescProd,cantProductos,
                        arrCodeProductoDef,arrStockProductoDef,
                        arrDescProdDef,cantProductosDef);


    //Reporte sin ordenar:

    generarReporte("ArchivoDeReportes/ReporteDeStocksDeProductos.txt",
        arrCodeProducto,arrStockProducto,arrDescProd,cantProductos,
        arrCodeProductoDef,arrStockProductoDef,arrDescProdDef,cantProductosDef);

    //Reporte ordenado

    ordenarReporte(arrCodeProducto,arrStockProducto,arrDescProd,cantProductos,
        arrCodeProductoDef,arrStockProductoDef,arrDescProdDef,cantProductosDef);

    generarReporte("ArchivoDeReportes/ReporteDeStocksDeProductos-Ordenado.txt",
        arrCodeProducto,arrStockProducto,arrDescProd,cantProductos,
        arrCodeProductoDef,arrStockProductoDef,arrDescProdDef,cantProductosDef);




    return 0;
}
