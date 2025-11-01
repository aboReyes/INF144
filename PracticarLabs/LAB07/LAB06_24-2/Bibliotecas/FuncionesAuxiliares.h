//
// Created by ASUS on 30/10/2025.
//

#ifndef LAB06_24_2_FUNCIONESAUXILIARES_H
#define LAB06_24_2_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#define MAX_REPARTOS 150
#define NO_ENCONTRADO -1

//apertura archivos

void aperturaArchivoLectura(const char* nombArch,ifstream& arch);
void aperturaArchivoEscritura(const char* nombArch,ofstream& arch);

//modulos principales


void cargarRepartos(const char* nombArch,
                    int *arrNumPlatosVendidos,int *arrCodigoPlatos,int &cantRepartos);

void procesamientoPlatos(int cantPlatos,int codePlatos,
                    int *arrNumPlatosVendidos,int *arrCodigoPlatos,int &cantRepartos);

int busquedaBinaria(int codePlato,int *arrCodePlato,int& cant);

void insertarOrdenado(int cantPlatos,int codePlatos,
                    int *arrNumPlatosVendidos,int *arrCodigoPlatos,int &cantRepartos);

void procesarPlatos(const char* nombArch,
                int *arrNumPlatosVendidos,int *arrCodigoPlatos,int cantRepartos,
                double *arrPrecio,double *arrIngresoBruto,double *arrDescuento,double *arrTotal,
                bool *arrTieneDescuento);

void pruebaDatos(const char* nombArchRep,
                int *arrNumPlatosVendidos,int *arrCodigoPlatos,int cantRepartos,
                double *arrPrecio,double *arrIngresoBruto,double *arrDescuento,double *arrTotal,
                bool *arrTieneDescuento);

void crearReporte(const char *nombArchPlatos,
                const char* nombArchRep,
                int *arrNumPlatosVendidos,int *arrCodigoPlatos,int cantRepartos,
                double *arrPrecio,double *arrIngresoBruto,double *arrDescuento,double *arrTotal,
                bool *arrTieneDescuento);

void modificarCadena(char *nombrePlato,char *categoriaPlato,bool tieneDescuento);

void formato1(char *nombrePlato);

void formato2(char *nombrePlato);

void formato3(char *nombrePlato,char* categoriaPlato);

void formato4(char* nombrePlato,char* categoriaPlato);

//modulos auxiliares
void imprimirSubtituloRepFinal(ofstream& output);
void imprimirSubtituloRepPrueba(ofstream& output);
void imprimirLineas(char c,int cant,ofstream& output) ;
void imprimirNroOrden(ofstream& output,int nroOrden);
void ignorar(ifstream& input,char delimitador);

#endif //LAB06_24_2_FUNCIONESAUXILIARES_H
