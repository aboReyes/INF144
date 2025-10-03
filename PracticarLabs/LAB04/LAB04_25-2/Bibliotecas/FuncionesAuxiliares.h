//
// Created by DIEGO on 10/2/2025.
//

#ifndef LAB04_25_2_FUNCIONESAUXILIARES_H
#define LAB04_25_2_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#define MAX_CANALES 120
#define MAX_ETIQUETAS 120

//Modulos para apertura de archivos y lectura de tarifa

void aperturaArchivoLectura(const char* nombArch,ifstream& arch);
void aperturaArchivoEscritura(const char* nombArch,ofstream& arch);
void preguntarTarifa(double &tarifaDurEtiquetas);

//Modulos principales

void cargarCanales(const char* nomArchCanales,int *arrFechaCanal,char *arrCodeCharCanal,
                    int *arrCodeIntCanal,double *arrRatingCanal,int &nroCanales);
void pruebaCanales(const char* nombArchRepCanales,int *arrFechaCanal,char *arrCodeCharCanal,
                    int *arrCodeIntCanal,double *arrRatingCanal,int nroCanales);

void cargarEtiquetas(const char* nombArchEtiquetas,int *arrCodeEtiqueta,int *arrTiempoDurEtiqueta,int &nroEtiquetas);
void pruebaEtiquetas(const char* nombArchRepEtiquetas,int *arrCodeEtiqueta,int *arrTiempoDurEtiqueta,int nroEtiquetas);


void procesarReproducciones(const char* nombArchReproEtiquetas,int *arrFechaCanal,char *arrCodeCharCanal,
                            int *arrCodeIntCanal,double *arrRatingCanal,int nroCanales,
                            int *arrCodeEtiqueta,int *arrTiempoDurEtiqueta,int nroEtiquetas,
                            int *arrNroTotalReproCanales,int *arrTiempoTotalReproCanales,int *arrCantTotalReproEtiquetas,
                            int *arrTiempoTotalReproEtiquetas,double tarifaDurEtiquetas);

void generarReporte(const char* output,int *arrFechaCanal,char *arrCodeCharCanal,
                    int *arrCodeIntCanal,double *arrRatingCanal,int nroCanales,
                    int *arrCodeEtiqueta,int *arrTiempoDurEtiqueta,int nroEtiquetas,
                    int *arrNroTotalReproCanales,int *arrTiempoTotalReproCanales,int *arrCantTotalReproEtiquetas,
                    int *arrTiempoTotalReproEtiquetas,double tarifaDurEtiquetas);

//Modulos auxiliares
double filtrarRating(ofstream &output,double rating);
void imprimirNroOrden(ofstream& output,int nroOrden);
void imprimirSubtituloCanales(ofstream& output);
void imprimirSubtituloEtiquetas(ofstream& output);
void imprimirTituloReporte(ofstream& output,double tarifaDurEtiquetas);
int buscarCanales(char *arrCodeCharCanal,int *arrCodeIntCanal,
                char codeCharEtiquetaArch,int codeIntEtiquetaArch, int nroCanales);
int buscarEtiquetas(int *arrCodeEtiqueta,int codeEtiquetaArch,int nroEtiquetas );
void imprimirTituloRepEtiquetas(ofstream& output);
int leerTiempo(ifstream& input);
void imprimirTiempo(ofstream& output,int tiempo,bool esMinuto);
void imprimirTituloRepCanales(ofstream& output);
void imprimirLineas(char c,int cant,ofstream& output);
void ignorar(ifstream& input,char delimitador);
int leerFecha(ifstream& input);
void imprimirFecha(ofstream& output,int fecha);

#endif //LAB04_25_2_FUNCIONESAUXILIARES_H
