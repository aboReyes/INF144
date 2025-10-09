//
// Created by DIEGO on 10/6/2025.
//

#ifndef INC_2025_2_LAB05_ARREGLOS_ORDENACION_FUNCIONESAUXILIARES_H
#define INC_2025_2_LAB05_ARREGLOS_ORDENACION_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#define MAX_CANALES 120
#define MAX_ETIQUETAS 120
#define MAX_ETIQUETA_CANAL 600

//Modulo apertura de archivos y preguntarTarifa
void aperturaArchivoLectura(const char* nombArch,ifstream& arch);
void aperturaArchivoEscritura(const char* nombArch,ofstream& arch);
void preguntarTarifa(double &tarifaDur);

//Modulos principales
void cargarCanales(const char* nombArchCanales,int *arrFechaCanal,
                    char *arrCodeCharCanal,int *arrCodeIntCanal,
                    double *arrRatingCanal,int &nroCanales);
void pruebaCanales(const char* nombArchRepPruebaCanales,int *arrFechaCanal,
                    char *arrCodeCharCanal,int *arrCodeIntCanal,
                    double *arrRatingCanal,int nroCanales);


void cargarEtiquetas(const char* nombArchEtiquetas,int* arrCodeEtiqueta,
                    int* arrTiempoDurEtiqueta,int& nroEtiquetas);
void pruebaEtiquetas(const char* nombArchRepPruebaEtiquetas,int* arrCodeEtiqueta,
                    int* arrTiempoDurEtiqueta,int nroEtiquetas);

void cargarEtiquetaCanal(const char* nombArchEtiquetaCanales,
                        char *arrCodeCharEtiquetaCanal,int *arrCodeIntEtiquetaCanal,
                        int *arrCodeEtiquetaCanal,int &nroEtiquetaCanal);
void pruebaEtiquetaCanal(const char* nombArchRepPruebaEtiCanal,
                        char *arrCodeCharEtiquetaCanal,int *arrCodeIntEtiquetaCanal,
                        int *arrCodeEtiquetaCanal,int nroEtiquetaCanal);

void procesarReproEtiquetas(const char* nombArchReproEtiquetas,
                            char *arrCodeCharCanal,int *arrCodeIntCanal,
                            double *arrRatingCanal,int nroCanales,
                            int *arrCodeEtiqueta,int *arrTiempoDurEtiqueta,int nroEtiquetas,
                            double *arrSumaRatingCanalLigadoEtiqueta,int *arrCantCanalLigadoEtiqueta,
                            char *arrCodeCharEtiquetaCanal,int *arrCodeIntEtiquetaCanal,
                            int *arrCodeEtiquetaCanal,int nroEtiquetaCanal,double* arrRatingCanalEtiquetaCanal,
                            int *arrNroTotalReproCanal,int *arrTiempoTotalReproCanal,
                            int *arrNroTotalReproCanalGlobal,int *arrTiempoTotalReproCanalGlobal,
                            double *arrIngresoPorReproEtiqueta,double tarifaDurEtiqueta);

int buscarEtiquetaCanal(char *arrCodeCharEtiquetaCanal,int *arrCodeIntEtiquetaCanal,
                char codeCharCanalArch,int codeIntCanalArch,
                int *arrCodeEtiquetaCanal,int codeEtiquetaReproArch,
                int nroEtiquetaCanal);

int buscarEtiqueta(int *arrCodeEtiqueta,int codeEtiquetaReproArch,int nroEtiquetas);

double buscarRatingCanal(char *arrCodeCharCanal,int *arrCodeIntCanal,double *arrRatingCanal,
                    char codeCharEtiCanalArch,int codeIntEtiCanalArch,int nroCanales);

void ordenarEtiquetas(int *arrCodeEtiqueta,int *arrTiempoDurEtiqueta,int nroEtiquetas);

void generarReporte(const char* nombArchReporte,char *arrCodeCharCanal,int *arrCodeIntCanal,
                    double *arrRatingCanal,int nroCanales,
                    int *arrCodeEtiqueta,int *arrTiempoDurEtiqueta,int nroEtiquetas,
                    double *arrSumaRatingCanalLigadoEtiqueta,int *arrCantCanalLigadoEtiqueta,
                    char *arrCodeCharEtiquetaCanal,int *arrCodeIntEtiquetaCanal,
                    int *arrCodeEtiquetaCanal,int nroEtiquetaCanal,double* arrRatingCanalEtiquetaCanal,
                    int *arrNroTotalReproCanal,int *arrTiempoTotalReproCanal,
                    int *arrNroTotalReproCanalGlobal,int *arrTiempoTotalReproCanalGlobal,
                    double *arrIngresoPorReproEtiqueta,double tarifaDurEtiqueta);

void imprimirTitulo(ofstream &output,double tarifaDur);

void imprimirResumen(ofstream &output,int *arrNroTotalReproCanalGlobal,int *arrTiempoTotalReproCanalGlobal,
                    double *arrIngresoPorReproEtiqueta,double *arrSumaRatingCanalLigadoEtiqueta,int *arrCantCanalLigadoEtiqueta,int i);

//Modulos auxiliares
int filtrarRating(ofstream&output,double promedioRating );
void swapInt(int &a,int &b);
void imprimirSubtitulo(ofstream &output);
int leerTiempo(ifstream& input);
void imprimirTiempo(ofstream& output,int tiempo,bool esMinuto);
void imprimirNumeroOrden(ofstream& output,int nroOrden,bool tieneCero);
void imprimirLineas(char c,int cant,ofstream& output);
void ignorar(ifstream& input,char delimitador);
int leerFecha(ifstream& input);
void imprimirFecha(ofstream& output,int fecha);

#endif //INC_2025_2_LAB05_ARREGLOS_ORDENACION_FUNCIONESAUXILIARES_H
