//
// Created by aml on 21/11/2025.
//

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#define NO_ENCONTRADO -1
#define MAX_LIBROS 50
#define MAX_USUARIOS 70

#include "Libro.h"
#include "LibroEnSuPoder.h"
#include "Usuario.h"
#include "UsuarioConElLibro.h"

//Modulos de apertura de archivos
void aperturaArchivoLectura(const char* nombArch,ifstream& arch);
void aperturaArchivoEscritura(const char* nombArch,ofstream& arch);


//Modulos principales
void leerLibros(const char* arch,
                Libro *arrLibros,int &cantidadLibros);
void pruebaLibros(const char* nombArc,
                            Libro *arrLibros,int cantidadLibros);
void leerUsuarios(const char* nombArch,
                Usuario *arrUsuarios,int &cantidadUsuarios);


//Modulos auxiliares
char leerChar(ifstream& input);
int leerFecha(ifstream& input);
char* asignarCadena(char *fuente);
char* leerCadena(ifstream& input,char delimitador,int n);
double leerDouble(ifstream& input);
int leerEntero(ifstream& input);
void imprimirFecha(ofstream& output,int fecha);


#endif //FUNCIONESAUXILIARES_H
