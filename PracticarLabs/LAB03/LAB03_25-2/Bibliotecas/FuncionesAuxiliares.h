//
// Created by ASUS on 12/10/2025.
//

#ifndef LAB03_25_2_FUNCIONESAUXILIARES_H
#define LAB03_25_2_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

//Modulos apertura de archivos
void aperturaArchivoLectura(const char* nombArch,ifstream& arch);
void aperturaArchivoEscritura(const char* nombArch,ofstream& arch);

//Modulos principales

void generarReporte(const char* nombArchCanales,
                    const char* nombArchEtiquetas,
                    const char* nombArchReproEtiquetas,
                    const char* nombArchReporte);

void imprimirTituloReporte(ofstream& archRep,double tarifaDur);
void imprimirSubtituloDatosCanales(ofstream& archRep);

void leerImprimirDatosCanales(ifstream &archCanales,ifstream&archEtiquetas,
                                ifstream& archReproEtiquetas,ofstream& archRep,
                                char &letraCodCanal,int &numCodCanal,int &etiqueta,
                                double tarifaDur,int &cantCanales);

int procesarEtiquetasReproducidas(ifstream& archReproEtiquetas,ifstream&archEtiquetas,
                                ofstream& archRep,char letraCodCanal,int numCodCanal,
                                int etiqueta,int &cantEtiquetas);
void imprimirSubtituloEtiquetasReproducidas(ofstream& archRep) ;

int buscarEtiquetas(ifstream& archEtiquetas,ofstream&archRep,
                    int etiquetaArch);

void imprimirResumen(ofstream& archRep,int tiempoTotalGlobal,double ratingCanal,
                    double tarifaDur);
//Modulos auxiliares
double filtrarRating(ofstream& archRep,double rating) ;
void imprimirOrden(ofstream& archRep,int nroOrden);
void imprimirLineas(char c,int cant,ofstream& archRep);
void leerTarifa(double &tarifaDur);
void leerImprimirNombreVarios(ifstream& input,ofstream& output,
                            int tam,char delimitador,bool mayus);
void imprimirTiempo(ofstream& output,int tiempo,bool esMinuto);
int leerTiempo(ifstream& input);
int leerFecha(ifstream& input);
void imprimirFecha(ofstream& output,int fecha);



#endif //LAB03_25_2_FUNCIONESAUXILIARES_H
