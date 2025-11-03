//
// Created by ASUS on 1/11/2025.
//

#ifndef PRACTICAR_FUNCIONESAUXILIARES_H
#define PRACTICAR_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#define MAX_NOMBRES 10
#define MAX_CARACTERES 100

void aperturaArchivoLectura(const char* nombArch,ifstream& arch);
void aperturaArchivoEscritura(const char* nombArch,ofstream& arch);

void cargarArchivos(const char *nombArch,
                    char **arrNombres,int &cantNombres,
                    bool esformato1,bool esformato2,bool esformato3,bool esformato4);

void imprimirReporte(const char*nombArchRep,
                    char **arrNombres,int cantNombres);

char* leerString(ifstream&input);

void formato1(char *arrNombres);
void formato2(char *arrNombres);
void formato3(char *arrNombres);
void formato4(char *arrNombres);
void formato5(char* arrNombres);


#endif //PRACTICAR_FUNCIONESAUXILIARES_H
