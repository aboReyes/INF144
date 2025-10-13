//
// Created by ASUS on 11/10/2025.
//

#ifndef TALLER_ARREGLOS_FUNCIONESAUXILIARES_H
#define TALLER_ARREGLOS_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#define MAX_LIBROS 300

//Modulos apertura de archivos

void aperturaArchivoLectura(const char* nombArch,ifstream& arch);
void aperturaArchivoEscritura(const char* nombArch,ofstream& arch);

//Modulos principales

void leerLibros(const char* nombArchLibros,int *arrCodeLibro,
                double *arrPrecioLibro,int &cantLibros);

void insertarOrdenado(int codeLibro,double precioLibro,int* arrCodeLibro,
                        double *arrPrecioLibro,int &cantLibros);

void ordenarLibros(int *arrCodeLibro,
                double *arrPrecioLibro,int cantLibros);

void repPruebaLibros(const char* nombArchRepLibros,int *arrCodeLibro,
                    double *arrPrecioLibro,int cantLibros);

void leerProcesarVentas(const char* nombArchVentas,
                        int *arrCodeLibro,double *arrPrecioLibro,
                        int *arrUnidadesVentas,double *arrPromCalVentas,
                        double *arrTotalVentas,int* arrPrimeraFechaVentas,
                        int *arrPrimerDniVentas,int *arrUltimaFechaVentas,
                        int *arrUltimoDniVentas,int cantLibros);

int buscarLibro(int* arrCodeLibro,int codeLibroArch,int cantLibros);

void imprimirReporte(const char* nombArchRep,int *arrCodeLibro,double *arrPrecioLibro,
                    int *arrUnidadesVentas,double* arrPromCalVentas,double *arrTotalVentas,
                    int *arrPrimeraFechaVentas,int *arrPrimerDniVentas,int *arrUltimaFechaVentas,
                    int *arrUltimoDniVentas,int cantLibros);

void ordenarReporte(int *arrCodeLibro,double *arrPrecioLibro,
                    int *arrUnidadesVentas,double* arrPromCalVentas,double *arrTotalVentas,
                    int *arrPrimeraFechaVentas,int *arrPrimerDniVentas,int *arrUltimaFechaVentas,
                    int *arrUltimoDniVentas,int cantLibros);

void imprimirResumen(ofstream& archRep,int totalGlobalUnidades,double totalGlobalVentas);

//Modulos auxiliares
void imprimirCabeceraReporte(ofstream& output);
void imprimirOrden(ofstream& output,int nroOrden);
void imprimirFecha(ofstream& output,int fecha);
int leerFecha(ifstream& input);
void imprimirCabeceraRepLibros(ofstream& archRep);
void imprimirLineas(char c,int cant,ofstream& archRep);
void ignorar(ifstream& input,char delimitador,bool esPrimero);
void swapInt(int &a,int &b);
void swapDouble(double &a,double &b);
void swapChar(char &a,char&b);

#endif //TALLER_ARREGLOS_FUNCIONESAUXILIARES_H
