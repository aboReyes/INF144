//
// Created by aml on 3/10/2025.
//

#include "FuncionesAuxiliares.h"

void aperturaArchivoLectura(const char* nombArch,ifstream &arch) {
    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout << "Error, el archivo" << nombArch << " no se puede abrir"<<endl;
        exit(1);
    }
}

void aperturaArchivoEscritura(const char* nombArch,ofstream &arch) {
    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout << "Error, el archivo" << nombArch << " no se puede abrir"<<endl;
        exit(1);
    }
}

void ingresarRangoFechas(int &diaIni,int &mesIni,int &añoIni,
                        int &diaFin,int &mesFin,int &añoFin) {

    cout<<"Ingrese dia inicial: ";
    cin>>diaIni;

    cout<<"Ingrese mes inicial: ";
    cin>>mesIni;

    cout<<"Ingrese año inicial: ";
    cin>>añoIni;

    cout<<"Ingrese dia final: ";
    cin>>diaFin;

    cout<<"Ingrese mes final: ";
    cin>>mesFin;

    cout<<"Ingrese año final: ";
    cin>>añoFin;
}

void crearReporte(const char* nombArchLibros,
                const char* nombArchVentas,
                const char* nombArchClientes,
                const char* nombArchReporteVentas) {

    int diaIni=1,mesIni=1,añoIni=2005,diaFin=31,mesFin=12,añoFin=2025;
    int rangoFechaIni,rangoFechaFin;
    ifstream archLibros,archVentas,archClientes;
    ofstream archReporte;
    aperturaArchivoLectura(nombArchLibros,archLibros);
    aperturaArchivoLectura(nombArchVentas,archVentas);
    aperturaArchivoLectura(nombArchClientes,archClientes);
    aperturaArchivoEscritura(nombArchReporteVentas,archReporte);

    /*ingresarRangoFechas(diaIni,mesIni,añoIni,
                        diaFin,mesFin,añoFin);*/
    rangoFechaIni = convertirDDMMYYYY_Num(diaIni,mesIni,añoIni);
    rangoFechaFin = convertirDDMMYYYY_Num(diaFin,mesFin,añoFin);

    imprimirTitulo(archReporte,rangoFechaIni,rangoFechaFin);

    int codigoLibro;
    archReporte<<fixed<<setprecision(2);
    while (true) {
        //9155175	[Diamantes y pedernales]	*Jose Maria Arguedas*	69.02
        leerImprimirLibros_Autor(archLibros,archReporte,codigoLibro);
        if (archLibros.eof()) break;
    }
}

void leerImprimirLibros_Autor(ifstream& archLibros,ofstream&archReporte,int &codigoLibro) {
    //9155175	[Diamantes y pedernales]	*Jose Maria Arguedas*	69.02
    double precioLibro;
    while (true) {
        archLibros>>codigoLibro;
        if (archLibros.eof()) break;
        archReporte<<"LIBRO: ";
        leerImprimirDatosNombres(archLibros,archReporte,60,']',true,true);
        archReporte<<"AUTOR: ";
        leerImprimirDatosNombres(archLibros,archReporte,40,'*',true,false);
        archLibros>>precioLibro;
        archReporte<<"PRECIO S/. "<<setw(10)<<right<<precioLibro;
        archReporte<<endl;
        imprimirLineas('-',140,archReporte);
        while (archLibros.get()!='\n');
    }
}

//CASO LIBROS 9155175	[Diamantes y pedernales]	*Jose Maria Arguedas*	69.02
//CASO CLIENTES 54393647  A   Reyes Tang Edward

void leerImprimirDatosNombres(ifstream& input,ofstream& output,int tamaño,char delimitador,bool primerCar,bool mayus) {
    char c;
    int cantEspaciosBlanco=0;
    input>>ws;

    if (primerCar) {
        input.get();
    }
    while (true) {
        c=input.get();
        if (c==delimitador) break;
        if (mayus) {
            if (c>='a' and c<='z') c-='a'-'A';
        }
        output<<c;
        cantEspaciosBlanco++;
    }
    output<<setw(tamaño-cantEspaciosBlanco)<<" ";
}

void imprimirTitulo(ofstream& output,int rangoFechaIni,int rangoFechaFin) {
    imprimirLineas('=',140,output);
    output<<setw(60)<<" "<<"REPORTE DE VENTAS POR LIBROS"<<endl;
    output<<setw(55)<<" "<<"DESDE: "; imprimirNum_DDMMYYYY(output,rangoFechaIni);
    output<<setw(5)<<" "<<"HASTA: "; imprimirNum_DDMMYYYY(output,rangoFechaFin); output<<endl;
    imprimirLineas('=',140,output);
}

void imprimirLineas(char c,int cant,ofstream& output) {
    for (int i=0;i<cant;i++) output << c;
    output << endl;
}

void imprimirNum_DDMMYYYY(ofstream& output,int num) {
    int dd,mm,yyyy;
    yyyy=num/10000;
    num=num%10000;
    mm=num/100;
    num=num%100;
    dd=num;
    output.fill('0');
    output<<setw(2)<<right<<dd<<"/"<<setw(2)<<right<<mm<<"/"<<setw(4)<<yyyy;
    output.fill(' ');
}


int convertirDDMMYYYY_Num(int dd,int mm,int yyyy) {
    return yyyy*10000+mm*100+dd;
}
