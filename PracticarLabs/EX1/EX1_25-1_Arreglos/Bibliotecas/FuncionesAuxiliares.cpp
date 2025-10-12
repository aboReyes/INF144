//
// Created by ASUS on 11/10/2025.
//

#include "FuncionesAuxiliares.h"

void aperturaArchivoLectura(const char* nombArch,ifstream& arch) {
    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"ERROR: el archivo "<<nombArch<<" no se puede abrir"<<endl;
        exit(1);
    }
}

void aperturaArchivoEscritura(const char* nombArch,ofstream& arch) {
    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout<<"ERROR: el archivo "<<nombArch<<" no se puede abrir"<<endl;
        exit(1);
    }
}

void leerTablaInfracciones(const char* nombArchTablaInfra,
                        char *arrLetraInfraccion,int *arrNumInfraccion,
                        double* arrMultaInfraccion,int &cantInfraccion) {
    //G2007   425.23      No conducir ...
    ifstream archTablaInfra;
    char letraInfraccion;
    aperturaArchivoLectura(nombArchTablaInfra,archTablaInfra);
    while (true) {
        archTablaInfra>>letraInfraccion;
        if (archTablaInfra.eof()) break;
        archTablaInfra>>arrNumInfraccion[cantInfraccion];
        archTablaInfra>>arrMultaInfraccion[cantInfraccion];
        ignorar(archTablaInfra,'\n');
        arrLetraInfraccion[cantInfraccion]=letraInfraccion;
        cantInfraccion++;
    }
    //cout<<"Hay "<<cantInfraccion<<endl;
}

void pruebaTablaInfracciones(const char* nombArchRepTabInfra,
                            char* arrLetraInfraccion,int *arrNumInfraccion,
                            double* arrMultaInfraccion,int cantInfraccion) {
    //G2007   425.23      No conducir ...
    ofstream archRep;
    aperturaArchivoEscritura(nombArchRepTabInfra,archRep);
    imprimirCabeceraRepTablaInfra(archRep);
    archRep<<fixed<<setprecision(2);
    for (int i = 0; i < cantInfraccion; i++) {
        archRep<<setw(15)<<right<<arrLetraInfraccion[i];
        archRep<<arrNumInfraccion[i];
        archRep<<setw(20)<<right<<arrMultaInfraccion[i];
        archRep<<endl;
    }
}

void imprimirCabeceraRepTablaInfra(ofstream& archRep) {
    archRep<<setw(5)<<" "<<"REPORTE DE PRUEBA PARA TABLA INFRACCIONES"<<endl;
    imprimirLineas('=',50,archRep);
    archRep<<setw(25)<<right<<"CODIGO INFRACCION";
    archRep<<setw(20)<<right<<"MULTA INFRACCION"<<endl;
}

void leerInfraccionesCometidas(const char* nombArchInfraCom,
                            char *arrLetraInfraccion,int *arrNumInfraccion,
                            double *arrMultaInfraccion,int cantInfraccion,
                            char *arrLetraPlacaInfraCom,int *arrNum1PlacaInfraCom,
                            int *arrNum2PlacaInfraCom,int *arrCantMultasPagadasInfraCom,
                            double* arrTotalMultasPagadasInfraCom,int *arrCantMultasPendInfraCom,
                            double *arrTotalMultasPendInfraCom,int *arrFechaMasAntiguaInfraCom,
                            int &cantPlacas) {
    //1/12/2020   G760-721      G2022  (no pagadas)
    //23/7/2023      P474-593     G2060   P     22/8/2023 (pagadas)
    ifstream archInfraCom;
    int fechaInfraCom,fechaPago,numInfraArch,posPlaca,num1Placa,num2Placa;
    char c,letraInfraArch,letraPlaca,letraPago,verificar;
    double valorMulta;
    aperturaArchivoLectura(nombArchInfraCom,archInfraCom);
    cantPlacas=0; //importante porque no cargamos anteriormente
    while (true) {
        fechaInfraCom=leerFecha(archInfraCom);
        if (archInfraCom.eof()) break;
        archInfraCom>>letraPlaca>>num1Placa>>c>>num2Placa>>letraInfraArch>>numInfraArch;
        verificar=archInfraCom.get();
        if (verificar==' ') {
            archInfraCom>>letraPago;
            fechaPago=leerFecha(archInfraCom); //no sirve
        }
        valorMulta=buscarMulta(arrLetraInfraccion,arrNumInfraccion,arrMultaInfraccion,
                                    letraInfraArch,numInfraArch,cantInfraccion);
        posPlaca=buscarPlaca(arrLetraPlacaInfraCom,arrNum1PlacaInfraCom,arrNum2PlacaInfraCom,
                                letraPlaca,num1Placa,num2Placa,cantPlacas);
        if (posPlaca==NO_ENCONTRADO) {
            registrarPlacaNueva(arrLetraPlacaInfraCom,arrNum1PlacaInfraCom,arrNum2PlacaInfraCom,
                                letraPlaca,num1Placa,num2Placa,cantPlacas);
            if (verificar==' ') { //Multa pagada
                arrCantMultasPagadasInfraCom[cantPlacas]++;
                arrTotalMultasPagadasInfraCom[cantPlacas]+=valorMulta;
            }else { //Multa no pagada
                arrCantMultasPendInfraCom[cantPlacas]++;
                arrTotalMultasPendInfraCom[cantPlacas]+=valorMulta;
                arrFechaMasAntiguaInfraCom[cantPlacas]=fechaInfraCom;
            }
            cantPlacas++;
        }else { //Si está registrado
            if (verificar==' ') { //Multa pagada
                arrCantMultasPagadasInfraCom[posPlaca]++;
                arrTotalMultasPagadasInfraCom[posPlaca]+=valorMulta;
            }else { //Multa no pagada
                arrCantMultasPendInfraCom[posPlaca]++;
                arrTotalMultasPendInfraCom[posPlaca]+=valorMulta;
                if (arrFechaMasAntiguaInfraCom[posPlaca]==0 or
                    arrFechaMasAntiguaInfraCom[posPlaca]>fechaInfraCom) {
                    arrFechaMasAntiguaInfraCom[posPlaca]=fechaInfraCom;
                }
            }
        }
    }
}

void registrarPlacaNueva(char*arrLetraPlacaInfraCom,int *arrNum1PlacaInfraCom,int *arrNum2PlacaInfraCom,
                        char letraPlaca,int num1Placa,int num2Placa,int cantPlacas) {
    arrLetraPlacaInfraCom[cantPlacas] = letraPlaca;
    arrNum1PlacaInfraCom[cantPlacas]  = num1Placa;
    arrNum2PlacaInfraCom[cantPlacas]  = num2Placa;
}

void ordenarPlacas(char *arrLetraInfraccion,int *arrNumInfraccion,
                    double *arrMultaInfraccion,
                    char *arrLetraPlacaInfraCom,int *arrNum1PlacaInfraCom,
                    int *arrNum2PlacaInfraCom,int *arrCantMultasPagadasInfraCom,
                    double *arrTotalMultasPagadasInfraCom,int *arrCantMultasPendInfraCom,
                    double *arrTotalMultasPendInfraCom,int *arrFechaMasAntiguaInfraCom,
                    int cantPlacas) {
    for (int i=0; i<cantPlacas-1; i++) {
        for (int j=i+1; j<cantPlacas; j++) {
            if (arrLetraPlacaInfraCom[i]>arrLetraPlacaInfraCom[j]) {
                swapChar(arrLetraInfraccion[i],arrLetraInfraccion[j]);
                swapInt(arrNumInfraccion[i],arrNumInfraccion[j]);
                swapDouble(arrMultaInfraccion[i],arrMultaInfraccion[j]);
                swapChar(arrLetraPlacaInfraCom[i],arrLetraPlacaInfraCom[j]);
                swapInt(arrNum1PlacaInfraCom[i],arrNum1PlacaInfraCom[j]);
                swapInt(arrNum2PlacaInfraCom[i],arrNum2PlacaInfraCom[j]);
                swapInt(arrCantMultasPagadasInfraCom[i],arrCantMultasPagadasInfraCom[j]);
                swapDouble(arrTotalMultasPagadasInfraCom[i],arrTotalMultasPagadasInfraCom[j]);
                swapInt(arrCantMultasPendInfraCom[i],arrCantMultasPendInfraCom[j]);
                swapDouble(arrTotalMultasPendInfraCom[i],arrTotalMultasPendInfraCom[j]);
                swapInt(arrFechaMasAntiguaInfraCom[i],arrFechaMasAntiguaInfraCom[j]);
            }
        }
    }
}

void generarReporte(const char* nombArchRep,
                    char *arrLetraPlacaInfraCom,int *arrNum1PlacaInfraCom,
                    int *arrNum2PlacaInfraCom,int *arrCantMultasPagadasInfraCom,
                    double* arrTotalMultasPagadasInfraCom,int *arrCantMultasPendInfraCom,
                    double *arrTotalMultasPendInfraCom,int *arrFechaMasAntiguaInfraCom,
                    int cantPlacas) {
    ofstream archRep;
    int cantTotal=0,cantMultasPagadasGlobal=0,cantMultasPendGlobal=0,cantMultasTotalGlobal=0;
    double totalPago=0;
    aperturaArchivoEscritura(nombArchRep,archRep);
    imprimirCabeceraReporte(archRep);
    archRep<<fixed<<setprecision(2);
    for (int i=0; i<cantPlacas; i++) {
        imprimirNroOrden(archRep,i+1);
        archRep<<setw(3)<<right<<arrLetraPlacaInfraCom[i];
        archRep<<arrNum1PlacaInfraCom[i]<<"-"<<arrNum2PlacaInfraCom[i];
        archRep<<setw(12)<<right<<arrCantMultasPagadasInfraCom[i];
        archRep<<setw(14)<<right<<arrTotalMultasPagadasInfraCom[i];
        if (arrCantMultasPendInfraCom[i]==0) {
            archRep<<setw(12)<<right<<arrCantMultasPendInfraCom[i];
            archRep<<setw(13)<<right<<arrTotalMultasPendInfraCom[i];
            archRep<<setw(15)<<right<<"----------";
        }else {
            archRep<<setw(12)<<right<<arrCantMultasPendInfraCom[i];
            archRep<<setw(13)<<right<<arrTotalMultasPendInfraCom[i];
            archRep<<setw(5)<<" ";imprimirFecha(archRep,arrFechaMasAntiguaInfraCom[i]);
        }
        cantTotal=arrCantMultasPagadasInfraCom[i]+arrCantMultasPendInfraCom[i];
        totalPago=arrTotalMultasPagadasInfraCom[i]+arrTotalMultasPendInfraCom[i];
        archRep<<setw(12)<<right<<cantTotal;
        archRep<<setw(13)<<right<<totalPago<<endl;
        cantMultasPagadasGlobal+=arrCantMultasPagadasInfraCom[i];
        cantMultasPendGlobal+=arrCantMultasPendInfraCom[i];
        cantMultasTotalGlobal+=cantTotal;
    }
    //ImprimirResumenFinal --->flojera
}

void imprimirNroOrden(ofstream& archRep,int orden) {
    archRep<<setw(3)<<right<<orden<<")";
}

void imprimirCabeceraReporte(ofstream& archRep) {
    archRep<<setw(40)<<" "<<"MINISTERIO DE TRANSPORTES"<<endl;
    archRep<<setw(30)<<" "<<"LISTADO DE INFRACCIONES TOTALIZADAS POR PLACA"<<endl;
    imprimirLineas('=',110,archRep);
    archRep<<setw(38)<<right<<"MULTAS PAGADAS";
    archRep<<setw(35)<<right<<"MULTAS PENDIENTES";
    archRep<<setw(30)<<right<<"MULTAS TOTALES"<<endl;
    archRep<<setw(11)<<right<<"PLACA";
    archRep<<setw(19)<<right<<"CANTIDAD";
    archRep<<setw(10)<<right<<"TOTAL";
    archRep<<setw(15)<<right<<"CANTIDAD";
    archRep<<setw(10)<<right<<"TOTAL";
    archRep<<setw(15)<<right<<"MAS ANTIGUA";
    archRep<<setw(15)<<right<<"CANTIDAD";
    archRep<<setw(10)<<right<<"TOTAL"<<endl;
    imprimirLineas('=',110,archRep);
}

void swapInt(int &a,int &b) {
    int aux=a;
    a=b;
    b=aux;
}

void swapDouble(double &a,double &b) {
    double aux=a;
    a=b;
    b=aux;
}

void swapChar(char &a,char &b) {
    char aux=a;
    a=b;
    b=aux;
}

int buscarPlaca(char *arrLetraPlacaInfraCom,int *arrNum1PlacaInfraCom,int *arrNum2PlacaInfraCom,
                char letraPlaca,int num1Placa,int num2Placa,int cantPlacas) {
    for (int i = 0; i < cantPlacas; i++)
        if (arrLetraPlacaInfraCom[i]==letraPlaca and
            arrNum1PlacaInfraCom[i]==num1Placa and
            arrNum2PlacaInfraCom[i]==num2Placa) return i;
    return NO_ENCONTRADO;
}

double buscarMulta(char *arrLetraInfraccion,int *arrNumInfraccion,double* arrMultaInfraccion,
                    char letraInfraArch,int numInfraArch,int cantInfraccion) {
    for (int i = 0; i < cantInfraccion; i++)
        if (arrLetraInfraccion[i]==letraInfraArch and
            arrNumInfraccion[i]==numInfraArch) return arrMultaInfraccion[i];
    return NO_ENCONTRADO;
}

int leerFecha(ifstream& input) {
    int dd,mm,yyyy;
    char c;
    input>>dd>>c>>mm>>c>>yyyy;
    return yyyy*10000+mm*100+dd;
}

void imprimirFecha(ofstream& output,int fecha) {
    int dd,mm,yyyy;
    yyyy=fecha/10000;
    fecha%=10000;
    mm=fecha/100;
    fecha%=100;
    dd=fecha;
    output.fill('0');
    output<<setw(2)<<right<<dd<<"/";
    output<<setw(2)<<right<<mm<<"/";
    output<<setw(4)<<right<<yyyy;
    output.fill(' ');
}

void imprimirLineas(char c,int cant,ofstream& archRep) {
    for (int i = 0; i < cant; i++) archRep<<c;
    archRep<<endl;
}

void ignorar(ifstream& input,char delimitador) {
    char c;
    input>>ws;
    while (true) {
        c=input.get();
        if (c==delimitador) break;
    }
}
