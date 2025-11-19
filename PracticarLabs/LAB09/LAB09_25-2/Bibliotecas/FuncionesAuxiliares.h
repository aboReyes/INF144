//
// Created by ASUS on 19/11/2025.
//

#ifndef LAB09_25_2_FUNCIONESAUXILIARES_H
#define LAB09_25_2_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <iomanip>
using namespace std;
#define NO_ENCONTRADO -1
#define MAX_CATEGORIAS 120

#include "Categoria.h"
#include "Reproduccion.h"

//apertura archivo datos
void aperturaArchivoLectura(const char*nombArch,ifstream&arch);
void aperturaArchivoEscritura(const char*nombArch,ofstream&arch);

//modulos principales
void leerCategorias(const char* nombArch,
                    Categoria *arrCategoria,int &cantidadCategorias);
void pruebaCategorias(const char* nombArchRep,
                    Categoria *arrCategoria,int cantidadCategorias,
                    bool conRepro,bool conComent);
int buscarCanal(char* codigoCategoria,Categoria *arrCategoria,int cantidadCategorias);
void leerStreamsReproducidos(const char* nombArch,
                            Categoria *arrCategoria,int cantidadCategorias);
void ordenarDatos(Categoria *arrCategoria,int cantidadCategorias);
void leerComentarios(const char* nombArch,
                    Categoria *arrCategoria,int cantidadCategorias);

//modulos auxiliares
void swapStruct(Categoria &dato1,Categoria&dato2);
double leerDouble(ifstream& input);
void imprimirLineas(char c,int cant,ofstream& output);
int leerHora(ifstream& input);
void imprimirHora(ofstream& output,int tiempo);
char* leerCadena(ifstream& input,char delimitador,int n);
char* asignarCadena(char* fuente);

#endif //LAB09_25_2_FUNCIONESAUXILIARES_H
