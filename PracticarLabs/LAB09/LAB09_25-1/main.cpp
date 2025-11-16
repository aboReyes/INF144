/*
*Autor: Diego Axel Lopez Reyes
*Titulo:
*Fecha y Hora:
*/

#include  "Bibliotecas/FuncionesAuxiliares.h"

int main(int argc, char **argv) {

    TablaDeInfracciones *arrTablaDeInfracciones=new TablaDeInfracciones[MAX_TABLA_INFRA]{} ;
    int cantTablaDeInfracciones=0;

    EmpresaRegistrada *arrEmpresasRegistradas=new EmpresaRegistrada[MAX_EMPRE_REG]{} ;
    int cantEmpresasRegistradas=0;


    leerTablaDeInfracciones("ArchivoDeDatos/TablaDeInfracciones (1).csv",
                            arrTablaDeInfracciones,cantTablaDeInfracciones);

    /*for (int i=0;i<cantTablaDeInfracciones;i++) {
        cout<<arrTablaDeInfracciones[i].codigo<<" - ";
        cout<<arrTablaDeInfracciones[i].multa<<" - ";
        cout<<arrTablaDeInfracciones[i].descripcion<<endl;
    }*/

    leerEmpresasRegistradas("ArchivoDeDatos/EmpresasRegistradas (1).csv",
                            arrEmpresasRegistradas,cantEmpresasRegistradas);

    /*for (int i=0;i<cantEmpresasRegistradas;i++) {
        cout<<arrEmpresasRegistradas[i].dni<<" - ";
        cout<<arrEmpresasRegistradas[i].nombre<<" - ";
        cout<<arrEmpresasRegistradas[i].distrito<<endl;
    }*/

    leerCompletarPlacasRegistradas("ArchivoDeDatos/PlacasRegistradas.csv",
                                arrEmpresasRegistradas,cantEmpresasRegistradas);

    //y si sirve para los dos casos
    /*for (int i=0;i<cantEmpresasRegistradas;i++) {
        cout<<arrEmpresasRegistradas[i].dni<<" - ";
        cout<<arrEmpresasRegistradas[i].nombre<<" - ";
        cout<<arrEmpresasRegistradas[i].distrito<<endl;
        cout<<" PLACAS: "<<endl;
        for (int j=0;j<arrEmpresasRegistradas[i].numPlacas;j++) {
            cout<<arrEmpresasRegistradas[i].placas[j]<<" ";
        }
        cout<<endl;
    }*/

    leerInfraccionesCometidas("ArchivoDeDatos/InfraccionesCometidas (1).csv",
                            arrTablaDeInfracciones,cantTablaDeInfracciones,
                            arrEmpresasRegistradas,cantEmpresasRegistradas);

    calcularMontosTotalesYAdeudados(arrEmpresasRegistradas,cantEmpresasRegistradas);

    ordenarEmpresasRegistradas(arrEmpresasRegistradas,cantEmpresasRegistradas);

    //no sé si sea la manera correcta pero es la única que se me ocurrió


    emitirReporte("ArchivoDeReportes/ReporteInfracciones.txt",
                arrTablaDeInfracciones,cantTablaDeInfracciones,
                arrEmpresasRegistradas,cantEmpresasRegistradas);


    return 0;
}
