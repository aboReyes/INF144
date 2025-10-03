/*
*Autor: Diego Axel Lopez Reyes
*Titulo: En base al archivo de texto proporcionado, se
*realizará un reporte indicando los datos y multas vehiculares de el representante
*legal de cada compañia
*Fecha y Hora: 
*
*/

#include "Bibliotecas/FuncionesAuxiliares.h"

int main(int argc, char **argv) {
    int diaIni,mesIni,añoIni,diaFin,mesFin,añoFin;
    cout<<fixed;
    cout.precision(2);
    leerFecha_MostrarTitulo(diaIni,mesIni,añoIni,
                            diaFin,mesFin,añoFin);
    leerImprimirReporteCompañia(diaIni,mesIni,añoIni,
                                diaFin,mesFin,añoFin);
    return 0;
}
