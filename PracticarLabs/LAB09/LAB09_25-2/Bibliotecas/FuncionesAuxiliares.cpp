//
// Created by ASUS on 19/11/2025.
//


#include "FuncionesAuxiliares.h"

#include <cstring>

void aperturaArchivoLectura(const char*nombArch,ifstream&arch) {
    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"Error, no se puede abrir el archivo"<<nombArch<<endl;
        exit(1);
    }
}

void aperturaArchivoEscritura(const char*nombArch,ofstream&arch) {
    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout<<"Error, no se puede abrir el archivo"<<nombArch<<endl;
        exit(1);
    }
}

void leerCategorias(const char* nombArch,
                    Categoria *arrCategoria,int &cantidadCategorias) {
    //UM163F47,just chatting,Casual conversations; reactions; and hangouts without a main game.
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    char *codigoCategoria;
    while (true) {
        codigoCategoria=leerCadena(input,',',20);
        if (input.eof() or codigoCategoria==nullptr) break;
        arrCategoria[cantidadCategorias].codigo=asignarCadena(codigoCategoria);
        arrCategoria[cantidadCategorias].nombre=leerCadena(input,',',50);
        arrCategoria[cantidadCategorias].descripcion=leerCadena(input,'\n',150);
        //las inicializaciones:
        arrCategoria[cantidadCategorias].reproducciones=new Reproduccion[15]{};
        arrCategoria[cantidadCategorias].promedioRating=0.0;
        arrCategoria[cantidadCategorias].duracionTotal=0;
        cantidadCategorias++;
    }
}

void pruebaCategorias(const char* nombArchRep,
                    Categoria *arrCategoria,int cantidadCategorias,
                    bool conRepro,bool conComent) {
    ofstream output;
    aperturaArchivoEscritura(nombArchRep,output);
    output<<setw(38)<<" "<<"REPORTE POR CATEGORIAS"<<endl;
    imprimirLineas('=',100,output);
    output<<fixed<<setprecision(2);
    for (int i=0;i<cantidadCategorias;i++) {
        output<<"Codigo: "<<setw(5)<<" "<<arrCategoria[i].codigo<<endl;
        output<<"Nombre: "<<setw(5)<<" "<<arrCategoria[i].nombre<<endl;
        output<<"Descripcion: "<<arrCategoria[i].descripcion<<endl;
        imprimirLineas('-',100,output);
        if (conRepro) {
            output<<"REPRODUCCIONES:"<<endl;
            for (int j=0;j<arrCategoria[i].numReproducciones;j++) {
                output<<"CANAL: "<<setw(20)<<left<<arrCategoria[i].reproducciones[j].canal;
                output<<"RATING: "<<setw(5)<<right<<arrCategoria[i].reproducciones[j].rating;
                output<<setw(15)<<right<<"DURACION: ";
                imprimirHora(output,arrCategoria[i].reproducciones[j].duracion);
                output<<endl;
                if (conComent) {
                    output<<setw(3)<<" "<<"COMENTARIOS:"<<endl;
                    for (int k=0;k<arrCategoria[i].reproducciones[j].numComentarios;k++) {
                        output<<setw(3)<<" "<<"- "<<arrCategoria[i].reproducciones[j].comentarios[k]<<endl;
                    }
                }
            }
            imprimirLineas('=',100,output);
        }
    }
}

void leerStreamsReproducidos(const char* nombArch,
                            Categoria *arrCategoria,int cantidadCategorias) {
    //Sardoche,ZT132U54,4.410,01:41:48
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    char *nombreCanal,*codigoCategoria;
    double rating;
    int duracion;
    while (true) {
        nombreCanal=leerCadena(input,',',50);
        if (input.eof() or nombreCanal==nullptr) break;
        codigoCategoria=leerCadena(input,',',20);
        rating=leerDouble(input);
        duracion=leerHora(input);
        int posCanal=buscarCanal(codigoCategoria,arrCategoria,cantidadCategorias);
        if (posCanal!=NO_ENCONTRADO) {
            int n=arrCategoria[posCanal].numReproducciones;
            arrCategoria[posCanal].reproducciones[n].canal=asignarCadena(nombreCanal);
            arrCategoria[posCanal].reproducciones[n].rating=rating;
            arrCategoria[posCanal].reproducciones[n].duracion=duracion;
            arrCategoria[posCanal].numReproducciones++;
        }
    }
}

void ordenarDatos(Categoria *arrCategoria,int cantidadCategorias) {
    for (int i=0;i<cantidadCategorias-1;i++) {
        for (int j=i+1;j<cantidadCategorias;j++) {
            if (strcmp(arrCategoria[i].nombre,arrCategoria[j].nombre)>0) {
                swapStruct(arrCategoria[i],arrCategoria[j]);
            }
        }
    }
}

void leerComentarios(const char* nombArch,
                    Categoria *arrCategoria,int cantidadCategorias) {
    //LCK,this is the problem with d1 rewards no consumables
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    char *nombreCanalLeido;
    char* comentarios;
    while (true) {
        nombreCanalLeido=leerCadena(input,',',50);
        if (input.eof() or nombreCanalLeido==nullptr) break;
        comentarios=leerCadena(input,'\n',200);
        for (int i=0;i<cantidadCategorias;i++) {
            for (int j=0;j<arrCategoria[i].numReproducciones;j++) {
                if (strcmp(nombreCanalLeido,arrCategoria[i].reproducciones[j].canal)==0) {
                    int n=arrCategoria[i].reproducciones[j].numComentarios;
                    arrCategoria[i].reproducciones[j].comentarios[n]=asignarCadena(comentarios);
                    arrCategoria[i].reproducciones[j].numComentarios++;
                }
            }
        }
    }
}

void swapStruct(Categoria &dato1,Categoria&dato2) {
    Categoria aux;
    aux=dato1;
    dato1=dato2;
    dato2=aux;
}

int buscarCanal(char* codigoCategoria,Categoria *arrCategoria,int cantidadCategorias) {
    for (int i=0;i<cantidadCategorias;i++)
        if (strcmp(codigoCategoria,arrCategoria[i].codigo)==0) return i;
    return NO_ENCONTRADO;
}

double leerDouble(ifstream& input) {
    double d;
    input>>d;
    input.get();
    return d;
}

void imprimirLineas(char c,int cant,ofstream& output) {
    for (int i=0;i<cant;i++) output<<c;
    output<<endl;
}

int leerHora(ifstream& input) {
    int hh,mm,ss;
    char c;
    input>>hh>>c>>mm>>c>>ss;
    input.get();
    return hh*3600+mm*60+ss;
}

void imprimirHora(ofstream& output,int tiempo) {
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

char* leerCadena(ifstream& input,char delimitador,int n) {
    char buffer[n];
    input.getline(buffer,n,delimitador);
    if (input.eof()) return nullptr;
    char* src=new char[strlen(buffer)+1];
    strcpy(src,buffer);
    return src;
}

char* asignarCadena(char* fuente) {
    char *src=new char[strlen(fuente)+1];
    strcpy(src,fuente);
    return src;
}
