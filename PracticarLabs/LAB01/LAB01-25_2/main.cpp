/*
*Autor: Diego Axel Lopez Reyes
*Titulo:
*Fecha y Hora:
*/

#include "Bibliotecas/FuncionesAuxiliares.h"

int main(int argc, char **argv) {
    //leer el archivo de datos
    /*ifstream archTwitch("ArchivoDatos/twitchdataTP.txt",ios::in);
    if (not archTwitch.is_open()) {
        cout << "ERROR, no se pudo abrir el archivo";
        exit(1);
    }
    ofstream archReporte("ArchivoReporte/Reporte.txt",ios::out); //para crear el reporte*/

    procesarDatos("ArchivoDatos/twitchdataTP.txt","ArchivoReporte/Reporte.txt");

    return 0;
}
