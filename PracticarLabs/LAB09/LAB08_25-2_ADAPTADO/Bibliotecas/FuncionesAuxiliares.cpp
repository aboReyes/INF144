//
// Created by ASUS on 16/11/2025.
//

#include "FuncionesAuxiliares.h"


void aperturaArchivoLectura(const char* nombArch,ifstream& arch) {
    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"Error, no se pudo abrir el archivo"<<nombArch<<endl;
        exit(1);
    }
}

void aperturaArchivoEscritura(const char* nombArch,ofstream& arch) {
    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout<<"Error, no se pudo abrir el archivo"<<nombArch<<endl;
        exit(1);
    }
}

//Modulo Forma1:
void cargarCategorias1(const char* nombArch,
                    Categoria *arrCategorias,int &cantidadCategorias) {
    //UM163F47,just chatting
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    char *codigo;
    while (true) {
        codigo=leerCadena(input,',',20);
        if (input.eof() or codigo==nullptr) break;
        arrCategorias[cantidadCategorias].codigo=asignarCadena(codigo);
        arrCategorias[cantidadCategorias].nombre=leerCadena(input,'\n',50);
        formato2(arrCategorias[cantidadCategorias].nombre);
        arrCategorias[cantidadCategorias].reproducciones=new Reproduccion[15];
        arrCategorias[cantidadCategorias].numReproducciones=0;
        arrCategorias[cantidadCategorias].promedioRating=0.0;
        arrCategorias[cantidadCategorias].duracionTotal=0;
        cantidadCategorias++;
    }
}

//1:00

//Modulo Forma2:

/*void cargarCategorias2(const char* nombArch,
                    Categoria *&arrCategorias,int &cantidadCategorias) {
    //UM163F47,just chatting
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    arrCategorias=new Categoria [MAX_CATEGORIAS];
    char *codigo;
    while (true) {
        codigo=leerCadena(input,',',20);
        if (input.eof() or codigo==nullptr) break;
        arrCategorias[cantidadCategorias].codigo=asignarCadena(codigo);
        arrCategorias[cantidadCategorias].nombre=leerCadena(input,'\n',50);
        arrCategorias[cantidadCategorias].reproducciones=new Reproduccion[15];
        cantidadCategorias++;
    }
}*/

void cargarReproducciones(const char* nombArch,
                        Categoria *arrCategorias,int cantidadCategorias) {
    //Sardoche,ZT132U54,4.410,01:41:48
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    char *nombreCanal;
    char codigoReproduccion[20];
    double rating;
    int duracion;
    while (true) {
        nombreCanal=leerCadena(input,',',50);
        if (input.eof() or nombreCanal==nullptr) break;
        input.getline(codigoReproduccion,20,',');
        rating=leerDouble(input);
        duracion=leerTiempo(input);
        int posCanal=buscarCanal(codigoReproduccion,arrCategorias,cantidadCategorias);
        if (posCanal!=NO_ENCONTRADO) {
            int n=arrCategorias[posCanal].numReproducciones;
            arrCategorias[posCanal].reproducciones[n].canal=asignarCadena(nombreCanal);
            formato2(arrCategorias[posCanal].reproducciones[n].canal);
            arrCategorias[posCanal].reproducciones[n].rating=rating;
            arrCategorias[posCanal].reproducciones[n].duracion=duracion;
            arrCategorias[posCanal].numReproducciones++;
        }
       delete[] nombreCanal; //opcional, pero sirve para liberar memoria
    }
}

void reportePruebaCategorias(const char* nombArchRep,
                            Categoria *arrCategorias,int cantidadCategorias,bool conRepro) {
    ofstream output;
    aperturaArchivoEscritura(nombArchRep,output);
    output<<setw(15)<<" "<<"REPORTE POR CATEGORIAS"<<endl;
    imprimirLineas('=',50,output);
    output<<fixed<<setprecision(2);
    for (int i=0;i<cantidadCategorias;i++) {
        output<<"Codigo: "<<arrCategorias[i].codigo<<endl;
        output<<"Nombre: "<<arrCategorias[i].nombre<<endl;
        imprimirLineas('-',50,output);
        if (conRepro) {
            output<<"REPRODUCCIONES: "<<endl;
            output<<"CANAL"<<setw(25)<<right<<"RATING"<<setw(17)<<right<<"DURACION"<<endl;
            for (int j=0;j<arrCategorias[i].numReproducciones;j++) {
                output<<setw(25)<<left<<arrCategorias[i].reproducciones[j].canal;
                output<<arrCategorias[i].reproducciones[j].rating;
                output<<setw(10)<<" ";
                imprimirTiempo(output,arrCategorias[i].reproducciones[j].duracion);
                output<<endl;
            }
            imprimirLineas('-',50,output);
        }
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
    strcat(enlace,"https://Laboratorio08_2025_2/");
    strcat(enlace,"ArchivoDeReportes/");
    strcat(enlace,formato);
}

void emitirReporte2(Categoria * arrCategorias,int cantidadCategorias) {
    char* nombreArchivo,*enlace;
    for (int i=0;i<cantidadCategorias;i++) {
        ofstream output;
        generarArchivoEnlace(arrCategorias[i].nombre,nombreArchivo,enlace);
        aperturaArchivoEscritura(nombreArchivo,output);
        output<<fixed<<setprecision(2);
        output<<setw(15)<<" "<<"REPORTE POR CATEGORIA:"<<endl;
        imprimirLineas('=',50,output);
        output<<"Codigo: "<<arrCategorias[i].codigo<<endl;
        output<<"Nombre: "<<arrCategorias[i].nombre<<endl;
        output<<"Enlace: "<<enlace<<endl;
        imprimirLineas('-',50,output);
        output<<"REPRODUCCIONES: "<<endl;
        output<<"CANAL"<<setw(25)<<right<<"RATING"<<setw(17)<<right<<"DURACION"<<endl;
        for (int j=0;j<arrCategorias[i].numReproducciones;j++) {
            output<<setw(25)<<left<<arrCategorias[i].reproducciones[j].canal;
            output<<arrCategorias[i].reproducciones[j].rating;
            output<<setw(10)<<" ";
            imprimirTiempo(output,arrCategorias[i].reproducciones[j].duracion);
            output<<endl;
        }
        imprimirLineas('-',50,output);
        imprimirResumen(output,arrCategorias[i]);
        imprimirLineas('=',50,output);
    }
}

void ordenarRating(Categoria *arrCategorias,int cantidadCategorias) {
    for (int i=0;i<cantidadCategorias;i++) {
        for (int j=0;j<arrCategorias[i].numReproducciones-1;j++) {
            for (int k=j+1;k<arrCategorias[i].numReproducciones;k++) {
                if (arrCategorias[i].reproducciones[j].rating>arrCategorias[i].reproducciones[k].rating) {
                    swapRepro(arrCategorias[i].reproducciones[j],arrCategorias[i].reproducciones[k]);
                }
            }
        }
    }
}

void ordenarNombres(Categoria *arrCategorias,int cantidadCategorias) {
    for (int i=0;i<cantidadCategorias;i++) {
        for (int j=0;j<arrCategorias[i].numReproducciones-1;j++) {
            for (int k=j+1;k<arrCategorias[i].numReproducciones;k++) {
                if (strcmp(arrCategorias[i].reproducciones[j].canal,arrCategorias[i].reproducciones[k].canal)>0) {
                    swapRepro(arrCategorias[i].reproducciones[j],arrCategorias[i].reproducciones[k]);
                }
            }
        }
    }
}

void swapRepro(Reproduccion&dato1,Reproduccion&dato2) {
    Reproduccion aux;
    aux=dato1;
    dato1=dato2;
    dato2=aux;
}

void formato2(char* nombre) {
    for (int i=0;nombre[i];i++) {
        if (nombre[i]>='a' and nombre[i]<='z') nombre[i]-='a'-'A';
    }
}

void formato1(char* nombre) {
    //xxx_yyyy_zzz --> Xxx_Yyyy_Zzz
    bool esPrimero=true;
    for (int i=0;nombre[i];i++) {
        if (esPrimero) {
            esPrimero=false;
            if (nombre[i]>='a' and nombre[i]<='z') {
                nombre[i]=nombre[i]-32;
            }
        }else {
            if (nombre[i]=='_') esPrimero=true;
        }
    }
}

void calcularTotalesYPromedios(Categoria *arrCategorias,int cantidadCategorias) {
    for (int i=0;i<cantidadCategorias;i++) {
        arrCategorias[i].duracionTotal=0;
        arrCategorias[i].promedioRating=0;
        for (int j=0;j<arrCategorias[i].numReproducciones;j++) {
            arrCategorias[i].duracionTotal+=arrCategorias[i].reproducciones[j].duracion;
            arrCategorias[i].promedioRating+=arrCategorias[i].reproducciones[j].rating;
        }
        arrCategorias[i].promedioRating/=arrCategorias[i].numReproducciones;
    }
}

void ordenarCategorias(Categoria *arrCategorias,int cantidadCategorias) {
    for (int i=0;i<cantidadCategorias-1;i++) {
        for (int j=0;j<cantidadCategorias;j++) {
            if (arrCategorias[i].promedioRating>arrCategorias[j].promedioRating) {
                swapStruct(arrCategorias[i],arrCategorias[j]);
            }
        }
    }
}

/*strcmp(arrCategorias[i].codigo,arrCategorias[j].codigo)<0 or
                strcmp(arrCategorias[i].codigo,arrCategorias[j].codigo)==0 and*/

void emitirReporte(const char* nombArchRep,
                    Categoria *arrCategorias,int cantidadCategorias) {
    ofstream output;
    aperturaArchivoEscritura(nombArchRep,output);
    output<<setw(15)<<" "<<"REPORTE POR CATEGORIAS"<<endl;
    imprimirLineas('=',50,output);
    output<<fixed<<setprecision(2);
    for (int i=0;i<cantidadCategorias;i++) {
        output<<"Codigo: "<<arrCategorias[i].codigo<<endl;
        output<<"Nombre: "<<arrCategorias[i].nombre<<endl;
        imprimirLineas('-',50,output);
        output<<"REPRODUCCIONES: "<<endl;
        output<<"CANAL"<<setw(25)<<right<<"RATING"<<setw(17)<<right<<"DURACION"<<endl;
        for (int j=0;j<arrCategorias[i].numReproducciones;j++) {
            output<<setw(25)<<left<<arrCategorias[i].reproducciones[j].canal;
            output<<arrCategorias[i].reproducciones[j].rating;
            output<<setw(10)<<" ";
            imprimirTiempo(output,arrCategorias[i].reproducciones[j].duracion);
            output<<endl;
        }
        imprimirLineas('-',50,output);
        imprimirResumen(output,arrCategorias[i]);
        imprimirLineas('=',50,output);
    }
}

void imprimirResumen(ofstream& output,Categoria &categoria) {
    output<<"RATING PROMEDIO: "<<setw(15)<<right<<categoria.promedioRating<<endl;
    output<<"DURACION TOTAL: "<<setw(11)<<" ";
    imprimirTiempo(output,categoria.duracionTotal);
    output<<endl;
}

void swapStruct(Categoria &dato1,Categoria &dato2) {
    Categoria aux;
    aux=dato1;
    dato1=dato2;
    dato2=aux;
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

int buscarCanal(char *codigoReproduccion,Categoria *arrCategorias,int cantidadCategorias) {
    for (int i=0;i<cantidadCategorias;i++)
        if (strcmp(codigoReproduccion,arrCategorias[i].codigo)==0) return i;
    return NO_ENCONTRADO;
}

double leerDouble(ifstream& input) {
    double d;
    input>>d;
    input.get();
    return d;
}

int leerEntero(ifstream& input) {
    int i;
    input>>i;
    input.get();
    return i;
}

char* asignarCadena(char *origen) {
    char*src=new char[strlen(origen)+1];
    strcpy(src,origen);
    return src;
}

char* leerCadena(ifstream& input,char delimitador,int n) {
    char buffer[n];
    input.getline(buffer,n,delimitador);
    if (input.eof()) return nullptr;
    char* src=new char [strlen(buffer)+1];
    strcpy(src,buffer);
    return src;
}
