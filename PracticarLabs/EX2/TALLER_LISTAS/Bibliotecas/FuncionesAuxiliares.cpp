//
// Created by aml on 28/11/2025.
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

void cargarUsuarios(const char* nombArch,NodoUsuario *&listaUsuarios) {

    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    Usuario usuario{};
    while (true) {
        leerUsuarios(input,usuario);
        if (input.eof()) break;
        insertarSimple(usuario,listaUsuarios);
    }
}

void insertarSimple(Usuario usuario,NodoUsuario *&listaUsuarios) {
    NodoUsuario* nuevo= new NodoUsuario;
    nuevo->usuario=usuario;
    nuevo->siguiente=nullptr;
    nuevo->siguiente=listaUsuarios;
    listaUsuarios=nuevo;
}

void leerUsuarios(ifstream& input,Usuario &usuario) {
    //54393647,Reyes Tang Edward,V,13.00
    usuario.dni=leerEntero(input);
    usuario.nombre=leerCadena(input,',',100);
    input>>usuario.categoria;
    input.get();//la coma
    usuario.calificacion=leerDouble(input);
    usuario.libros=new LibroEnSuPoder[6];
}

void pruebaUsuarios(const char* nombArch,NodoUsuario *listaUsuarios) {
    ofstream output;
    aperturaArchivoEscritura(nombArch,output);
    NodoUsuario *p=listaUsuarios;
    output<<setw(35)<<" "<<"REPORTE DE USUARIOS"<<endl;
    imprimirLineas('=',100,output);
    while (p) {
        imprimirCabeceraUsuarios(output);
        output<<p->usuario.dni;
        output<<setw(5)<<" "<<setw(36)<<left<<p->usuario.nombre;
        output<<setw(10)<<left<<p->usuario.categoria;
        output<<setw(20)<<right<<p->usuario.calificacion<<endl;
        imprimirLineas('=',100,output);
        p=p->siguiente;
    }
}

void actualizarPrestamo(const char* nombArch,NodoUsuario *&listaUsuarios) {
    //QV96140     17750908     3/07/2023     ...
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    char* codigoLibro;
    int dniUsuario,fechaMaxima;
    while (true) {
        codigoLibro=leerCadena(input,' ',50);
        if (input.eof() or codigoLibro==nullptr) break;
        input>>dniUsuario;
        //fechaMaxima=leerFecha(input);
    }
}

void imprimirCabeceraUsuarios(ofstream &output) {
    output << "Dni:";
    output << setw(9) << " " << "Nombre:";
    output << setw(25) << " " << "Categoria:";
    output << setw(15) << " " << "Calificacion:" << endl;
}

void imprimirLineas(char c,int cant,ofstream& output) {
    for (int i=0;i<cant;i++) output << c;
    output << endl;
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
