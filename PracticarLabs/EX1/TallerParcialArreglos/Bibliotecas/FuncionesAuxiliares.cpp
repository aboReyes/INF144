//
// Created by ASUS on 11/10/2025.
//

#include "FuncionesAuxiliares.h"


void aperturaArchivoLectura(const char* nombArch,ifstream& arch) {
    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"ERROR: el archivo "<<nombArch<<" no se puede abrir"<<endl;
    }
}

void aperturaArchivoEscritura(const char* nombArch,ofstream& arch) {
    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout<<"ERROR: el archivo "<<nombArch<<" no se puede abrir"<<endl;
    }
}

void leerLibros(const char* nombArchLibros,int *arrCodeLibro,
                double *arrPrecioLibro,int &cantLibros) {
    //9155175	[Diamantes y pedernales]	*Jose Maria Arguedas*	69.02
    ifstream archLibros;
    aperturaArchivoLectura(nombArchLibros,archLibros);
    int codeLibro;
    double precioLibro;
    while (true) {
        archLibros>>codeLibro;
        if (archLibros.eof()) break;
        ignorar(archLibros,']',true);
        ignorar(archLibros,'*',true);
        archLibros>>precioLibro;
        insertarOrdenado(codeLibro,precioLibro,arrCodeLibro,arrPrecioLibro,cantLibros);
    }
    //cout<<"hay "<<cantLibros<<endl;
}

void insertarOrdenado(int codeLibro,double precioLibro,int* arrCodeLibro,
                        double *arrPrecioLibro,int &cantLibros) {
    int i=cantLibros-1;
    //comienza a ordenar
    while (i>=0 and arrPrecioLibro[i]>precioLibro) {
        arrCodeLibro[i+1]=arrCodeLibro[i];
        arrPrecioLibro[i+1]=arrPrecioLibro[i];
        i--;
    }
    //cuando empieza no entran al while y los registra con lo leimos
    arrCodeLibro[i+1]=codeLibro;
    arrPrecioLibro[i+1]=precioLibro;
    cantLibros++;
}

//otro método de ordenamiento pero en este caso, es por separado. En mi caso, utilizé el leerInsertarOrdenado
void ordenarLibros(int *arrCodeLibro,
                double *arrPrecioLibro,int cantLibros) {
    for(int i=0;i<cantLibros-1;i++) {
        for(int j=i+1;j<cantLibros;j++) {
            if (arrPrecioLibro[i]>arrPrecioLibro[j]) {
                swapInt(arrCodeLibro[i],arrCodeLibro[j]);
                swapDouble(arrPrecioLibro[i],arrPrecioLibro[j]);
            }
        }
    }
}

void repPruebaLibros(const char* nombArchRepLibros,int *arrCodeLibro,
                    double *arrPrecioLibro,int cantLibros) {
    ofstream archRepLibros;
    aperturaArchivoEscritura(nombArchRepLibros,archRepLibros);
    imprimirCabeceraRepLibros(archRepLibros);
    archRepLibros<<fixed<<setprecision(2);
    for (int i=0;i<cantLibros;i++) {
        archRepLibros<<setw(15)<<right<<arrCodeLibro[i];
        archRepLibros<<setw(15)<<right<<arrPrecioLibro[i]<<endl;
    }
}

void leerProcesarVentas(const char* nombArchVentas,
                        int *arrCodeLibro,double *arrPrecioLibro,
                        int *arrUnidadesVentas,double *arrPromCalVentas,
                        double *arrTotalVentas,int* arrPrimeraFechaVentas,
                        int *arrPrimerDniVentas,int *arrUltimaFechaVentas,
                        int *arrUltimoDniVentas,int cantLibros) {
    //99377    29/04/2024    --> repite:    6398790    92240876    18    ...
    ifstream archVentas;
    aperturaArchivoLectura(nombArchVentas,archVentas);
    int fechaVenta,codeLibreria,codeLibroArch,dniArch,calificacionArch,posLibro;
    while (true) {
        archVentas>>codeLibreria;
        if (archVentas.eof()) break;
        fechaVenta=leerFecha(archVentas);
        while (true) {
            archVentas>>codeLibroArch>>dniArch>>calificacionArch;
            posLibro=buscarLibro(arrCodeLibro,codeLibroArch,cantLibros);
            if (posLibro!=-1) {
                arrUnidadesVentas[posLibro]++;
                arrPromCalVentas[posLibro]+=calificacionArch;
                arrTotalVentas[posLibro]+=arrPrecioLibro[posLibro];
                if (arrPrimeraFechaVentas[posLibro]==0 or
                    fechaVenta<arrPrimeraFechaVentas[posLibro]) {
                    arrPrimeraFechaVentas[posLibro]=fechaVenta;
                    arrPrimerDniVentas[posLibro]=dniArch;
                    }
                if (arrUltimaFechaVentas[posLibro]==0 or
                    fechaVenta>arrUltimaFechaVentas[posLibro]) {
                    arrUltimaFechaVentas[posLibro]=fechaVenta;
                    arrUltimoDniVentas[posLibro]=dniArch;
                    }
            }
            if (archVentas.get()=='\n') break;
        }
    }
    //Cálculo del promedio de calificacion
    for (int i=0;i<cantLibros;i++) {
        if (arrUnidadesVentas[i]>0) {
            arrPromCalVentas[i]/=arrUnidadesVentas[i];
        }
    }
}

void imprimirReporte(const char* nombArchRep,int *arrCodeLibro,double *arrPrecioLibro,
                    int *arrUnidadesVentas,double* arrPromCalVentas,double *arrTotalVentas,
                    int *arrPrimeraFechaVentas,int *arrPrimerDniVentas,int *arrUltimaFechaVentas,
                    int *arrUltimoDniVentas,int cantLibros) {
    ofstream archRep;
    int totalGlobalUnidades=0;
    double totalGlobalVentas=0.0;
    aperturaArchivoEscritura(nombArchRep,archRep);
    imprimirCabeceraReporte(archRep);
    archRep<<fixed<<setprecision(2);
    for (int i=0;i<cantLibros;i++) {
        imprimirOrden(archRep,i+1);
        archRep<<setw(15)<<right<<arrCodeLibro[i];
        archRep<<setw(12)<<right<<arrPrecioLibro[i];
        archRep<<setw(13)<<right<<arrUnidadesVentas[i];
        if (arrPromCalVentas[i]==0) {
            archRep<<setw(21)<<right<<"-";
            archRep<<setw(25)<<right<<arrPromCalVentas[i];
            archRep<<setw(15)<<right<<"-";
            archRep<<setw(7)<<right<<"-";
            archRep<<setw(23)<<right<<"-";
            archRep<<setw(7)<<right<<"-"<<endl;
        }else {
            archRep<<setw(23)<<right<<arrPromCalVentas[i];
            archRep<<setw(23)<<right<<arrTotalVentas[i];
            archRep<<setw(8)<<" "; imprimirFecha(archRep,arrPrimeraFechaVentas[i]);
            archRep<<setw(10)<<right<<arrPrimerDniVentas[i];
            archRep<<setw(8)<<" "; imprimirFecha(archRep,arrUltimaFechaVentas[i]);
            archRep<<setw(10)<<right<<arrUltimoDniVentas[i]<<endl;
        }
        totalGlobalUnidades+=arrUnidadesVentas[i];
        totalGlobalVentas+=arrTotalVentas[i];
    }
    imprimirResumen(archRep,totalGlobalUnidades,totalGlobalVentas);
}

void ordenarReporte(int *arrCodeLibro, double *arrPrecioLibro,
                    int *arrUnidadesVentas, double *arrPromCalVentas, double *arrTotalVentas,
                    int *arrPrimeraFechaVentas, int *arrPrimerDniVentas, int *arrUltimaFechaVentas,
                    int *arrUltimoDniVentas, int cantLibros) {
    //ordenar unidades descendente y promedio ascentende
    //entonces (aUni<bUni and aUni==bUni or cProm>dProm)
    for (int i=0;i<cantLibros-1;i++) {
        for (int j=i+1;j<cantLibros;j++) {
            if (arrUnidadesVentas[i]<arrUnidadesVentas[j] and
                arrUnidadesVentas[i]==arrUnidadesVentas[j] or
                arrPromCalVentas[i]>arrPromCalVentas[j]) {
                swapInt(arrCodeLibro[i],arrCodeLibro[j]);
                swapDouble(arrPrecioLibro[i],arrPrecioLibro[j]);
                swapInt(arrUnidadesVentas[i],arrUnidadesVentas[j]);
                swapDouble(arrPromCalVentas[i],arrPromCalVentas[j]);
                swapDouble(arrTotalVentas[i],arrTotalVentas[j]);
                swapInt(arrPrimeraFechaVentas[i],arrPrimeraFechaVentas[j]);
                swapInt(arrPrimerDniVentas[i],arrPrimerDniVentas[j]);
                swapInt(arrUltimaFechaVentas[i],arrUltimaFechaVentas[j]);
                swapInt(arrUltimoDniVentas[i],arrUltimoDniVentas[j]);
            }
        }
    }
}

void imprimirResumen(ofstream& archRep,int totalGlobalUnidades,double totalGlobalVentas) {
    imprimirLineas('-',150,archRep);
    archRep<<"TOTALES: "<<setw(37)<<right<<totalGlobalUnidades;
    archRep<<setw(45)<<right<<totalGlobalVentas<<endl;
    imprimirLineas('=',150,archRep);
}

void imprimirOrden(ofstream& output,int nroOrden) {
    output.fill('0');
    output<<setw(4)<<right<<nroOrden<<")";
    output.fill(' ');
}

void imprimirCabeceraReporte(ofstream& output) {
    imprimirLineas('=',150,output);
    output<<setw(55)<<" "<<"REPORTE DE VENTAS POR LIBRO"<<endl;
    imprimirLineas('-',150,output);
    output<<" # ";
    output<<setw(15)<<right<<"LIBRO";
    output<<setw(15)<<right<<"PRECIO";
    output<<setw(20)<<right<<"UNIDADES.VENDIDAS";
    output<<setw(20)<<right<<"PROM.CALIFICACION";
    output<<setw(20)<<right<<"TOT.VENTAS";
    output<<setw(22)<<right<<"PRIMERA.VENTA";
    output<<setw(28)<<right<<"ULTIMA.VENTA"<<endl;
    imprimirLineas('-',150,output);
}

int buscarLibro(int* arrCodeLibro,int codeLibroArch,int cantLibros) {
    for (int i=0;i<cantLibros;i++)
        if (arrCodeLibro[i]==codeLibroArch) return i;
    return -1; //indiceNoEncontrado=-1;
}

int leerFecha(ifstream& input) {
    int dd,mm,yyyy;
    char c;
    input>>dd>>c>>mm>>c>>yyyy;
    return yyyy*10000+mm*100+dd;
}

void imprimirFecha(ofstream& output,int fecha) {
    int dd,mm,yyyy;
    yyyy=fecha/10000;
    fecha=fecha%10000;
    mm=fecha/100;
    fecha=fecha%100;
    dd=fecha;
    output.fill('0');
    output<<setw(2)<<right<<dd<<"/";
    output<<setw(2)<<right<<mm<<"/";
    output<<setw(4)<<right<<yyyy;
    output.fill(' ');
}

void imprimirCabeceraRepLibros(ofstream& archRep) {
    archRep<<setw(5)<<" "<<"REPORTE DE PRUEBA PARA ARCHIVO LIBROS"<<endl;
    imprimirLineas('=',50,archRep);
    archRep<<setw(14)<<right<<"CODIGO";
    archRep<<setw(16)<<right<<"PRECIO"<<endl;
    imprimirLineas('-',50,archRep);
}

void imprimirLineas(char c,int cant,ofstream& archRep) {
    for(int i=0;i<cant;i++) archRep<<c;
    archRep<<endl;
}

void swapInt(int &a,int &b) {
    int aux=a;
    a=b;
    b=aux;
}

void swapDouble(double &a,double &b) {
    double aux=a;
    a=b;
    b=aux;
}

void swapChar(char &a,char&b) {
    char aux=a;
    a=b;
    b=aux;
}

void ignorar(ifstream& input,char delimitador,bool esPrimero) {
    char c;
    input>>ws;
    if (esPrimero) input.get(c);
    while (true) {
        c=input.get();
        if (c==delimitador) break;
    }
}
