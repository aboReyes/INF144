//
// Created by ASUS on 12/11/2025.
//

#include "FuncionesAuxiliares.h"

void aperturaArchivoLectura(const char* nombArch,ifstream& arch) {
    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"ERROR, el archivo"<<nombArch<<" no se puede abrir"<<endl;
        exit(1);
    }
}

void aperturaArchivoEscritura(const char* nombArch,ofstream& arch) {
    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout<<"ERROR, el archivo"<<nombArch<<" no se puede abrir"<<endl;
        exit(1);
    }
}

void leerCategorias(const char* nombArch,
                    Categoria *arrCategorias,int &cantCategorias) {
    //UM163F47,just chatting
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    Categoria c;
    char* codigoCategoria; //Como es el primero que se lee, por "buenas prácticas" se realiza de esta forma:
    while (true) {
        codigoCategoria=readString(input,',');
        if (input.eof()) break;
        c.codigo=codigoCategoria;
        c.nombre=readString(input,'\n');
        arrCategorias[cantCategorias]=c;
        cantCategorias++;
    }
}

void pruebaCategorias(const char* nombArch,
                    Categoria *arrCategorias,int cantCategorias,
                    bool conReproducciones) {
    ofstream output;
    aperturaArchivoEscritura(nombArch,output);
    output<<setw(15)<<" "<<"REPORTE DE PRUEBA CATEGORIAS"<<endl;
    imprimirLineas('=',60,output);
    output<<fixed<<setprecision(2);
    for (int i=0;i<cantCategorias;i++) {
        output<<"Codigo: "<<setw(15)<<left<<arrCategorias[i].codigo<<endl;
        output<<"Nombre: "<<setw(15)<<left<<arrCategorias[i].nombre<<endl;
        imprimirLineas('-',60,output);
        if (conReproducciones) {
            imprimirCabeceraReproducciones(output);
            for (int j=0;j<arrCategorias[i].numReproducciones;j++) {
                output<<setw(25)<<left<<arrCategorias[i].reproducciones[j].canal;
                output<<arrCategorias[i].reproducciones[j].rating;
                output<<setw(10)<<" ";
                imprimirTiempo(output,arrCategorias[i].reproducciones[j].duracion);
                output<<endl;
            }
            imprimirLineas('=',60,output);
        }
    }
}

void imprimirCabeceraReproducciones(ofstream& output) {
    output<<"REPRODUCCIONES: "<<endl;
    output<<"CANAL";
    output<<setw(25)<<right<<"RATING";
    output<<setw(17)<<right<<"DURACION"<<endl;
}

void leerProcesarReproducciones(const char* nombArch,
                    Categoria *arrCategorias,int cantCategorias) {
    //Sardoche,ZT132U54,4.410,01:41:48
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    char* nombreCanal;
    char codigoCategoria[50];
    double rating;
    int durStream;
    while (true) {
        nombreCanal=readString(input,',');
        if (input.eof()) break;
        input.getline(codigoCategoria,50,',');
        rating=readDouble(input);
        durStream=leerTiempo(input);
        int pos=buscarCategoria(codigoCategoria,arrCategorias,cantCategorias);
        if (pos!=NO_ENCONTRADO) {
            int n=arrCategorias[pos].numReproducciones;
            arrCategorias[pos].reproducciones[n].canal=nombreCanal;
            arrCategorias[pos].reproducciones[n].rating=rating;
            arrCategorias[pos].reproducciones[n].duracion=durStream;
            arrCategorias[pos].numReproducciones++;
        }
    }
}

void calcularPromedioYDuracionesTotales(Categoria *arrCategorias,int cantCategorias){
    for (int i=0;i<cantCategorias;i++) {
        arrCategorias[i].duracionTotal=0;
        arrCategorias[i].promedioRating=0;
        for (int j=0;j<arrCategorias[i].numReproducciones;j++) {
            arrCategorias[i].promedioRating+=arrCategorias[i].reproducciones[j].rating;
            arrCategorias[i].duracionTotal+=arrCategorias[i].reproducciones[j].duracion;
        }
        arrCategorias[i].promedioRating/=arrCategorias[i].numReproducciones;
    }
}

void emitirReporte(const char* nombArchRep,
                    Categoria *arrCategorias,int cantCategorias) {
    ofstream output;
    aperturaArchivoEscritura(nombArchRep,output);
    output<<setw(15)<<" "<<"REPORTE DE PRUEBA CATEGORIAS"<<endl;
    imprimirLineas('=',60,output);
    output<<fixed<<setprecision(2);
    for (int i=0;i<cantCategorias;i++) {
        output<<"Codigo: "<<setw(15)<<left<<arrCategorias[i].codigo<<endl;
        output<<"Nombre: "<<setw(15)<<left<<arrCategorias[i].nombre<<endl;
        imprimirLineas('-',60,output);
        imprimirCabeceraReproducciones(output);
        for (int j=0;j<arrCategorias[i].numReproducciones;j++) {
            output<<setw(25)<<left<<arrCategorias[i].reproducciones[j].canal;
            output<<arrCategorias[i].reproducciones[j].rating;
            output<<setw(10)<<" ";
            imprimirTiempo(output,arrCategorias[i].reproducciones[j].duracion);
            output<<endl;
        }
        imprimirLineas('-',60,output);
        output<<"RATING PROMEDIO: "<<setw(13)<<right<<arrCategorias[i].promedioRating<<endl;
        output<<"DURACION TOTAL: "<<setw(10)<<" ";
        imprimirTiempo(output,arrCategorias[i].duracionTotal);
        output<<endl;
        imprimirLineas('=',60,output);
    }
}

int buscarCategoria(char *codigoCategoria,Categoria *arrCategorias,
                    int cantCategorias) {
    for (int i=0;i<cantCategorias;i++)
        if (strcmp(codigoCategoria,arrCategorias[i].codigo)==0) return i;
    return NO_ENCONTRADO;
}

void imprimirLineas(char c,int cant,ofstream& output) {
    for (int i=0;i<cant;i++) output<<c;
    output<<endl;
}

int leerTiempo(ifstream& input) {
    int hh,mm,ss;
    char c;
    input>>hh>>c>>mm>>c>>ss;
    input.get();
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


int readInt(ifstream& input) {
    int i;
    input>>i;
    input.get();
    return i;
}

double readDouble(ifstream& input) {
    double d;
    input>>d;
    input.get();
    return d;
}

char *readString(ifstream& input,char delimitador) {
    char buffer[MAX_CARACTERES];
    input.getline(buffer,MAX_CARACTERES,delimitador);
    if (input.eof()) return nullptr;
    char *src=new char[strlen(buffer)+1];
    strcpy(src,buffer);
    return src;
}
