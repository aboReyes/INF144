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

void pruebaStreams(const char* nombArchRep,
                    int *arrCodeStream,int *arrDurStream,
                    int *arrCodeIdiomaStream,char* arrCharCatIdiomaStream,
                    int *arrIntCatIdiomaStream,
                    int cantStreams) {
    //803100    1:22:25    4003    C1072
    ofstream output;
    aperturaArchivoEscritura(nombArchRep,output);
    imprimirSubtituloPruebaStreams(output);
    for (int i=0;i<cantStreams;i++) {
        output<<setw(10)<<right<<arrCodeStream[i];
        output<<setw(10)<<" ";imprimirTiempo(output,arrDurStream[i]);
        output<<setw(20)<<right<<arrCodeIdiomaStream[i];
        output<<setw(15)<<right<<arrCharCatIdiomaStream[i]<<arrIntCatIdiomaStream[i]<<endl;
    }
}

void procesarCanales(const char* nombArchCanales,int *arrCodeStream,int *arrDurStream,
                    char *arrCodeCharCanal,int *arrCodeIntCanal,
                    int *arrFechaAntiguaCanal,int *arrFechaRecienteCanal,
                    double *arrRatingPromCanal,double *arrTasaDropPromCanal,
                    int *arrCantReproducciones,int *arrDurTotalReproduccionesl,
                    int cantStreams) {
    //Canales.txt
    //1/10/2022    A1911    AdmiralBulldog
    //a partir de aquí, se repite
    //738184    1/9/2025    15:13:35    3.38    0.628
    //929142    18/8/2025    5:22:57    3.78    0.320

    ifstream archCanales;
    aperturaArchivoLectura(nombArchCanales,archCanales);
    int creCanal,codeIntCanal,codeStream,posStream,fechaCanal,durStreamCanal;
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
                if (arrCantReproducciones[posStream]==0) {
                    arrCodeCharCanal[posStream]=codeCharCanal;
                    arrCodeIntCanal[posStream]=codeIntCanal;
                    arrFechaAntiguaCanal[posStream]=fechaCanal;
                    arrFechaRecienteCanal[posStream]=fechaCanal;
                }else {
                    if (arrFechaAntiguaCanal[posStream]==0 or
                     fechaCanal<arrFechaAntiguaCanal[posStream]) {
                        arrFechaAntiguaCanal[posStream]=fechaCanal;
                     }
                    if (arrFechaRecienteCanal[posStream]==0 or
                        fechaCanal>arrFechaRecienteCanal[posStream]) {
                        arrFechaRecienteCanal[posStream]=fechaCanal;
                    }
                }
                arrRatingPromCanal[posStream]+=rating;
                arrTasaDropPromCanal[posStream]+=drop;
                arrCantReproducciones[posStream]++;
            }
            if (archCanales.get()=='\n') break;
        }
    }
    for (int i=0;i<cantStreams;i++) {
        if (arrCantReproducciones[i]>0) {
            arrRatingPromCanal[i]=arrRatingPromCanal[i]/arrCantReproducciones[i];
            arrTasaDropPromCanal[i]=arrTasaDropPromCanal[i]/arrCantReproducciones[i];
            arrDurTotalReproduccionesl[i]+=arrDurStream[i]*arrCantReproducciones[i];
        }
    }
}

void imprimirReporte(const char* nombArchRep,
                    int *arrCodeStream,int *arrDurStream,int *arrCodeIdiomaStream,
                    char *arrCharCatIdiomaStream,int *arrIntCatIdiomaStream,int cantStreams,
                    int *arrFechaAntiguaCanal,int *arrFechaRecienteCanal,
                    double *arrRatingPromCanal,double *arrTasaDropPromCanal,
                    int *arrCantReproducciones,int *arrDurTotalReproducciones,
                    bool ordenado) {
    ofstream output;
    int codeMenor,codeMayor,mayorDuracion=0,menorDuracion=999999;
    aperturaArchivoEscritura(nombArchRep,output);
    imprimirCabeceraReporte(output);
    output<<fixed<<setprecision(2);
    for (int i=0;i<cantStreams;i++) {
        output<<arrCodeStream[i];
        output<<setw(10)<<right<<arrCodeIdiomaStream[i];
        output<<setw(8)<<right<<arrCharCatIdiomaStream[i]<<arrIntCatIdiomaStream[i];
        if (arrCantReproducciones[i]==0) {
            imprimirGuiones(output);
            output<<setw(15)<<" ";imprimirTiempo(output,arrDurStream[i]);
            output<<setw(12)<<right<<arrCantReproducciones[i];
            output<<setw(8)<<" ";imprimirTiempo(output,arrDurTotalReproducciones[i]);
            output<<endl;
        }else {
            output<<setw(8)<<" ";imprimirFecha(output,arrFechaAntiguaCanal[i]);
            output<<setw(8)<<" ";imprimirFecha(output,arrFechaRecienteCanal[i]);
            output<<setw(11)<<right<<arrRatingPromCanal[i];
            output<<setw(17)<<right<<arrTasaDropPromCanal[i];
            output<<setw(15)<<" ";imprimirTiempo(output,arrDurStream[i]);
            output<<setw(12)<<right<<arrCantReproducciones[i];
            output<<setw(8)<<" ";imprimirTiempo(output,arrDurTotalReproducciones[i]);
            output<<endl;
        }
        if (arrDurStream[i]>mayorDuracion) {
            mayorDuracion=arrDurStream[i];
            codeMayor=arrCodeStream[i];
        }
        if (arrDurStream[i]<menorDuracion) {
            menorDuracion=arrDurStream[i];
            codeMenor=arrCodeStream[i];
        }
    }
    if (ordenado) {
        imprimirLineas('-',150,output);
        output<<"RESUMEN:"<<endl;
        output<<"STREAM CON MAYOR DURACION:"<<setw(15)<<right<<codeMayor<<" - ";
        imprimirTiempo(output,mayorDuracion); output<<endl;
        output<<"STREAM CON MENOR DURACION:"<<setw(15)<<right<<codeMenor<<" - ";
        imprimirTiempo(output,menorDuracion); output<<endl;
        imprimirLineas('=',150,output);
    }
}

void ordenacion(int *arrCodeStream,int *arrDurStream,int *arrCodeIdiomaStream,
                    char *arrCharCatIdiomaStream,int *arrIntCatIdiomaStream,int cantStreams,
                    int *arrFechaAntiguaCanal,int *arrFechaRecienteCanal,
                    double *arrRatingPromCanal,double *arrTasaDropPromCanal,
                    int *arrCantReproducciones,int *arrDurTotalReproducciones) {
    for (int i=0;i<cantStreams-1;i++) {
        for (int j=i+1;j<cantStreams;j++) {
            if (arrCodeIdiomaStream[i]>arrCodeIdiomaStream[j] or
                arrCodeIdiomaStream[i]==arrCodeIdiomaStream[j] and
                arrTasaDropPromCanal[i]<arrTasaDropPromCanal[j]) {
                swapInt(arrCodeStream[i],arrCodeStream[j]);
                swapInt(arrDurStream[i],arrDurStream[j]);
                swapInt(arrCodeIdiomaStream[i],arrCodeIdiomaStream[j]);
                swapChar(arrCharCatIdiomaStream[i], arrCharCatIdiomaStream[j]);
                swapInt(arrIntCatIdiomaStream[i], arrIntCatIdiomaStream[j]);
                swapInt(arrFechaAntiguaCanal[i],arrFechaAntiguaCanal[j]);
                swapInt(arrFechaRecienteCanal[i],arrFechaRecienteCanal[j]);
                swapDouble(arrRatingPromCanal[i],arrRatingPromCanal[j]);
                swapDouble(arrTasaDropPromCanal[i],arrTasaDropPromCanal[j]);
                swapInt(arrCantReproducciones[i],arrCantReproducciones[j]);
                swapInt(arrDurTotalReproducciones[i],arrDurTotalReproducciones[j]);
            }
        }
    }
}

void swapInt(int &a,int &b) {
    int aux=a;
    a=b;
    b=aux;
}

void swapChar(char &a,char &b) {
    char aux=a;
    a=b;
    b=aux;
}

void swapDouble(double &a,double &b) {
    double aux=a;
    a=b;
    b=aux;
}

void imprimirGuiones(ofstream& output) {
    output<<setw(18)<<right<<"----------";
    output<<setw(18)<<right<<"----------";
    output<<setw(11)<<right<<"----";
    output<<setw(17)<<right<<"----";
}

void imprimirCabeceraReporte(ofstream& output) {
    imprimirLineas('=',150,output);
    output<<setw(60)<<" "<<"PLATAFORMA DE STREAMING TP"<<endl;
    output<<setw(55)<<" "<<"DETALLE COMPLETO DE REPRODUCCION DE STREAMS"<<endl;
    imprimirLineas('=',150,output);
    output<<"STREAM";
    output<<setw(11)<<right<<"IDIOMA";
    output<<setw(13)<<right<<"CATEGORIA";
    output<<setw(17)<<right<<"REP.ANTIGUA";
    output<<setw(18)<<right<<"REP.RECIENTE";
    output<<setw(15)<<right<<"PROM.RAT.CAL";
    output<<setw(20)<<right<<"PROM.TASA.DROP-OFF";
    output<<setw(14)<<right<<"DURAC.";
    output<<setw(15)<<right<<"#REPR.";
    output<<setw(15)<<right<<"TOT.REPR."<<endl;
    imprimirLineas('-',150,output);
}


int buscarStream(int *arrCodeStream,int codeStream,int cantStreams) {
    for (int i=0;i<cantStreams;i++)
        if (arrCodeStream[i]==codeStream) return i;
    return NO_ENCONTRADO;
}

void imprimirSubtituloPruebaStreams(ofstream& output) {
    //803100    1:22:25    4003    C1072
    output<<setw(25)<<" "<<"REPORTE DE PRUEBA STREAMS"<<endl;
    imprimirLineas('=',80,output);
    output<<"CODIGO STREAM";
    output<<setw(20)<<right<<"DURACION STREAM";
    output<<setw(20)<<right<<"CODIGO IDIOMA";
    output<<setw(20)<<right<<"CATEGORIA IDIOMA "<<endl;
}


void imprimirLineas(char c,int cant,ofstream& output) {
    for (int i=0;i<cant;i++) output << c;
    output << endl;
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
    output<<setw(2)<<right<<dd<<'/';
    output<<setw(2)<<right<<mm<<'/';
    output<<setw(4)<<right<<yyyy;
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
    output<<setw(2)<<right<<hh<<':';
    output<<setw(2)<<right<<mm<<':';
    output<<setw(2)<<right<<ss;
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
