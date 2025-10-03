//
// Created by aml on 3/10/2025.
//

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

//Modulos de apertura y lectura de fechas:

void aperturaArchivoLectura(const char* nombArch,ifstream &arch);
void aperturaArchivoEscritura(const char* nombArch,ofstream &arch);
void ingresarRangoFechas(int &diaIni,int &mesIni,int &añoIni,
                        int &diaFin,int &mesFin,int &añoFin);

//Modulos principales

void crearReporte(const char* nombArchLibros,
                const char* nombArchVentas,
                const char* nombArchClientes,
                const char* nombArchReporteVentas);

void imprimirTitulo(ofstream& output,int rangoFechaIni,int rangoFechaFin);

void leerImprimirLibros_Autor(ifstream& archLibros,ofstream&archReporte,int &codigoLibro);

//Modulos Auxiliares
void leerImprimirDatosNombres(ifstream& input,ofstream& output,int tamaño,char delimitador,bool primerCar,bool mayus);
int convertirDDMMYYYY_Num(int dd,int mm,int yyyy);
void imprimirLineas(char c,int cant,ofstream& output);
void imprimirNum_DDMMYYYY(ofstream& output,int num);

#endif //FUNCIONESAUXILIARES_H
