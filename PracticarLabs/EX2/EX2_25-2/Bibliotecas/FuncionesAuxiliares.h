//
// Created by DIEGO on 05/12/2025.
//

#ifndef P1_FUNCIONESAUXILIARES_H
#define P1_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;

#include "Transmision.h"

#define  MAX_TRANSMISIONES 150
#define  NO_ENCONTRADO -1

//Modulos apertura de archivos
void aperturaArchivoLectura(const char* nombArch,ifstream& arch);
void aperturaArchivoEscritura(const char* nombArch,ofstream& arch);

//Modulos principales
void cargarTransmisiones(const char* nombArch,Transmision *transmisiones,int &cantidadTransmisiones);
void cargarStreamers(const char* nombArch,Transmision *transmisiones,int cantidadTransmisiones);
int buscarStreamer(int id_streamer,Transmision *transmisiones,int cantidadTransmisiones);
void cargarComentarios(const char* nombArch,Transmision *transmisiones,int cantidadTransmisiones);
int buscarComentarios(int idTransmision,Transmision *transmisiones,int cantidadTransmisiones);
char* preProcesarComentario(char* comentarioOriginal);
void imprimirLineas(char c,int cant,ofstream& output);
void emitirReporte(const char* nombArch,Transmision *transmisiones,int cantidadTransmisiones);

//Modulos auxiliares
void imprimirCabeceraReporte(ofstream &output);
int leerFecha(ifstream& input);
void imprimirFecha(ofstream& output,int fecha);
int leerEntero(ifstream& input);
double leerDouble(ifstream& input);
int leerEntero(ifstream& input);
char* asignarCadena(char *buffer);
char* leerCadena(ifstream& input,char delimitador,int n);

#endif //P1_FUNCIONESAUXILIARES_H
