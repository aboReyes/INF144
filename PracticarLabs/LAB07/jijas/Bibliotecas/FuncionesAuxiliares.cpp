//
// Created by ASUS on 1/11/2025.
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

void cargarArchivos(const char *nombArch,
                    char **arrNombres,int &cantNombres,
                    bool esformato1,bool esformato2,bool esformato3,bool esformato4) {
    ifstream input;
    char *nombre;
    aperturaArchivoLectura(nombArch,input);
    while (true) {
        arrNombres[cantNombres]=leerString(input);
        //nombre=leerString(input);
        if (input.eof()) break;
        if (esformato1) formato1(arrNombres[cantNombres]);
        else if (esformato2) {
            formato1(arrNombres[cantNombres]);
            formato2(arrNombres[cantNombres]);
        }else if (esformato3) {
            formato1(arrNombres[cantNombres]);
            formato2(arrNombres[cantNombres]);
            formato3(arrNombres[cantNombres]);
        }else if (esformato4) {
            formato1(arrNombres[cantNombres]);
            formato2(arrNombres[cantNombres]);
            formato3(arrNombres[cantNombres]);
            formato4(arrNombres[cantNombres]);
            formato5(arrNombres[cantNombres]);
        }
        cantNombres++;
    }
}

void formato4(char *arrNombres) {
    //Lopez Reyes, Diego Axel --> LOPEZ
    //Guardamos el primer espacio en blanco
    int primerEspacio=0;
    for (int i=0;arrNombres[i];i++) {
        if (arrNombres[i]==' ') {
            primerEspacio=i;
            break;
        }
    }
    arrNombres[primerEspacio]='\0';
}

void formato5(char* arrNombres) {
    //Lopez -->LOPEZ
    for (int i=0;arrNombres[i];i++) {
        if (arrNombres[i]>='a' and arrNombres[i]<='z') {
            arrNombres[i]-='a'-'A';
        }
    }
}


void formato3(char *arrNombres) {
    //Diego Axel Lopez Reyes --> Lopez Reyes, Diego Axel
    //Guardamos el ultimo y penultimo que tiene ' '
    int penultimo=-1,ultimo=-1;
    for (int i=0;arrNombres[i];i++) {
        if (arrNombres[i]==' ') {
            penultimo=ultimo;
            ultimo=i;
        }
    }
    if (penultimo==-1) return;

    char nombre2[2*MAX_CARACTERES+3]; //buffer temporal grande
    nombre2[0]='\0';
    strcat(nombre2,arrNombres+penultimo+1); //Lopez Reyes
    strcat(nombre2,", "); //Lopez Reyes,
    arrNombres[penultimo]='\0'; //Original: Diego Axel
    strcat(nombre2,arrNombres); //Lopez Reyes, Diego Axel
    strcpy(arrNombres,nombre2); //copio al resultado devuelta a arrNombres
}

void imprimirReporte(const char*nombArchRep,
                    char **arrNombres,int cantNombres) {
    ofstream output;
    aperturaArchivoEscritura(nombArchRep,output);
    for (int i=0;i<cantNombres;i++) {
        output<<arrNombres[i]<<endl;
    }
}

void formato2(char *arrNombres) {
    //diego axel lopez reyes
    bool esPrimero=true;
    for (int i=0;arrNombres[i];i++) {
        if (esPrimero) {
            esPrimero=false;
            if (arrNombres[i]>='a' and arrNombres[i]<='z') {
                arrNombres[i]-='a'-'A';
            }
        }else {
            if (arrNombres[i]==' ') {
                esPrimero=true;
            }
        }
    }
}

void formato1(char *arrNombres) {
    for (int i=0; arrNombres[i]; i++)
        if (arrNombres[i]=='_') arrNombres[i]=' ';
}

char* leerString(ifstream&input) {
    char buffer[MAX_CARACTERES];
    input>>buffer;
    if (input.eof()) return nullptr;
    char* str=new char[strlen(buffer)+1];
    strcpy(str,buffer);
    return str;
}
