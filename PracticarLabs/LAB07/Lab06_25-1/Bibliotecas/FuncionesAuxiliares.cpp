//
// Created by ASUS on 2/11/2025.
//

#include "FuncionesAuxiliares.h"


void aperturaArchivoLectura(const char*nombArch,ifstream& arch) {
    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"ERROR, el archivo "<<nombArch<<" no se puede abrir"<<endl;
        exit(1);
    }
}

void aperturaArchivoEscritura(const char*nombArch,ofstream& arch) {
    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout<<"ERROR, el archivo "<<nombArch<<" no se puede abrir"<<endl;
        exit(1);
    }
}

void cargarInfracciones(const char* nombArch,
                        int *arrCodigoInfraccion,double *arrMultasInfraccion,
                        int &cantInfracciones) {

    //2007   425.23      No conducir po...
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    int codigoInfra;
    double multaInfra;
    while (true) {
        input>>codigoInfra;
        if (input.eof()) break;
        input>>multaInfra;
        ignorar(input,'\n');
        insertarOrdenado(codigoInfra,multaInfra,
                        arrCodigoInfraccion,arrMultasInfraccion,
                        cantInfracciones);
    }
}

void insertarOrdenado(int codigoInfra,double multaInfra,
                    int *arrCodigoInfraccion,double *arrMultasInfraccion,
                    int &cantInfracciones) {
    int i=cantInfracciones-1;
    while (i>=0 and codigoInfra<arrCodigoInfraccion[i]) {
        arrCodigoInfraccion[i+1]=arrCodigoInfraccion[i];
        arrMultasInfraccion[i+1]=arrMultasInfraccion[i];
        i--;
    }
    arrCodigoInfraccion[i+1]=codigoInfra;
    arrMultasInfraccion[i+1]=multaInfra;
    cantInfracciones++;
}

void cargarInfraCom(const char *nombArch,
                   const char* nombArchRep,
                   int *arrCodigoInfraccion,double *arrMultasInfraccion,int cantInfracciones,
                   int *arrDni,int *arrMasMultaAntigua,int *arrUltimaPendiente,
                   double *arrTotalMultas,double *arrTotalPagadas,double *arrTotalPendientes,
                   char **arrPlacasEmpresa,int &cantInfraCom) {
    //1/12/2020   G760-721     89314225   2022
    //23/7/2023      P474-593      89941095     2060   P     22/8/2023
    ifstream input;
    ofstream output;
    aperturaArchivoLectura(nombArch,input);
    aperturaArchivoEscritura(nombArchRep,output);

    int fechaInfraccion,fechaPago,dniRepEmpresa,codigoInfraccion,posCodigo;
    char placa[10],c,pago;
    while (true) {
        fechaInfraccion=leerFecha(input);
        if (input.eof()) break;
        input>>placa;
        input>>dniRepEmpresa;
        input>>codigoInfraccion;

        output<<dniRepEmpresa<<" "<<placa<<endl;
        pago='N';
        if (input.get()==' ') {
            input>>pago;
            fechaPago=leerFecha(input);
        }

        posCodigo=busquedaBinaria(codigoInfraccion,arrCodigoInfraccion,cantInfracciones);
        double valorMulta=arrMultasInfraccion[posCodigo];
        insertarActualizarInformacion(fechaInfraccion,dniRepEmpresa,pago,fechaPago,valorMulta,
                                    arrDni,arrMasMultaAntigua,arrUltimaPendiente,
                                    arrTotalMultas,arrTotalPagadas,placa,
                                    arrPlacasEmpresa,cantInfraCom);
    }
}

void insertarActualizarInformacion(int fechaInfraccion,int dniRepEmpresa,char pago,
                                    int fechaPago,double valorMulta,
                                    int *arrDni,int *arrMasMultaAntigua,int *arrUltimaPendiente,
                                    double *arrTotalMultas,double* arrTotalPagadas,char *placa,
                                    char** arrPlacasEmpresa,int &cantInfraCom) {
    int posInfraCom=busquedaBinaria(dniRepEmpresa,arrDni,cantInfraCom);
    if (posInfraCom!=NO_ENCONTRADO) {
        if (fechaInfraccion<arrMasMultaAntigua[posInfraCom]) {
            arrMasMultaAntigua[posInfraCom]=fechaInfraccion;
        }
        if (pago=='P') {
            arrTotalPagadas[posInfraCom]+=valorMulta;
            if (fechaPago>arrUltimaPendiente[posInfraCom]) {
                arrUltimaPendiente[posInfraCom]=fechaPago;
            }
        }
        arrTotalMultas[posInfraCom]+=valorMulta;

        if (strstr(arrPlacasEmpresa[posInfraCom],placa)==nullptr) {
            char placaOriginal[1000]; //creamos un char
            strcpy(placaOriginal,arrPlacasEmpresa[posInfraCom]); //copiamos ese nuevo char al arreglo
            strcat(placaOriginal,"/"); //concatenamos placa1/
            strcat(placaOriginal,placa);//concatenamos placa1/placa2
            delete arrPlacasEmpresa[posInfraCom]; //eliminamos los datos del arreglo anterior
            arrPlacasEmpresa[posInfraCom]=new char[strlen(placaOriginal)+1]; //inicializamos a un nuevo char que tiene la longitud de la placa original anteriormente creada
            strcpy(arrPlacasEmpresa[posInfraCom],placaOriginal);//copias y queda
        }

    }else {
        insertarOrdenadoInfraCom(fechaInfraccion,dniRepEmpresa,pago,
            fechaPago,valorMulta,arrDni,arrMasMultaAntigua,arrUltimaPendiente,
            arrTotalMultas,arrTotalPagadas,placa,arrPlacasEmpresa,cantInfraCom);
    }
}

void insertarOrdenadoInfraCom(int fechaInfraccion,int dniRepEmpresa,char pago,
                                int fechaPago,double valorMulta,
                                int *arrDni,int *arrMasMultaAntigua,int *arrUltimaPendiente,
                                double *arrTotalMultas,double* arrTotalPagadas,char *placa,
                                char **arrPlacasEmpresa,int &cantInfraCom) {
    int i=cantInfraCom-1;
    while (i>=0 and dniRepEmpresa<arrDni[i]) {
        arrDni[i+1]=arrDni[i];
        arrMasMultaAntigua[i+1]=arrMasMultaAntigua[i];
        arrUltimaPendiente[i+1]=arrUltimaPendiente[i];
        arrTotalMultas[i+1]=arrTotalMultas[i];
        arrTotalPagadas[i+1]=arrTotalPagadas[i];
        arrPlacasEmpresa[i+1]=arrPlacasEmpresa[i];
        i--;
    }
    arrDni[i+1]=dniRepEmpresa;
    arrMasMultaAntigua[i+1]=fechaInfraccion;
    if (pago=='P') {
        arrUltimaPendiente[i+1]=fechaPago;
    }else {
        arrUltimaPendiente[i+1]=0.0;
    }
    arrTotalMultas[i+1]=valorMulta;
    if (pago=='P') {
        arrTotalPagadas[i+1]=valorMulta;
    }else {
        arrTotalPagadas[i+1]=0.0;
    }
    arrPlacasEmpresa[i+1]=new char[strlen(placa)+1];
    strcpy(arrPlacasEmpresa[i+1],placa);
    cantInfraCom++;
}

int busquedaBinaria(int codigoInfraccion,int *arrCodigoInfraccion,int cantInfracciones) {
    int limiteInferior=0;
    int limiteSuperior=cantInfracciones-1;
    int puntoMedio;
    while (true) {
        if (limiteInferior>limiteSuperior) return NO_ENCONTRADO;
        puntoMedio=(limiteInferior+limiteSuperior)/2;
        if (codigoInfraccion==arrCodigoInfraccion[puntoMedio]) return puntoMedio;
        //Considerando ascendente (1,2,3,4,5,6...)
        if (codigoInfraccion>arrCodigoInfraccion[puntoMedio]) {
            limiteInferior=puntoMedio+1;
        }else {
            limiteSuperior=puntoMedio-1;
        }
    }
}

void crearReporte(const char* nombArch,
                const char* nombArchRep,
                int *arrDni,int *arrMasMultaAntigua,int *arrUltimaPendiente,char **arrPlacasEmpresa,
                double *arrTotalMultas,double *arrTotalPagadas,int cantInfraCom) {
    ifstream input;
    ofstream output;
    aperturaArchivoEscritura(nombArchRep,output);
    aperturaArchivoLectura(nombArch,input);

    double multasPendientes;
    imprimirCabeceraReporte(output);
    output<<fixed<<setprecision(2);
    for (int i=0;i<cantInfraCom;i++) {
        output<<setw(4)<<right<<i+1<<")";
        output<<setw(15)<<right<<arrDni[i];
        output<<setw(10)<<" "<<setw(50)<<left<<arrPlacasEmpresa[i];
        output<<setw(10)<<" "; imprimirFecha(output,arrMasMultaAntigua[i]);
        output<<setw(5)<<" "; imprimirFecha(output,arrUltimaPendiente[i]);
        output<<setw(15)<<right<<arrTotalMultas[i];
        output<<setw(15)<<right<<arrTotalPagadas[i];
        multasPendientes=arrTotalMultas[i]-arrTotalPagadas[i];
        output<<setw(13)<<right<<multasPendientes<<endl;
    }
    //imprimirResumen
}

void imprimirCabeceraReporte(ofstream& output) {
    output<<setw(50)<<" "<<"MINISTERIO DE TRANSPORTES"<<endl;
    output<<setw(50)<<" "<<"LISTADO DE INFRACCIONES"<<endl;
    imprimirLinea('=',160,output);
    output<<setw(98)<<right<<"MULTA MAS";
    output<<setw(17)<<right<<"ULTIMA MULTA";
    output<<setw(15)<<right<<"TOTAL EN";
    output<<setw(13)<<right<<"MULTAS";
    output<<setw(13)<<right<<"MULTAS"<<endl;
    output<<setw(5)<<right<<"No.";
    output<<setw(10)<<right<<"DNI";
    output<<setw(21)<<right<<"PLACAS";
    output<<setw(61)<<right<<"ANTIGUA";
    output<<setw(14)<<right<<"PAGADA";
    output<<setw(18)<<right<<"MULTAS";
    output<<setw(15)<<right<<"PAGADAS";
    output<<setw(15)<<right<<"PENDIENTES"<<endl;
    imprimirLinea('-',160,output);
}


void imprimirLinea(char c,int cant,ofstream& output) {
    for (int i=0;i<cant;i++) output<<c;
    output<<endl;
}
int leerFecha(ifstream &input) {
    int dd,mm,yyyy;
    char c;
    input>>dd>>c>>mm>>c>>yyyy;
    return yyyy*10000+mm*100+dd;
}

void imprimirFecha(ofstream &output,int fecha) {
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

char *readString(ifstream& input) {
    char buffer[MAX_CARACTERES];
    input>>buffer;
    if (input.eof()) return nullptr;
    char* src=new char[strlen(buffer)+1];
    strcpy(src,buffer);
    return src;
}

void ignorar(ifstream &input,char delimitador) {
    char c;
    input>>ws;
    while (true) {
        c=input.get();
        if (c==delimitador) break;
    }
}

