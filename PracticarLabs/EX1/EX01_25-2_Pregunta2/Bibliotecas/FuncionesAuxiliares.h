//
// Created by aml on 20/10/2025.
//

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#define NO_ENCONTRADO -1
#define MAX_STREAMS 120

void aperturaArchivoLectura(const char* nombArch,ifstream& arch);
void aperturaArchivoEscritura(const char* nombArch,ofstream& arch);

void cargarStreams(const char* nombArchStreams,
                int *arrCodeStream,int *arrDurStream,
                int *arrCodeIdiomaStream,char* arrCharCatIdiomaStream,
                int *arrIntCatIdiomaStream,
                int &cantStreams);
int buscarStream(int *arrCodeStream,int codeStream,int cantStreams);


void procesarCanales(const char* nombArchCanales,int *arrCodeStream,
                    int *arrFechaCanal,char *arrCodeCharCanal,int *arrCodeIntCanal,
                    int *arrFechaAntiguaCanal,int *arrFechaRecienteCanal,
                    double *arrRatingPromCanal,double *arrTasaDropPromCanal,
                    int *arrDurStreamCanal,int cantStreams);


int leerFecha(ifstream& input);
void imprimirFecha(ofstream& output,int fecha);
void ignorar(ifstream &arch,char delimitador);
int leerTiempo(ifstream& input);
void imprimirTiempo(ofstream& output,int tiempo);



#endif //FUNCIONESAUXILIARES_H
