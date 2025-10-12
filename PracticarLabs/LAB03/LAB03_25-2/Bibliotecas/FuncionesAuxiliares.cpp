//
// Created by ASUS on 12/10/2025.
//

#include "FuncionesAuxiliares.h"

void aperturaArchivoLectura(const char* nombArch,ifstream& arch) {
    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"ERROR: el archivo "<<nombArch<<" no se puede abrir"<<endl;
        exit(1);
    }
}

void aperturaArchivoEscritura(const char* nombArch,ofstream& arch) {
    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout<<"ERROR: el archivo "<<nombArch<<" no se puede abrir"<<endl;
        exit(1);
    }
}

void generarReporte(const char* nombArchCanales,
                    const char* nombArchEtiquetas,
                    const char* nombArchReproEtiquetas,
                    const char* nombArchReporte) {
    ifstream archCanales,archEtiquetas,archReproEtiquetas;
    ofstream archRep;
    aperturaArchivoLectura(nombArchCanales,archCanales);
    aperturaArchivoLectura(nombArchEtiquetas,archEtiquetas);
    aperturaArchivoLectura(nombArchReproEtiquetas,archReproEtiquetas);
    aperturaArchivoEscritura(nombArchReporte,archRep);

    double tarifaDur=0.78;
    //leerTarifa(tarifaDur); harcode

    archRep<<fixed<<setprecision(2);
    imprimirTituloReporte(archRep,tarifaDur);
    char letraCodCanal;
    int numCodCanal,etiqueta,cantCanales=0;
    while (true) {
        leerImprimirDatosCanales(archCanales,archEtiquetas,archReproEtiquetas,archRep,
                                letraCodCanal,numCodCanal,etiqueta,tarifaDur,cantCanales);
        if (archCanales.eof()) break;
    }
}

void leerImprimirDatosCanales(ifstream &archCanales,ifstream&archEtiquetas,
                                ifstream& archReproEtiquetas,ofstream& archRep,
                                char &letraCodCanal,int &numCodCanal,int &etiqueta,
                                double tarifaDur,int &cantCanales) {
    //21/02/2023      S6846      summit1g      4.8      866146-380174-770185
    int fechaCreCanal,cantEtiquetas,tiempoTotalGlobal;
    double ratingCanal;
    char c;
    while (true) {
        fechaCreCanal=leerFecha(archCanales);
        if (archCanales.eof()) break;
        cantCanales++;
        archRep<<"CANAL No. "<<setw(4)<<right<<cantCanales<<endl;
        archCanales>>letraCodCanal>>numCodCanal;
        imprimirSubtituloDatosCanales(archRep);
        archRep<<setw(4)<<" ";
        leerImprimirNombreVarios(archCanales,archRep,20,' ',true);
        archRep<<letraCodCanal<<numCodCanal;
        archRep<<setw(6)<<" "; imprimirFecha(archRep,fechaCreCanal);
        archCanales>>ratingCanal;
        archRep<<setw(12)<<right<<ratingCanal<<endl;
        imprimirLineas('-',130,archRep);
        cantEtiquetas=0;
        tiempoTotalGlobal=0;
        imprimirSubtituloEtiquetasReproducidas(archRep);
        while (true) {
            archCanales>>etiqueta;
            c=archCanales.get();
            tiempoTotalGlobal+=procesarEtiquetasReproducidas(archReproEtiquetas,archEtiquetas,archRep,
                                            letraCodCanal,numCodCanal,
                                            etiqueta,cantEtiquetas);
            if (c=='\n') break;
        }
        imprimirLineas('-',130,archRep);
        imprimirResumen(archRep,tiempoTotalGlobal,ratingCanal,tarifaDur);
        imprimirLineas('=',130,archRep);
    }

}

void imprimirResumen(ofstream& archRep,int tiempoTotalGlobal,double ratingCanal,
                    double tarifaDur) {
    archRep<<"TIEMPO TOTAL DE REPRODUCCIONES DE ETIQUETAS: ";
    imprimirTiempo(archRep,tiempoTotalGlobal,false);
    archRep<<endl;
    archRep<<"PORCENTAJE POR RATING DE CALIDAD: ";
    double rating=filtrarRating(archRep,ratingCanal);
    double ingresosRepEti=((double)tiempoTotalGlobal/60.0)*rating*tarifaDur;
    archRep<<"INGRESOS POR REPRODUCCION DE ETIQUETAS: "<<setw(12)<<right<<ingresosRepEti<<endl;
}

double filtrarRating(ofstream& archRep,double rating) {
    if (rating>4 and rating<=5) {
        archRep<<setw(15)<<right<<"+30%"<<endl;
        return 1.3;
    }else if (rating>3 and rating<=4) {
        archRep<<setw(15)<<right<<"+20%"<<endl;
        return 1.2;
    }else if (rating>2 and rating<=3) {
        archRep<<setw(15)<<right<<"0%"<<endl;
        return 0.0;
    }else if (rating>1 and rating<=2) {
        archRep<<setw(15)<<right<<"-25%"<<endl;
        return 0.75;
    }
    return 0;
}

int procesarEtiquetasReproducidas(ifstream& archReproEtiquetas,ifstream&archEtiquetas,
                                ofstream& archRep,char letraCodCanal,int numCodCanal,
                                int etiqueta,int &cantEtiquetas) {
    //28/02/2025  E6696      888106      244
    int fechaRegEtiqueta,cantRepro,numCodCanalArch,etiquetaArch,durEtiqueta;
    int tiempoTotalReproducido,tiempoTotalGlobal=0;
    char letraCodCanalArch;
    archReproEtiquetas.clear();
    archReproEtiquetas.seekg(0,ios::beg);
    while (true) {
        fechaRegEtiqueta=leerFecha(archReproEtiquetas);
        if (archReproEtiquetas.eof()) break;
        archReproEtiquetas>>letraCodCanalArch>>numCodCanalArch>>etiquetaArch>>cantRepro;
        if (letraCodCanalArch==letraCodCanal and
            numCodCanalArch==numCodCanal and
            etiquetaArch==etiqueta) {
            cantEtiquetas++;
            imprimirOrden(archRep,cantEtiquetas);
            archRep<<setw(5)<<" "; imprimirFecha(archRep,fechaRegEtiqueta);
            archRep<<setw(10)<<right<<etiquetaArch;
            durEtiqueta=buscarEtiquetas(archEtiquetas,archRep,etiquetaArch);
            archRep<<setw(23)<<right<<cantRepro;
            tiempoTotalReproducido=durEtiqueta*cantRepro;
            archRep<<setw(27)<<" "; imprimirTiempo(archRep,tiempoTotalReproducido,false);
            archRep<<endl;
            tiempoTotalGlobal+=tiempoTotalReproducido;
            return tiempoTotalGlobal;
        }else {
            while (archReproEtiquetas.get()!='\n');
        }
    }
    return 0;
}



void imprimirOrden(ofstream& archRep,int nroOrden) {
    archRep<<setw(3)<<" ";
    archRep.fill('0');
    archRep<<setw(2)<<right<<nroOrden<<")";
    archRep.fill(' ');
}

int buscarEtiquetas(ifstream& archEtiquetas,ofstream&archRep,
                    int etiquetaArch) {
    //803100    dropsenabled   01:27
    int etiquetaArch2,durEtiqueta;
    archEtiquetas.clear();
    archEtiquetas.seekg(0,ios::beg);
    while (true) {
        archEtiquetas>>etiquetaArch2;
        if (archEtiquetas.eof()) break;
        if (etiquetaArch2==etiquetaArch) {
            archRep<<setw(6)<<" ";
            leerImprimirNombreVarios(archEtiquetas,archRep,20,' ',false);
            durEtiqueta=leerTiempo(archEtiquetas);
            imprimirTiempo(archRep,durEtiqueta,true);
            return durEtiqueta;
        }else {
            while (archEtiquetas.get()!='\n');
        }
    }
    return 0;
}


void imprimirSubtituloEtiquetasReproducidas(ofstream& archRep) {
    archRep<<"ETIQUETAS REPRODUCIDAS:"<<endl;
    archRep<<setw(6)<<right<<"No.";
    archRep<<setw(10)<<right<<"FECHA";
    archRep<<setw(17)<<right<<"ETIQUETA";
    archRep<<setw(15)<<right<<"DESCRIPCION";
    archRep<<setw(15)<<right<<"DURACION";
    archRep<<setw(35)<<right<<"CANTIDAD DE REPRODUCCIONES";
    archRep<<setw(30)<<right<<"TIEMPO TOTAL REPRODUCIDO"<<endl;
}

void imprimirSubtituloDatosCanales(ofstream& archRep) {
    archRep<<setw(10)<<right<<"NOMBRE";
    archRep<<setw(20)<<right<<"CODIGO";
    archRep<<setw(14)<<right<<"CREADO EL";
    archRep<<setw(20)<<right<<"RATING DE CALIDAD"<<endl;
}

void imprimirTituloReporte(ofstream& archRep,double tarifaDur) {
    archRep<<setw(55)<<" "<<"PLATAFORMA TP_Twitch"<<endl;
    archRep<<setw(30)<<" "<<"TARIFA POR DURACION DE LAS ETIQUETAS: "<<tarifaDur;
    archRep<<" POR CADA MINUTO Y FRACCION"<<endl;
    imprimirLineas('=',130,archRep);
}

void imprimirLineas(char c,int cant,ofstream& archRep) {
    for (int i=0;i<cant;i++) archRep<<c;
    archRep<<endl;
}

void leerTarifa(double &tarifaDur) {
    cout<<"Ingrese tarifa por duracion de las etiquetas: ";
    cin>>tarifaDur;
}
void leerImprimirNombreVarios(ifstream& input,ofstream& output,
                            int tam,char delimitador,bool mayus) {
    char c;
    int cantEspaciosBlanco=0;
    input>>ws;
    while (true) {
        c=input.get();
        if (c==delimitador) break;
        if (mayus) {
            if (c>='a' and c<='z') c=c-32;
        }
        output<<c;
        cantEspaciosBlanco++;
    }
    output<<setw(tam-cantEspaciosBlanco)<<" ";
}


int leerTiempo(ifstream& input) {
    int mm,ss; //solo leemos ese caso
    char c;
    input>>mm>>c>>ss;
    return mm*60+ss;
}

void imprimirTiempo(ofstream& output,int tiempo,bool esMinuto) {
    int hh,mm,ss;
    hh=tiempo/3600;
    tiempo=tiempo%3600;
    mm=tiempo/60;
    tiempo=tiempo%60;
    ss=tiempo;
    output.fill('0');
    if (esMinuto) {
        output<<setw(2)<<right<<mm<<":";
        output<<setw(2)<<right<<ss;
    }else {
        output<<setw(2)<<right<<hh<<":";
        output<<setw(2)<<right<<mm<<":";
        output<<setw(2)<<right<<ss;
    }
    output.fill(' ');
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
