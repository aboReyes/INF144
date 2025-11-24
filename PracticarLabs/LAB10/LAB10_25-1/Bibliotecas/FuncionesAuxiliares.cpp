//
// Created by ASUS on 24/11/2025.
//

#include "FuncionesAuxiliares.h"

#include <functional>

void aperturaArchivoLectura(const char* nombArch,ifstream& arch) {
    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"Error al abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
}

void aperturaArchivoEscritura(const char* nombArch,ofstream& arch) {
    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout<<"Error al abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
}

void inicializaCuentasBancarias(struct Cuenta &cuenta) {
    cuenta.codigo = 0;
    cuenta.nombre = nullptr;
    cuenta.saldo = 0.0;
    cuenta.fechaSobregiro = 0;
    cuenta.sobregiro = false; //comienza sin sobregiro
}

void cargarCuentasBancarias(const char* nombArch,Nodo *&listaCuentasBancarias) {
    //58477632,Larriega Velasquez Moises Roberto,23326.62
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    Cuenta cuenta;
    while (true) {
        inicializaCuentasBancarias(cuenta);
        leerCuentasBancarias(input,cuenta);
        if (input.eof()) break;
        insertarOrdenado(listaCuentasBancarias,cuenta);
    }
}

void insertarOrdenado(Nodo *&listaCuentasBancarias,Cuenta cuenta) {
    Nodo *p=listaCuentasBancarias;
    Nodo *anterior=nullptr;
    Nodo *nuevo=new Nodo;
    nuevo->cuenta=cuenta;
    while (p and p->cuenta.codigo<cuenta.codigo) {
        anterior=p;
        p=p->siguiente;
    }
    nuevo->siguiente=p;
    if (anterior==nullptr) {
        listaCuentasBancarias=nuevo;
    }else {
        anterior->siguiente=nuevo;
    }
}

void leerCuentasBancarias(ifstream& input,Cuenta &cuenta) {
    int codigoCuenta=leerEntero(input);
    if (input.eof()) return;
    cuenta.codigo=codigoCuenta;
    cuenta.nombre=leerCadenaExacta(input,',',100);
    cuenta.saldo=leerDouble(input);
}

void cargarMovimientoDeCuentas(const char* nombArch,Nodo *&listaCuentasBancarias) {
    //2/11/2024,67392071,14445.59,71839426,15211.07,70642877,-18247.08,14398081,10907.03,64627562,-17161.58
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    int fechaAtentida,codigoCuenta;
    double monto;
    while (true) {
        fechaAtentida=leerFecha(input);
        if (input.eof())break;
        while (true) {
            codigoCuenta=leerEntero(input);
            input>>monto;
            Nodo *nodoAActualizar=buscarCuenta(listaCuentasBancarias,codigoCuenta);
            if (nodoAActualizar!=nullptr) {
                double saldoAnterior=nodoAActualizar->cuenta.saldo;
                double nuevoSaldo= nodoAActualizar->cuenta.saldo+monto;
                if (nuevoSaldo<0 and saldoAnterior>=0) {
                    nodoAActualizar->cuenta.sobregiro=true;
                    nodoAActualizar->cuenta.fechaSobregiro=fechaAtentida;
                }
                nodoAActualizar->cuenta.saldo=nuevoSaldo;
            }
            if (input.get()=='\n') break;
        }
    }
}

void emitirReporte(const char*nombArch,Nodo *listaCuentasBancarias) {
    ofstream output;
    aperturaArchivoEscritura(nombArch,output);
    Nodo *p=listaCuentasBancarias;
    imprimirCabeceraReporte(output);
    int contador=0;
    output<<fixed<<setprecision(2);
    while (p) {
        contador++;
        imprimirNroOrden(output,contador);
        output<<setw(10)<<right<<p->cuenta.codigo;
        output<<setw(5)<<" "<<setw(40)<<left<<p->cuenta.nombre;
        output<<setw(15)<<right<<p->cuenta.saldo;
        if (p->cuenta.sobregiro==true) output<<setw(13)<<right<<"SI";
        else output<<setw(13)<<right<<"NO";
        output<<setw(20)<<" ";
        imprimirFecha(output,p->cuenta.fechaSobregiro);
        output<<endl;
        p=p->siguiente;
    }
}

void eliminarSaldosPositivos(Nodo *&listaCuentasBancarias) {
    Nodo*p=listaCuentasBancarias;
    Nodo*anterior=nullptr;
    //Consideramos: LISTA-->N1-->N2-->N3-->nullptr
    //Donde: p=N2 y anterior=N1
    while (p) {
        if (p->cuenta.saldo>0) {
            if (anterior==nullptr) {
                listaCuentasBancarias=p->siguiente;
                delete p;
                p=listaCuentasBancarias;
            }else {
                anterior->siguiente=p->siguiente;
                delete p;
                p=anterior->siguiente;
            }
        }else {
            anterior=p;
            p=p->siguiente;
        }
    }
}

Nodo *buscarCuenta(Nodo *&listaCuentasBancarias,int codigoCuenta) {
    Nodo *p=listaCuentasBancarias;
    while (p) {
        if (codigoCuenta==p->cuenta.codigo) return p;
        p=p->siguiente;
    }
    return nullptr;
}

void imprimirNroOrden(ofstream& output,int contador) {
    output.fill('0');
    output<<setw(2)<<right<<contador<<")";
    output.fill(' ');
}

void imprimirCabeceraReporte(ofstream& output) {
    output<<setw(50)<<" "<<"BANCO DE LOS CLIENTES DE TP"<<endl;
    output<<setw(40)<<" "<<"LISTADO DE LAS CUENTAS DE AHORROS DE NUESTROS CLIENTES"<<endl;
    imprimirLineas('=',130,output);
    output<<"No.";
    output<<setw(8)<<right<<"CUENTA";
    output<<setw(14)<<right<<"CLIENTE";
    output<<setw(46)<<right<<"SALDO";
    output<<setw(19)<<right<<"SOBREGIRADA";
    output<<setw(35)<<right<<"FECHA DEL ULTIMO SOBREGIRO"<<endl;
}

void imprimirLineas(char c,int cant,ofstream& output) {
    for (int i=0;i<cant;i++) output<<c;
    output<<endl;
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
    output<<setw(4)<<right<<aa;
    output.fill(' ');
}

int leerFecha(ifstream& input) {
    int dd,mm,aa;
    char c;
    input>>dd>>c>>mm>>c>>aa;
    input.get();
    return aa*10000+mm*100+dd;
}

int leerEntero(ifstream& input) {
    int i;
    input>>i;
    input.get();
    return i;
}

double leerDouble(ifstream& input) {
    double d;
    input>>d;
    input.get();
    return d;
}

char* asignarCadena(char* buffer) {
    char* src=new char [strlen(buffer)+1];
    strcpy(src,buffer);
    return src;
}


char* leerCadenaExacta(ifstream& input,char delimitador,int n) {
    char buffer[n];
    input.getline(buffer,n,delimitador);
    if (input.eof()) return nullptr;
    char* src=new char [strlen(buffer)+1];
    strcpy(src,buffer);
    return src;
}
