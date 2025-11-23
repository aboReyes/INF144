
//
// Created by aml on 21/11/2025.
//

#include "FuncionesAuxiliares.h"


void aperturaArchivoLectura(const char* nombArch,ifstream& arch) {
    arch.open(nombArch,ios::in);
    if(!arch.is_open()) {
        cout << "Error al abrir el archivo" << nombArch<<endl;
        exit(1);
    }
}

void aperturaArchivoEscritura(const char* nombArch,ofstream& arch) {
    arch.open(nombArch,ios::out);
    if(!arch.is_open()) {
        cout << "Error al abrir el archivo" << nombArch<<endl;
        exit(1);
    }
}

void leerLibros(const char* arch,
                Libro *arrLibros,int &cantidadLibros) {
    //QV96140,El Duque en su territorio,Fiorella Florencio Polo,12,37.47
    ifstream input;
    aperturaArchivoLectura(arch,input);
    char *codigoLibro;
    while (true) {
        codigoLibro=leerCadena(input,',',20);
        if (input.eof() or codigoLibro==nullptr) break;
        arrLibros[cantidadLibros].codigo=asignarCadena(codigoLibro);
        arrLibros[cantidadLibros].titulo=leerCadena(input,',',100);
        arrLibros[cantidadLibros].autor=leerCadena(input,',',100);
        arrLibros[cantidadLibros].cantidad=leerEntero(input);
        arrLibros[cantidadLibros].precio=leerDouble(input);
        arrLibros[cantidadLibros].usuarios=new UsuarioConElLibro[20];
        cantidadLibros++;
    }
}

void pruebaLibros(const char* nombArc,
                            Libro *arrLibros,int cantidadLibros) {
    ofstream output;
    aperturaArchivoEscritura(nombArc,output);

}

void leerUsuarios(const char* nombArch,
                Usuario *arrUsuarios,int &cantidadUsuarios) {
    //54393647,Reyes Tang Edward,V,13.00
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    int dni;
    while (true) {
        dni=leerEntero(input);
        if (input.eof()) break;
        arrUsuarios[cantidadUsuarios].dni=dni;
        arrUsuarios[cantidadUsuarios].nombre=leerCadena(input,',',100);
        arrUsuarios[cantidadUsuarios].categoria=leerChar(input);
        arrUsuarios[cantidadUsuarios].calificacion=leerDouble(input);
        arrUsuarios[cantidadUsuarios].libros=new LibroEnSuPoder[6];
        cantidadUsuarios++;
    }
}

char leerChar(ifstream& input) {
    char c;
    input>>c;
    input.get();
    return c;
}


int leerFecha(ifstream& input) {
    int dd,mm,aa;
    char c;
    input>>dd>>c>>mm>>c>>aa;
    input.get();
    return aa*10000+mm*100+dd;
}

void imprimirFecha(ofstream& output,int fecha) {
    int dd,mm,aa;
    aa=fecha/10000;
    fecha=fecha%10000;
    mm=fecha/100;
    fecha=fecha%100;
    dd=fecha;
    output.fill('0');
    output<<setw(2)<<right<<dd<<"/";
    output<<setw(2)<<right<<mm<<"/";
    output<<setw(2)<<right<<aa;
    output.fill(' ');
}

double leerDouble(ifstream& input) {
    double d;
    input >> d;
    input.get();
    return d;
}

int leerEntero(ifstream& input) {
    int i;
    input >> i;
    input.get();
    return i;
}

char* asignarCadena(char *fuente) {
    char* str=new char[strlen(fuente)+1];
    strcpy(str,fuente);
    return str;
}

char* leerCadena(ifstream& input,char delimitador,int n) {
    char buffer[n];
    input.getline(buffer,n,delimitador);
    if (input.eof()) return nullptr;
    char* str=new char[strlen(buffer)+1];
    strcpy(str,buffer);
    return str;
}
