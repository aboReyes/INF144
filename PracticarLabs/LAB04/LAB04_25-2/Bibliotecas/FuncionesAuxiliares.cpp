//
// Created by DIEGO on 10/2/2025.
//

#include "FuncionesAuxiliares.h"

void aperturaArchivoLectura(const char* nombArch,ifstream& arch) {
    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout << "Error opening file " << nombArch << endl;
    }
}

void aperturaArchivoEscritura(const char* nombArch,ofstream& arch) {
    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout << "Error opening file " << nombArch << endl;
    }
}

void preguntarTarifa(double &tarifaDurEtiquetas) {
    cout<<"Ingrese tarifa por duracion de etiquetas: ";
    cin>>tarifaDurEtiquetas;
}

void cargarCanales(const char* nomArchCanales,int *arrFechaCanal,char *arrCodeCharCanal,
                    int *arrCodeIntCanal,double *arrRatingCanal,int &nroCanales) {
    //19/06/2022    X5514      xQcOW      2.5      632180
    ifstream archCanales;
    int fechaCanal;
    aperturaArchivoLectura(nomArchCanales,archCanales);
    while (true) {
        fechaCanal = leerFecha(archCanales);
        if (archCanales.eof())break;
        archCanales>>arrCodeCharCanal[nroCanales];
        archCanales>>arrCodeIntCanal[nroCanales];
        ignorar(archCanales,' ');
        archCanales>>arrRatingCanal[nroCanales];
        ignorar(archCanales,'\n');
        arrFechaCanal[nroCanales] = fechaCanal;
        nroCanales++;
    }
}

void pruebaCanales(const char* nombArchRepCanales,int *arrFechaCanal,char *arrCodeCharCanal,
                    int *arrCodeIntCanal,double *arrRatingCanal,int nroCanales) {
    ofstream repCanales;
    aperturaArchivoEscritura(nombArchRepCanales,repCanales);
    imprimirTituloRepCanales(repCanales);\
    repCanales<<fixed<<setprecision(2);
    for (int i = 0; i < nroCanales; i++) {
        imprimirFecha(repCanales,arrFechaCanal[i]);
        repCanales<<setw(11)<<right<<arrCodeCharCanal[i]<<arrCodeIntCanal[i];
        repCanales<<setw(16)<<right<<arrRatingCanal[i];
        repCanales<<endl;
    }
}

void cargarEtiquetas(const char* nombArchEtiquetas,int *arrCodeEtiqueta,int *arrTiempoDurEtiqueta,int &nroEtiquetas) {
    //803100    dropsenabled   01:27
    ifstream archEtiquetas;
    int codeEtiqueta,fechaEtiqueta;
    aperturaArchivoLectura(nombArchEtiquetas,archEtiquetas);
    while (true) {
        archEtiquetas>>codeEtiqueta;
        if (archEtiquetas.eof()) break;
        ignorar(archEtiquetas,' ');
        fechaEtiqueta=leerTiempo(archEtiquetas);
        arrCodeEtiqueta[nroEtiquetas] = codeEtiqueta;
        arrTiempoDurEtiqueta[nroEtiquetas] = fechaEtiqueta;
        nroEtiquetas++;
    }
}

void pruebaEtiquetas(const char* nombArchRepEtiquetas,int *arrCodeEtiqueta,int *arrTiempoDurEtiqueta,int nroEtiquetas) {
    ofstream repEtiquetas;
    aperturaArchivoEscritura(nombArchRepEtiquetas,repEtiquetas);
    imprimirTituloRepEtiquetas(repEtiquetas);
    for (int i = 0; i < nroEtiquetas; i++) {
        repEtiquetas<<setw(24)<<left<<arrCodeEtiqueta[i];
        imprimirTiempo(repEtiquetas,arrTiempoDurEtiqueta[i],true);
        repEtiquetas<<endl;
    }
}

void procesarReproducciones(const char* nombArchReproEtiquetas,int *arrFechaCanal,char *arrCodeCharCanal,
                            int *arrCodeIntCanal,double *arrRatingCanal,int nroCanales,
                            int *arrCodeEtiqueta,int *arrTiempoDurEtiqueta,int nroEtiquetas,
                            int *arrNroTotalReproCanales,int *arrTiempoTotalReproCanales,int *arrCantTotalReproEtiquetas,
                            int *arrTiempoTotalReproEtiquetas,double tarifaDurEtiquetas) {
    //28/02/2025  E6696      888106 cod etiqueta     244 cantreproducciones
    ifstream archReproEtiquetas;
    char codeCharEtiquetaArch;
    int codeIntEtiquetaArch,fechaEtiquetaArch,codeEtiquetaArch,cantReproducciones,posCanalEncontrada,posEtiquetaEncontrada;
    aperturaArchivoLectura(nombArchReproEtiquetas,archReproEtiquetas);
    while (true) {
        fechaEtiquetaArch=leerFecha(archReproEtiquetas);
        if (archReproEtiquetas.eof()) break;
        archReproEtiquetas>>codeCharEtiquetaArch>>codeIntEtiquetaArch;
        archReproEtiquetas>>codeEtiquetaArch;
        archReproEtiquetas>>cantReproducciones;
        posCanalEncontrada=buscarCanales(arrCodeCharCanal,arrCodeIntCanal,codeCharEtiquetaArch,codeIntEtiquetaArch,nroCanales);
        posEtiquetaEncontrada=buscarEtiquetas(arrCodeEtiqueta,codeEtiquetaArch,nroEtiquetas);
        if (posCanalEncontrada!=-1) {
            arrNroTotalReproCanales[posCanalEncontrada]+=cantReproducciones;
            arrTiempoTotalReproCanales[posCanalEncontrada]+=arrTiempoDurEtiqueta[posEtiquetaEncontrada]*cantReproducciones;
        }else {
            cout<<"No se puedo encontrar el canal"<<endl;
        }
        if (posEtiquetaEncontrada!=-1) {
            arrCantTotalReproEtiquetas[posEtiquetaEncontrada]+=cantReproducciones;
            arrTiempoTotalReproEtiquetas[posEtiquetaEncontrada]+=arrCantTotalReproEtiquetas[posEtiquetaEncontrada]*arrTiempoDurEtiqueta[posEtiquetaEncontrada];
        }else  {
            cout<<"No se puedo encontrar la etiqueta del canal"<<endl;
        }
    }
}

void generarReporte(const char* output,int *arrFechaCanal,char *arrCodeCharCanal,
                    int *arrCodeIntCanal,double *arrRatingCanal,int nroCanales,
                    int *arrCodeEtiqueta,int *arrTiempoDurEtiqueta,int nroEtiquetas,
                    int *arrNroTotalReproCanales,int *arrTiempoTotalReproCanales,int *arrCantTotalReproEtiquetas,
                    int *arrTiempoTotalReproEtiquetas,double tarifaDurEtiquetas) {
    ofstream archReporte;
    double ingresosPorRepro,tarifaRating;
    aperturaArchivoEscritura(output,archReporte);
    imprimirTituloReporte(archReporte,tarifaDurEtiquetas);
    imprimirSubtituloCanales(archReporte);
    archReporte<<fixed<<setprecision(2);
    for (int i=0;i<nroCanales;i++) {
        imprimirNroOrden(archReporte,i+1); archReporte<<setw(5)<<" ";
        archReporte<<arrCodeCharCanal[i]<<setw(15)<<left<<arrCodeIntCanal[i];
        imprimirFecha(archReporte,arrFechaCanal[i]); archReporte<<setw(5)<<" ";
        archReporte<<setw(7)<<right<<arrRatingCanal[i];
        archReporte<<setw(17)<<right<<arrNroTotalReproCanales[i];
        archReporte<<setw(15)<<" "; imprimirTiempo(archReporte,arrTiempoTotalReproCanales[i],false);
        tarifaRating=filtrarRating(archReporte,arrRatingCanal[i]);
        ingresosPorRepro=((double)arrTiempoTotalReproCanales[i]/60.0)*tarifaDurEtiquetas*tarifaRating;
        archReporte<<setw(28)<<right<<ingresosPorRepro;
        archReporte<<endl;
    }
    imprimirLineas('=',130,archReporte);
    imprimirSubtituloEtiquetas(archReporte);
    for (int i=0;i<nroEtiquetas;i++) {
        imprimirNroOrden(archReporte,i+1);
        archReporte<<setw(13)<<right<<arrCodeEtiqueta[i];
        archReporte<<setw(6)<<" "; imprimirTiempo(archReporte,arrTiempoDurEtiqueta[i],true);
        archReporte<<setw(17)<<right<<arrCantTotalReproEtiquetas[i];
        archReporte<<setw(17)<<" "; imprimirTiempo(archReporte,arrTiempoTotalReproEtiquetas[i],false);
        archReporte<<endl;
    }
    imprimirLineas('=',130,archReporte);
}

double filtrarRating(ofstream &output,double rating) {
    if (rating>4 and rating<=5) {
        output<<setw(17)<<right<<"  30%";
        return 0.3;
    }else if (rating>3 and rating<=4) {
        output<<setw(17)<<right<<"  20%";
        return 0.2;
    }else if (rating>2 and rating<=3) {
        output<<setw(17)<<right<<"0%";
        return 0.0;
    }else if (rating>1 and rating<=2) {
        output<<setw(17)<<right<<"-25%";
        return 0.75;
    }
    return 0.0;
}

void imprimirNroOrden(ofstream& output,int nroOrden) {
    output.fill('0');
    output<<setw(2)<<right<<nroOrden<<")";
    output.fill(' ');
}

void imprimirSubtituloCanales(ofstream& output) {
    output<<"CANALES ADSCRITOS A LA PLATAFORMA"<<endl;
    imprimirLineas('-',130,output);
    output<<setw(40)<<" "<<"RATING DE"<<setw(7)<<" "<<"NUMERO TOTAL"<<setw(7)<<" "<<"TIEMPO TOTAL DE"<<
        setw(5)<<" "<<"PORCENTAJE POR"<<setw(5)<<" "<<" INGRESOS POR REPRODUCCION"<<endl;
    output<<"No."<<setw(5)<<" "<<"CODIGO"<<setw(5)<<" "<<"FECHA DE CREACION"<<setw(5)<<" "<<"CALIDAD"<<setw(5)<<" "<<
        "DE REPRODUCCIONES"<<setw(5)<<" "<<"REPRODUCCIONES"<<setw(5)<<" "<<"RATING DE CALIDAD"<<setw(10)<<" "<<"DE ETIQUETAS"<<endl;
}

void imprimirSubtituloEtiquetas(ofstream& output) {
    output<<"ETIQUETAS DE LA PLATAFORMA"<<endl;
    imprimirLineas('-',130,output);
    output<<setw(35)<<" "<<"CANTIDAD TOTAL"<<setw(10)<<" "<<"TIEMPO TOTAL DE"<<endl;
    output<<"No."<<setw(5)<<" "<<"ETIQUETA"<<setw(5)<<" "<<"DURACION"<<setw(5)<<" "<<"DE REPRODUCCIONES"<<setw(10)<<" "<<
        "REPRODUCIDO"<<endl;
}

void imprimirTituloReporte(ofstream& output,double tarifaDurEtiquetas) {
    output<<setw(50)<<" "<<"PLATAFORMA TP_Twitch"<<endl;
    output<<setw(25)<<" "<<"TARIFA POR DURACION DE LAS ETIQUETAS: "<<tarifaDurEtiquetas<<" POR CADA MINUTO Y FRACCION"<<endl;
    imprimirLineas('=',130,output);
}


int buscarCanales(char *arrCodeCharCanal,int *arrCodeIntCanal,
                char codeCharEtiquetaArch,int codeIntEtiquetaArch, int nroCanales) {
    for (int i = 0; i < nroCanales; i++)
        if (arrCodeCharCanal[i] == codeCharEtiquetaArch and arrCodeIntCanal[i] == codeIntEtiquetaArch) return i;
    return -1; //posicion de canal no encontrado
}

int buscarEtiquetas(int *arrCodeEtiqueta,int codeEtiquetaArch,int nroEtiquetas ) {
    for (int i = 0; i < nroEtiquetas; i++)
        if (arrCodeEtiqueta[i] == codeEtiquetaArch) return i;
    return -1;
}

void imprimirTituloRepEtiquetas(ofstream& output) {
    output<<setw(5)<<" "<<"REPORTE DE PRUEBA PARA ARCHIVO ETIQUETAS"<<endl;
    imprimirLineas('=',50,output);
    output << "ETIQUETA" <<setw(15)<<" "<< "DURACION" << endl;
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



void imprimirTituloRepCanales(ofstream& output) {
    output << setw(5)<<" "<<"REPORTE DE PRUEBA PARA EL ARCHIVO CANALES"<<endl;
    imprimirLineas('=',50,output);
    output << "FECHA" <<setw(15)<<" "<< "CODIGO" <<setw(10)<<" "<< "RATING" << endl;
}


void imprimirLineas(char c,int cant,ofstream& output) {
    for (int i = 0; i < cant; i++) output << c ;
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
