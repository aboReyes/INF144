//
// Created by ASUS on 30/10/2025.
//

#include "FuncionesAuxiliares.h"

#include <cstring>
#include <pstl/algorithm_fwd.h>

void aperturaArchivoLectura(const char* nombArch,ifstream& arch) {
    arch.open(nombArch, ios::in);
    if (not arch.is_open()) {
        cout<<"ERROR, el archivo "<<nombArch<<" no se puede abrir"<<endl;
        exit(1);
    }
}

void aperturaArchivoEscritura(const char* nombArch,ofstream& arch) {
    arch.open(nombArch, ios::out);
    if (not arch.is_open()) {
        cout<<"ERROR, el archivo "<<nombArch<<" no se puede abrir"<<endl;
        exit(1);
    }
}

void cargarProductosConCstring(const char* nombArch,
                    int *arrCodeProducto,int *arrStockProducto,
                    char* *arrDescProd,int &cantProductos){
    ////362085    96    ENALAPRIL T/30 10MG
    ifstream archProductos;
    int codeProducto;
    char cadenaAux[120]; //memoria estática, al final va a desaparecer
    aperturaArchivoLectura(nombArch,archProductos);
    while (true) {
        archProductos>>codeProducto;
        if (archProductos.eof()) break;
        archProductos>>arrStockProducto[cantProductos];

        //1)lee espacio blanco (ws)
        //2)getline (cadena estática, cantidad, delimitador)
        //3)crear un nuevo arreglo dinamico donde strlen guarda la cantidad de la cadena aux
        //recordar el +1 para el caracter de terminacion de cadena
        //4)lo copia strcpy (char **[i], cadena aux )
        archProductos>>ws;
        archProductos.getline(cadenaAux,120,'\n');
        arrDescProd[cantProductos]=new char [strlen(cadenaAux)+1]; //reserva de espacio
        strcpy (arrDescProd[cantProductos],cadenaAux);

        arrCodeProducto[cantProductos]=codeProducto;
        cantProductos++;
    }
}

void cargarProductosSinCstring(const char* nombArch,
                    int *arrCodeProducto,int *arrStockProducto,
                    char* *arrDescProd,int &cantProductos) {
    ////362085    96    ENALAPRIL T/30 10MG
    ifstream archProductos;
    int codeProducto,longitud;
    char cadenaAux[100]; //memoria estática, al final va a desaparecer
    aperturaArchivoLectura(nombArch,archProductos);
    while (true) {
        archProductos>>codeProducto;
        if (archProductos.eof()) break;
        archProductos>>arrStockProducto[cantProductos];

        archProductos>>ws;
        archProductos.getline(cadenaAux,100,'\n');
        longitud=calcularLongitud(cadenaAux);
        arrDescProd[cantProductos]=new char [longitud+1];
        copiar(arrDescProd[cantProductos],cadenaAux);

        arrCodeProducto[cantProductos]=codeProducto;
        cantProductos++;
    }
}

void pruebaProductos(const char* nombArchRep,
                    int *arrCodeProducto,int *arrStockProducto,
                    char **arrDescProd,int cantProductos) {
    ofstream output;
    aperturaArchivoEscritura(nombArchRep,output);
    imprimirSubtituloPruebaProductos(output);
    for (int i=0;i<cantProductos;i++) {
        output<<setw(13)<<right<<arrCodeProducto[i];
        output<<setw(17)<<right<<arrStockProducto[i];
        output<<setw(14)<<" "<<arrDescProd[i]<<endl;
    }
}

void procesarMovimientos(const char* nombArchMov,
                        int *arrCodeProducto,int *arrStockProducto,
                        char **arrDescProd,int &cantProductos,
                        int *arrCodeProductoDef,int *arrStockProductoDef,
                        char **arrDescProdDef,int &cantProductosDef) {
    //750   63640178   (P o R)
    //605093   24
    //835103   37
    //538466   20
    //R --> reponiendo (+)
    //P --> solicitando (-)
    ifstream archMov;
    int numOperacion,codeUnidad,codeProducto,cantMov;
    char tipoMov;
    aperturaArchivoLectura(nombArchMov,archMov);
    while (true) {
        archMov>>numOperacion;
        if (archMov.eof()) break;
        archMov>>codeUnidad;
        archMov>>tipoMov;
        while (true) {
            archMov>>codeProducto;
            archMov>>cantMov;
            actualizarMovimientos(tipoMov,codeProducto,cantMov,
                                arrCodeProducto,arrStockProducto,
                                arrDescProd,cantProductos,
                                arrCodeProductoDef,arrStockProductoDef,
                                arrDescProdDef,cantProductosDef);
            if (archMov.get()=='\n') break;
        }
    }
}

//lo haré después de comer c:
void actualizarMovimientos(char tipoMov,int codeProducto,int cantMov,
                            int *arrCodeProducto,int *arrStockProducto,
                            char **arrDescProd,int &cantProductos,
                            int *arrCodeProductoDef,int *arrStockProductoDef,
                            char **arrDescProdDef,int &cantProductosDef) {
    int posProducto=buscarPosicion(codeProducto,arrCodeProducto,cantProductos);
    if (posProducto!=NO_ENCONTRADO) {
        if (tipoMov=='R') {
            arrStockProducto[posProducto]+=cantMov;
        }else if (tipoMov=='P') {
            arrStockProducto[posProducto]-=cantMov;
            if (arrStockProducto[posProducto]<0) {
                enviarProductoAOtroArreglo(arrCodeProducto[posProducto],arrStockProducto[posProducto],
                                arrDescProd[posProducto],arrCodeProductoDef,arrStockProductoDef,
                                arrDescProdDef,cantProductosDef);
                eliminarProducto(arrCodeProducto,arrStockProducto,arrDescProd,cantProductos,posProducto);
            }
        }
    }else {
        posProducto=buscarPosicion(codeProducto,arrCodeProductoDef,cantProductosDef);
        if (posProducto!=NO_ENCONTRADO) {
            if (tipoMov=='P') {
                arrStockProductoDef[posProducto]+=cantMov;
            }else if (tipoMov=='R') {
                arrStockProductoDef[posProducto]-=cantMov;
                if (arrStockProductoDef[posProducto]<0) {
                    enviarProductoAOtroArreglo(arrCodeProductoDef[posProducto],
                    arrStockProductoDef[posProducto],arrDescProdDef[posProducto],
                                   arrCodeProducto,arrStockProducto,arrDescProd,
                                cantProductos);
                    eliminarProducto(arrCodeProductoDef,arrStockProductoDef,arrDescProdDef,
                                cantProductosDef,posProducto);
                }
            }
        }
    }
}


void generarReporte(const char *nombArchRep,
        int *arrCodeProducto,int *arrStockProducto,char **arrDescProd,int cantProductos,
        int *arrCodeProductoDef,int *arrStockProductoDef,char **arrDescProdDef,int cantProductosDef) {
    ofstream output;
    aperturaArchivoEscritura(nombArchRep,output);
    imprimirLineas('=',90,output);
    output<<setw(35)<<" "<<"ARREGLO ORIGINAL"<<endl;
    imprimirLineas('=',90,output);
    imprimirSubtituloReporte(output);
    for (int i=0;i<cantProductos;i++) {
        output<<setw(10)<<right<<arrCodeProducto[i];
        output<<setw(20)<<" ";
        output<<setw(45)<<left<<arrDescProd[i];
        output<<setw(10)<<right<<arrStockProducto[i]<<endl;
    }
    imprimirLineas('=',90,output);
    output<<setw(35)<<" "<<"ARREGLO DEFICIT"<<endl;
    imprimirLineas('=',90,output);
    imprimirSubtituloReporte(output);
    for (int i=0;i<cantProductosDef;i++) {
        output<<setw(10)<<right<<arrCodeProductoDef[i];
        output<<setw(20)<<" ";
        output<<setw(45)<<left<<arrDescProdDef[i];
        output<<setw(10)<<right<<arrStockProductoDef[i]<<endl;
    }
}

void ordenarReporte(int *arrCodeProducto,int *arrStockProducto,char **arrDescProd,int cantProductos,
                    int *arrCodeProductoDef,int *arrStockProductoDef,char **arrDescProdDef,int cantProductosDef) {
    for (int i=0;i<cantProductos-1;i++) {
        for (int j=i+1;j<cantProductos;j++) {
            if (arrCodeProducto[i]>arrCodeProducto[j]) {
                swapInt(arrCodeProducto[i],arrCodeProducto[j]);
                swapInt(arrStockProducto[i],arrStockProducto[j]);
                swapChar(arrDescProd[i],arrDescProd[j]);
            }
        }
    }
    for (int i=0;i<cantProductosDef-1;i++) {
        for (int j=i+1;j<cantProductosDef;j++) {
            if (arrCodeProductoDef[i]>arrCodeProductoDef[j]) {
                swapInt(arrCodeProductoDef[i],arrCodeProductoDef[j]);
                swapInt(arrStockProductoDef[i],arrStockProductoDef[j]);
                swapChar(arrDescProdDef[i],arrDescProdDef[j]);
            }
        }
    }
}

void swapInt(int&a,int&b) {
    int aux=a;
    a=b;
    b=aux;
}

//nuevo :o
void swapChar(char* &a,char* &b) {
    char* aux=a;
    a=b;
    b=aux;
}

void swapDouble(double&a,double&b) {
    double aux=a;
    a=b;
    b=aux;
}

void imprimirSubtituloReporte(ofstream& output) {
    output<<setw(10)<<right<<"CODIGO";
    output<<setw(40)<<right<<"DESCRIPCION";
    output<<setw(37)<<right<<"STOCK"<<endl;
    imprimirLineas('-',90,output);
}

void enviarProductoAOtroArreglo(int codeProducto,int stockProducto,char *descProducto,
                                int *arrCodeProducto,int *arrStockProducto,char**arrDescProducto,
                                int &cantProductos) {
    arrCodeProducto[cantProductos]=codeProducto;
    arrStockProducto[cantProductos]=-1*stockProducto;
    arrDescProducto[cantProductos]=descProducto;
    cantProductos++;
}

void eliminarProducto(int *arrCodeProducto,int *arrStockProducto,
                        char **arrDescProd,int &cantProductos,int posProducto) {
    for (int i=posProducto+1;i<cantProductos;i++) {
        arrCodeProducto[i-1]=arrCodeProducto[i];
        arrStockProducto[i-1]=arrStockProducto[i];
        arrDescProd[i-1]=arrDescProd[i];
    }
    cantProductos--;
}

int buscarPosicion(int dato,int *arrDato,int cantDatos) {
    for (int i=0;i<cantDatos;i++)
        if (dato==arrDato[i]) return i;
    return -1;
}

void imprimirSubtituloPruebaProductos(ofstream& output) {
    output<<setw(20)<<" "<<"REPORTE DE PRUEBA PARA PRODUCTOS "<<endl;
    imprimirLineas('=',80,output);
    output<<setw(18)<<right<<"CODIGO PRODUCTO";
    output<<setw(17)<<right<<"CODIGO STOCK";
    output<<setw(20)<<right<<"DESCRIPCION"<<endl;
    imprimirLineas('-',80,output);
}

void imprimirLineas(char c,int cant,ofstream& output) {
    for (int i=0;i<cant;i++) output<<c;
    output<<endl;
}

int calcularLongitud(const char *cadenaAux) {
    int i;
    for (i=0;cadenaAux[i];i++);
    return i;
}

void copiar(char* arrDescProd,const char* cadenaAux) {
    int i;
    for (i=0;cadenaAux[i];i++)
        arrDescProd[i]=cadenaAux[i];
    arrDescProd[i]='\0';
}
