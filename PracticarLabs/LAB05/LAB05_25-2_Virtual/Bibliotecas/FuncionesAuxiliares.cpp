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


void ordenarEtiquetas(int *arrCodeEtiqueta,int *arrTiempoDurEtiqueta,int nroEtiquetas) {
    for (int i=0;i<nroEtiquetas-1;i++) {
        for (int j=i+1;j<nroEtiquetas;j++) {
            if (arrTiempoDurEtiqueta[i]<arrTiempoDurEtiqueta[j]) {
                swapInt(arrCodeEtiqueta[i],arrCodeEtiqueta[j]);
                swapInt(arrTiempoDurEtiqueta[i],arrTiempoDurEtiqueta[j]);
            }
        }
    }
}

void swapInt(int &a,int &b) {
    int aux;
    aux=a;
    a=b;
    b=aux;
}

void procesarReproEtiquetas(const char* nombArchReproEtiquetas,
                            char *arrCodeCharCanal,int *arrCodeIntCanal,
                            double *arrRatingCanal,int nroCanales,
                            int *arrCodeEtiqueta,int *arrTiempoDurEtiqueta,int nroEtiquetas,
                            double *arrSumaRatingCanalLigadoEtiqueta,int *arrCantCanalLigadoEtiqueta,
                            char *arrCodeCharEtiquetaCanal,int *arrCodeIntEtiquetaCanal,
                            int *arrCodeEtiquetaCanal,int nroEtiquetaCanal,double* arrRatingCanalEtiquetaCanal,
                            int *arrNroTotalReproCanal,int *arrTiempoTotalReproCanal,
                            int *arrNroTotalReproCanalGlobal,int *arrTiempoTotalReproCanalGlobal,
                            double *arrIngresoPorReproEtiqueta,double tarifaDurEtiqueta) {
    //28/02/2025  E6696      888106      244
    ifstream archReproEtiqueta;
    int fechaRegEtiquetaArch,codeIntEtiCanalArch,codeEtiquetaReproArch,cantRepro;
    int posEtiquetaCanal,posEtiqueta;
    double ratingCanal;
    char codeCharEtiCanalArch;
    aperturaArchivoLectura(nombArchReproEtiquetas,archReproEtiqueta);
    while (true) {
        fechaRegEtiquetaArch=leerFecha(archReproEtiqueta);//no se necesita
        if (archReproEtiqueta.eof()) break;
        archReproEtiqueta>>codeCharEtiCanalArch>>codeIntEtiCanalArch;
        archReproEtiqueta>>codeEtiquetaReproArch;
        archReproEtiqueta>>cantRepro;
        posEtiquetaCanal=buscarEtiquetaCanal(arrCodeCharEtiquetaCanal,arrCodeIntEtiquetaCanal,
                            codeCharEtiCanalArch,codeIntEtiCanalArch,arrCodeEtiquetaCanal,codeEtiquetaReproArch,nroEtiquetaCanal);
        if (posEtiquetaCanal!=-1) {
            posEtiqueta=buscarEtiqueta(arrCodeEtiqueta,codeEtiquetaReproArch,nroEtiquetas);
            if (posEtiqueta!=-1) {
                ratingCanal=buscarRatingCanal(arrCodeCharCanal,arrCodeIntCanal,arrRatingCanal,codeCharEtiCanalArch,codeIntEtiCanalArch,nroCanales);
                if (ratingCanal!=-1) {
                    //resumen por canal
                    arrRatingCanalEtiquetaCanal[posEtiquetaCanal]=ratingCanal;
                    arrNroTotalReproCanal[posEtiquetaCanal]+=cantRepro;
                    arrTiempoTotalReproCanal[posEtiquetaCanal]+=arrTiempoDurEtiqueta[posEtiqueta]*cantRepro;
                    //Para el resumen global de cada etiqueta
                    arrNroTotalReproCanalGlobal[posEtiqueta]+=cantRepro;
                    arrTiempoTotalReproCanalGlobal[posEtiqueta]+=arrTiempoDurEtiqueta[posEtiqueta]*cantRepro;
                    arrIngresoPorReproEtiqueta[posEtiqueta]+=tarifaDurEtiqueta*(arrTiempoTotalReproCanalGlobal[posEtiqueta]/60.0);
                    arrSumaRatingCanalLigadoEtiqueta[posEtiqueta]+=ratingCanal;
                    arrCantCanalLigadoEtiqueta[posEtiqueta]++;
                }
            }
        }
    }
}

void generarReporte(const char* nombArchReporte,
                    char *arrCodeCharCanal,int *arrCodeIntCanal,
                    double *arrRatingCanal,int nroCanales,
                    int *arrCodeEtiqueta,int *arrTiempoDurEtiqueta,int nroEtiquetas,
                    double *arrSumaRatingCanalLigadoEtiqueta,int *arrCantCanalLigadoEtiqueta,
                    char *arrCodeCharEtiquetaCanal,int *arrCodeIntEtiquetaCanal,
                    int *arrCodeEtiquetaCanal,int nroEtiquetaCanal,double* arrRatingCanalEtiquetaCanal,
                    int *arrNroTotalReproCanal,int *arrTiempoTotalReproCanal,
                    int *arrNroTotalReproCanalGlobal,int *arrTiempoTotalReproCanalGlobal,
                    double *arrIngresoPorReproEtiqueta,double tarifaDurEtiqueta) {
    ofstream output;
    aperturaArchivoEscritura(nombArchReporte,output);
    imprimirTitulo(output,tarifaDurEtiqueta);
    output<<fixed<<setprecision(2);
    for (int i = 0; i < nroEtiquetas; i++) {
        output<<"ETIQUETA No. "; imprimirNumeroOrden(output,i+1,false); output<<endl;
        output<<setw(3)<<" "<<"CODIGO: "<<setw(7)<<right<<arrCodeEtiqueta[i]<<endl;
        output<<setw(3)<<" "<<"DURACION: "; imprimirTiempo(output,arrTiempoDurEtiqueta[i],true); output<<endl;
        imprimirLineas('-',100,output);
        imprimirSubtitulo(output);
        for (int j = 0,cant=0; j < nroEtiquetaCanal; j++) {
            if (arrCodeEtiqueta[i]==arrCodeEtiquetaCanal[j] and arrNroTotalReproCanal[j]>0) {
                cant++;
                imprimirNumeroOrden(output,cant,false);
                output<<")"<<setw(3)<<" "<<arrCodeCharEtiquetaCanal[j]<<arrCodeIntEtiquetaCanal[j];
                output<<setw(11)<<right<<arrRatingCanalEtiquetaCanal[j];
                output<<setw(16)<<right<<arrNroTotalReproCanal[j]; output<<setw(16)<<" ";
                imprimirTiempo(output,arrTiempoTotalReproCanal[j],false);
                output<<endl;
            }
        }
        imprimirLineas('-',100,output);
        imprimirResumen(output,arrNroTotalReproCanalGlobal,arrTiempoTotalReproCanalGlobal,
                    arrIngresoPorReproEtiqueta,arrSumaRatingCanalLigadoEtiqueta,arrCantCanalLigadoEtiqueta,i);
        imprimirLineas('=',100,output);
    }

}

int filtrarRating(ofstream&output,double promedioRating ) {
    if (promedioRating>4 and promedioRating<=5) {
        output<<setw(21)<<right<<"+30%"<<endl;
        return 1.3;
    }else if (promedioRating>3 and promedioRating<=4) {
        output<<setw(21)<<right<<"+20%"<<endl;
        return 1.2;
    }else if (promedioRating>2 and promedioRating<=3) {
        output<<setw(21)<<right<<"+0%"<<endl;
        return 0.0;
    }else if (promedioRating>1 and promedioRating<=2) {
        output<<setw(21)<<right<<"-20%"<<endl;
        return 0.75;
    }
    return 0.0;
}

void imprimirResumen(ofstream &output,int *arrNroTotalReproCanalGlobal,int *arrTiempoTotalReproCanalGlobal,
                    double *arrIngresoPorReproEtiqueta,double *arrSumaRatingCanalLigadoEtiqueta,int *arrCantCanalLigadoEtiqueta,int i) {
    output<<"RESUMEN DE LA ETIQUETA: "<<endl;
    output<<"TOTAL DE REPRODUCCIONES: "<<setw(28)<<right<<arrNroTotalReproCanalGlobal[i]<<endl;
    output<<"TIEMPO TOTAL REPRODUCIDO: "; output<<setw(19)<<right<<" "; imprimirTiempo(output,arrTiempoTotalReproCanalGlobal[i],false); output<<endl;
    double promedioRating=(arrSumaRatingCanalLigadoEtiqueta[i]/arrCantCanalLigadoEtiqueta[i]);
    output<<"PORCENTAJE PROMEDIO POR RATING: ";
    double tarifaRating=filtrarRating(output,promedioRating);
    output<<"INGRESOS POR REPRODUCCIONES:"<<setw(16)<<right<<"$ "<<setw(9)<<right<<arrIngresoPorReproEtiqueta[i]+(arrIngresoPorReproEtiqueta[i]*tarifaRating)<<endl;
}

void imprimirSubtitulo(ofstream &output) {
    output<<setw(3)<<" "<<"CANALES DONDE SE REPRODUCE: "<<endl;
    output<<setw(16)<<" "<<"RATING DE "<<setw(5)<<" "<<"NUMERO TOTAL"<<setw(8)<<" "<<"TIEMPO TOTAL DE"<<endl;
    output<<"No."<<setw(3)<<" "<<"CODIGO"<<setw(5)<<" "<<"CALIDAD"<<setw(5)<<" "<<"DE REPRODUCCIONES"<<setw(5)<<" "<<"REPRODUCCIONES"<<endl;
}

void imprimirNumeroOrden(ofstream& output,int nroOrden,bool tieneCero) {
    if (tieneCero) {
        output.fill('0');
        output<<setw(2)<<right<<nroOrden;
        output.fill(' ');
    }else {
        output<<setw(2)<<right<<nroOrden;
    }
}

void imprimirTitulo(ofstream &output,double tarifaDur) {
    output<<setw(40)<<" "<<"PLATAFORMA TP_Twitch"<<endl;
    output<<setw(15)<<" "<<"TARIFA POR DURACION DE LAS ETIQUETAS: "<<tarifaDur;
    output<<" POR CADA MINUTO Y FRACCION"<<endl;
    imprimirLineas('=',100,output);
}

double buscarRatingCanal(char *arrCodeCharCanal,int *arrCodeIntCanal,double *arrRatingCanal,
                    char codeCharEtiCanalArch,int codeIntEtiCanalArch,int nroCanales) {
    for (int i=0;i<nroCanales;i++)
        if (arrCodeCharCanal[i]==codeCharEtiCanalArch and arrCodeIntCanal[i]==codeIntEtiCanalArch) return arrRatingCanal[i];
    return -1;
}

int buscarEtiqueta(int *arrCodeEtiqueta,int codeEtiquetaReproArch,int nroEtiquetas) {
    for (int i=0;i<nroEtiquetas;i++)
        if (arrCodeEtiqueta[i]==codeEtiquetaReproArch) return i;
    return -1;
}

int buscarEtiquetaCanal(char *arrCodeCharEtiquetaCanal,int *arrCodeIntEtiquetaCanal,
                char codeCharCanalArch,int codeIntCanalArch,
                int *arrCodeEtiquetaCanal,int codeEtiquetaReproArch,
                int nroEtiquetaCanal) {
    for (int i=0;i<nroEtiquetaCanal;i++)
        if (arrCodeCharEtiquetaCanal[i]==codeCharCanalArch and arrCodeIntEtiquetaCanal[i]==codeIntCanalArch and arrCodeEtiquetaCanal[i]==codeEtiquetaReproArch) return i;
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
