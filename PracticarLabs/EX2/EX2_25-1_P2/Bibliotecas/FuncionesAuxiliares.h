//
// Created by ASUS on 30/11/2025.
//

#ifndef EX2_25_1_P2_FUNCIONESAUXILIARES_H
#define EX2_25_1_P2_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "Infraccion.h"
#include "Lista.h"
#include "Nodo.h"

//apertura de archivos
void aperturaArchivoLectura(const char* nombArch,ifstream& arch);
void aperturaArchivoEscritura(const char* nombArch,ofstream& arch);

//principales
void solicitarDron(char *idDron,char *idDron2);
void crearLista(const char*nombArch,Lista &lista,char* idDron);
void insertarAlInicio(Lista& lista,Infraccion infraccion);
void insertarAlFinal(Lista &lista,Infraccion infraccion);
void emitirReporte(const char*nombArch,Lista primeraLista,char* idDron,
                    Lista segundaLista,char* idDron2);
void imprimirDatosDron(ofstream& output,Lista lista,char* idDron);



//auxiliares
void imprimirLineas(char c,int cant,ofstream&output,bool saltoLinea);
char* leerCadenaExacta(ifstream&input,char delimitador,int n);
char* asignarCadena(char* buffer);
void imprimirFecha(ofstream& output,int fecha);
int leerFecha(ifstream& input);
double leerDouble(ifstream& input);
int leerEntero(ifstream& input);


#endif //EX2_25_1_P2_FUNCIONESAUXILIARES_H
