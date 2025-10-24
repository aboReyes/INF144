//
// Created by ASUS on 24/10/2025.
//

#include "FuncionesAuxiliares.h"

void aperturaArchivoLectura(const char* nombArch,ifstream& arch) {
    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"ERROR, el archivo "<< nombArch <<" no se puede abrir"<<endl;
        exit(1);
    }
}

void aperturaArchivoEscritura(const char* nombArch,ofstream& arch) {
    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout<<"ERROR, el archivo "<< nombArch <<" no se puede abrir"<<endl;
        exit(1);
    }
}

void cargarStreams(const char* nombArchStreams,
        int *arrCodeStream,int *arrDurStream,int *arrCodeIdiomaStream,
        char *arrLetraCatIdiomaStream,int *arrNumCatIdiomaStream,
        int &cantStreams) {
    //803100    1:22:25    4003    C1072
    ifstream archStreams;
    int codeStream,durStream,codeIdioma,numCatIdioma;
    char letraCatIdioma;
    aperturaArchivoLectura(nombArchStreams,archStreams);
    while (true) {
        archStreams>>codeStream;
        if (archStreams.eof()) break;
        durStream=leerTiempo(archStreams);
        archStreams>>codeIdioma;
        archStreams>>letraCatIdioma>>numCatIdioma;
        insertarOrdenado(codeStream,durStream,codeIdioma,
                        letraCatIdioma,numCatIdioma,
                        arrCodeStream,arrDurStream,arrCodeIdiomaStream,
                        arrLetraCatIdiomaStream,arrNumCatIdiomaStream,
                        cantStreams);
    }
}

void insertarOrdenado(int codeStream,int durStream,int codeIdioma,
                    char letraCatIdioma,int numCatIdioma,
                    int *arrCodeStream,int *arrDurStream,
                    int *arrCodeIdiomaStream,
                    char *arrLetraCatIdiomaStream,int *arrNumCatIdiomaStream,
                    int &cantStreams) {
    int i=cantStreams-1;
    while (i>=0 and arrCodeStream[i]>codeStream) {
        arrCodeStream[i+1]=arrCodeStream[i];
        arrDurStream[i+1]=arrDurStream[i];
        arrCodeIdiomaStream[i+1]=arrCodeIdiomaStream[i];
        arrLetraCatIdiomaStream[i+1]=arrLetraCatIdiomaStream[i];
        arrNumCatIdiomaStream[i+1]=arrNumCatIdiomaStream[i];
        i--;
    }
    arrCodeStream[i+1]=codeStream;
    arrDurStream[i+1]=durStream;
    arrCodeIdiomaStream[i+1]=codeIdioma;
    arrLetraCatIdiomaStream[i+1]=letraCatIdioma;
    arrNumCatIdiomaStream[i+1]=numCatIdioma;
    cantStreams++;
}

void pruebaStreams(const char* nombArchRep,
                    int *arrCodeStream,int *arrDurStream,int *arrCodeIdiomaStream,
                    char *arrLetraCatIdiomaStream,int *arrNumCatIdiomaStream,
                    int cantStreams) {
    //803100    1:22:25    4003    C1072
    ofstream output;
    aperturaArchivoEscritura(nombArchRep,output);
    imprimirSubtituloPruebaStreams(output);
    for (int i=0;i<cantStreams;i++) {
        output<<setw(10)<<right<<arrCodeStream[i];
        output<<setw(10)<<" ";imprimirTiempo(output,arrDurStream[i]);
        output<<setw(20)<<right<<arrCodeIdiomaStream[i];
        output<<setw(15)<<right<<arrLetraCatIdiomaStream[i]<<arrNumCatIdiomaStream[i]<<endl;
    }
}

void procesarCanales(const char* nombArchCanales,
        int *arrCodeStream,int *arrDurStream,int cantStreams,
        int *arrFechaAntiguaCanal,int *arrFechaRecienteCanal,
        double *arrPromRatingCanal,double *arrPromDropCanal,
        int *arrCantReproCanal,int *arrTiempoTotalReproCanal) {
    //1/10/2022    A1911    AdmiralBulldog
    //estos se repiten:
    //738184    1/9/2025    15:13:35    3.38    0.628
    //929142    18/8/2025    5:22:57    3.78    0.320
    ifstream archCanales;
    int fechaCreCanal,numCanal,codeStream,posStream,fechaStream,durStream;
    double rating,drop;
    char letraCanal;
    aperturaArchivoLectura(nombArchCanales,archCanales);
    while (true) {
        fechaCreCanal=leerFecha(archCanales);
        if (archCanales.eof()) break;
        archCanales>>letraCanal>>numCanal;
        ignorar(archCanales,' ');
        while (true) {
            archCanales>>codeStream;
            fechaStream=leerFecha(archCanales);
            durStream=leerTiempo(archCanales);
            archCanales>>rating>>drop;
            posStream=buscarBinario(codeStream,arrCodeStream,cantStreams);
            if (posStream!=NO_ENCONTRADO) {
                if (arrCantReproCanal[posStream]==0) {
                    arrFechaAntiguaCanal[posStream]=fechaStream;
                    arrFechaRecienteCanal[posStream]=fechaStream;
                }
                if (fechaStream<arrFechaAntiguaCanal[posStream]) {
                    arrFechaAntiguaCanal[posStream]=fechaStream;
                }
                if (fechaStream>arrFechaAntiguaCanal[posStream]) {
                    arrFechaRecienteCanal[posStream]=fechaStream;
                }
                arrPromRatingCanal[posStream]+=rating;
                arrPromDropCanal[posStream]+=drop;
                arrCantReproCanal[posStream]++;
            }
            if (archCanales.get()=='\n') break;
        }
    }
    for (int i=0;i<cantStreams;i++) {
        if (arrCantReproCanal[i]>0) {
            arrPromRatingCanal[i]+=arrPromRatingCanal[i]/arrCantReproCanal[i];
            arrPromDropCanal[i]+=arrPromDropCanal[i]/arrCantReproCanal[i];
            arrTiempoTotalReproCanal[i]+=arrDurStream[i]*arrCantReproCanal[i];
        }
    }
}

int buscarBinario(int codeStream,int *arrCodeStream,int cantStream) {
    int limiteInferior=0;
    int limiteSuperior=cantStream-1;
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

void reporteStream(const char* nombArchRep,
            int *arrCodeStream,int *arrCodeIdiomaStream,
            char *arrLetraCatIdiomaStream,int *arrNumCatIdiomaStream,
            int *arrFechaAntiguaCanal,int *arrFechaRecienteCanal,
            double*arrPromRatingCanal,double*arrPromDropCanal,int *arrDurStream,
            int *arrCantReproCanal,int *arrTiempoTotalReproCanal,
            int cantStreams,bool esOrdenado) {
    ofstream output;
    int mayorTiempo=0,menorTiempo=99999,codeMayor,codeMenor;
    aperturaArchivoEscritura(nombArchRep,output);
    imprimirCabeceraReporte(output);
    output<<fixed<<setprecision(2);
    for (int i=0;i<cantStreams;i++) {
        output<<arrCodeStream[i];
        output<<setw(10)<<right<<arrCodeIdiomaStream[i];
        output<<setw(8)<<right<<arrLetraCatIdiomaStream[i]<<arrNumCatIdiomaStream[i];
        if (arrCantReproCanal[i]==0) {
            imprimirGuiones(output);
            output<<setw(15)<<" ";imprimirTiempo(output,arrDurStream[i]);
            output<<setw(12)<<right<<arrCantReproCanal[i];
            output<<setw(8)<<" ";imprimirTiempo(output,arrTiempoTotalReproCanal[i]);
            output<<endl;
        }else {
            output<<setw(8)<<" "; imprimirFecha(output,arrFechaAntiguaCanal[i]);
            output<<setw(8)<<" "; imprimirFecha(output,arrFechaRecienteCanal[i]);
            output<<setw(11)<<right<<arrPromRatingCanal[i];
            output<<setw(17)<<right<<arrPromDropCanal[i];
            output<<setw(15)<<" "; imprimirTiempo(output,arrDurStream[i]);
            output<<setw(12)<<right<<arrCantReproCanal[i];
            output<<setw(8)<<" "; imprimirTiempo(output,arrTiempoTotalReproCanal[i]);
            output<<endl;
        }

        if (mayorTiempo<arrDurStream[i]) {
            mayorTiempo=arrDurStream[i];
            codeMayor=arrCodeStream[i];
        }
        if (menorTiempo>arrDurStream[i]) {
            menorTiempo=arrDurStream[i];
            codeMenor=arrCodeStream[i];
        }
    }
    if (esOrdenado) {
        imprimirResumen(output,mayorTiempo,codeMayor,menorTiempo,codeMenor);
    }
}

void imprimirResumen(ofstream& output,int mayorTiempo,int codeMayor,
                    int menorTiempo,int codeMenor) {
    imprimirLineas('-',150,output);
    output<<"RESUMEN:"<<endl;
    output<<"STREAM CON MAYOR DURACION: "<<setw(15)<<right<<codeMayor<<" - ";
    imprimirTiempo(output,mayorTiempo); output<<" hrs"<<endl;
    output<<"STREAM CON MENOR DURACION: "<<setw(15)<<right<<codeMenor<<" - ";
    imprimirTiempo(output,menorTiempo);
    output<<" hrs"<<endl;
    imprimirLineas('=',150,output);
}

void eliminar(int *arrCodeStream,int *arrCodeIdiomaStream,
            char *arrLetraCatIdiomaStream,int *arrNumCatIdiomaStream,
            int *arrFechaAntiguaCanal,int *arrFechaRecienteCanal,
            double *arrPromRatingCanal,double *arrPromDropCanal,int *arrDurStream,
            int *arrCantReproCanal,int *arrTiempoTotalReproCanal,
            int cantStreams) {
    for (int i=0;i<cantStreams;) {
        if (arrCantReproCanal[i]==0) {
            for (int j=i+1;j<cantStreams;j++) {
                arrCodeStream[j-1]=arrCodeStream[j];
                arrCodeIdiomaStream[j-1]=arrCodeIdiomaStream[j];
                arrLetraCatIdiomaStream[j-1]=arrLetraCatIdiomaStream[j];
                arrNumCatIdiomaStream[j-1]=arrNumCatIdiomaStream[j];
                arrFechaAntiguaCanal[j-1]=arrFechaAntiguaCanal[j];
                arrFechaRecienteCanal[j-1]=arrFechaRecienteCanal[j];
                arrPromRatingCanal[j-1]=arrPromRatingCanal[j];
                arrPromDropCanal[j-1]=arrPromDropCanal[j];
                arrDurStream[j-1]=arrDurStream[j];
                arrCantReproCanal[j-1]=arrCantReproCanal[j];
                arrTiempoTotalReproCanal[j-1]=arrTiempoTotalReproCanal[j];
            }
        }else {
            i++;
        }
    }
}


void ordenarReporte(int *arrCodeStream,int *arrCodeIdiomaStream,
            char *arrLetraCatIdiomaStream,int *arrNumCatIdiomaStream,
            int *arrFechaAntiguaCanal,int *arrFechaRecienteCanal,
            double *arrPromRatingCanal,double *arrPromDropCanal,int *arrDurStream,
            int *arrCantReproCanal,int *arrTiempoTotalReproCanal,
            int cantStreams) {
    for (int i=0;i<cantStreams-1;i++) {
        for (int j=i+1;j<cantStreams;j++) {
            if (arrCodeIdiomaStream[i]>arrCodeIdiomaStream[j] or
                arrCodeIdiomaStream[i]==arrCodeIdiomaStream[j] and
                arrPromDropCanal[i]<arrPromDropCanal[j]) {//Condición del problema
                swapInt(arrCodeStream[i],arrCodeStream[j]);
                swapInt(arrCodeIdiomaStream[i],arrCodeIdiomaStream[j]);
                swapChar(arrLetraCatIdiomaStream[i],arrLetraCatIdiomaStream[j]);
                swapInt(arrNumCatIdiomaStream[i],arrNumCatIdiomaStream[j]);
                swapInt(arrFechaAntiguaCanal[i],arrFechaAntiguaCanal[j]);
                swapInt(arrFechaRecienteCanal[i],arrFechaRecienteCanal[j]);
                swapDouble(arrPromRatingCanal[i],arrPromRatingCanal[j]);
                swapDouble(arrPromDropCanal[i],arrPromDropCanal[j]);
                swapInt(arrDurStream[i],arrDurStream[j]);
                swapInt(arrCantReproCanal[i],arrCantReproCanal[j]);
                swapInt(arrTiempoTotalReproCanal[i],arrTiempoTotalReproCanal[j]);
            }
        }
    }
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

void ignorar(ifstream& input,char delimitador) {
    char c;
    input>>ws;
    while (true) {
        c=input.get();
        if (c==delimitador) break;
    }
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
    output<<setw(2)<<right<<hh<<":";
    output<<setw(2)<<right<<mm<<":";
    output<<setw(2)<<right<<ss;
    output.fill(' ');

}

//////

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
