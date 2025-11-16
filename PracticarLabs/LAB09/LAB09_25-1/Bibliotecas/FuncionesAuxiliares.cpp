//
// Created by ASUS on 16/11/2025.
//

#include "FuncionesAuxiliares.h"

void aperturaArchivoLectura(const char* nombArch,ifstream& arch) {
    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"No se pudo abrir el archivo"<<nombArch<<endl;
        exit(1);
    }
}

void aperturaArchivoEscritura(const char* nombArch,ofstream& arch) {
    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout<<"No se pudo abrir el archivo"<<nombArch<<endl;
        exit(1);
    }
}

void leerTablaDeInfracciones(const char* nombArch,
                            TablaDeInfracciones *arrTablaDeInfracciones,
                            int &cantTablaDeInfracciones) {
    //G2007,425.23,No conducir...
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    int n=cantTablaDeInfracciones;
    while (true) {
        char *codigoInfraccion = leerCadena(input, ',', 10);
        if (input.eof()) break;
        arrTablaDeInfracciones[n].codigo=codigoInfraccion;
        arrTablaDeInfracciones[n].multa=leerDouble(input);
        arrTablaDeInfracciones[n].descripcion=leerCadena(input, '\n', 200);
        modificarTextoAMayus(arrTablaDeInfracciones[n].descripcion);
        n++;
    }
    cantTablaDeInfracciones=n;
}

void leerEmpresasRegistradas(const char* nombArch,
                            EmpresaRegistrada *arrEmpresasRegistradas,
                            int &cantEmpresasRegistradas) {
    //79672079,contreras chang johana cinthia,Chorrillos
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    int n=cantEmpresasRegistradas;
    while (true) {
        int dni = leerEntero(input);
        if (input.eof()) break;
        arrEmpresasRegistradas[n].dni=dni;
        arrEmpresasRegistradas[n].nombre=leerCadena(input, ',', 100);
        modificarTextoAMayus(arrEmpresasRegistradas[n].nombre);
        arrEmpresasRegistradas[n].distrito=leerCadena(input, '\n', 100);
        modificarTextoAMayus(arrEmpresasRegistradas[n].distrito);

        //necesario, inicializarlas:
        arrEmpresasRegistradas[n].numPlacas=0;
        arrEmpresasRegistradas[n].infracciones=new InfraccionCometida[40]; //40 sale del dato del lab
        arrEmpresasRegistradas[n].cantidadDeInfracciones=0;
        arrEmpresasRegistradas[n].totalAdeudado=0.0;
        arrEmpresasRegistradas[n].totalPagado=0.0;
        n++;
    }
    cantEmpresasRegistradas=n;
}

void leerCompletarPlacasRegistradas(const char* nombArch,
                                    EmpresaRegistrada *arrEmpresasRegistradas,
                                    int cantEmpresasRegistradas) {
    //12443643,M421-807
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    char placaLeida[20];
    while (true) {
        int dniLeido=leerEntero(input);
        if (input.eof()) break;
        //Esta es una manera pero trataré de usar el modulo de asignar cadena
        //para que no se empolvé ahí xd
        //char* placaLeida=leerCadena(input,'\n',20);
        input.getline(placaLeida,20,'\n');
        int posPlaca=buscarPlaca(dniLeido,arrEmpresasRegistradas,cantEmpresasRegistradas);
        if (posPlaca!=NO_ENCONTRADO) {
            int n=arrEmpresasRegistradas[posPlaca].numPlacas;
            //antes con el leerCadena pasaba normal pq ya le reservaba memoria en ese módulo
            //ahora cambia la cosa:
            //arrEmpresasRegistradas[posPlaca].placas[n]=placaLeida;
            arrEmpresasRegistradas[posPlaca].placas[n]=asignarCadena(placaLeida);
            arrEmpresasRegistradas[posPlaca].numPlacas++;
        }
    }
}

void leerInfraccionesCometidas(const char* nombArch,
                            TablaDeInfracciones *arrTablaDeInfracciones,
                            int cantTablaDeInfracciones,
                            EmpresaRegistrada *arrEmpresasRegistradas,
                            int cantEmpresasRegistradas){
    //1/12/2020,G760-721,G2022,N             CASO NO PAGADO
    //23/7/2023,P474-593,G2060,P,22/8/2023   CASO PAGADO
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    int diaInfra,mesInfra,añoInfra,diaPago,mesPago,añoPago;
    char c,placaLeida[20],codigoInfraccion[20],letraPago;
    while (true) {
        input>>diaInfra>>c>>mesInfra>>c>>añoInfra;
        if (input.eof()) break;
        input.ignore();//la coma
        input.getline(placaLeida,20,',');
        input.getline(codigoInfraccion,20,',');
        input>>letraPago;
        input.ignore();
        if (letraPago=='P') input>>diaPago>>c>>mesPago>>c>>añoPago;
        //else if (letraPago=='N')  no hay nada que hacer
        int posEmpresa=buscarEmpresa(placaLeida,arrEmpresasRegistradas,cantEmpresasRegistradas);
        if (posEmpresa!=NO_ENCONTRADO) {
            int posInfraccion=buscarInfraccion(codigoInfraccion,arrTablaDeInfracciones,
                                                cantTablaDeInfracciones);
            if (posInfraccion!=NO_ENCONTRADO) {
                agregarInfraccion(arrEmpresasRegistradas[posEmpresa],arrTablaDeInfracciones[posInfraccion],
                            diaInfra,mesInfra,añoInfra,diaPago,mesPago,añoPago,letraPago,placaLeida);
            }
        }
    }
}

void agregarInfraccion(EmpresaRegistrada &empresa,TablaDeInfracciones infraccion,
                        int diaInfra,int mesInfra,int añoInfra,
                        int diaPago,int mesPago,int añoPago,char letraPago,char* placaLeida) {
    int n=empresa.cantidadDeInfracciones;
    empresa.infracciones[n].placa=asignarCadena(placaLeida);
    empresa.infracciones[n].infraccion=infraccion;
    empresa.infracciones[n].fechaDeInfraccion={diaInfra,mesInfra,añoInfra,
                                            añoInfra*10000+mesInfra*100+diaInfra};
    if (letraPago=='P') {
        empresa.infracciones[n].fechaDePago={diaPago,mesPago,añoPago,
                                            añoPago*10000+mesPago*100+diaPago};
        empresa.infracciones[n].multaPagada=true;
    }else {
        empresa.infracciones[n].multaPagada=false;
    }
    empresa.cantidadDeInfracciones++;
}

void calcularMontosTotalesYAdeudados(EmpresaRegistrada *arrEmpresaRegistrada,
                                    int cantEmpresasRegistradas) {
    for (int i=0;i<cantEmpresasRegistradas;i++) {
        arrEmpresaRegistrada[i].totalPagado=0.0;
        arrEmpresaRegistrada[i].totalAdeudado=0.0;
        for (int j=0;j<arrEmpresaRegistrada[i].cantidadDeInfracciones;j++) {
            if (arrEmpresaRegistrada[i].infracciones[j].multaPagada) {//o sea si pagó
                arrEmpresaRegistrada[i].totalPagado+=arrEmpresaRegistrada[i].infracciones[j].infraccion.multa;
            }else {
                arrEmpresaRegistrada[i].totalAdeudado+=arrEmpresaRegistrada[i].infracciones[j].infraccion.multa;
            }
        }
    }
}

void ordenarEmpresasRegistradas(EmpresaRegistrada *arrEmpresasRegistradas,int cantEmpresasRegistradas) {
    for (int i=0;i<cantEmpresasRegistradas-1;i++) {
        for (int j=i+1;j<cantEmpresasRegistradas;j++) {
            if (strcmp(arrEmpresasRegistradas[i].distrito,arrEmpresasRegistradas[j].distrito)>0) {
                //ya no es 1x1 sino que cambia struct por struct, mucho mejor
                swapStruct(arrEmpresasRegistradas[i],arrEmpresasRegistradas[j]);
            }
        }
    }
}

void ordenarInfracciones(EmpresaRegistrada &empresa) {
    for (int i=0;i<empresa.cantidadDeInfracciones-1;i++) {
        if (empresa.infracciones[i].multaPagada) continue;
        for (int j=i+1;j<empresa.cantidadDeInfracciones;j++) {
            if (empresa.infracciones[j].multaPagada) {
                swapInfraccion(empresa.infracciones[i],empresa.infracciones[j]);
                break;
            }
        }
    }
}

void emitirReporte(const char* nombArchReporte,
                TablaDeInfracciones *arrTablaDeInfracciones,int cantTablaDeInfracciones,
                EmpresaRegistrada *arrEmpresasRegistradas,int cantEmpresasRegistradas){
    ofstream output;
    aperturaArchivoEscritura(nombArchReporte,output);
    output<<fixed<<setprecision(2);
    for (int i=0;i<cantEmpresasRegistradas;i++) {
        ordenarInfracciones(arrEmpresasRegistradas[i]);
    }
    imprimirCabeceraReporte(output);
    for (int i=0;i<cantEmpresasRegistradas;i++) {
        imprimirOrden(output,i+1,true);
        output<<setw(8)<<right<<"DNI: "<<arrEmpresasRegistradas[i].dni;
        output<<setw(10)<<right<<"NOMBRE: "<<setw(40)<<left<<arrEmpresasRegistradas[i].nombre;
        output<<setw(15)<<right<<"DISTRITO: "<<setw(15)<<left<<arrEmpresasRegistradas[i].distrito;
        output<<"PLACAS: ";
        for (int j=0;j<arrEmpresasRegistradas[i].numPlacas;j++) {
            output<<arrEmpresasRegistradas[i].placas[j];
            if (j<arrEmpresasRegistradas[i].numPlacas-1) {
                output<<"/";
            }
        }
        output<<endl;
        imprimirLineas('=',220,output);

        imprimirMultasEmpresa(output,arrEmpresasRegistradas[i],true);
        imprimirMultasEmpresa(output,arrEmpresasRegistradas[i],false);

    }
}

void imprimirMultasEmpresa(ofstream &output,EmpresaRegistrada &empresa, bool esPagada) {
    imprimirCabeceraMultas(output,esPagada);
    int contador=1;
    for (int k=0;k<empresa.cantidadDeInfracciones;k++) {
        if (empresa.infracciones[k].multaPagada!=esPagada) continue;
        imprimirOrden(output,contador,false);
        contador++;
        output<<setw(3)<<" ";
        imprimirFecha(output,empresa.infracciones[k].fechaDeInfraccion.fecha);
        output<<setw(5)<<" "<<setw(13)<<left<<empresa.infracciones[k].placa;
        output<<setw(10)<<left<<empresa.infracciones[k].infraccion.codigo;
        output<<setw(150)<<left<<empresa.infracciones[k].infraccion.descripcion;
        output<<setw(10)<<right<<empresa.infracciones[k].infraccion.multa;
        if (empresa.infracciones[k].multaPagada) {
            output<<setw(5)<<" ";
            imprimirFecha(output,empresa.infracciones[k].fechaDePago.fecha);
        }
        output<<endl;
    }
    imprimirLineas('-',220,output);
    if (esPagada) {
        output<<"TOTAL PAGADO: "<<setw(10)<<right<<empresa.totalPagado<<endl;
    }else {
        output<<"TOTAL ADEUDADO: "<<setw(10)<<right<<empresa.totalAdeudado<<endl;
    }
    imprimirLineas('=',220,output);
}

void imprimirCabeceraMultas(ofstream& output,bool esPagada) {
    if (esPagada) {
        output<<setw(1)<<" "<<"MULTAS PAGADAS: "<<endl;
    }else {
        output<<setw(1)<<" "<<"MULTAS ADEUDADAS: "<<endl;
    }

    output<<setw(11)<<right<<"FECHA";
    output<<setw(15)<<right<<"PLACA";
    output<<setw(25)<<right<<"CODIGO DE INFRACCION";
    output<<setw(20)<<right<<"DESCRIPCION";
    output<<setw(132)<<right<<"MULTA";
    if (esPagada) {
        output<<setw(17)<<right<<"FECHA DE PAGO"<<endl;
    }else {
        output<<endl;
    }
    imprimirLineas('-',220,output);
}

void imprimirCabeceraReporte(ofstream& output) {
    output<<setw(100)<<" "<<"MINISTERIO DE TRANSPORTES"<<endl;
    output<<setw(95)<<" "<<"LISTADO DE INFRACCIONES POR EMPRESA"<<endl;
    imprimirLineas('=',220,output);
}

void imprimirLineas(char c,int cant,ofstream& output) {
    for (int i=0;i<cant;i++) output<<c;
    output<<endl;
}

void imprimirOrden(ofstream& output,int nroOrden,bool formato1) {
    if (formato1) {
        output.fill('0');
        output<<setw(2)<<right<<nroOrden<<")";
        output.fill(' ');
    }else {
        output<<setw(2)<<right<<nroOrden<<")";
    }

}

void swapInfraccion(InfraccionCometida &dato1,InfraccionCometida&dato2) {
    InfraccionCometida aux;
    aux=dato1;
    dato1=dato2;
    dato2=aux;
}

void swapStruct(EmpresaRegistrada &dato1,EmpresaRegistrada &dato2) {
    EmpresaRegistrada aux;
    aux=dato1;
    dato1=dato2;
    dato2=aux;
}

int buscarInfraccion(char *codigoInfraccion,TablaDeInfracciones *arrTablaDeInfracciones,int cantTablaDeInfracciones) {
    for (int i=0;i<cantTablaDeInfracciones;i++)
        if (strcmp(codigoInfraccion,arrTablaDeInfracciones[i].codigo)==0) return i;
    return NO_ENCONTRADO;
}

int buscarEmpresa(char *placaLeida,EmpresaRegistrada *arrEmpresasRegistradas,int cantEmpresasRegistradas){
    for (int i=0;i<cantEmpresasRegistradas;i++) {
        for (int j=0;j<arrEmpresasRegistradas[i].numPlacas;j++) {
            if (strcmp(placaLeida,arrEmpresasRegistradas[i].placas[j])==0) return i;
        }
    }
    return NO_ENCONTRADO;
}

int leerFecha(ifstream& input) {
    int dd,mm,aa;
    char c;
    input>>dd>>c>>mm>>c>>aa;

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
    output<<setw(4)<<right<<aa;
    output.fill(' ');
}

int buscarPlaca(int dniLeido,EmpresaRegistrada *arrEmpresasRegistradas,int cantEmpresasRegistradas){
    for (int i=0;i<cantEmpresasRegistradas;i++)
        if (dniLeido==arrEmpresasRegistradas[i].dni) return i;
    return NO_ENCONTRADO;
}

void modificarTextoAMayus(char* texto) {
    for (int i=0; texto[i]; i++) {
        if (texto[i]>='a' && texto[i]<='z') texto[i]-='a'-'A';
    }
}

char* asignarCadena(const char* origen) {
    char* str = new char[strlen(origen)+1];
    strcpy(str,origen);
    return str;
}

char* leerCadena(ifstream& input,char delimitador,int n) {
    char buffer[n];
    input.getline(buffer,n,delimitador);
    if (input.eof()) return nullptr;
    char* str=new char [strlen(buffer)+1];
    strcpy(str,buffer);
    return str;
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
