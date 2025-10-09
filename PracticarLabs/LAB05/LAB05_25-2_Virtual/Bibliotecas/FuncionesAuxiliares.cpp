//
// Created by DIEGO on 10/6/2025.
//

#include "FuncionesAuxiliares.h"

void aperturaArchivoLectura(const char* nombArch,ifstream& arch) {
    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"ERROR, el archivo"<<nombArch<<" no se pudo abrir"<<endl;
        exit(1);
    }
}

void aperturaArchivoEscritura(const char* nombArch,ofstream& arch) {
    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout<<"ERROR, el archivo"<<nombArch<<" no se pudo abrir"<<endl;
        exit(1);
    }
}

void preguntarTarifa(double &tarifaDur) {
    cout<<"Ingrese tarifa por duracion de etiquetas: ";
    cin>>tarifaDur;
}

void cargarCanales(const char* nombArchCanales,int *arrFechaCanal,
                    char *arrCodeCharCanal,int *arrCodeIntCanal,
                    double *arrRatingCanal,int &nroCanales) {
    //19/06/2022     X5514     xQcOW     2.5
    ifstream archCanales;
    int fechaCanal;
    aperturaArchivoLectura(nombArchCanales,archCanales);
    while (true) {
        fechaCanal = leerFecha(archCanales);
        if (archCanales.eof()) break;
        archCanales>>arrCodeCharCanal[nroCanales];
        archCanales>>arrCodeIntCanal[nroCanales];
        ignorar(archCanales,' ');
        archCanales>>arrRatingCanal[nroCanales];
        arrFechaCanal[nroCanales] = fechaCanal;
        nroCanales++;
    }
}

void pruebaCanales(const char* nombArchRepPruebaCanales,int *arrFechaCanal,
                    char *arrCodeCharCanal,int *arrCodeIntCanal,
                    double *arrRatingCanal,int nroCanales) {
    //19/06/2022     X5514     xQcOW     2.5
    ofstream output;
    aperturaArchivoEscritura(nombArchRepPruebaCanales,output);
    output<<setw(5)<<" "<<"REPORTE DE PRUEBA PARA CANALES"<<endl;
    imprimirLineas('=',50,output);
    output<<setw(5)<<" "<<"FECHA"<<setw(15)<<" "<<"CODIGO"<<setw(15)<<" "<<"RATING"<<endl;
    output<<fixed<<setprecision(2);
    for (int i=0;i<nroCanales;i++) {
        output<<setw(5)<<" "; imprimirFecha(output,arrFechaCanal[i]);
        output<<setw(10)<<" "<<arrCodeCharCanal[i]<<arrCodeIntCanal[i];
        output<<setw(20)<<right<<arrRatingCanal[i]<<endl;
    }
}

void cargarEtiquetas(const char* nombArchEtiquetas,int* arrCodeEtiqueta,
                    int* arrTiempoDurEtiqueta,int& nroEtiquetas) {
    //803100    dropsenabled   01:27
    ifstream archEtiquetas;
    int codeEtiqueta,fechaEtiqueta;
    aperturaArchivoLectura(nombArchEtiquetas,archEtiquetas);
    while (true) {
        archEtiquetas>>codeEtiqueta;
        if (archEtiquetas.eof()) break;
        ignorar(archEtiquetas,' ');
        fechaEtiqueta = leerTiempo(archEtiquetas);
        arrTiempoDurEtiqueta[nroEtiquetas]=fechaEtiqueta;
        arrCodeEtiqueta[nroEtiquetas]=codeEtiqueta;
        nroEtiquetas++;
    }
}
void pruebaEtiquetas(const char *nombArchRepPruebaEtiquetas,int* arrCodeEtiqueta,
                    int* arrTiempoDurEtiqueta,int nroEtiquetas) {
    //803100    dropsenabled   01:27
    ofstream output;
    aperturaArchivoEscritura(nombArchRepPruebaEtiquetas,output);
    output<<setw(5)<<" "<<"REPORTE DE PRUEBA PARA ETIQUETAS"<<endl;
    imprimirLineas('=',50,output);
    output<<setw(5)<<" "<<"CODIGO"<<setw(15)<<" "<<"DURACION"<<endl;
    for (int i=0;i<nroEtiquetas;i++) {
        output<<setw(5)<<" "<<arrCodeEtiqueta[i];
        output<<setw(15)<<" "; imprimirTiempo(output,arrTiempoDurEtiqueta[i],true);
        output<<endl;
    }
}

void cargarEtiquetaCanal(const char* nombArchEtiquetaCanales,
                        char *arrCodeCharEtiquetaCanal,int *arrCodeIntEtiquetaCanal,
                        int *arrCodeEtiquetaCanal,int &nroEtiquetaCanal) {
    //P7271    113141
    ifstream archEtiquetaCanal;
    char codeCharEtiquetaCanal;
    int codeIntEtiquetaCanal;
    aperturaArchivoLectura(nombArchEtiquetaCanales,archEtiquetaCanal);
    while (true) {
        archEtiquetaCanal>>codeCharEtiquetaCanal>>codeIntEtiquetaCanal;
        if (archEtiquetaCanal.eof()) break;
        archEtiquetaCanal>>arrCodeEtiquetaCanal[nroEtiquetaCanal];
        arrCodeCharEtiquetaCanal[nroEtiquetaCanal]=codeCharEtiquetaCanal;
        arrCodeIntEtiquetaCanal[nroEtiquetaCanal]=codeIntEtiquetaCanal;
        nroEtiquetaCanal++;
    }
}
void pruebaEtiquetaCanal(const char* nombArchRepPruebaEtiCanal,
                        char *arrCodeCharEtiquetaCanal,int *arrCodeIntEtiquetaCanal,
                        int *arrCodeEtiquetaCanal,int nroEtiquetaCanal) {
    //P7271    113141
    ofstream output;
    aperturaArchivoEscritura(nombArchRepPruebaEtiCanal,output);
    output<<setw(5)<<" "<<"REPORTE DE PRUEBA PARA ETIQUETA EN CANALES"<<endl;
    imprimirLineas('=',50,output);
    output<<setw(5)<<" "<<"CODIGO CANAL"<<setw(15)<<" "<<"CODIGO ETIQUETA"<<endl;
    for (int i=0;i<nroEtiquetaCanal;i++) {
        output<<setw(5)<<" "<<arrCodeCharEtiquetaCanal[i]<<arrCodeIntEtiquetaCanal[i];
        output<<setw(26)<<" "; output<<arrCodeEtiquetaCanal[i];
        output<<endl;
    }
}

void procesarReproEtiquetas(const char* nombArchReproEtiquetas,
                            int *arrFechaCanal,char *arrCodeCharCanal,int *arrCodeIntCanal,
                            double *arrRatingCanal,int nroCanales,
                            int *arrCodeEtiqueta,int *arrTiempoDurEtiqueta,int nroEtiquetas,
                            char *arrCodeCharEtiquetaCanal,int *arrCodeIntEtiquetaCanal,
                            int *arrCodeEtiquetaCanal,int nroEtiquetaCanal,
                            int *arrNroTotalReproCanal,int *arrTiempoTotalReproCanal,
                            int *arrNroTotalReproCanalGlobal,int *arrTiempoTotalReproCanalGlobal) {
    //28/02/2025  E6696      888106      244
    ifstream archReproEtiqueta;
    int fechaRegEtiquetaArch,codeIntCanalArch,codeEtiquetaReproArch,cantRepro;
    int posCanal;
    char codeCharCanalArch;
    aperturaArchivoLectura(nombArchReproEtiquetas,archReproEtiqueta);
    while (true) {
        fechaRegEtiquetaArch=leerFecha(archReproEtiqueta);//no se necesita
        if (archReproEtiqueta.eof()) break;
        archReproEtiqueta>>codeCharCanalArch>>codeIntCanalArch;
        archReproEtiqueta>>codeEtiquetaReproArch;
        archReproEtiqueta>>cantRepro;
        posCanal=buscarCanal(arrCodeCharCanal,arrCodeIntCanal,
                            codeCharCanalArch,codeIntCanalArch,nroEtiquetaCanal);
        if (posCanal!=-1) {
            //posEtiqueta=
        }
    }
}

int buscarCanal(char *arrCodeCharCanal,int *arrCodeIntCanal,
                char codeCharCanalArch,int codeIntCanalArch,int nroEtiquetaCanal) {
    for (int i=0;i<nroEtiquetaCanal;i++)
        if (arrCodeCharCanal[i]==codeCharCanalArch and arrCodeIntCanal[i]==codeIntCanalArch) return i;
    return -1;
}










int leerTiempo(ifstream& input) {
    int mm,ss;
    char c;
    input >> mm >> c >> ss;
    return mm*60 + ss;
}

void imprimirTiempo(ofstream& output,int tiempo,bool esMinuto) {
    int hh,mm,ss;
    hh=tiempo/3600;
    tiempo%=3600;
    mm=tiempo/60;
    tiempo%=60;
    ss=tiempo;
    output.fill('0');
    if (esMinuto) {
        output<<setw(2)<<right<<mm<<":"<<setw(2)<<right<<ss;
    }else {
        output<<setw(2)<<right<<hh<<":"<<setw(2)<<right<<mm<<":"<<setw(2)<<right<<ss;
    }
    output.fill(' ');
}

void imprimirLineas(char c,int cant,ofstream& output) {
    for (int i = 0; i < cant; i++) output << c ;
    output << endl;
}

void imprimirNroOrden(ofstream& output,int nroOrden) {
    output.fill('0');
    output<<setw(2)<<right<<nroOrden<<")";
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

int leerFecha(ifstream& input) {
    int dd,mm,yyyy;
    char c;
    input >> dd >> c >> mm >> c >> yyyy;
    return yyyy*10000+mm*100+dd;
}

void imprimirFecha(ofstream& output,int fecha) {
    int dd,mm,yyyy;
    yyyy = fecha/10000;
    fecha=fecha%10000;
    mm = fecha/100;
    fecha=fecha%100;
    dd = fecha;
    output.fill('0');
    output << setw(2) << right << dd << '/' << setw(2) << right << mm <<  '/' << yyyy;
    output.fill(' ');
}










