/*
*Autor: Diego Axel Lopez Reyes
*Titulo:
*Fecha y Hora:
*/

#include "Bibliotecas/FuncionesAuxiliares.h"

int main(int argc, char **argv) {

    //RepartosARealizar.txt
    //358019   93231760
    //se repite...
    //8   11471
    //7   77572

    int arrNumPlatosVendidos[MAX_REPARTOS]{};
    int arrCodigoPlatos[MAX_REPARTOS]{};
    int cantRepartos=0;

    cargarRepartos("ArchivoDeDatos/RepartosARealizar (4).txt",
                    arrNumPlatosVendidos,arrCodigoPlatos,cantRepartos);

    /*for (int i=0;i<cantRepartos;i++) {
        cout<<arrNumPlatosVendidos[i]<<" - "<<arrCodigoPlatos[i]<<endl;
    }*/
    //PlatosOfrecidos.txt
    //puede tener o no descuento
    //39747     COCA_COLA_1/2_LITRO      7      ADICIONAL    9.03%
    //90365     MOLLEGITAS_A_LA_PARRILLA    25.9    ADICIONAL

    double arrPrecio[MAX_REPARTOS]{};
    double arrIngresoBruto[MAX_REPARTOS]{};
    double arrDescuento[MAX_REPARTOS]{};
    bool arrTieneDescuento[MAX_REPARTOS]{};
    double arrTotal[MAX_REPARTOS]{};

    procesarPlatos("ArchivoDeDatos/PlatosOfrecidos (4).txt",
                arrNumPlatosVendidos,arrCodigoPlatos,cantRepartos,
                arrPrecio,arrIngresoBruto,arrDescuento,arrTotal,
                arrTieneDescuento);

    pruebaDatos("ArchivoDeReportes/ReporteDePruebaDeCargaDeDatos.txt",
                arrNumPlatosVendidos,arrCodigoPlatos,cantRepartos,
                arrPrecio,arrIngresoBruto,arrDescuento,arrTotal,
                arrTieneDescuento);

    
    //Reporte con los formatos de modificacion de cadena:
    crearReporte("ArchivoDeDatos/PlatosOfrecidos (4).txt",
                "ArchivoDeReportes/ReportePlatos.txt",
                arrNumPlatosVendidos,arrCodigoPlatos,cantRepartos,
                arrPrecio,arrIngresoBruto,arrDescuento,arrTotal,
                arrTieneDescuento);

    return 0;
}
