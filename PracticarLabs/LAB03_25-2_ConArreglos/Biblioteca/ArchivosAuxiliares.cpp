//
// Created by ASUS on 28/09/2025.
//

#include "ArchivosAuxiliares.h"

void aperturaArchivoLectura(const char *nombArch, ifstream &arch) {
    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout << "Error el archivo" << nombArch << " no se pudo abrir"<<endl;
        exit(1);
    }
}

void aperturaArchivoEscritura(const char *nombArch, ofstream &arch) {
    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout << "Error el archivo" << nombArch << " no se pudo abrir"<<endl;
        exit(1);
    }
}

void cargarEtiquetas(const char *nombArchEtiqueta,int *arrCodigoEtiqueta,
                    int *arrDurEtiqueta,int &nroEtiquetas) {
    ifstream archEtiqueta;
    aperturaArchivoLectura(nombArchEtiqueta,archEtiqueta);
    //803100    dropsenabled   01:27
    int horaSeg;
    int etiquetas;
    while (true) {
        archEtiqueta>>etiquetas;
        if (archEtiqueta.eof()) break;
        archEtiqueta>>ws;
        ignorar(archEtiqueta,' ');
        horaSeg=leerHora(archEtiqueta);
        arrDurEtiqueta[nroEtiquetas]=horaSeg;
        arrCodigoEtiqueta[nroEtiquetas]=etiquetas;
        nroEtiquetas++;
    }
}

void imprimirReportePruebaEtiquetas(const char* nombArchReporte,int *arrCodigoEtiqueta,
                    int *arrDurEtiqueta,int nroEtiquetas) {
    ofstream archReporte;
    aperturaArchivoEscritura(nombArchReporte,archReporte);
    archReporte<<setw(5)<<" "<<"REPORTE DE PRUEBA PARA EL ARCHIVO ETIQUETAS"<<endl;
    imprimirLineas('=',50,archReporte);
    imprimirSubtituloReportePruebaEtiqueta(archReporte);
    for (int i=0;i<nroEtiquetas;i++) {
        archReporte<<setw(23)<<left<<arrCodigoEtiqueta[i];
        imprimirHora(archReporte,arrDurEtiqueta[i],true);
        archReporte<<endl;
    }
}

void cargarReproEtiquetas(const char* nombArchReproEtiquetas,int *arrFechaReproEtiquetas,
                        char *arrCodeCharStreamer,int *arrCodeIntStreamer,int *arrCantReproducciones,
                        int *arrCodigoEtiquetaRepro,int &nroReproducciones) {
    ifstream archReproEtiquetas;
    aperturaArchivoLectura(nombArchReproEtiquetas,archReproEtiquetas);
    //28/02/2025  E6696      888106      244
    int fechaRep;
    while (true) {
        fechaRep=leerFecha(archReproEtiquetas);
        if (archReproEtiquetas.eof()) break;
        archReproEtiquetas>>arrCodeCharStreamer[nroReproducciones];
        archReproEtiquetas>>arrCodeIntStreamer[nroReproducciones];
        archReproEtiquetas>>arrCodigoEtiquetaRepro[nroReproducciones];
        archReproEtiquetas>>arrCantReproducciones[nroReproducciones];
        arrFechaReproEtiquetas[nroReproducciones]=fechaRep;
        nroReproducciones++;
    }
}

void imprimirReportePruebaReproEtiquetas(const char* nombArchReportePruebaReproEtiquetas,
                                        int *arrFechaReproEtiquetas,char *arrCodeCharStreamer,
                                        int *arrCodeIntStreamer,int *arrCodigoEtiquetaRepro,int *arrCantReproducciones,
                                        int nroReproducciones) {
    ofstream archReporte;
    aperturaArchivoEscritura(nombArchReportePruebaReproEtiquetas,archReporte);
    archReporte<<setw(5)<<" "<<"REPORTE DE PRUEBA PARA EL ARCHIVO REPRODUCCIONES DE ETIQUETAS"<<endl;
    imprimirLineas('=',60,archReporte);
    imprimirSubtituloReportePruebaReproEtiquetas(archReporte);
    //28/02/2025  E6696      888106      244
    for (int i=0;i<nroReproducciones;i++) {
        imprimirFecha(archReporte,arrFechaReproEtiquetas[i]);
        archReporte<<setw(10)<<" ";
        archReporte<<arrCodeCharStreamer[i];
        archReporte<<arrCodeIntStreamer[i];
        archReporte<<setw(15)<<right<<arrCodigoEtiquetaRepro[i];
        archReporte<<setw(25)<<right<<arrCantReproducciones[i]<<endl;
    }
}

void crearReporte(const char* nombArchCanales,const char* nombArchReporte,
                int *arrCodigoEtiqueta,int *arrDurEtiqueta,int nroEtiquetas,
                int *arrFechaReproEtiquetas,char *arrCodeCharStreamer,int *arrCodeIntStreamer,
                int *arrCantReproducciones,int *arrCodigoEtiquetaRepro,int nroReproducciones,double tarifaDur) {
    ifstream archCanales;
    ofstream archReporte;
    aperturaArchivoLectura(nombArchCanales,archCanales);
    aperturaArchivoEscritura(nombArchReporte,archReporte);
    //19/06/2022    X5514      xQcOW      2.5      632180
    char letraCodCanal;
    int numCodCanal,nroCanal=0,nroDeEtiqueta=0;
    double rating;
    imprimirTitulo(archReporte,tarifaDur);
    while (true) {
        leerDatosCanalImprimirCabecera(archCanales,archReporte,letraCodCanal,numCodCanal,rating,nroCanal);
        if (archCanales.eof())break;
        leerEtiquetasReproducidasCanales(archCanales,letraCodCanal,numCodCanal,rating,nroDeEtiqueta,
                                        arrCodigoEtiqueta,arrDurEtiqueta,nroEtiquetas,
                                            arrFechaReproEtiquetas,arrCodeCharStreamer,arrCodeIntStreamer,
                                            arrCantReproducciones,arrCodigoEtiquetaRepro,nroReproducciones,archReporte);
    }
}

void imprimirTitulo(ofstream &archReporte,double tarifaDur) {
    archReporte<<"PLATAFORMA TP_Twitch"<<endl;
    archReporte<<"TARIFA POR DURACION DE LAS ETIQUETAS: "<<tarifaDur<<" POR CADA MINUTO Y FRACCION"<<endl;
    imprimirLineas('=',130,archReporte);
}

void leerEtiquetasReproducidasCanales(ifstream &archCanales,char letraCodCanal,int numCodCanal,
                                    double rating,int &nroDeEtiqueta,
                                    int *arrCodigoEtiqueta,int *arrDurEtiqueta,int nroEtiquetas,
                                    int *arrFechaReproEtiquetas,char *arrCodeCharStreamer,int *arrCodeIntStreamer,
                                    int *arrCantReproducciones,int *arrCodigoEtiquetaRepro,int nroReproducciones,
                                    ofstream &archReporte) {
    int etiqueta,tiempoGlobal=0;
    int tiempoTotal=0;
    char c;
    double tarifaDur=0.78;
    while (true) {
        archCanales>>etiqueta;
        c=archCanales.get();
        //procesamiento
        double duracion=obtenerDuracion(arrCodigoEtiqueta,arrDurEtiqueta,nroEtiquetas,etiqueta);
        tiempoTotal=imprimirInfo(etiqueta,letraCodCanal,numCodCanal,duracion,
                    arrFechaReproEtiquetas,arrCodeCharStreamer,arrCodeIntStreamer,
                    arrCantReproducciones,arrCodigoEtiquetaRepro,nroReproducciones,archReporte);
        tiempoGlobal+=tiempoTotal;
        if (c=='\n') break;
    }
    imprimirLineas('-',130,archReporte);
    imprimirResumen(archReporte,tiempoGlobal,rating,tarifaDur);
}

void imprimirResumen(ofstream &archReporte,int tiempoTotal,double rating,double tarifaDur) {

    archReporte<<fixed;
    archReporte<<setprecision(2);
    archReporte<<"TIEMPO TOTAL DE REPRODUCCIONES DE ETIQUETAS: "<<setw(10)<<" ";
    imprimirHora(archReporte,tiempoTotal,false); archReporte<<endl;
    double ratingCalculado=filtrarRating(archReporte,rating);
    archReporte<<endl;
    double ingresoRepEtiquetas=tarifaDur*((double)tiempoTotal/60.0);
    archReporte<<"INGRESOS POR REPRODUCCION DE ETIQUETAS: "<<setw(23)<<right<<ingresoRepEtiquetas<<endl;
    imprimirLineas('=',130,archReporte);
}

double filtrarRating(ofstream& archReporte,double rating) {
    archReporte<<"PORCENTAJE POR RATING DE CALIDAD ";
    archReporte<<setw(30)<<right;
    if (rating>=4.0 and rating<=5.0) {
        archReporte<<"+30%";
        return 0.3;
    }else if (rating>=3.0 and rating<4.0) {
        archReporte<<"+20%";
        return 0.2;
    }else if (rating>=2.0 and rating<3.0) {
        archReporte<<"+0%";
        return 0.0;
    }else if (rating>=1.0 and rating<2.0) {
        archReporte<<"-25%";
        return 0.25;
    }else return 0.0;
}

int imprimirInfo(int etiqueta,char letraCodCanal,int numCodCanal,double duracion,
                int *arrFechaReproEtiquetas,char *arrCodeCharStreamer,int *arrCodeIntStreamer,
                int *arrCantReproducciones,int *arrCodigoEtiquetaRepro,int nroReproducciones,
                ofstream &archReporte) {
    int tiempoTotal=0;
    for (int i=0;i<nroReproducciones;i++) {
        if (arrCodeCharStreamer[i]==letraCodCanal and arrCodeIntStreamer[i]==numCodCanal and arrCodigoEtiquetaRepro[i]==etiqueta) {
            int fecha=arrFechaReproEtiquetas[i];
            int nroRepro=arrCantReproducciones[i];
            int tiempoDuracion=duracion*arrCantReproducciones[i];
            imprimirFecha(archReporte,fecha);
            archReporte<<setw(10)<<right<<arrCodigoEtiquetaRepro[i];
            archReporte<<setw(10)<<" "; imprimirHora(archReporte,duracion,true);
            archReporte<<setw(10)<<right<<nroRepro;
            archReporte<<setw(10)<<" "; imprimirHora(archReporte,tiempoDuracion,false);
            tiempoTotal+=tiempoDuracion;
            archReporte<<endl;
            break;
        }
    }
    return tiempoTotal;
}

double obtenerDuracion(int *arrCodigoEtiqueta,int *arrDurEtiqueta,int nroEtiquetas,int etiqueta) {
    for (int i=0;i<nroEtiquetas;i++)
        if (arrCodigoEtiqueta[i]==etiqueta)
            return arrDurEtiqueta[i];
    return 0;
}

void leerDatosCanalImprimirCabecera(ifstream& archCanales,ofstream &archReporte,
                                    char &letraCodCanal,int &numCodCanal,
                                    double &rating,int &nroCanal) {
    int fechaCreacion=leerFecha(archCanales);
    if (archCanales.eof()) return;
    nroCanal++;
    archReporte<<"CANAL No. "<<nroCanal<<endl;
    imprimirSubtituloDatosStreamers(archReporte);
    archCanales>>ws>>letraCodCanal>>numCodCanal;
    archReporte<<setw(5)<<" "; leerNombreStreamer(archCanales,archReporte);
    archCanales>>rating;
    archReporte<<letraCodCanal<<setw(10)<<left<<numCodCanal;
    imprimirFecha(archReporte,fechaCreacion);
    archReporte<<setw(18)<<right<<rating<<endl;
    imprimirLineas('-',130,archReporte);
    //while (archCanales.get()!='\n');
}

void leerNombreStreamer(ifstream &archCanales,ofstream &archReporte) {
    int cantEspaciosBlanco=0;
    char c;
    archCanales>>ws;
    while (true) {
        c=archCanales.get();
        if (c==' ') break;
        if (c>='a' and c<='z') c-='a'-'A';
        archReporte<<c;
        cantEspaciosBlanco++;
    }
    archReporte<<setw(20-cantEspaciosBlanco)<<" ";
}


void imprimirSubtituloDatosStreamers(ofstream &archReporte) {
    archReporte<<setw(5)<<" "<<"NOMBRE"<<setw(14)<<" "<<"CODIGO"<<setw(5)<<" "<<"CREADO EL"<<
        setw(10)<<" "<<"RATING DE CALIDAD"<<endl;
}

void imprimirSubtituloReportePruebaReproEtiquetas(ofstream& archReporte) {
    archReporte<<"FECHA"<<setw(15)<<" "<<"CODIGO"<<setw(8)<<" "<<"ETIQUETA"<<
        setw(10)<<" "<<"CANTIDAD REPRODUCCIONES"<<endl;
}

void imprimirSubtituloReportePruebaEtiqueta(ofstream & archReporte) {
    archReporte<<"ETIQUETA"<<setw(15)<<" "<<"DURACION"<<endl;
}

void ignorar(ifstream& arch,char delimitador) {
    char c;
    arch>>ws;
    while (true) {
        c=arch.get();
        if (c==delimitador) break;
    }
}
int leerFecha(ifstream& arch) {
    //19/06/2022
    int dia,mes,año,fecha;
    char c;
    arch>>dia>>c>>mes>>c>>año;
    fecha=año*10000+mes*100+dia;
    return fecha;
}

void imprimirFecha(ofstream& arch,int fecha) {
    int dia,mes,año;
    año=fecha/10000;
    fecha=fecha%10000;
    mes=fecha/100;
    fecha=fecha%100;
    dia=fecha;
    arch.fill('0');
    arch<<setw(2)<<right<<dia<<"/"<<setw(2)<<right<<mes<<"/"<<año;
    arch.fill(' ');
}

int leerHora(ifstream& arch) {
    int mm,ss,horaSeg;
    char c;
    arch>>mm>>c>>ss;
    horaSeg=mm*60+ss;
    return horaSeg;
}

void imprimirHora(ofstream& arch,int horaSeg,bool esMinuto) {
    int hh,mm,ss;
    hh=horaSeg/3600;
    horaSeg=horaSeg%3600;
    mm=horaSeg/60;
    horaSeg=horaSeg%60;
    ss=horaSeg;
    arch.fill('0');
    if (esMinuto) {
        arch<<setw(2)<<right<<mm<<":"<<setw(2)<<right<<ss;
    }else {
        arch<<setw(2)<<right<<hh<<":"<<setw(2)<<right<<mm<<":"<<setw(2)<<right<<ss;
    }
    arch.fill(' ');
}

void imprimirLineas(char c,int cant,ofstream &archReporte) {
    for (int i=0;i<cant;i++) archReporte<<c;
    archReporte<<endl;
}
