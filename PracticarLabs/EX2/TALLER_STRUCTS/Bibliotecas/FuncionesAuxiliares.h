
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
void pruebaLibros(const char* nombArch,
                            Libro *arrLibros,int cantidadLibros,bool prestamo) ;
void leerUsuarios(const char* nombArch,
                Usuario *arrUsuarios,int &cantidadUsuarios);
void pruebaUsuarios(const char* nombArch,
                    Usuario *arrUsuarios,int cantidadUsuarios,bool prestamo);
void actualizarPrestamos(const char* nombArch,
                Libro *arrLibros,int cantidadLibros,Usuario *arrUsuarios,int cantidadUsuarios);
int buscarCodigoLibro(char *codigoLibro,Libro *arrLibros,int cantidadLibros);
int buscarUsuario(int dniUsuario,Usuario *arrUsuarios,int cantidadUsuarios);
void ordenarReporte(Libro *arrLibros,int cantidadLibros);
void SwapStruct2(UsuarioConElLibro&dato1,UsuarioConElLibro&dato2) ;
void ordenarUsuarios(Libro &libros,int cantUsuarios);

//Modulos auxiliares
void SwapStruct(Libro &dato1,Libro &dato2);
void imprimirCabeceraUsuarios(ofstream& output);
void imprimirCabeceraLibros(ofstream& output);
void imprimirLineas(char c,int cant,ofstream& output);
char leerChar(ifstream& input);
int leerFecha(ifstream& input);
char* asignarCadena(char *fuente);
char* leerCadena(ifstream& input,char delimitador,int n);
double leerDouble(ifstream& input);
int leerEntero(ifstream& input);
void imprimirFecha(ofstream& output,int fecha);


#endif //FUNCIONESAUXILIARES_H
