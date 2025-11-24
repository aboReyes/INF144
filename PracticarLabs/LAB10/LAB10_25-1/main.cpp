//9:56

#include "Bibliotecas/FuncionesAuxiliares.h"


int main(int argc, char **argv) {

    Nodo *listaCuentasBancarias=nullptr;

    cargarCuentasBancarias("ArchivoDeDatos/CuentasBancarias.csv",
                        listaCuentasBancarias);

    cargarMovimientoDeCuentas("ArchivoDeDatos/MovimientosDeCuentas.csv",
                                listaCuentasBancarias);

    emitirReporte("ArchivoDeReportes/ReporteDeSaldosDeLasCuentas.txt",
                    listaCuentasBancarias);

    eliminarSaldosPositivos(listaCuentasBancarias);

    emitirReporte("ArchivoDeReportes/ReporteDeCuentasQueSeCierran.txt",
                    listaCuentasBancarias);
    
    return 0;
}
