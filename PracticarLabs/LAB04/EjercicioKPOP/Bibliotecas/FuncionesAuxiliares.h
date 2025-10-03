//
// Created by ASUS on 22/09/2025.
//

#ifndef EJERCICIOKPOP_FUNCIONESAUXILIARES_H
#define EJERCICIOKPOP_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

void aperturaArchivoLectura(const char* nombArch,ifstream&arch);
void aperturaArchivoEscritura(const char* nombArch,ofstream& arch);

void leerTarifa(double &tarifa);

void crearReporte(const char* nombArchArt,const char* nombArchCan,const char* nombArchRepro,
                    const char* nombArchReporte);

void imprimirTitulo(ofstream &archReporte,double tarifa);
void leerImprimirDatosArtista(ifstream& archArt,ofstream& archReporte,int &nroArtista,char &letraCodArtista,int &numCodArtista) ;
void imprimirDatosCancionesArtista(ifstream& archRepro,ifstream &archCan,ofstream& archReporte,char letraCodArtista,int numCodArtista,int &nroCancion);
int procesarDatosCancion(ifstream &archCan,ofstream& archReporte,int codeCancion);


int leerMMSS_Seg(ifstream& archCan);
void convertirSeg_HHMMSS(ofstream &archRep,int numero);
void leerImprimirNombreArtistayCancion(ifstream& arch,ofstream& archReporte,int tamaño);
void imprimirNro(ofstream& archReporte,int nro);
void imprimirSubtitulo(ofstream& archReporte);
void imprimirSubtitulo2(ofstream &archReporte);
void imprimirFecha(int dia,int mes,int año,ofstream& archReporte);
void imprimirLineas(char c,int cant,ofstream& archReporte);


#endif //EJERCICIOKPOP_FUNCIONESAUXILIARES_H
