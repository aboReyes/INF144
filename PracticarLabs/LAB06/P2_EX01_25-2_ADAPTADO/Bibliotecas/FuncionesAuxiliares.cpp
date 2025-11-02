//
// Created by ASUS on 26/10/2025.
//

#include "FuncionesAuxiliares.h"


void aperturaArchivosLectura(const char* nombArch,ifstream& arch) {
    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"ERROR, el archivo "<<nombArch<<" no se puede abrir "<<endl;
        exit(1);
    }
}

void aperturaArchivosEscritura(const char* nombArch,ofstream& arch) {
    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout<<"ERROR, el archivo "<<nombArch<<" no se puede abrir "<<endl;
        exit(1);
    }
}

void cargarStreams(const char*nombArchStreams,
        int *arrCodeStream,int *arrDurStream,int *arrCodeIdioma,
        char *arrCodeCharCatIdioma,int *arrCodeIntCatIdioma,int &cantStreams) {
    //803100    1:22:25    4003    C1072
    ifstream archStreams;
    int codeStream,durStream,codeIdioma,codeIntCatIdioma;
    char codeCharCatIdioma;
    aperturaArchivosLectura(nombArchStreams,archStreams);
    while (true) {
        archStreams>>codeStream;
        if (archStreams.eof()) break;
        durStream=leerTiempo(archStreams);
        archStreams>>codeIdioma;
        archStreams>>codeCharCatIdioma>>codeIntCatIdioma;
        insertarOrdenado(codeStream,durStream,codeIdioma,
            codeCharCatIdioma,codeIntCatIdioma,
            arrCodeStream,arrDurStream,arrCodeIdioma,
            arrCodeCharCatIdioma,arrCodeIntCatIdioma,cantStreams);
    }
}

void insertarOrdenado(int codeStream,int durStream,int codeIdioma,
            char codeCharCatIdioma,int codeIntCatIdioma,
            int *arrCodeStream,int *arrDurStream,int *arrCodeIdioma,
            char *arrCodeCharCatIdioma,int *arrCodeIntCatIdioma,int &cantStreams){
    int i=cantStreams-1;
    while (i>=0 and codeStream<arrCodeStream[i]) {
        arrCodeStream[i+1]=arrCodeStream[i];
        arrDurStream[i+1]=arrDurStream[i];
        arrCodeIdioma[i+1]=arrCodeIdioma[i];
        arrCodeCharCatIdioma[i+1]=arrCodeCharCatIdioma[i];
        arrCodeIntCatIdioma[i+1]=arrCodeIntCatIdioma[i];
        i--;
    }
    arrCodeStream[i+1]=codeStream;
    arrDurStream[i+1]=durStream;
    arrCodeIdioma[i+1]=codeIdioma;
    arrCodeCharCatIdioma[i+1]=codeCharCatIdioma;
    arrCodeIntCatIdioma[i+1]=codeIntCatIdioma;
    cantStreams++;
}

void pruebaStreams(const char* nombArchRep,
            int *arrCodeStream,int *arrDurStream,int *arrCodeIdioma,
            char *arrCodeCharCatIdioma,int *arrCodeIntCatIdioma,int cantStreams){
    //803100    1:22:25    4003    C1072
    ofstream output;
    aperturaArchivosEscritura(nombArchRep,output);
    imprimirSubtituloReportePrueba(output);
    for (int i=0;i<cantStreams;i++) {
        output<<setw(10)<<right<<arrCodeStream[i];
        output<<setw(10)<<" "; imprimirTiempo(output,arrDurStream[i]);
        output<<setw(20)<<right<<arrCodeIdioma[i];
        output<<setw(15)<<right<<arrCodeCharCatIdioma[i]<<arrCodeIntCatIdioma[i]<<endl;
    }
}

void procesarCanales(const char* nombArch,
        int *arrCodeStream,int *arrDurStream,int cantStreams,
        int *arrFechaAntiguaCanal,int *arrFechaRecienteCanal,
        double *arrPromDropCanal,double *arrPromRatingCanal,
        int *arrCantReproCanal,int *arrTiempoTotalReproCanal) {
    //1/10/2022    A1911    AdmiralBulldog
    //738184    1/9/2025    15:13:35    3.38    0.628
    //929142    18/8/2025    5:22:57    3.78    0.320
    ifstream input;
    int fechaCreCanal,codeIntCanal,codeStream,fechaReproCanal,durStreamCanal,posStream;
    double rating,drop;
    char codeCharCanal;
    aperturaArchivosLectura(nombArch,input);
    while (true) {
        fechaCreCanal=leerFecha(input);
        if (input.eof()) break;
        input>>codeCharCanal>>codeIntCanal;
        ignorar(input,' ');
        while (true) {
            input>>codeStream;
            fechaReproCanal=leerFecha(input);
            durStreamCanal=leerTiempo(input);
            input>>rating>>drop;
            posStream=busquedaBinaria(codeStream,arrCodeStream,cantStreams);
            if (posStream!=NO_ENCONTRADO) {
                if (arrCantReproCanal[posStream]==0 or
                    fechaReproCanal<arrFechaAntiguaCanal[posStream]){
                    arrFechaAntiguaCanal[posStream]=fechaReproCanal;
                }
                if (arrCantReproCanal[posStream]==0 or
                    fechaReproCanal>arrFechaRecienteCanal[posStream]) {
                    arrFechaRecienteCanal[posStream]=fechaReproCanal;
                }
                arrPromDropCanal[posStream]+=drop;
                arrPromRatingCanal[posStream]+=rating;
                arrCantReproCanal[posStream]++;
            }
            if (input.get()=='\n') break;
        }
    }
    for (int i=0;i<cantStreams;i++) {
        if (arrCantReproCanal[i]>0) {
            arrPromRatingCanal[i]+=arrPromRatingCanal[i]/arrCantReproCanal[i];
            arrPromDropCanal[i]+=arrPromDropCanal[i]/arrCantReproCanal[i];
            arrTiempoTotalReproCanal[i]+=arrDurStream[i]/arrCantReproCanal[i];
        }
    }
}

int busquedaBinaria(int codeStream,int *arrCodeStream,int cantStreams) {
    int limiteInferior=0;
    int limiteSuperior=cantStreams-1;
    int puntoMedio;
    while (true) {
        if (limiteInferior>limiteSuperior) return NO_ENCONTRADO;
        puntoMedio=(limiteInferior+limiteSuperior)/2;
        if (codeStream==arrCodeStream[puntoMedio]) return puntoMedio;
        if (codeStream>arrCodeStream[puntoMedio]) {
            limiteInferior=puntoMedio+1;
        }else {
            limiteSuperior=puntoMedio-1;
        }
    }
}

void imprimirReporte(const char *nombArchRep,
        int *arrCodeStream,int *arrDurStream,int *arrCodeIdioma,
        char *arrCodeCharCatIdioma,int *arrCodeIntCatIdioma,int cantStreams,
        int *arrFechaAntiguaCanal,int *arrFechaRecienteCanal,
        double *arrPromDropCanal,double *arrPromRatingCanal,
        int *arrCantReproCanal,int *arrTiempoTotalReproCanal,
        bool ordenado) {
    ofstream output;
    int mayorCode,mayorDur=0,menorCode,menorDur=999999;
    aperturaArchivosEscritura(nombArchRep,output);
    imprimirLineas('=',170,output);
    output<<setw(65)<<" "<<"PLATAFORMA DE STREAMING TP"<<endl;
    if (ordenado) {
        output<<setw(55)<<" "<<"DETALLE COMPLETO DE REPRODUCCIONES DE STREAMS";
        output<<" ORDENADO POR IDIOMA Y TASA DROP-OFF."<<endl;
    }else {
        output<<setw(55)<<" "<<"DETALLE COMPLETO DE REPRODUCCIONES DE STREAMS"<<endl;
    }
    imprimirLineas('=',170,output);
    imprimirSubtituloReporteFinal(output);
    output<<fixed<<setprecision(2);
    for (int i=0;i<cantStreams;i++) {
        output<<setw(10)<<right<<arrCodeStream[i];
        output<<setw(13)<<right<<arrCodeIdioma[i];
        output<<setw(10)<<right<<arrCodeCharCatIdioma[i]<<arrCodeIntCatIdioma[i];
        if (arrCantReproCanal[i]==0) {
            imprimirGuiones(output);
        }else {
            output<<setw(11)<<" ";imprimirFecha(output,arrFechaAntiguaCanal[i]);
            output<<setw(11)<<" ";imprimirFecha(output,arrFechaRecienteCanal[i]);
            output<<setw(17)<<right<<arrPromRatingCanal[i];
            output<<setw(20)<<right<<arrPromDropCanal[i];
        }
        output<<setw(17)<<" ";imprimirTiempo(output,arrDurStream[i]);
        output<<setw(11)<<right<<arrCantReproCanal[i];
        output<<setw(9)<<" ";imprimirTiempo(output,arrTiempoTotalReproCanal[i]);
        output<<endl;
        if (mayorDur<arrDurStream[i]) {
            mayorDur=arrDurStream[i];
            mayorCode=arrCodeStream[i];
        }
        if (menorDur>arrDurStream[i]) {
            menorDur=arrDurStream[i];
            menorCode=arrCodeStream[i];
        }
    }
    if (not ordenado){
        imprimirResumen(output,mayorDur,mayorCode,menorDur,menorCode);
    }
}

void ordenarReporte(int *arrCodeStream,int *arrDurStream,int *arrCodeIdioma,
        char *arrCodeCharCatIdioma,int *arrCodeIntCatIdioma,int cantStreams,
        int *arrFechaAntiguaCanal,int *arrFechaRecienteCanal,
        double *arrPromDropCanal,double *arrPromRatingCanal,
        int *arrCantReproCanal,int *arrTiempoTotalReproCanal) {
    for (int i=0;i<cantStreams-1;i++) {
        for (int j=i+1;j<cantStreams;j++) {
            if (arrCodeIdioma[i]<arrCodeIdioma[j] or
                arrCodeIdioma[i]==arrCodeIdioma[j] and
                arrPromDropCanal[i]>arrPromDropCanal[j]) {
                swapInt(arrCodeStream[i],arrCodeStream[j]);
                swapInt(arrDurStream[i],arrDurStream[j]);
                swapInt(arrCodeIdioma[i],arrCodeIdioma[j]);
                swapChar(arrCodeCharCatIdioma[i],arrCodeCharCatIdioma[j]);
                swapInt(arrCodeIntCatIdioma[i],arrCodeIntCatIdioma[j]);
                swapInt(arrFechaAntiguaCanal[i],arrFechaAntiguaCanal[j]);
                swapInt(arrFechaRecienteCanal[i],arrFechaRecienteCanal[j]);
                swapDouble(arrPromRatingCanal[i],arrPromRatingCanal[j]);
                swapDouble(arrPromDropCanal[i],arrPromDropCanal[j]);
                swapInt(arrCantReproCanal[i],arrCantReproCanal[j]);
                swapInt(arrTiempoTotalReproCanal[i],arrTiempoTotalReproCanal[j]);
            }
        }
    }
}

//si categoria de idioma ascendente y tasa drop descendente
void ordenarReporte(int *arrCodeStream,int *arrDurStream,int *arrCodeIdioma,
        char *arrCodeCharCatIdioma,int *arrCodeIntCatIdioma,int cantStreams,
        int *arrFechaAntiguaCanal,int *arrFechaRecienteCanal,
        double *arrPromDropCanal,double *arrPromRatingCanal,
        int *arrCantReproCanal,int *arrTiempoTotalReproCanal) {
    for (int i=0;i<cantStreams-1;i++) {
        for (int j=i+1;j<cantStreams;j++) {
            if (arrCodeCharCatIdioma[i]>arrCodeCharCatIdioma[j] or
                arrCodeCharCatIdioma[i]==arrCodeCharCatIdioma[j] and
                arrCodeIntCatIdioma[i]>arrCodeIntCatIdioma[j] or
                arrCodeIntCatIdioma[i]==arrCodeIntCatIdioma[j] and
                arrPromDropCanal[i]<arrPromDropCanal[j]) {
                swapInt(arrCodeStream[i],arrCodeStream[j]);
                swapInt(arrDurStream[i],arrDurStream[j]);
                swapInt(arrCodeIdioma[i],arrCodeIdioma[j]);
                swapChar(arrCodeCharCatIdioma[i],arrCodeCharCatIdioma[j]);
                swapInt(arrCodeIntCatIdioma[i],arrCodeIntCatIdioma[j]);
                swapInt(arrFechaAntiguaCanal[i],arrFechaAntiguaCanal[j]);
                swapInt(arrFechaRecienteCanal[i],arrFechaRecienteCanal[j]);
                swapDouble(arrPromRatingCanal[i],arrPromRatingCanal[j]);
                swapDouble(arrPromDropCanal[i],arrPromDropCanal[j]);
                swapInt(arrCantReproCanal[i],arrCantReproCanal[j]);
                swapInt(arrTiempoTotalReproCanal[i],arrTiempoTotalReproCanal[j]);
            }
        }
    }
}

void eliminar(int *arrCodeStream,int *arrDurStream,int *arrCodeIdioma,
        char *arrCodeCharCatIdioma,int *arrCodeIntCatIdioma,int cantStreams,
        int *arrFechaAntiguaCanal,int *arrFechaRecienteCanal,
        double *arrPromDropCanal,double *arrPromRatingCanal,
        int *arrCantReproCanal,int *arrTiempoTotalReproCanal) {
    for (int i=0;i<cantStreams-1;) {
        if (arrCantReproCanal[i]==0) {
            for (int j=i+1;j<cantStreams;j++) {
                arrCodeStream[j-1]=arrCodeStream[j];
                arrDurStream[j-1]=arrDurStream[j];
                arrCodeIdioma[j-1]=arrCodeIdioma[j];
                arrCodeCharCatIdioma[j-1]=arrCodeCharCatIdioma[j];
                arrCodeIntCatIdioma[j-1]=arrCodeIntCatIdioma[j];
                arrFechaAntiguaCanal[j-1]=arrFechaAntiguaCanal[j];
                arrFechaRecienteCanal[j-1]=arrFechaRecienteCanal[j];
                arrPromDropCanal[j-1]=arrPromDropCanal[j];
                arrPromRatingCanal[j-1]=arrPromRatingCanal[j];
                arrCantReproCanal[j-1]=arrCantReproCanal[j];
                arrTiempoTotalReproCanal[j-1]=arrTiempoTotalReproCanal[j];
            }
        }else {
            i++;
        }
    }
}

void swapInt(int &a,int&b) {
    int temp=a;
    a=b;
    b=temp;
}

void swapChar(char &a,char&b) {
    char temp=a;
    a=b;
    b=temp;
}
void swapDouble(double &a,double&b) {
    double temp=a;
    a=b;
    b=temp;
}
void imprimirResumen(ofstream&output,
    int mayorDur,int mayorCode,int menorDur,int menorCode) {
    imprimirLineas('-',170,output);
    output<<"RESUMEN:"<<endl;
    output<<"STREAM CON MAYOR DURACION: "<<setw(15)<<right<<mayorCode<<" - ";
    imprimirTiempo(output,mayorDur); output<<" hrs"<<endl;
    output<<"STREAM CON MENOR DURACION: "<<setw(15)<<right<<menorCode<<" - ";;
    imprimirTiempo(output,menorDur); output<<" hrs"<<endl;
    imprimirLineas('=',170,output);
}

void imprimirGuiones(ofstream& output) {
    output<<setw(21)<<right<<"----------";
    output<<setw(21)<<right<<"----------";
    output<<setw(17)<<right<<"-----";
    output<<setw(20)<<right<<"-----";
}

void imprimirSubtituloReporteFinal(ofstream& output) {
    output<<setw(10)<<right<<"STREAM";
    output<<setw(15)<<right<<"IDIOMA";
    output<<setw(15)<<right<<"CATEGORIA";
    output<<setw(20)<<right<<"REP.ANTIGUA";
    output<<setw(20)<<right<<"REP.RECIENTE";
    output<<setw(20)<<right<<"PROM.RAT.CAL";
    output<<setw(25)<<right<<"PROM.TASA.DROP-OFF";
    output<<setw(15)<<right<<"DURAC.";
    output<<setw(15)<<right<<"#REPR.";
    output<<setw(15)<<right<<"TOT.REPR."<<endl;
    imprimirLineas('-',170,output);
}

void imprimirSubtituloReportePrueba(ofstream& output) {
    output<<setw(25)<<" "<<"REPORTE DE PRUEBA STREAMS"<<endl;
    imprimirLineas('=',80,output);
    output<<setw(10)<<right<<"CODIGO STREAM";
    output<<setw(20)<<right<<"DURACION STREAM";
    output<<setw(20)<<right<<"CODIGO IDIOMA";
    output<<setw(20)<<right<<"CATEGORIA IDIOMA"<<endl;
    imprimirLineas('-',80,output);
}

void imprimirLineas(char c,int cant,ofstream&output) {
    for (int i=0;i<cant;i++) output << c;
    output << endl;
}

void ignorar(ifstream& input,char delimitador) {
    char c;
    input>>ws;
    while (true) {
        c=input.get();
        if (c==delimitador) break;
    }
}

int leerFecha(ifstream& input) {
    int dd,mm,yyyy;
    char c;
    input >> dd>>c>>mm>>c>>yyyy;
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

int leerTiempo(ifstream&input) {
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
    output<<setw(2)<<right<<hh<<":";
    output<<setw(2)<<right<<mm<<":";
    output<<setw(2)<<right<<ss;
    output.fill(' ');
}


