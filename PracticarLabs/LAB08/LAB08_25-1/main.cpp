

#include "Bibliotecas/FuncionesAuxiliares.h"

//se trabajará con estático los campos de los structs y en el main

int main(int argc, char **argv) {

    TablaDeInfracciones arrTablaDeInfracciones[MAX_TABLA_INFRA]{};
    int cantTablaDeInfracciones = 0;

    EmpresasRegistradas arrEmpresasRegistradas[MAX_EMPRESA_REG]{};
    int cantEmpresasRegistradas = 0;


    leerTablaInfracciones("ArchivoDeDatos/TablaDeInfracciones.csv",
                        arrTablaDeInfracciones,cantTablaDeInfracciones);

    /*for (int i=0; i<cantTablaDeInfracciones; i++) {
        cout<<arrTablaDeInfracciones[i].codigo<<" - ";
        cout<<arrTablaDeInfracciones[i].multa<<" - ";
        cout<<arrTablaDeInfracciones[i].descripcion<<endl;
    }*/

    leerEmpresasRegistradas ("ArchivoDeDatos/EmpresasRegistradas.csv",
                            arrEmpresasRegistradas,cantEmpresasRegistradas);

    /*for (int i=0; i<cantEmpresasRegistradas; i++) {
        cout<<arrEmpresasRegistradas[i].dni<<" - ";
        cout<<arrEmpresasRegistradas[i].nombre<<" - ";
        cout<<arrEmpresasRegistradas[i].distrito<<endl;
    }*/


    completarPlacasRegistradas("ArchivoDeDatos/PlacasRegistradas (2).txt",
                            arrEmpresasRegistradas,cantEmpresasRegistradas);

    /*for (int i=0; i<cantEmpresasRegistradas; i++) {
        cout<<"EMPRESA: "<<i+1<<arrEmpresasRegistradas[i].dni<<endl;
        int numPlacas=arrEmpresasRegistradas[i].numPlacas;
        for (int j=0; j<numPlacas; j++) {
            cout<<setw(10)<<right<<arrEmpresasRegistradas[i].placas[j]<<endl;
        }
    }*/

    completarInfracciones("ArchivoDeDatos/InfraccionesCometidas.csv",
                           arrTablaDeInfracciones,cantTablaDeInfracciones,
                           arrEmpresasRegistradas,cantEmpresasRegistradas);

    ordenarEmpresasRegistradas(arrEmpresasRegistradas,cantEmpresasRegistradas);

    ordenarTablaDeInfracciones(arrTablaDeInfracciones,cantTablaDeInfracciones);

    //por fin :')

    imprimirReporte("ArchivoDeReportes/ReporteInfraccionesPorEmpresa.txt",
                    arrTablaDeInfracciones,cantTablaDeInfracciones,
                    arrEmpresasRegistradas,cantEmpresasRegistradas);

    return 0;
}
