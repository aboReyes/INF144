/*
*Autor: Diego Axel Lopez Reyes
*Titulo:
*Fecha y Hora:
*/


#include "Bibliotecas/FuncionesAuxiliares.h"

int main(int argc, char **argv) {

    //Repartidores.txt
    //54805724   Vizcardo_Sinche_Maribel     Motocicleta      4826   Santa_Rosa
    int arrDniRepartidor[MAX_REPARTIDORES]{};
    char *arrNombreRepartidor[MAX_REPARTIDORES]{};
    char *arrTipoVehiculo[MAX_REPARTIDORES]{};
    int arrCodigoDistrito[MAX_REPARTIDORES]{};
    char *arrNombreDistrito[MAX_REPARTIDORES]{};
    int cantRepartidores=0;

    cargarRepartidores("ArchivoDeDatos/Repartidores (4).txt",
                        arrDniRepartidor,arrNombreRepartidor,
                        arrTipoVehiculo,arrCodigoDistrito,
                        arrNombreDistrito,cantRepartidores);

    //PlatosOfrecidos.txt
    //con y sin descuento
    //73428       TEQUENOS       19.50       APERITIVO
    //11283   2_BOLAS_DE_HELADO      14.90   POSTRES    17.72%
    int arrCodigoPlato[MAX_PLATOS_OFRECIDOS]{};
    char *arrNombrePlato[MAX_PLATOS_OFRECIDOS]{};
    double arrPrecioPlato[MAX_PLATOS_OFRECIDOS]{};
    char *arrCategoriaPlato[MAX_PLATOS_OFRECIDOS]{};
    double arrDescuentoPlato[MAX_PLATOS_OFRECIDOS]{};
    int cantPlatos=0;

    cargarPlatos("ArchivoDeDatos/PlatosOfrecidos (5).txt",
                arrCodigoPlato,arrNombrePlato,
                arrPrecioPlato,arrCategoriaPlato,
                arrDescuentoPlato,cantPlatos);

    //Reporte de prueba para Repartidores.txt y PlatosOfrecidos.txt

    reportePrueba("ArchivoDeReportes/ReporteDePrueba.txt",
                arrDniRepartidor,arrNombreRepartidor,
                arrTipoVehiculo,arrCodigoDistrito,
                arrNombreDistrito,cantRepartidores,
                arrCodigoPlato,arrNombrePlato,
                arrPrecioPlato,arrCategoriaPlato,
                arrDescuentoPlato,cantPlatos);

    //Ordenar Repartidores ascendentemente

    ordenarRepartidores(arrDniRepartidor,arrNombreRepartidor,
                        arrTipoVehiculo,arrCodigoDistrito,
                        arrNombreDistrito,cantRepartidores);

    reportePrueba("ArchivoDeReportes/ReporteOrdenadoDePrueba.txt",
                arrDniRepartidor,arrNombreRepartidor,
                arrTipoVehiculo,arrCodigoDistrito,
                arrNombreDistrito,cantRepartidores,
                arrCodigoPlato,arrNombrePlato,
                arrPrecioPlato,arrCategoriaPlato,
                arrDescuentoPlato,cantPlatos);

    //RepartosARealizar.txt
    //358019   93231760   7752        Bicicleta        S        19.47%
    //se repite
    //8   11471
    //7   77572

    //804501   71422479   8280       Motocicleta       N
    ////se repite
    //3   39475
    //1   15760

    //para reporte repartidores
    int arrTotalCantPlatosRep[MAX_REPARTIDORES]{};
    double arrMontoTotalPlatos[MAX_REPARTIDORES]{};
    double arrDescuentoPorPlatos[MAX_REPARTIDORES]{};
    double arrDescuentoPorClientes[MAX_REPARTIDORES]{};
    double arrPagoAlRepartidor[MAX_REPARTIDORES]{};
    double arrTotalIngresadoRep[MAX_REPARTIDORES]{};

    //para reporte platos
    int arrTotalCantPlatos[MAX_PLATOS_OFRECIDOS]{};
    double arrMontoVendido[MAX_PLATOS_OFRECIDOS]{};
    double arrDescuentoAlPlato[MAX_PLATOS_OFRECIDOS]{};
    double arrDescuentoAlCliente[MAX_PLATOS_OFRECIDOS]{};
    double arrTotalIngresadoPlatos[MAX_PLATOS_OFRECIDOS]{};


    procesarRepartosARealizar("ArchivoDeDatos/RepartosARealizar (5).txt",
                            arrTipoVehiculo,arrCodigoDistrito,cantRepartidores,
                            arrCodigoPlato,arrPrecioPlato,arrDescuentoPlato,cantPlatos,
                            arrTotalCantPlatosRep,arrMontoTotalPlatos,arrDescuentoPorPlatos,
                            arrDescuentoPorClientes,arrPagoAlRepartidor,arrTotalIngresadoRep,
                            arrTotalCantPlatos,arrMontoVendido,arrDescuentoAlPlato,
                            arrDescuentoAlCliente,arrTotalIngresadoPlatos);


    //ordenar los platos
    //descendente por su cantidad vendida y ascendente por el nombre del plato

    ordenarPlatos(arrCodigoPlato,arrNombrePlato,
                arrPrecioPlato,arrCategoriaPlato,
                arrDescuentoPlato,cantPlatos,
                arrTotalCantPlatos,arrMontoVendido,
                arrDescuentoAlPlato,arrDescuentoAlCliente,
                arrTotalIngresadoPlatos);

    //Reporte1: Repartidores

    generarReportePorRepartidores("ArchivoDeReportes/EntregasPorRepartidor.txt",
                                arrDniRepartidor,arrNombreRepartidor,arrTipoVehiculo,
                                arrNombreDistrito,arrTotalCantPlatosRep,arrMontoTotalPlatos,
                                arrDescuentoPorPlatos,arrDescuentoPorClientes,arrPagoAlRepartidor,
                                arrTotalIngresadoRep,cantRepartidores);

    //Reporte2: Platos

    generarReportePorPlatos("ArchivoDeReportes/EntregasPorPlato.txt",
                            arrCodigoPlato,arrNombrePlato,arrCategoriaPlato,
                            arrPrecioPlato,arrDescuentoPlato,arrTotalCantPlatos,
                            arrMontoVendido,arrDescuentoAlPlato,arrDescuentoAlCliente,
                            arrTotalIngresadoPlatos,cantPlatos);

    return 0;
}
