//
// Created by ASUS on 5/10/2025.
//

#include "FuncionesAuxiliares.h"
#include <regex>

void aperturaArchivoLectura(const char* nombArch,ifstream& arch) {
    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"ERROR, el archivo"<<nombArch<<" no se pudo abrir"<<endl;
        exit(1);
    }
}

void aperturaArchivoEscritura(const char* nombArch,ofstream& arch) {
    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout<<"ERROR, el archivo"<<nombArch<<" no se pudo abrir"<<endl;
        exit(1);
    }
}

void cargarRepresentantesEmpresas(const char* nombArchEmpresas,
                                int *arrDniRepreEmpresa, int &nroRepreEmpresa) {
    ifstream archEmpresas;
    int dniRepreEmpresa;
    aperturaArchivoLectura(nombArchEmpresas,archEmpresas);
    //79672079      contreras/chang/johana-cinthia    Chorrillos
    while (true) {
        archEmpresas>>dniRepreEmpresa;
        if (archEmpresas.eof()) break;
        ignorar(archEmpresas,'\n');
        arrDniRepreEmpresa[nroRepreEmpresa]=dniRepreEmpresa;
        nroRepreEmpresa++;
    }
}

void cargarMultasInfraccion(const char* nombArchTablaInfra,char *arrCodeCharInfraccion,
                            int *arrCodeIntInfraccion,double *arrMultaInfraccion,int &nroMultas) {
    //G2007   425.23      No conducir ...
    ifstream archTablaInfra;
    char codeCharInfraArch;
    int codeIntInfraArch;
    aperturaArchivoLectura(nombArchTablaInfra,archTablaInfra);
    while (true) {
        archTablaInfra>>codeCharInfraArch>>codeIntInfraArch;
        if (archTablaInfra.eof()) break;
        archTablaInfra>>arrMultaInfraccion[nroMultas];
        ignorar(archTablaInfra,'\n');
        arrCodeCharInfraccion[nroMultas]=codeCharInfraArch;
        arrCodeIntInfraccion[nroMultas]=codeIntInfraArch;
        nroMultas++;
    }
}

void cargarPlacas(const char*nombArchPlacasReg,int *arrDniRegistroPlaca,
                char*arrCodeCharPlaca,int *arrCodeIntPlaca,int &nroPlacas) {
    //82870470     P516-487
    ifstream archPlacasReg;
    int dniPlacaReg,placa1,placa2;
    char c;
    aperturaArchivoLectura(nombArchPlacasReg,archPlacasReg);
    while (true) {
        archPlacasReg>>dniPlacaReg;
        if (archPlacasReg.eof()) break;
        archPlacasReg>>arrCodeCharPlaca[nroPlacas];
        archPlacasReg>>placa1>>c;
        archPlacasReg>>placa2;
        arrCodeIntPlaca[nroPlacas]=placa1*1000+placa2;
        arrDniRegistroPlaca[nroPlacas]=dniPlacaReg;
        nroPlacas++;
    }
}

void procesarInfraccionesCometidas(const char* nombArchInfraCom,int *arrDniRepreEmpresa,int nroRepreEmpresa,
                            char *arrCodeCharInfraccion,int *arrCodeIntInfraccion,double *arrMultaInfraccion,int nroMultas,
                            int *arrDniRegistroPlaca,char* arrCodeCharPlaca,int *arrCodeIntPlaca,int nroPlacas,
                            int *arrCantLevesEmpresas,int *arrCantGravesEmpresas,int *arrCantMuyGravesEmpresas,
                            double *arrMontoLevesEmpresas,double *arrMontoGravesEmpresas,double *arrMontoMuyGravesEmpresas,
                            int *arrCantMultasInfraccion,double *arrTotalMultasInfraccion) {
    //1/12/2020   G760-721      G2022
    ifstream archInfraCom;
    aperturaArchivoLectura(nombArchInfraCom,archInfraCom);
    int num1,num2,num3;//fecha que no me sirve
    int placa1,placa2,codeIntPlaca,dniEmpresa,codeIntMulta;
    char c,codeCharPlaca,codeCharMulta;
    while (true) {
        archInfraCom>>num1>>c>>num2>>c>>num3;
        if (archInfraCom.eof()) break;
        archInfraCom>>codeCharPlaca>>placa1>>c>>placa2>>codeCharMulta>>codeIntMulta;
        codeIntPlaca=placa1*1000+placa2;
        int dniEmpresa=obtenerDniEmpresa(codeCharPlaca,codeIntPlaca,arrDniRegistroPlaca,
                                        arrCodeCharPlaca,arrCodeIntPlaca,nroPlacas);
        if (dniEmpresa!=-1) {
            int posEmpresa=buscarEmpresa(dniEmpresa,arrDniRepreEmpresa,nroRepreEmpresa);
            if (posEmpresa!=-1) {
                int posMulta=buscarMulta(codeCharMulta,codeIntMulta,arrCodeCharInfraccion,arrCodeIntInfraccion,nroMultas);
                if (posMulta!=-1) {
                    double valorMulta=arrMultaInfraccion[posMulta];
                    arrCantMultasInfraccion[posMulta]++;
                    arrTotalMultasInfraccion[posMulta]+=valorMulta;
                    if (codeCharMulta=='L') {
                        arrCantLevesEmpresas[posEmpresa]++;
                        arrMontoLevesEmpresas[posEmpresa]+=valorMulta;
                    }else if (codeCharMulta=='G') {
                        arrCantGravesEmpresas[posEmpresa]++;
                        arrMontoGravesEmpresas[posEmpresa]+=valorMulta;
                    }else if (codeCharMulta=='M') {
                        arrCantMuyGravesEmpresas[posEmpresa]++;
                        arrMontoMuyGravesEmpresas[posEmpresa]+=valorMulta;
                    }
                }
            }
        }
    }
}
void ordenarReporte(int *arrDniRepreEmpresa,int nroRepreEmpresa,
                    int *arrCantLevesEmpresas,int *arrCantGravesEmpresas,int *arrCantMuyGravesEmpresas,
                    double *arrMontoLevesEmpresas,double *arrMontoGravesEmpresas,double *arrMontoMuyGravesEmpresas,
                    char *arrCodeCharInfraccion,int *arrCodeIntInfraccion,double *arrMultaInfraccion,int nroMultas,
                    int *arrCantMultasInfraccion,double *arrTotalMultasInfraccion) {
    for (int i = 0; i < nroRepreEmpresa-1; i++) {
        for (int k = i+1; k < nroRepreEmpresa; k++){
            if (arrDniRepreEmpresa[i]>arrDniRepreEmpresa[k]) {
                swapInt(arrDniRepreEmpresa[i],arrDniRepreEmpresa[k]);
                swapInt(arrCantLevesEmpresas[i],arrCantLevesEmpresas[k]);
                swapInt(arrCantGravesEmpresas[i],arrCantGravesEmpresas[k]);
                swapInt(arrCantMuyGravesEmpresas[i],arrCantMuyGravesEmpresas[k]);
                swapDouble(arrMontoLevesEmpresas[i],arrMontoLevesEmpresas[k]);
                swapDouble(arrMontoGravesEmpresas[i],arrMontoGravesEmpresas[k]);
                swapDouble(arrMontoMuyGravesEmpresas[i],arrMontoMuyGravesEmpresas[k]);
            }
        }
    }
    for (int i=0;i<nroMultas-1;i++) {
        for (int k = i+1; k < nroMultas; k++) {
            if (arrCodeIntInfraccion[i]>arrCodeIntInfraccion[k]) {
                swapInt(arrCodeIntInfraccion[i],arrCodeIntInfraccion[k]);
                swapChar(arrCodeCharInfraccion[i],arrCodeCharInfraccion[k]);
                swapDouble(arrMultaInfraccion[i],arrMultaInfraccion[k]);
                swapInt(arrCantMultasInfraccion[i],arrCantMultasInfraccion[k]);
                swapDouble(arrTotalMultasInfraccion[i],arrTotalMultasInfraccion[k]);
            }
        }
    }
}

void generarReporte(const char* nombArchRep,int *arrDniRepreEmpresa,int nroRepreEmpresa,
                    int *arrCantLevesEmpresas,int *arrCantGravesEmpresas,int *arrCantMuyGravesEmpresas,
                    double *arrMontoLevesEmpresas,double *arrMontoGravesEmpresas,double *arrMontoMuyGravesEmpresas,
                    char *arrCodeCharInfraccion,int *arrCodeIntInfraccion,double *arrMultaInfraccion,int nroMultas,
                    int *arrCantMultasInfraccion,double *arrTotalMultasInfraccion){
    ofstream output;
    aperturaArchivoEscritura(nombArchRep,output);
    imprimirTitulo(output);
    output<<fixed<<setprecision(2);
    for (int i = 0; i < nroRepreEmpresa; i++) {
        output<<"COMPANIA No. "<<setw(2)<<right<<i+1;
        output<<" DNI DEL REPRESENTANTE LEGAL:"<<setw(10)<<right<<arrDniRepreEmpresa[i]<<endl;
        imprimirLineas('-',150,output);
        imprimirSubtituloRepEmpresas(output);
        output<<setw(8)<<" "<<arrCantLevesEmpresas[i]<<setw(20)<<right<<arrMontoLevesEmpresas[i];
        output<<setw(17)<<" "<<arrCantGravesEmpresas[i]<<setw(20)<<right<<arrMontoGravesEmpresas[i];
        output<<setw(17)<<" "<<arrCantMuyGravesEmpresas[i]<<setw(20)<<right<<arrMontoMuyGravesEmpresas[i];
        output<<setw(17)<<" "<<arrCantMultasInfraccion[i]<<setw(20)<<right<<arrTotalMultasInfraccion[i];
        output<<endl;
        imprimirLineas('-',150,output);
    }
    imprimirLineas('/',130,output);
    output<<setw(45)<<" "<<"MULTAS IMPUESTAS POR INFRACCION"<<endl;
    imprimirLineas('=',150,output);
    for (int i=0;i<nroMultas;i++) {
        imprimirSubtituloMultasInfraccion(output);
        output<<setw(25)<<" "<<arrCodeIntInfraccion[i];
        if (arrCodeCharInfraccion[i]=='L') {
            output<<setw(15)<<right<<"LEVE";
        }else if (arrCodeCharInfraccion[i]=='G') {
            output<<setw(15)<<right<<"GRAVE";
        }else if (arrCodeCharInfraccion[i]=='M') {
            output<<setw(15)<<right<<"MUY GRAVE";
        }
        output<<setw(15)<<right<<arrMultaInfraccion[i];
        output<<setw(15)<<right<<arrCantMultasInfraccion[i];
        output<<setw(23)<<right<<arrTotalMultasInfraccion[i];
        output<<endl;
        imprimirLineas('-',150,output);
    }
}

void imprimirSubtituloMultasInfraccion(ofstream &output) {
    output<<setw(25)<<" "<<"CODIGO";
    output<<setw(5)<<" "<<"GRAVEDAD";
    output<<setw(10)<<" "<<"MULTA";
    output<<setw(10)<<" "<<"CANTIDAD";
    output<<setw(10)<<" "<<"MONTO TOTAL"<<endl;
}

void imprimirSubtituloRepEmpresas(ofstream& output) {
    output<<"MULTAS APLICADAS SEGUN LA GRAVEDAD:"<<endl;
    output<<setw(13)<<" "<<"LEVES"<<setw(33)<<" "<<"GRAVES"<<setw(31)<<" "<<"MUY GRAVES"<<setw(28)<<" "<<"TOTALES"<<endl;
    output<<setw(5)<<" "<<"CANTIDAD"<<setw(5)<<" "<<"TOTAL DE MULTAS"<<setw(10)<<" "<<"CANTIDAD"<<setw(5)<<" "<<"TOTAL DE MULTAS"
    <<setw(10)<<" "<<"CANTIDAD"<<setw(5)<<" "<<"TOTAL DE MULTAS"<<setw(10)<<" "<<"CANTIDAD"<<setw(5)<<" "<<"TOTAL DE MULTAS"<<endl;
}

int obtenerDniEmpresa(char codeCharPlaca,int codeIntPlaca,int *arrDniRegistroPlaca,
                        char *arrCodeCharPlaca,int *arrCodeIntPlaca,int nroPlacas) {
    for (int i=0;i<nroPlacas;i++)
        if (codeCharPlaca==arrCodeCharPlaca[i] and codeIntPlaca==arrCodeIntPlaca[i]) return arrDniRegistroPlaca[i];
    return -1;
}

int buscarEmpresa(int dniEmpresa,int *arrDniRepreEmpresa,int nroRepreEmpresa) {
    for (int i=0; i<nroRepreEmpresa; i++)
        if (arrDniRepreEmpresa[i]==dniEmpresa) return i;
    return -1;
}

int buscarMulta(char codeCharMulta,int codeIntMulta,char *arrCodeCharInfraccion,int *arrCodeIntInfraccion,int nroMultas) {
    for (int i=0;i<nroMultas;i++)
        if (arrCodeCharInfraccion[i]==codeCharMulta and codeIntMulta==arrCodeIntInfraccion[i]) return i;
    return -1;
}

void imprimirTitulo(ofstream& output) {
    output<<setw(60)<<" "<<"MINISTERIO DE TRANSPORTE"<<endl;
    output<<setw(55)<<" "<<"MULTAS IMPUESTAS A LAS COMPAÑIAS"<<endl;
    imprimirLineas('=',150,output);
}

void imprimirLineas(char c,int cant,ofstream& output) {
    for (int i = 0; i < cant; i++) output << c ;
    output << endl;
}

void imprimirOrden(ofstream& output,int nroOrden) {
    output.fill('0');
    output << setw(2)<< right<< nroOrden<<")";
    output.fill(' ');
}

void swapInt(int &a, int &b) {
    int aux;
    aux = a;
    a = b;
    b = aux;
}

void swapDouble(double &a,double& b) {
    double aux;
    aux = a;
    a = b;
    b = aux;
}

void swapChar(char &a,char&b) {
    char aux;
    aux = a;
    a = b;
    b = aux;
}

void ignorar(ifstream& input,char delimitador) {
    char c;
    input>>ws;
    while (true) {
        c=input.get();
        if (c==delimitador) break;
    }
}
