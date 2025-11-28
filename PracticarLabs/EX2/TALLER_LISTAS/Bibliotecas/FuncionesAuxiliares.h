//
// Created by aml on 28/11/2025.
//

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "LibroEnSuPoder.h"
#include "Usuario.h"
#include "NodoUsuario.h"
#include "NodoUsuarioMoroso.h"

//Apertura de archivos
void aperturaArchivoLectura(const char* nombArch,ifstream& arch);
void aperturaArchivoEscritura(const char* nombArch,ofstream& arch);


//Principales
void cargarUsuarios(const char* nombArch,NodoUsuario *&listaUsuarios);
void leerUsuarios(ifstream& input,Usuario &usuario);
void insertarSimple(Usuario usuario,NodoUsuario *&listaUsuarios);
void imprimirLineas(char c,int cant,ofstream& output);
void pruebaUsuarios(const char* nombArch,NodoUsuario *listaUsuarios);
void imprimirCabeceraUsuarios(ofstream& output);
void actualizarPrestamo(NodoUsuario *&listaUsuarios);

//Auxiliares
double leerDouble(ifstream& input);
int leerEntero(ifstream& input);
char* asignarCadena(char *fuente);
char* leerCadena(ifstream& input,char delimitador,int n);


#endif //FUNCIONESAUXILIARES_H
