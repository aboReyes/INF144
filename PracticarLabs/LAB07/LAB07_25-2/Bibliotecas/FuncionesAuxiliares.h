//
// Created by ASUS on 5/11/2025.
//

#ifndef LAB07_25_2_FUNCIONESAUXILIARES_H
#define LAB07_25_2_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#define MAX_CATEGORIAS 120
#define MAX_CARACTERES 100
#define MAX_REPRO_STREAM 420


//Apertura de archivos
void aperturaArchivosLectura(const char* nombArch,ifstream& arch);
void aperturaArchivosEscritura(const char* nombArch,ofstream& arch);

//Modulos principales
void cargarCategorias(const char *nombArch,
                     char **arrCodigoCategoria,char **arrNombreCategoria,int &cantCategorias);
void probarCategorias(const char* nombArch,
                    char **arrCodigoCategoria,char **arrNombreCategoria,int cantCategorias);

void cargarReproStreams(const char* nombArch,
                        int *arrFechaStream,char **arrNombreCanalStream,char **arrCodigoCanalStream,
                        double *arrRatingStream,double *arrDropStream,int *arrDurStream,int &cantStreams);

void pruebaReproStreams(const char* nombArchRep,
                        int *arrFechaStream,char **arrNombreCanalStream,char **arrCodigoCanalStream,
                        double *arrRatingStream,double *arrDropStream,
                        int *arrDurStream,int cantStreams);

void generarArchivoEnlace(char* categoria,char* &nombArchivo,char* &enlace);

void procesarReporte(char **arrCodigoCategoria,char **arrNombreCategoria,int cantCategorias,
                    int *arrFechaStream,char **arrNombreCanalStream,char **arrCodigoCanalStream,
                    double *arrRatingStream,double *arrDropStream,
                    int *arrDurStream,int cantStreams);

void imprimirReporte(ofstream& output,char** arrCodigoCategoria,
                    int *arrFechaStream,char **arrNombreCanalStream,char **arrCodigoCanalStream,
                    double *arrRatingStream,double *arrDropStream,
                    int *arrDurStream,int cantStreams,int i) ;

void imprimirResumen(ofstream& output,double ratingPromedio,double dropPromedio,int durTotal,int cant) ;

//Modulos Auxiliares
void imprimirCabeceraReporteFinal(ofstream& output);
void imprimirCabeceraRepPruebaStreams(ofstream &output);
void formato1(char* fuente);
void imprimirTiempo(ofstream& output,int tiempo);
int leerTiempo(ifstream& input);
int leerFecha(ifstream& input);
void imprimirFecha(ofstream& output,int fecha);
void imprimirCabeceraRepCat(ofstream &output);
char* readString(ifstream& input);
void imprimirLineas(char c,int cant,ofstream & output) ;


#endif //LAB07_25_2_FUNCIONESAUXILIARES_H
