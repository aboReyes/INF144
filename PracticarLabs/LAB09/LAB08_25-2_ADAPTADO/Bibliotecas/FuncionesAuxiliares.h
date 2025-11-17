//
// Created by ASUS on 16/11/2025.
//

#ifndef LAB08_25_2_AGAIN_FUNCIONESAUXILIARES_H
#define LAB08_25_2_AGAIN_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#define NO_ENCONTRADO -1
#define MAX_CATEGORIAS 150

#include "Categoria.h"
#include "Reproduccion.h"

//apertura de archivos
void aperturaArchivoLectura(const char* nombArch,ifstream& arch);
void aperturaArchivoEscritura(const char* nombArch,ofstream& arch);

//modulos principales
void cargarCategorias1(const char* nombArch,
                    Categoria *arrCategorias,int &cantidadCategorias);
void cargarCategorias2(const char* nombArch,
                    Categoria *&arrCategorias,int &cantidadCategorias);
void cargarReproducciones(const char* nombArch,
                        Categoria *arrCategorias,int cantidadCategorias);
int buscarCanal(char *codigoReproduccion,Categoria *arrCategorias,int cantidadCategorias);

void reportePruebaCategorias(const char* nombArchRep,
                            Categoria *arrCategorias,int cantidadCategorias,bool conRepro);
void calcularTotalesYPromedios(Categoria *arrCategorias,int cantidadCategorias);

void ordenarCategorias(Categoria *arrCategorias,int cantidadCategorias);

void emitirReporte(const char* nombArchRep,
                    Categoria *arrCategorias,int cantidadCategorias);

void imprimirResumen(ofstream& output,Categoria &categoria);

void emitirReporte2(Categoria * arrCategorias,int cantidadCategorias);

//modulos auxiliares
void ordenarNombres(Categoria *arrCategorias,int cantidadCategorias);
void ordenarRating(Categoria *arrCategorias,int cantidadCategorias);
void swapRepro(Reproduccion&dato1,Reproduccion&dato2);
void formato2(char* nombre);
void generarArchivoEnlace(char* categoria,char* &nombArchivo,char* &enlace);
void formato1(char* nombre);
void swapStruct(Categoria &dato1,Categoria &dato2);
void imprimirLineas(char c,int cant,ofstream& output);
int leerTiempo(ifstream& input);
void imprimirTiempo(ofstream& output,int tiempo);
char* leerCadena(ifstream& input,char delimitador,int n);
char* asignarCadena(char *origen);
int leerEntero(ifstream& input);
double leerDouble(ifstream& input);

#endif //LAB08_25_2_AGAIN_FUNCIONESAUXILIARES_H
