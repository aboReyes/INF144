//
// Created by aml on 20/10/2025.
//

#include "FuncionesAuxiliares.h"

void aperturaArchivoLectura(const char* nombArch,ifstream& arch) {
    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"ERROR, el archivo "<<nombArch<<" no se puede abrir"<<endl;
        exit(1);
    }
}

void aperturaArchivoEscritura(const char* nombArch,ofstream& arch) {
    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout<<"ERROR, el archivo "<<nombArch<<" no se puede abrir"<<endl;
        exit(1);
    }
}

void cargarStreams(const char* nombArchStreams,
                int *arrCodeStream,int *arrDurStream,
                int *arrCodeIdiomaStream,char* arrCharCatIdiomaStream,
                int *arrIntCatIdiomaStream,
                int &cantStreams) {
    //803100    1:22:25    4003    C1072
    ifstream archStreams;
    aperturaArchivoLectura(nombArchStreams,archStreams);
    int codeStream,durStream;
    while (true) {
        archStreams>>codeStream;
        if (archStreams.eof()) break;
        durStream=leerTiempo(archStreams);
        archStreams>>arrCodeIdiomaStream[cantStreams];
        archStreams>>arrCharCatIdiomaStream[cantStreams];
        archStreams>>arrIntCatIdiomaStream[cantStreams];
        arrDurStream[cantStreams]=durStream;
        arrCodeStream[cantStreams]=codeStream;
        cantStreams++;
    }
    //cout<<"HAY "<<cantStreams;
}

void procesarCanales(const char* nombArchCanales,int *arrCodeStream,
                    int *arrFechaCanal,char *arrCodeCharCanal,int *arrCodeIntCanal,
                    int *arrFechaAntiguaCanal,int *arrFechaRecienteCanal,
                    double *arrRatingPromCanal,double *arrTasaDropPromCanal,
                    int *arrDurStreamCanal,int cantStreams,
                    int *arrCantRepro) {
    //Canales.txt
    //1/10/2022    A1911    AdmiralBulldog
    //a partir de aquí, se repite
    //738184    1/9/2025    15:13:35    3.38    0.628
    //929142    18/8/2025    5:22:57    3.78    0.320

    ifstream archCanales;
    aperturaArchivoLectura(nombArchCanales,archCanales);
    int creCanal,codeIntCanal,codeStream,posStream,fechaCanal,durStreamCanal;
    arrCantRepro=0;
    double rating,drop;
    char codeCharCanal;
    while (true) {
        creCanal=leerFecha(archCanales);
        if (archCanales.eof()) break;
        archCanales>>codeCharCanal>>codeIntCanal;
        ignorar(archCanales,' ');
        while (true) {
            archCanales>>codeStream;
            fechaCanal=leerFecha(archCanales);
            durStreamCanal=leerTiempo(archCanales);
            archCanales>>rating>>drop;
            posStream=buscarStream(arrCodeStream,codeStream,cantStreams);
            if (posStream!=NO_ENCONTRADO) {
                arrRatingPromCanal[cantStreams]+=rating;
                arrTasaDropPromCanal[cantStreams]+=drop;
                arrCantRepro[posStream]++;
                if (arrFechaAntiguaCanal[posStream]==0 or
                    fechaCanal<arrFechaAntiguaCanal[posStream]) {
                    arrFechaAntiguaCanal[posStream]=fechaCanal;
                }
                if (arrFechaRecienteCanal[posStream]==0 or
                    fechaCanal>arrFechaRecienteCanal[posStream]) {
                    arrFechaRecienteCanal[posStream]=fechaCanal;
                }
            }
            if (archCanales.get()=='\n') break;
        }
    }
}

void reporteStreams(const char *nombArchReporte,
                    int *arrCodeStream,int *arrFechaCanal,
                    char *arrCodeCharCanal,int *arrCodeIntCanal,
                    int *arrFechaAntiguaCanal,int *arrFechaRecienteCanal,
                    double *arrRatingPromCanal,double *arrTasaDropPromCanal,
                    int *arrDurStreamCanal,int cantStreams){
    ofstream archReporte;
    aperturaArchivoEscritura(nombArchReporte,archReporte);
    for (int i=0;i<cantStreams;i++) {

    }
}


int buscarStream(int *arrCodeStream,int codeStream,int cantStreams) {
    for (int i=0;i<cantStreams;i++)
        if (arrCodeStream[i]==codeStream) return i;
    return NO_ENCONTRADO;
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
    output<<dd<<'/'<<mm<<'/'<<yyyy;
    output.fill(' ');
}

int leerTiempo(ifstream& input) {
    int hh,mm,ss;
    char c;
    input>>hh>>c>>mm>>c>>ss;
    return hh*3600+mm*60+ss;
}

void imprimirTiempo(ofstream& output,int tiempo) {
    int hh,mm,ss;
    hh=tiempo/3600;
    tiempo=tiempo%3600;
    mm=tiempo/60;
    tiempo=tiempo%60;
    ss=tiempo;
    output.fill('0');
    output<<hh<<":"<<mm<<":"<<ss;
    output.fill(' ');
}

void ignorar(ifstream &arch,char delimitador) {
    char c;
    arch>>ws;
    while (true) {
       c=arch.get();
        if (c==delimitador) break;
    }
}
