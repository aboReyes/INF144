//
// Created by ASUS on 28/09/2025.
//

#ifndef LAB3_25_2_ARREGLOS_ARCHIVOSAUXILIARES_H
#define LAB3_25_2_ARREGLOS_ARCHIVOSAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#define MAX_ETIQUETAS 200
#define MAX_REPRODUCCIONES 1000

//modulo apertura archivos
void aperturaArchivoLectura(const char *nombArch, ifstream &arch);
void aperturaArchivoEscritura(const char *nombArch, ofstream &arch);

//modulos principales
void cargarEtiquetas(const char *nombArchEtiqueta,int *arrCodigoEtiqueta,
                    int *arrDurEtiqueta,int &nroEtiquetas);
void imprimirReportePruebaEtiquetas(const char* nombArchReporte,int *arrCodigoEtiqueta,
                    int *arrDurEtiqueta,int nroEtiquetas);


void cargarReproEtiquetas(const char* nombArchReproEtiquetas,int *arrFechaReproEtiquetas,
                        char *arrCodeCharStreamer,int *arrCodeIntStreamer,int *arrCantReproducciones,
                        int *arrCodigoEtiquetaRepro,int &nroReproducciones);
void imprimirReportePruebaReproEtiquetas(const char* nombArchReportePruebaReproEtiquetas,
                                        int *arrFechaReproEtiquetas,char *arrCodeCharStreamer,
                                        int *arrCodeIntStreamer,int *arrCodigoEtiquetaRepro,int *arrCantReproducciones,
                                        int nroReproducciones) ;

void imprimirTitulo(ofstream &archReporte,double tarifaDur);

void crearReporte(const char* nombArchCanales,const char* nombArchReporte,
                int *arrCodigoEtiqueta,int *arrDurEtiqueta,int nroEtiquetas,
                int *arrFechaReproEtiquetas,char *arrCodeCharStreamer,int *arrCodeIntStreamer,
                int *arrCantReproducciones,int *arrCodigoEtiquetaRepro,int nroReproducciones,double tarifaDur);

void leerDatosCanalImprimirCabecera(ifstream& archCanales,ofstream &archReporte,
                                    char &letraCodCanal,int &numCodCanal,
                                    double &rating,int &nroCanal);

void leerEtiquetasReproducidasCanales(ifstream &archCanales,char letraCodCanal,int numCodCanal,
                                    double rating,int &nroDeEtiqueta,
                                    int *arrCodigoEtiqueta,int *arrDurEtiqueta,int nroEtiquetas,
                                    int *arrFechaReproEtiquetas,char *arrCodeCharStreamer,int *arrCodeIntStreamer,
                                    int *arrCantReproducciones,int *arrCodigoEtiquetaRepro,int nroReproducciones,
                                    ofstream &archReporte);

int imprimirInfo(int etiqueta,char letraCodCanal,int numCodCanal,double duracion,
                int *arrFechaReproEtiquetas,char *arrCodeCharStreamer,int *arrCodeIntStreamer,
                int *arrCantReproducciones,int *arrCodigoEtiquetaRepro,int nroReproducciones,
                ofstream &archReporte);

void imprimirResumen(ofstream &archReporte,int tiempoTotal,double rating,double tarifaDur);

//modulos auxiliares
double filtrarRating(ofstream& archReporte,double rating);
double obtenerDuracion(int *arrCodigoEtiqueta,int *arrDurEtiqueta,int nroEtiquetas,int etiqueta);
void leerNombreStreamer(ifstream &archCanales,ofstream &archReporte);
void imprimirSubtituloDatosStreamers(ofstream &archReporte);
void imprimirSubtituloReportePruebaReproEtiquetas(ofstream& archReporte);
void imprimirSubtituloReportePruebaEtiqueta(ofstream & archReporte) ;
void ignorar(ifstream& arch,char delimitador);
int leerFecha(ifstream& arch);
void imprimirFecha(ofstream& arch,int fecha);
int leerHora(ifstream& arch);
void imprimirHora(ofstream& arch,int horaSeg,bool esMinuto);
void imprimirLineas(char c,int cant,ofstream &archReporte);

#endif //LAB3_25_2_ARREGLOS_ARCHIVOSAUXILIARES_H
