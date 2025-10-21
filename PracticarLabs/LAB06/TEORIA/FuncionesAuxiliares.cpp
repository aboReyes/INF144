//
// Created by DIEGO on 10/21/2025.
//

#include "FuncionesAuxiliares.h"


void aperturaArchivoLectura(const char* nombArch,ifstream& arch) {
    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"ERROR, el archivo "<<nombArch<<" no se puede abrir"<<endl;
        exit(1);
    }
}

void aperturaArchivoEscritura(const char* nombArch,ofstream& arch) {
    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout<<"ERROR, el archivo "<<nombArch<<" no se puede abrir"<<endl;
        exit(1);
    }
}

void ordenar(int *arr1,char* arr2,double* arr3,int cant) {
    for(int i=0;i<cant-1;i++) {
        for(int j=i+1;j<cant;j++) {
            //si me piden a>b and c<d
            if (arr1[i]>arr1[j] or
                arr1[i]==arr1[j] and
                arr2[i]<arr2[j]) {
                //lo que cambiaras
                swapInt(arr1[i],arr1[j]);
                swapChar(arr2[i],arr2[j]);
                swapDouble(arr3[i],arr3[j]);
            }
        }
    }
}

void leerInsertarOrdenado(const char* nombArch,
                        int* arrDato1,double* arrDato2,
                        char* arrDato3,int cantDatos) {
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    //dato1  dato2  dato3
    int dato1;
    double dato2;
    char dato3;
    while(true) {
        input>>dato1;
        if (input.eof()) break;
        input>>dato2;
        input>>dato3;
        insertarOrdenado(dato1,dato2,dato3,
                        arrDato1,arrDato2,arrDato3,cantDatos);
    }
}

void insertarOrdenado(int dato1,double dato2,char dato3,
                    int* arrDato1,double* arrDato2,char* arrDato3,
                    int &cantDatos) {
    int i=cantDatos-1;
    while (i>0 and arrDato1[i]<dato1) { //condición
        arrDato1[i+1]=arrDato1[i];
        arrDato2[i+1]=arrDato2[i];
        arrDato3[i+1]=arrDato3[i];
        i--;
    }
    //acá se inicializan, osea cuando no entran al bucle
    arrDato1[i+1]=dato1;
    arrDato2[i+1]=dato2;
    arrDato3[i+1]=dato3;
    cantDatos++;
}

int buscarBinario(int dato1,int* arrDato1,int cant) {
    int limiteInferior=0;
    int limiteSuperior=cant-1;
    //puntoMedio=posEncontrada
    while (true) {
        if (limiteInferior>limiteSuperior) return -1;
        int puntoMedio=(limiteInferior+limiteSuperior)/2;
        if (dato1==arrDato1[puntoMedio]) return puntoMedio;
        if (dato1>arrDato1[puntoMedio])
            limiteInferior=puntoMedio;
        else
            limiteSuperior=puntoMedio;
    }
}

//queda en duda este
void eliminar(int*arrDato1,char*arrDato2,double*arrDato3,int cantDatos) {

    for (int i=0;i<cantDatos;) {
        //Elimino?
        if (arrDato1[i]<0) {
            for (int j=i+1;j<cantDatos;j++) {
                arrDato1[j-1]=arrDato1[j];
                arrDato2[j-1]=arrDato2[j];
                arrDato3[j-1]=arrDato3[j];
            }
        }else {
            i++;
        }
    }
}

void swapInt(int &a,int &b) {
    int temp=a;
    a=b;
    b=temp;
}

void swapChar(char &a,char &b) {
    char temp=a;
    a=b;
    b=temp;
}

void swapDouble(double &a,double &b) {
    double temp=a;
    a=b;
    b=temp;
}
