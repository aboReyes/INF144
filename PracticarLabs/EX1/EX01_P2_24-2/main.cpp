/*
*Autor: Diego Axel Lopez Reyes
*Titulo:
*Fecha y Hora:
*/

#include "Bibliotecas/FuncionesAuxiliares.h"

int main(int argc, char **argv) {

    //PlatosOfrecidos.txt
    //cuando hay descuento: 31796 ANTICUCHO DE CORAZON AL PLATO}   31.90   43   19.94%
    //cuando no hay descuento: 53265 ANTICUCHO}   12.90   150
    int arrCodigoPlato[MAX_PLATOS]{};
    double arrPrecioPlato[MAX_PLATOS]{};
    int arrCantPlatosAtendidos[MAX_PLATOS]{};
    double arrDescuentoPlato[MAX_PLATOS]{};
    int nroPlatos=0;

    cargarPlatosOfrecidos("ArchivoDeDatos/PlatosOfrecidos (3).txt",arrCodigoPlato,
                            arrPrecioPlato,arrCantPlatosAtendidos,arrDescuentoPlato,
                            nroPlatos);


    //Clientes.txt
    // con descuento:  90367684   CORONEL CHUMPITAZ HELI]   8594   Villa_Maria_del_Triunfo   M   S   13.04%
    // sin descuento: 66039166   LAURA WONG MELVIN HENRRY]   3562   Rimac   B   N
    int arrDniCliente[MAX_CLIENTES]{};
    double arrDescuentoCliente[MAX_CLIENTES]{};
    int nroClientes=0;

    cargarClientes("ArchivoDeDatos/Clientes (3).txt",
                    arrDniCliente,arrDescuentoCliente,nroClientes);

    //Reporte prueba para clientes.txt y PlatosOfrecidos.txt
    reportePrueba("ArchivoDeReportes/ReportePrueba.txt",
                arrCodigoPlato,arrPrecioPlato,
                arrCantPlatosAtendidos,arrDescuentoPlato,nroPlatos,
                arrDniCliente,arrDescuentoCliente,nroClientes);


    //RepartosARealizar.txt
    //961419(nroPedido)   77324146(dniClien)   9(cantPedida)   53764(codPlato)   4   90766   1   90758....
    int arrCantAtendida[MAX_PLATOS]{}; //supongo que serán las atendidas
    int arrCantNoAtendida[MAX_PLATOS]{};
    double arrMontoEsperado[MAX_PLATOS]{};
    double arrMontoBruto[MAX_PLATOS]{};
    double arrMontoRecibido[MAX_PLATOS]{};

    cargarRepartosARealizar("ArchivoDeDatos/RepartosARealizar (3).txt",
                            arrCodigoPlato,arrPrecioPlato,
                            arrCantPlatosAtendidos,arrDescuentoPlato,nroPlatos,
                            arrDniCliente,arrDescuentoCliente,nroClientes,
                            arrCantAtendida,arrCantNoAtendida,arrMontoEsperado,
                            arrMontoBruto,arrMontoRecibido);

    ordenarReporte(arrCodigoPlato,arrPrecioPlato,
                    arrCantPlatosAtendidos,arrDescuentoPlato,nroPlatos,
                    arrDniCliente,arrDescuentoCliente,
                    arrCantAtendida,arrCantNoAtendida,arrMontoEsperado,
                    arrMontoBruto,arrMontoRecibido);

    imprimirReporte("ArchivoDeReportes/Reporte1Repartos.txt",
                    arrCodigoPlato,arrPrecioPlato,
                    arrCantPlatosAtendidos,arrDescuentoPlato,nroPlatos,
                    arrDniCliente,arrDescuentoCliente,nroClientes,
                    arrCantAtendida,arrCantNoAtendida,arrMontoEsperado,
                    arrMontoBruto,arrMontoRecibido);

    eliminarNoAtendidos_0(arrCodigoPlato,arrPrecioPlato,
                        arrCantPlatosAtendidos,arrDescuentoPlato,nroPlatos,
                        arrCantAtendida,arrCantNoAtendida,arrMontoEsperado,
                        arrMontoBruto,arrMontoRecibido);

    imprimirReporte("ArchivoDeReportes/Reporte2Repartos.txt",
                    arrCodigoPlato,arrPrecioPlato,
                    arrCantPlatosAtendidos,arrDescuentoPlato,nroPlatos,
                    arrDniCliente,arrDescuentoCliente,nroClientes,
                    arrCantAtendida,arrCantNoAtendida,arrMontoEsperado,
                    arrMontoBruto,arrMontoRecibido);

    return 0;
}
