//
// Created by ASUS on 5/11/2025.
//

#include "FuncionesAuxiliares.h"

#include <format>

void aperturaArchivosLectura(const char* nombArch,ifstream& arch) {
    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"Error, el archivo "<<nombArch<<" no se puede abrir"<<endl;
        exit(1);
    }
}

void aperturaArchivosEscritura(const char* nombArch,ofstream& arch) {
    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout<<"Error, el archivo "<<nombArch<<" no se puede abrir"<<endl;
        exit(1);
    }
}

void cargarCategorias(const char *nombArch,
                     char **arrCodigoCategoria,char **arrNombreCategoria,int &cantCategorias) {
    //UM163F47   just_chatting
    ifstream input;
    aperturaArchivosLectura(nombArch,input);
    while (true) {
        arrCodigoCategoria[cantCategorias]=readString(input);
        if (input.eof()) break;
        arrNombreCategoria[cantCategorias]=readString(input);
        cantCategorias++;
    }
}

void probarCategorias(const char* nombArch,
                    char **arrCodigoCategoria,char **arrNombreCategoria,int cantCategorias) {
    ofstream output;
    aperturaArchivosEscritura(nombArch,output);
    imprimirCabeceraRepCat(output);
    for (int i=0;i<cantCategorias;i++) {
        output<<setw(5)<<" "<<setw(15)<<left<<arrCodigoCategoria[i];
        output<<setw(15)<<left<<arrNombreCategoria[i]<<endl;
    }
}

void cargarReproStreams(const char* nombArch,
                        int *arrFechaStream,char **arrNombreCanalStream,char **arrCodigoCanalStream,
                        double *arrRatingStream,double *arrDropStream,int *arrDurStream,int &cantStreams) {
    //31/8/2025  Sardoche    ZT132U54    4.410    0.715    1:41:48
    ifstream input;
    aperturaArchivosLectura(nombArch,input);
    int fechaStream,durStream;
    while (true) {
        fechaStream=leerFecha(input);
        if (input.eof()) break;
        arrNombreCanalStream[cantStreams]=readString(input);
        arrCodigoCanalStream[cantStreams]=readString(input);
        input>>arrRatingStream[cantStreams];
        input>>arrDropStream[cantStreams];
        durStream=leerTiempo(input);
        arrDurStream[cantStreams]=durStream;
        arrFechaStream[cantStreams]=fechaStream;
        cantStreams++;
    }
}

void generarArchivoEnlace(char* categoria,char* &nombArchivo,char* &enlace) {
    char formato[200];
    strcpy(formato,categoria);
    formato1(formato);

    nombArchivo=new char[strlen(formato)+24]{};
    enlace=new char[strlen(formato)+48]{};

    //nombArchivo[0]='\0'; ya no lo necesito gracias al {} en el new char
    strcat(nombArchivo,"ArchivoDeReportes/");
    strcat(nombArchivo,formato);
    strcat(nombArchivo,".txt");

    //enlace[0]='\0'; ya no lo necesito gracias al {} en el new char
    strcat(enlace,"https://Laboratorio06_2025_2/");
    strcat(enlace,"ArchivoDeReportes/");
    strcat(enlace,formato);


}

void formato1(char* fuente) {
    //xxx_yyyy_zzz --> Xxx_Yyyy_Zzz
    bool esPrimero=true;
    for (int i=0;fuente[i];i++) {
        if (esPrimero) {
            esPrimero=false;
            if (fuente[i]>='a' and fuente[i]<='z') {
                fuente[i]-='a'-'A';
            }
        }else {
            if (fuente[i]=='_') esPrimero=true;
        }
    }
}

void pruebaReproStreams(const char* nombArchRep,
                        int *arrFechaStream,char **arrNombreCanalStream,char **arrCodigoCanalStream,
                        double *arrRatingStream,double *arrDropStream,
                        int *arrDurStream,int cantStreams) {
    //31/8/2025  Sardoche    ZT132U54    4.410    0.715    1:41:48
    ofstream output;
    aperturaArchivosEscritura(nombArchRep,output);
    imprimirCabeceraRepPruebaStreams(output);
    output<<fixed<<setprecision(2);
    for (int i=0;i<cantStreams;i++) {
        imprimirFecha(output,arrFechaStream[i]);
        output<<setw(5)<<" "<<setw(15)<<left<<arrNombreCanalStream[i];
        output<<setw(10)<<right<<arrCodigoCanalStream[i];
        output<<setw(10)<<right<<arrRatingStream[i];
        output<<setw(10)<<right<<arrDropStream[i];
        output<<setw(5)<<" "; imprimirTiempo(output,arrDurStream[i]);
        output<<endl;
    }
}

void procesarReporte(char **arrCodigoCategoria,char **arrNombreCategoria,int cantCategorias,
                    int *arrFechaStream,char **arrNombreCanalStream,char **arrCodigoCanalStream,
                    double *arrRatingStream,double *arrDropStream,
                    int *arrDurStream,int cantStreams) {
    char* nombreArchivo[MAX_CATEGORIAS]{};
    char* enlace[MAX_CATEGORIAS]{};
    for (int i=0;i<cantCategorias;i++) {
        generarArchivoEnlace(arrNombreCategoria[i],nombreArchivo[i],enlace[i]);
        ofstream output;
        aperturaArchivosEscritura(nombreArchivo[i],output);
        output<<"Codigo: "<<arrCodigoCategoria[i]<<endl;
        output<<"Nombre: "<<arrNombreCategoria[i]<<endl;
        output<<"Enlace: "<<enlace[i]<<endl;
        output<<"REPRODUCCIONES: "<<endl;
        imprimirLineas('=',80,output);
        imprimirReporte(output,arrCodigoCategoria,
                        arrFechaStream,arrNombreCanalStream,arrCodigoCanalStream,
                        arrRatingStream,arrDropStream,arrDurStream,cantStreams,i);
    }
}

void imprimirReporte(ofstream& output,char** arrCodigoCategoria,
                    int *arrFechaStream,char **arrNombreCanalStream,char **arrCodigoCanalStream,
                    double *arrRatingStream,double *arrDropStream,
                    int *arrDurStream,int cantStreams,int i) {
    imprimirCabeceraReporteFinal(output);
    output<<fixed<<setprecision(2);
    double ratingPromedio=0.0,dropPromedio=0.0;
    int durTotal=0,cant=0;

    for (int k=0;k<cantStreams;k++) {
        if (strcmp(arrCodigoCategoria[i],arrCodigoCanalStream[k])==0) {
            imprimirFecha(output,arrFechaStream[k]);
            output<<setw(5)<<" "<<setw(20)<<left<<arrNombreCanalStream[k];
            output<<setw(9)<<right<<arrRatingStream[k];
            output<<setw(14)<<right<<arrDropStream[k];
            output<<setw(9)<<" ",imprimirTiempo(output,arrDurStream[k]);
            output<<endl;
            ratingPromedio+=arrRatingStream[k];
            dropPromedio+=arrDropStream[k];
            durTotal+=arrDurStream[k];
            cant++;
        }
    }
    imprimirResumen(output,ratingPromedio,dropPromedio,durTotal,cant);
}

void imprimirResumen(ofstream& output,double ratingPromedio,double dropPromedio,int durTotal,int cant) {
    imprimirLineas('=',80,output);
    output<<"PROMEDIO DE RATING:   "<<setw(15)<<right<<ratingPromedio/cant<<endl;
    output<<"PROMEDIO DE DROP-OFF: "<<setw(15)<<right<<dropPromedio/cant<<endl;
    output<<"DURACION TOTAL:       ";
    output<<setw(10)<<" "; imprimirTiempo(output,durTotal);
    output<<endl;
}

void imprimirCabeceraReporteFinal(ofstream& output) {
    output<<"FECHA";
    output<<setw(15)<<right<<"CANAL";
    output<<setw(25)<<right<<"RATING";
    output<<setw(15)<<right<<"DROP-OFF";
    output<<setw(15)<<right<<"DURACION"<<endl;
}

void imprimirCabeceraRepPruebaStreams(ofstream &output) {
    output<<setw(20)<<" "<<"REPORTE DE PRUEBA PARA STREAMS REPRODUCIDOS"<<endl;
    imprimirLineas('=',80,output);
    output<<"FECHA";
    output<<setw(16)<<right<<"NOMBRE";
    output<<setw(17)<<right<<"CODIGO";
    output<<setw(13)<<right<<"RATING";
    output<<setw(9)<<right<<"DROP";
    output<<setw(13)<<right<<"DURACION"<<endl;
    imprimirLineas('-',80,output);
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
void imprimirCabeceraRepCat(ofstream &output) {
    output<<setw(5)<<" "<<"REPORTE DE PRUEBA PARA CATEGORIAS"<<endl;
    imprimirLineas('=',50,output);
    output<<setw(11)<<right<<"CODIGO";
    output<<setw(18)<<right<<"CATEGORIA"<<endl;
    imprimirLineas('-',50,output);
}

void imprimirLineas(char c,int cant,ofstream & output) {
    for (int i=0;i<cant;i++) output<<c;
    output<<endl;
}

char* readString(ifstream& input) {
    char buffer[MAX_CARACTERES];
    input>>buffer;
    if (input.eof()) return nullptr;
    char* src=new char[strlen(buffer)+1];
    strcpy(src,buffer);
    return src;
}
