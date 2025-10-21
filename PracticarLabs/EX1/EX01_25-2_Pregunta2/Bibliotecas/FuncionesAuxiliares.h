//
// Created by DIEGO on 10/20/2025.
//

#ifndef EX01_PREGUNTA2_FUNCIONESAUXILIARES_H
#define EX01_PREGUNTA2_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#define NO_ENCONTRADO -1
#define MAX_STREAMS 120

//Funciones apertura archivos
void aperturaArchivoLectura(const char* nombArch,ifstream& arch);
void aperturaArchivoEscritura(const char* nombArch,ofstream& arch);


//Funciones principales
void cargarStreams(const char* nombArchStreams,
                int *arrCodeStream,int *arrDurStream,
                int *arrCodeIdiomaStream,char* arrCharCatIdiomaStream,
                int *arrIntCatIdiomaStream,
                int &cantStreams);

void pruebaStreams(const char* nombArchRep,
                    int *arrCodeStream,int *arrDurStream,
                    int *arrCodeIdiomaStream,char* arrCharCatIdiomaStream,
                    int *arrIntCatIdiomaStream,
                    int cantStreams);

void procesarCanales(const char* nombArchCanales,int *arrCodeStream,int *arrDurStream,
                    char *arrCodeCharCanal,int *arrCodeIntCanal,
                    int *arrFechaAntiguaCanal,int *arrFechaRecienteCanal,
                    double *arrRatingPromCanal,double *arrTasaDropPromCanal,
                    int *arrCantReproduccionesl,int *arrDurTotalReproducciones,
                    int cantStreams);

int buscarStream(int *arrCodeStream,int codeStream,int cantStreams) ;

void imprimirReporte(const char* nombArchRep,
                    int *arrCodeStream,int *arrDurStream,int *arrCodeIdiomaStream,
                    char *arrCharCatIdiomaStream,int *arrIntCatIdiomaStream,int cantStreams,
                    int *arrFechaAntiguaCanal,int *arrFechaRecienteCanal,
                    double *arrRatingPromCanal,double *arrTasaDropPromCanal,
                    int *arrCantReproducciones,int *arrDurTotalReproducciones,
                    bool ordenado);

void ordenacion(int *arrCodeStream,int *arrDurStream,int *arrCodeIdiomaStream,
                    char *arrCharCatIdiomaStream,int *arrIntCatIdiomaStream,int cantStreams,
                    int *arrFechaAntiguaCanal,int *arrFechaRecienteCanal,
                    double *arrRatingPromCanal,double *arrTasaDropPromCanal,
                    int *arrCantReproducciones,int *arrDurTotalReproducciones);

//Funciones auxiliares
void swapDouble(double &a,double &b);
void swapChar(char &a,char &b);
void swapInt(int &a,int &b);
void imprimirGuiones(ofstream& output);
void imprimirCabeceraReporte(ofstream& output);
void imprimirSubtituloPruebaStreams(ofstream& output);
void imprimirLineas(char c,int cant,ofstream& output);
int leerFecha(ifstream& input);
void imprimirFecha(ofstream& output,int fecha);
int leerTiempo(ifstream& input);
void imprimirTiempo(ofstream& output,int tiempo);
void ignorar(ifstream &arch,char delimitador) ;


#endif //EX01_PREGUNTA2_FUNCIONESAUXILIARES_H
