/*
*Autor: Diego Axel Lopez Reyes
*Titulo:
*Fecha y Hora:
*/

#include "Bibliotecas/FuncionesAuxiliares.h"
#include "Bibliotecas/Distrito.h"
#include "Bibliotecas/Plato.h"
#include "Bibliotecas/Cliente.h"

int main(int argc, char **argv) {

    Distrito arrDistritos[MAX_DISTRITOS]{};
    int cantDistritos = 0;

    Plato arrPlatos[MAX_PLATOS]{};
    int cantPlatos = 0;

    Cliente arrClientes[MAX_CLIENTES]{};
    int cantClientes = 0;

    //PlatosOfrecidos.csv
    //PO-11283,2 BOLAS DE HELADO,14.90,POSTRES

    leerPlatosOfrecidos("ArchivoDeDatos/PlatosOfrecidos.csv",
                        arrPlatos,cantPlatos);

    pruebaPlatosOfrecidos("ArchivoDeReportes/ReportePruebaPlatosOfrecidos.txt",
                        arrPlatos,cantPlatos);

    //Distritos.csv
    //LN3085,Ancon,NORTE

    leerDistritos("ArchivoDeDatos/Distritos.csv",
                arrDistritos,cantDistritos);

    pruebaDistritos("ArchivoDeReportes/ReportePruebaDistritos.txt",
                arrDistritos,cantDistritos);

    //Clientes.csv
    //90367684,CORONEL CHUMPITAZ HELI,LO4328

    leerClientes("ArchivoDeDatos/Clientes.csv",
                arrClientes,cantClientes,arrDistritos,cantDistritos);

    pruebaClientes("ArchivoDeReportes/ReportePruebaClientes.txt",
                arrClientes,cantClientes);

    //PedidosRealizados.txt (la verdadera chamba) :'u
    procesarPedidosRealizados("ArchivoDeDatos/PedidosRealizados.txt",
                            arrPlatos,cantPlatos,arrDistritos,cantDistritos,
                            arrClientes,cantClientes);

    //recuerda:
    //strcmp() >0 --> ascendente
    //strcmp() <0 --> descendente

    ordenarClientes(arrClientes,cantClientes);

    ordenarPlatosPedidos(arrClientes,cantClientes);

    emitirReporte("ArchivoDeReportes/ReportePedidosCliente.txt",
                arrClientes,cantClientes,
                arrDistritos,cantDistritos,
                arrPlatos,cantPlatos);


    return 0;
}
