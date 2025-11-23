//
// Created by ASUS on 22/11/2025.
//

#ifndef LAB09_NODOS_FUNCIONESAUXILIARES_H
#define LAB09_NODOS_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
using namespace std;
#include "Reproduccion.h"
#include "Categoria.h"
#include "Nodo.h"

//Modulo apertura de archivos
void aperturaArchivoLectura(const char*nombArch,ifstream&arch) ;
void aperturaArchivoEscritura(const char*nombArch,ofstream&arch);


//Modulos principales
void leerCategorias(const char* nombArch,Nodo *&listaCategoria,
                    bool inicio,bool final,bool ordenado);
void leerCategoria(ifstream &input,Categoria &categoria);


void insertarAlFinal(Nodo *&listaCategoria,Categoria categoria);
void insertarAlInicio(Nodo *&listaCategoria,Categoria categoria);
void insertarOrdenado(Nodo *&listaCategoria,Categoria categoria);

void pruebaCategorias(const char* nombArch,
                    Nodo *listaCategoria);

void actualizarLista(const char* nombArch,Nodo *&listaCategoria);

struct Nodo* buscarCategoria(Nodo *listaCategoria,char *codigoCanal);

void actualizarComentarios(const char* nombArch,Nodo *&listaCategoria) ;
void insertarNodoEspecial(char *nombreCanal,Nodo *&listaCategoria,
                                    char* comentario);
void generarReporte(const char* nombArch,Nodo *listaCategoria);


//Modulos auxiliares
void imprimirLineas(char c,int cant,ofstream &output);
char* leerCadena(ifstream& input,char delimitador,int n);
char* asignarCadena(char* buffer);
int leerHora(ifstream& input);
void imprimirHora(ofstream& output,int tiempo);
double leerDouble(ifstream& input);



#endif //LAB09_NODOS_FUNCIONESAUXILIARES_H
