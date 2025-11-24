//
// Created by ASUS on 24/11/2025.
//

#ifndef LAB10_25_1_FUNCIONESAUXILIARES_H
#define LAB10_25_1_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include "fstream"
#include <cstring>
using namespace std;
#include "Cuenta.h"
#include "Nodo.h"

//aperturaArchivos
void aperturaArchivoLectura(const char* nombArch,ifstream& arch);
void aperturaArchivoEscritura(const char* nombArch,ofstream& arch);

//principales
void inicializaCuentasBancarias(struct Cuenta &cuenta);
void cargarCuentasBancarias(const char* nombArch,Nodo *&listaCuentasBancarias);
void leerCuentasBancarias(ifstream& input,Cuenta &cuenta);
void insertarOrdenado(Nodo *&listaCuentasBancarias,Cuenta cuenta);
void cargarMovimientoDeCuentas(const char* nombArch,Nodo *&listaCuentasBancarias);
Nodo *buscarCuenta(Nodo *&listaCuentasBancarias,int codigoCuenta);
void emitirReporte(const char*nombArch,Nodo *listaCuentasBancarias);
void eliminarSaldosPositivos(Nodo *&listaCuentasBancarias);


//auxiliares
void imprimirNroOrden(ofstream& output,int contador);
void imprimirCabeceraReporte(ofstream& output);
void imprimirLineas(char c,int cant,ofstream& output);
int leerEntero(ifstream& input);
void imprimirFecha(ofstream& output,int fecha);
int leerFecha(ifstream& input);
double leerDouble(ifstream& input);
char* leerCadenaExacta(ifstream& input,char delimitador,int n);
char* asignarCadena(char* buffer);



#endif //LAB10_25_1_FUNCIONESAUXILIARES_H
