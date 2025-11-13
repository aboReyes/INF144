//
// Created by ASUS on 12/11/2025.
//

#ifndef LAB08_25_2_CON_DINAMICO_FUNCIONESAUXILIARES_H
#define LAB08_25_2_CON_DINAMICO_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;

#define MAX_CARACTERES 100
#define NO_ENCONTRADO -1
#define MAX_CATEGORIAS 150

#include "Categoria.h"
#include "Reproduccion.h"

//apertura de archivos
void aperturaArchivoLectura(const char* nombArch,ifstream& arch);
void aperturaArchivoEscritura(const char* nombArch,ofstream& arch);

//principales
void leerCategorias(const char* nombArch,
                    Categoria *arrCategorias,int &cantCategorias);
void pruebaCategorias(const char* nombArch,
                    Categoria *arrCategorias,int cantCategorias,
                    bool conReproducciones);


void leerProcesarReproducciones(const char* nombArch,
                    Categoria *arrCategorias,int cantCategorias);
int buscarCategoria(char *codigoCategoria,Categoria *arrCategorias,
                    int cantCategorias);

void calcularPromedioYDuracionesTotales(Categoria *arrCategorias,int cantCategorias);

void emitirReporte(const char* nombArchRep,
                    Categoria *arrCategorias,int cantCategorias);

//auxiliares
void imprimirCabeceraReproducciones(ofstream& output);
void imprimirLineas(char c,int cant,ofstream& output);
int leerTiempo(ifstream& input);
void imprimirTiempo(ofstream& output,int tiempo);
int readInt(ifstream& input);
char *readString(ifstream& input,char delimitador);
double readDouble(ifstream& input);

#endif //LAB08_25_2_CON_DINAMICO_FUNCIONESAUXILIARES_H
