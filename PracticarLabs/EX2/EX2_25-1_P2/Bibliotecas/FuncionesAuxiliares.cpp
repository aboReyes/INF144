//
// Created by ASUS on 30/11/2025.
//

#include "FuncionesAuxiliares.h"


void aperturaArchivoLectura(const char* nombArch,ifstream& arch) {
    arch.open(nombArch, ios::in);
    if (not arch.is_open()) {
        cout<<"Error al abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
}

void aperturaArchivoEscritura(const char* nombArch,ofstream& arch) {
    arch.open(nombArch, ios::out);
    if (not arch.is_open()) {
        cout<<"Error al abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
}

void solicitarDron(char *idDron,char *idDron2) {
    char auxIdDron[10],auxIdDron2[10];
    cout<<"Ingrese dos codigos de drones separados por un espacio en blanco: "<<endl;
    cin>>auxIdDron>>auxIdDron2;
    strcpy(idDron,auxIdDron);
    strcpy(idDron2,auxIdDron2);
}

void crearLista(const char*nombArch,Lista &lista,char* idDron) {
    //IP6-005,Grave,234,Conducir sin habilitacion
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    Infraccion infraccion{};
    char idDronLeido[10];
    while (true) {
        input.getline(idDronLeido,10,',');
        if (input.eof()) break;
        if (strcmp(idDronLeido,idDron)==0) {
            infraccion.gravedad=leerCadenaExacta(input,',',20);
            infraccion.codigo=leerEntero(input);
            infraccion.descripcion=leerCadenaExacta(input,'\n',100);
            if (strcmp(infraccion.gravedad,"Leve")==0) {
                insertarAlFinal(lista,infraccion);
            }else if (strcmp(infraccion.gravedad,"Grave")==0) {
                insertarAlInicio(lista,infraccion);
            }
        }else {
            while (input.get()!='\n');
        }
    }
}

void insertarAlFinal(Lista &lista,Infraccion infraccion) {
    Nodo *nuevo=new Nodo;
    nuevo->infraccion=infraccion;
    nuevo->siguiente=nullptr;

    if (lista.inicio==nullptr) {
        lista.inicio=nuevo;
    }else {
        lista.fin->siguiente=nuevo;
    }
    lista.fin=nuevo;
}

void insertarAlInicio(Lista& lista,Infraccion infraccion) {
    Nodo *nuevo=new Nodo;
    nuevo->infraccion=infraccion;
    nuevo->siguiente=nullptr;
    nuevo->siguiente=lista.inicio;
    lista.inicio=nuevo;
    if (lista.fin==nullptr) {
        lista.fin=nuevo;
    }
}

void emitirReporte(const char*nombArch,Lista primeraLista,char* idDron,
                    Lista segundaLista,char* idDron2) {
    ofstream output;
    aperturaArchivoEscritura(nombArch,output);
    imprimirDatosDron(output,primeraLista,idDron);
    imprimirLineas('=',20,output,true);
    imprimirDatosDron(output,segundaLista,idDron2);
}

void imprimirDatosDron(ofstream& output,Lista lista,char* idDron) {
    Nodo *p=lista.inicio;
    imprimirLineas('=',3,output,false);
    output<<" Dron "<<idDron<<" ";
    imprimirLineas('=',3,output,false);
    output<<endl;
    int cantLeves=0,cantGraves=0;
    while (p) {
        output<<"["<<setw(5)<<left<<p->infraccion.gravedad<<"] ";
        output<<"Codigo: "<<p->infraccion.codigo<<" - ";
        output<<p->infraccion.descripcion<<endl;
        if (strcmp(p->infraccion.gravedad,"Leve")==0) cantLeves++;
        if (strcmp(p->infraccion.gravedad,"Grave")==0) cantGraves++;
        p=p->siguiente;
    }
    output<<"Leves: "<<cantLeves<<", "<<"Graves: "<<cantGraves<<endl;
}

void imprimirLineas(char c,int cant,ofstream&output,bool saltoLinea) {
    for (int i=0;i<cant;i++) output<<c;
    if (saltoLinea) {
        output<<endl;
    }
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

char* leerCadenaExacta(ifstream&input,char delimitador,int n) {
    char buffer[n];
    input.getline(buffer,n,delimitador);
    if (input.eof()) return nullptr;
    char* src=new char[strlen(buffer)+1];
    strcpy(src,buffer);
    return src;
}

char* asignarCadena(char* buffer) {
    char* src=new char[strlen(buffer)+1];
    strcpy(src,buffer);
    return src;
}
