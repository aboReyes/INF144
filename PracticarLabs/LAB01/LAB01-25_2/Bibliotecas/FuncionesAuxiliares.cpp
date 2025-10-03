//
// Created by ASUS on 11/09/2025.
//

#include "FuncionesAuxiliares.h"

void procesarDatos(const char* nomArchIn,const char* nomArchOut) {

    ifstream archTwitch(nomArchIn,ios::in);
    if (not archTwitch.is_open()) {
        cout<<"ERROR, no se pudo abrir el archivo"<<endl;
        exit(1);
    }

    ofstream archRep(nomArchOut,ios::out);

    archRep<<fixed;
    archRep.precision(2);

    int cantTotalStreams=0;
    int durTotalStreamsSeg=0;
    double ingTotalStreams=0.0;

    double mayorIngresoCanal=0.0;
    char letraCanalMayorIngreso;
    int codigoCanalMayorIngreso;

    int nroCanal=0;
    while (true) {
        leerDatosCanalReporte(archTwitch,archRep,
                                cantTotalStreams,durTotalStreamsSeg,ingTotalStreams,
                                mayorIngresoCanal,codigoCanalMayorIngreso,letraCanalMayorIngreso,nroCanal);
        if (archTwitch.eof()) break;
    }
    imprimirResumenFinal(archRep,cantTotalStreams,durTotalStreamsSeg,ingTotalStreams,
                            mayorIngresoCanal,codigoCanalMayorIngreso,letraCanalMayorIngreso);
}

void leerDatosCanalReporte(ifstream &archTwitch,ofstream &archRep,
                        int &cantTotalStreams,int &durTotalStreamsSeg,double &ingTotalStreams,
                        double &mayorIngresoCanal,int &codigoCanalMayorIngreso,char &letraCanalMayorIngreso,int &nroCanal) {
    int dia,mes,año,numCodCanal;
    char c,letraCodCanal;

    archTwitch>>dia>>c>>mes>>c>>año>>letraCodCanal>>numCodCanal;
    if (archTwitch.eof()) return;
    nroCanal++;

    imprimirCabeceraCanal(dia,mes,año,letraCodCanal,numCodCanal,archTwitch,archRep,nroCanal);

    leerStreamsReporte(archTwitch,archRep,
                        cantTotalStreams,durTotalStreamsSeg,ingTotalStreams,
                        mayorIngresoCanal,codigoCanalMayorIngreso,letraCanalMayorIngreso,
                        letraCodCanal,numCodCanal);

    //while (archTwitch.get()!='\n'); //eliminar los datos que quedan en la linea
}

void imprimirCabeceraCanal(int dia,int mes,int año,char letraCodCanal,int numCodCanal,
                            ifstream &archTwitch,ofstream &archRep,int nroCanal) {

    archRep<<"CANAL No. "<<nroCanal<<endl;
    archRep<<setw(5)<<" "<<setw(15)<<left<<"NOMBRE"<<setw(10)<<left<<"CODIGO"<<setw(12)<<left<<"CREADO EL"<<
        setw(30)<<left<<"NUMERO DE SEGUIDORES"<<endl;
    archRep<<setw(5)<<" "; leerImprimirNombreCanal(archTwitch,archRep);
    archRep<<letraCodCanal<<setw(9)<<left<<numCodCanal;

    imprimirFecha(archRep,dia,mes,año);

    archRep<<setw(8)<<" ";
    int nroSeguidores;
    archTwitch>>nroSeguidores;
    archRep<<nroSeguidores<<endl;
    imprimirLinea('-',80,archRep);
    //54:21
}

void leerImprimirNombreCanal(ifstream &archTwitch,ofstream &archRep) {
    char c;
    int cantEspacios=1;
    archTwitch>>ws;
    while (true) {
        c=archTwitch.get();
        if (c==' ') break;
        if (c>='a' and c<='z') c-='a'-'A';
        archRep<<c;
        cantEspacios++;
    }
    archRep<<setw(15-cantEspacios)<<" ";
}

void imprimirLinea(char c,int cant,ofstream &archRep) {
    for (int i=0;i<cant;i++) archRep<<c;
    archRep<<endl;
}

void leerStreamsReporte(ifstream &archTwitch,ofstream &archRep,
                        int &cantTotalStreams,int &durTotalStreamsSeg,double &ingTotalStreams,
                        double &mayorIngresoCanal,int &codigoCanalMayorIngreso,char &letraCanalMayorIngreso,
                        char letraCodCanal,int numCodCanal ) {
    int dia,mes,año,hora,minuto,segundo, cantVistas;
    char c;

    archRep<<setw(5)<<" "<<"ULTIMAS REPRODUCCIONES"<<endl;
    archRep<<setw(10)<<" "<<setw(25)<<left<<"FECHA DE PUBLICACION "<<setw(22)<<left<<"TIEMPO DE DURACION "<<
        setw(25)<<left<<"NUMERO DE REPRODUCCIONES"<<endl;

    int durStreamsCanalSeg=0;
    int ultimaFechaStreamCanal=0; //mayor fecha
    int cantStreamsCanal=0;

    while (true) { //leer cada una de las transmisiones
        archTwitch>>dia>>c>>mes>>c>>año>>hora>>c>>minuto>>c>>segundo>>cantVistas;
        imprimirDatosTransmisiones(dia,mes,año,hora,minuto,segundo,cantVistas,archRep);
        //procesarlo
        procesarDatosTransmision(dia,mes,año,hora,minuto,segundo,cantVistas,
                                durStreamsCanalSeg,ultimaFechaStreamCanal,cantStreamsCanal);
        if (archTwitch.get()=='\n') break;
    }
    imprimirLinea('-',80,archRep);
    double ingresoCanal = imprimirResumenCanal(archRep,durStreamsCanalSeg,ultimaFechaStreamCanal,cantStreamsCanal);
    cantTotalStreams+=cantStreamsCanal;
    durTotalStreamsSeg+=durStreamsCanalSeg;
    ingTotalStreams+=ingresoCanal;

    if (ingresoCanal>mayorIngresoCanal) {
        mayorIngresoCanal=ingresoCanal;
        letraCanalMayorIngreso= letraCodCanal;
        codigoCanalMayorIngreso= numCodCanal ;
    }
}

void procesarDatosTransmision(int dia,int mes,int año,int hora,int minuto,int segundo,int cantVistas,
                                int &durStreamsCanalSeg,int &ultimaFechaStreamCanal,int &cantStreamsCanal) {
    int fecha=año*10000+mes*100+dia;
    int durSeg=hora*3600+minuto*60+segundo;

    cantStreamsCanal+=cantVistas;
    durStreamsCanalSeg+=durSeg;

    if (fecha>ultimaFechaStreamCanal) ultimaFechaStreamCanal=fecha;
}

double imprimirResumenCanal(ofstream &archRep,int durStreamsCanalSeg,int ultimaFechaStreamCanal,int cantStreamsCanal) {
    archRep<<setw(5)<<" "<<"RESUMEN DEL CANAL: "<<endl;

    int hora=durStreamsCanalSeg/3600;
    durStreamsCanalSeg=durStreamsCanalSeg%3600;
    int minuto=durStreamsCanalSeg/60;
    durStreamsCanalSeg=durStreamsCanalSeg%60;
    int segundo=durStreamsCanalSeg;

    archRep<<setw(5)<<" "<<setw(40)<<left<<"DURACION TOTAL DE LAS REPRODUCCIONES: ";
    imprimirHora(archRep,hora,minuto,segundo);
    archRep<<endl;

    int dia=ultimaFechaStreamCanal%100;
    ultimaFechaStreamCanal=ultimaFechaStreamCanal/100;
    int mes=ultimaFechaStreamCanal%100;
    ultimaFechaStreamCanal=ultimaFechaStreamCanal/100;
    int año=ultimaFechaStreamCanal;

    archRep<<setw(5)<<" "<<setw(40)<<left<<"ULTIMA PUBLICACION: ";
    imprimirFecha(archRep,dia,mes,año);
    archRep<<endl;

    archRep<<setw(5)<<" "<<setw(40)<<left<<"TOTAL DE REPRODUCCIONES: "<<cantStreamsCanal<<endl;
    archRep<<setw(5)<<" "<<setw(40)<<left<<"INGRESO POR PUBLICIDAD: "<<"$ "<<ceil((double)cantStreamsCanal/1000)*3.25<<endl;

    imprimirLinea('-',80,archRep);

    return ceil((double)cantStreamsCanal/1000)*3.25;
}

void imprimirDatosTransmisiones(int dia,int mes,int año,int hora,int minuto,int segundo,int cantVistas,ofstream &archRep) {

    archRep<<setw(10)<<" ";
    imprimirFecha(archRep,dia,mes,año);
    archRep<<setw(18)<<" ";
    imprimirHora(archRep,hora,minuto,segundo);
    archRep<<setw(14)<<" ";
    archRep<<setw(12)<<right<<cantVistas<<endl;
}

void imprimirResumenFinal(ofstream &archRep,int cantTotalStreamers,int durTotalStreamsSeg,
                        double ingTotalStreams,double mayorIngresoCanal,int codCanalMayorIngreso,char letraCanalMayorIngreso) {
    archRep<<"RESUMEN FINAL: "<<endl;
    archRep<<"CANTIDAD TOTAL DE STREAMS COLOCADOS POR LOS CANALES: "<<cantTotalStreamers<<endl;
    int hora=durTotalStreamsSeg/3600;
    durTotalStreamsSeg=durTotalStreamsSeg%3600;
    int minuto=durTotalStreamsSeg/60;
    durTotalStreamsSeg=durTotalStreamsSeg%60;
    int segundo=durTotalStreamsSeg;
    archRep<<"DURACION TOTAL DE LOS STREAMS PUBLICADOS: ";
    imprimirHora(archRep,hora,minuto,segundo);
    archRep<<endl;
    archRep<<"INGRESOS TOTALES POR PUBLICIDAD: $ "<<ingTotalStreams<<endl;
    archRep<<"CANAL CON MAYORES INGRESOS POR PUBLICIDAD: "<<letraCanalMayorIngreso<<codCanalMayorIngreso<<" CON $ "<<mayorIngresoCanal<<endl;


}

void imprimirHora(ofstream &archRep,int hora,int minuto,int segundo) {
    archRep.fill('0');
    archRep<<setw(2)<<right<<hora<<":"<<setw(2)<<right<<minuto<<":"<<setw(2)<<right<<segundo;
    archRep.fill(' ');
}

void imprimirFecha(ofstream &archRep,int dia,int mes,int año) {
    archRep.fill('0');
    archRep<<setw(2)<<right<<dia<<"/"<<setw(2)<<right<<mes<<"/"<<setw(4)<<right<<año;
    archRep.fill(' ');
}


//1:32:58
