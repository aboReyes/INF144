//
// Created by ASUS on 23/11/2025.
//

#ifndef REPASOLAB09_25_2_FUNCIONESAUXILIARES_H
#define REPASOLAB09_25_2_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "Categoria.h"
#include "Reproduccion.h"
#include "NodoCategoria.h"

//apertura archivos
void aperturaArchivoLectura(const char*nombArch,ifstream& arch);
void aperturaArchivoEscritura(const char*nombArch,ofstream& arch);

//principales
void crearListaCategoria(const char* nombArch,NodoCategoria *&listaCategoria);
void leerCategoria(ifstream& input,Categoria &categoria);
void insertarOrdenado(NodoCategoria *&listaCategoria,Categoria categoria);
NodoCategoria *buscarCanal(NodoCategoria *listaCategoria,char* codigoCanal);
void actualizarReproducciones(const char* nombArch,NodoCategoria *&listaCategoria);
void actualizarComentarios(const char* nombArch,NodoCategoria *&listaCategoria);
void insertarComentarios(NodoCategoria *&listaCategoria,char *nombreCanal,char *descripcion);
void calcularTotales(NodoCategoria *&listaCategoria);
void eliminarPorRating(NodoCategoria *&listaCategoria);
void emitirReporte(const char* nombArch,NodoCategoria *listaCategoria);

//auxiliares
void imprimirLineas(char c,int cant,ofstream& output);
void imprimirTiempo(ofstream& output,int tiempo);
int leerTiempo(ifstream& input);
char* leerCadena(ifstream& input,char delimitador,int n);
char* asignarCadena(char* buffer);
double leerDouble(ifstream& input);

#endif //REPASOLAB09_25_2_FUNCIONESAUXILIARES_H
