//
// Created by ASUS on 9/11/2025.
//

#include "FuncionesAuxiliares.h"


void aperturaArchivoDatos(const char* nombArch,ifstream& arch) {
    arch.open(nombArch, ios::in);
    if (not arch.is_open()) {
        cout<<"Error, no se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
}

void aperturaArchivoReporte(const char* nombArch,ofstream& arch) {
    arch.open(nombArch, ios::out);
    if (not arch.is_open()) {
        cout<<"Error, no se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
}

void leerTablaInfracciones(const char* nombArch,
                            TablaDeInfracciones *arrTablaDeInfracciones,
                            int& cantTablaDeInfracciones){
    //G2007,425.23,No conducir...
    ifstream input;
    aperturaArchivoDatos(nombArch,input);
    char codigo[7],descripcion[300];
    double multa;
    while (true) {
        input.getline(codigo,7,',');
        if (input.eof()) break;
        multa=readDouble(input,false);
        input.getline(descripcion,300,'\n');
        strcpy(arrTablaDeInfracciones[cantTablaDeInfracciones].codigo,codigo);
        arrTablaDeInfracciones[cantTablaDeInfracciones].multa=multa;
        strcpy(arrTablaDeInfracciones[cantTablaDeInfracciones].descripcion,descripcion);
        formatoAMayus(arrTablaDeInfracciones[cantTablaDeInfracciones].descripcion);
        cantTablaDeInfracciones++;
    }
}

void formatoAMayus(char* nombre) {
    //No conducir ....
    bool esPrimero=true;
    for (int i=0;nombre[i];i++) {
        if (nombre[i]>='a' && nombre[i]<='z') nombre[i]-='a'-'A';
    }
}


void leerEmpresasRegistradas(const char* nombArchEmpReg,
                            EmpresasRegistradas *arrEmpresasRegistradas,
                            int& cantEmpresasRegistradas) {
    //79672079,contreras chang johana cinthia,Chorrillos
    ifstream input;
    aperturaArchivoDatos(nombArchEmpReg,input);
    int dni;
    char nombre[200],distrito[100];
    while (true) {
        dni=readInt(input,false);
        if (input.eof()) break;
        input.getline(nombre,200,',');
        input.getline(distrito,100,'\n');
        arrEmpresasRegistradas[cantEmpresasRegistradas].dni=dni;
        strcpy(arrEmpresasRegistradas[cantEmpresasRegistradas].nombre,nombre);
        formatoAMayus(arrEmpresasRegistradas[cantEmpresasRegistradas].nombre);
        strcpy(arrEmpresasRegistradas[cantEmpresasRegistradas].distrito,distrito);
        formatoAMayus(arrEmpresasRegistradas[cantEmpresasRegistradas].distrito);
        cantEmpresasRegistradas++;
    }
}

void completarPlacasRegistradas(const char* nombArch,
                            EmpresasRegistradas *arrEmpresasRegistradas,
                            int cantEmpresasRegistradas) {
    //12443643      M421-807
    ifstream input;
    aperturaArchivoDatos(nombArch,input);
    int dniEmpresa;
    char *placa; //esto si es dinámico pq si fuera estática seria una matriz [10][7] algo así
    while (true) {
        input>>dniEmpresa;
        if (input.eof()) break;
        input>>ws;
        placa=readString(input,'\n');
        int pos=buscarEmpresa(dniEmpresa,arrEmpresasRegistradas,
                            cantEmpresasRegistradas);
        if (pos!=NO_ENCONTRADO) {
            int cantidadPlacas=arrEmpresasRegistradas[pos].numPlacas;
            arrEmpresasRegistradas[pos].placas[cantidadPlacas]=placa;
            arrEmpresasRegistradas[pos].numPlacas++;
        }
    }
}

void completarInfracciones(const char* nombArch,
                           TablaDeInfracciones *arrTablaDeInfracciones,int cantTablaDeInfracciones,
                           EmpresasRegistradas *arrEmpresasRegistradas,int cantEmpresasRegistradas){
    //23/7/2023,P474-593,G2060,P,22/8/2023
    //1/12/2020,G760-721,G2022,N
    ifstream input;
    aperturaArchivoDatos(nombArch,input);
    Fecha fechaVar;
    char c,placa[10],codigoInfra[10];
    while (true) {
        input>>fechaVar.dd;
        if (input.eof()) break;
        input>>c>>fechaVar.mm>>c>>fechaVar.aa;
        fechaVar.fecha=fechaVar.aa*10000+fechaVar.mm*100+fechaVar.dd;
        input.ignore();//ignoramos la coma
        input.getline(placa,10,',');
        int posEmpresa=buscarPlacaEnEmpresas(placa,arrEmpresasRegistradas,
                                            cantEmpresasRegistradas);
        if (posEmpresa!=NO_ENCONTRADO) {
            arrEmpresasRegistradas[posEmpresa].fechaDeInfraccion=fechaVar;
            input.getline(codigoInfra,10,',');
            int posInfraccion=buscarInfraccion(codigoInfra,arrTablaDeInfracciones,
                                        cantTablaDeInfracciones);
            if (posInfraccion!=NO_ENCONTRADO) {
                double multa=arrTablaDeInfracciones[posInfraccion].multa;
                c=input.get();//Leer si es "P" o "N"
                //Modulo para no tener 1000 lineas
                actualizarDatosEmpresasRegistradas(input,c,posEmpresa,multa,
                                                    arrEmpresasRegistradas);
                if (arrEmpresasRegistradas[posEmpresa].fechaDeInfraccion.fecha==0 or
                    fechaVar.fecha<arrEmpresasRegistradas[posEmpresa].fechaDeInfraccion.fecha) {
                    arrEmpresasRegistradas[posEmpresa].fechaDeInfraccion=fechaVar;
                }
                arrEmpresasRegistradas[posEmpresa].totalDeMultas+=multa;
                arrEmpresasRegistradas[posEmpresa].cantidadDeFaltas++;
            }else {
                while (input.get()!='\n');
            }
        }else {
            while (input.get()!='\n');
        }
    }
}

void actualizarDatosEmpresasRegistradas(ifstream& input,
                                        char c,int posEmpresa,double multa,
                                        EmpresasRegistradas *arrEmpresasRegistradas) {
    if (c=='P') {
        arrEmpresasRegistradas[posEmpresa].totalPagado+=multa;
        input.ignore();//la coma
        Fecha fechaPagoActual;
        input>>fechaPagoActual.dd>>c>>fechaPagoActual.mm>>
        c>>fechaPagoActual.aa;
        //input.get();//porsiacaso
        fechaPagoActual.fecha=fechaPagoActual.aa*10000+fechaPagoActual.mm*100+fechaPagoActual.dd;
        if (arrEmpresasRegistradas[posEmpresa].fechaDePago.fecha==0 or
            fechaPagoActual.fecha>arrEmpresasRegistradas[posEmpresa].fechaDePago.fecha) {
            arrEmpresasRegistradas[posEmpresa].fechaDePago=fechaPagoActual;
            }
    }else if (c=='N') {
        arrEmpresasRegistradas[posEmpresa].totalAdeudado+=multa;
        //input.get();//porsiacaso :u
    }
}

void ordenarEmpresasRegistradas(EmpresasRegistradas *arrEmpresasRegistradas,
                                int cantEmpresasRegistradas) {
    //Ascendente por el distrito y descendente por fecha de infraccion
    for (int i=0;i<cantEmpresasRegistradas-1;i++) {
        for (int j=i+1;j<cantEmpresasRegistradas;j++) {
            if (strcmp(arrEmpresasRegistradas[i].distrito,arrEmpresasRegistradas[j].distrito)>0 or
                strcmp(arrEmpresasRegistradas[i].distrito,arrEmpresasRegistradas[j].distrito)==0 and
                arrEmpresasRegistradas[i].fechaDeInfraccion.fecha<arrEmpresasRegistradas[j].fechaDeInfraccion.fecha) {
                swapStruct(arrEmpresasRegistradas[i],arrEmpresasRegistradas[j]);
            }
        }
    }
}

void ordenarTablaDeInfracciones(TablaDeInfracciones *arrTablaDeInfracciones,
                                int cantTablaDeInfracciones) {
    //Descendentemente por el codigo de la infraccion
    for (int i=0;i<cantTablaDeInfracciones-1;i++) {
        for (int j=i+1;j<cantTablaDeInfracciones;j++) {
            if (strcmp(arrTablaDeInfracciones[i].codigo,arrTablaDeInfracciones[j].codigo)<0) {
                swapStruct2(arrTablaDeInfracciones[i],arrTablaDeInfracciones[j]);
            }
        }
    }
}

void imprimirReporte(const char* nombArchRep,
                    TablaDeInfracciones *arrTablaDeInfracciones,int cantTablaDeInfracciones,
                    EmpresasRegistradas *arrEmpresasRegistradas,int cantEmpresasRegistradas) {
    ofstream output;
    aperturaArchivoReporte(nombArchRep,output);
    output<<fixed<<setprecision(2);
    imprimirCabeceraReporteEmpresas(output);
    for (int i=0;i<cantEmpresasRegistradas;i++) {
        output<<setw(2)<<right<<i+1<<")";
        output<<setw(10)<<right<<arrEmpresasRegistradas[i].dni;
        output<<setw(5)<<" "<<setw(45)<<left<<arrEmpresasRegistradas[i].nombre;
        output<<setw(5)<<" "<<setw(30)<<left<<arrEmpresasRegistradas[i].distrito;
        int n=arrEmpresasRegistradas[i].numPlacas;
        int tamaño=0,carUsado=0;
        for (int j=0;j<n;j++) {
            if (j>0) {//para empezar desde el segundo
                output<<"/";
                carUsado++;
            }
            output<<arrEmpresasRegistradas[i].placas[j];
            tamaño+=strlen(arrEmpresasRegistradas[i].placas[j]);
        }
        output<<setw(50-tamaño-carUsado)<<" ";
        imprimirFecha(output,arrEmpresasRegistradas[i].fechaDeInfraccion.fecha);
        output<<setw(5)<<" ";imprimirFecha(output,arrEmpresasRegistradas[i].fechaDePago.fecha);
        output<<setw(15)<<arrEmpresasRegistradas[i].totalPagado;
        output<<setw(15)<<arrEmpresasRegistradas[i].totalAdeudado;
        output<<setw(10)<<arrEmpresasRegistradas[i].cantidadDeFaltas<<endl;
    }
    //ImprimirResumen

    imprimirCabeceraReporteInfracciones(output);
    for (int i=0;i<cantTablaDeInfracciones;i++) {
        output<<setw(25)<<right<<arrTablaDeInfracciones[i].codigo;
        output<<setw(15)<<right<<arrTablaDeInfracciones[i].multa;
        output<<setw(5)<<" "<<setw(100)<<left<<arrTablaDeInfracciones[i].descripcion<<endl;
    }
}

void imprimirCabeceraReporteInfracciones(ofstream& output){
    imprimirLineas('=',220,output);
    output<<setw(90)<<" "<<"TABLA DE INFRACCIONES"<<endl;
    imprimirLineas('=',220,output);
    output<<setw(26)<<right<<"CODIGO";
    output<<setw(14)<<right<<"MULTA";
    output<<setw(16)<<right<<"DESCRIPCION"<<endl;
    imprimirLineas('=',220,output);

}

void imprimirCabeceraReporteEmpresas(ofstream& output) {
    output<<setw(95)<<" "<<"MINISTERIO DE TRANSPORTES"<<endl;
    output<<setw(90)<<" "<<"LISTADO DE INFRACCIONES POR EMPRESA"<<endl;
    imprimirLineas('=',220,output);
    output<<setw(45)<<right<<"EMPRESA";
    output<<setw(113)<<right<<"FECHA INF.";
    output<<setw(15)<<right<<"FECHA PAGO";
    output<<setw(43)<<right<<"CANTIDAD"<<endl;
    output<<setw(4)<<right<<"No.";
    output<<setw(4)<<right<<"DNI";
    output<<setw(16)<<right<<"NOMBRE";
    output<<setw(52)<<right<<"DISTRITO";
    output<<setw(28)<<right<<"PLACAS";
    output<<setw(55)<<right<<"MAS ANTIGUA";
    output<<setw(15)<<right<<"MAS RECIENTE";
    output<<setw(15)<<right<<"TOTAL PAGADO";
    output<<setw(15)<<right<<"TOTAL DEUDA";
    output<<setw(13)<<right<<"DE FALTAS"<<endl;
    imprimirLineas('=',220,output);
}

void imprimirLineas(char c,int cant,ofstream& output) {
    for (int i=0;i<cant;i++) output<<c;
    output<<endl;
}

void swapStruct(EmpresasRegistradas &datoA,EmpresasRegistradas &datoB) {
    EmpresasRegistradas aux;
    aux=datoA;
    datoA=datoB;
    datoB=aux;
}

void swapStruct2(TablaDeInfracciones &datoA,TablaDeInfracciones &datoB) {
    TablaDeInfracciones aux;
    aux=datoA;
    datoA=datoB;
    datoB=aux;
}

int buscarInfraccion(char* codigoInfra,TablaDeInfracciones *arrTablaDeInfracciones,
                    int cantTablaDeInfracciones) {
    for (int i=0;i<cantTablaDeInfracciones;i++)
        if (strcmp(codigoInfra,arrTablaDeInfracciones[i].codigo)==0) return i;
    return NO_ENCONTRADO;
}

int buscarPlacaEnEmpresas(char* placa,EmpresasRegistradas *arrEmpresasRegistradas,
                            int cantEmpresasRegistradas) {
    for (int i=0;i<cantEmpresasRegistradas;i++) {
        int numPlacas=arrEmpresasRegistradas[i].numPlacas;
        for (int j=0;j<numPlacas;j++) {
            if (strcmp(placa,arrEmpresasRegistradas[i].placas[j])==0) return i;
        }
    }
    return NO_ENCONTRADO;
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

int buscarEmpresa(int dniEmpresa,EmpresasRegistradas *arrEmpresasRegistradas,
                    int cantEmpresasRegistradas) {
    for (int i=0;i<cantEmpresasRegistradas;i++)
        if (dniEmpresa==arrEmpresasRegistradas[i].dni) return i;
    return NO_ENCONTRADO;
}

char* readString(ifstream& input,char delimitador) {
    char buffer[MAX_CARACTERES];
    input.getline(buffer,MAX_CARACTERES,delimitador);
    if (input.eof()) return nullptr;
    char* src=new char[strlen(buffer)+1];
    strcpy(src,buffer);
    return src;
}

int readInt(ifstream& input,bool esUltimo) {
    int i;
    input>>i;
    if (not esUltimo) input.get();
    return i;
}

double readDouble(ifstream& input,bool esUltimo) {
    double d;
    input>>d;
    if (not esUltimo) input.get();
    return d;
}
