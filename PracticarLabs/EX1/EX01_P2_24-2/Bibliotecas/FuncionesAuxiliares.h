//
// Created by ASUS on 12/10/2025.
//

#ifndef EX01_P2_24_2_FUNCIONESAUXILIARES_H
#define EX01_P2_24_2_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#define MAX_PLATOS 150
#define MAX_CLIENTES 120
#define NO_ENCONTRADO -1

//Modulos apertura de archivos

void aperturaArchivoLectura(const char* nombArch,ifstream& arch);
void aperturaArchivoEscritura(const char* nombArch,ofstream& arch);

//Modulos principales
void cargarPlatosOfrecidos(const char* nombArchPlatOfre,int *arrCodigoPlato,
                            double *arrPrecioPlato,int *arrCantPlatosAtendidos,
                            double *arrDescuentoPlato,int &nroPlatos) ;

void cargarClientes(const char* nombArchClientes,
                    int *arrDniCliente,double *arrDescuentoCliente,int&nroClientes);

void reportePrueba(const char* nombArchRepPrueba,
                int *arrCodigoPlato,double *arrPrecioPlato,
                int *arrCantPlatosAtendidos,double *arrDescuentoPlato,int nroPlatos,
                int *arrDniCliente,double *arrDescuentoCliente,int nroClientes) ;

void cargarRepartosARealizar(const char* nombArchRepReali,
                            int *arrCodigoPlato,double *arrPrecioPlato,
                            int *arrCantPlatosAtendidos,double *arrDescuentoPlato,int nroPlatos,
                            int *arrDniCliente,double *arrDescuentoCliente,int nroClientes,
                            int *arrCantAtendida,int *arrCantNoAtendida,double *arrMontoEsperado,
                            double *arrMontoBruto,double *arrMontoRecibido);

int buscarPlato(int *arrCodigoPlato,int codPlato,int nroPlatos);
int buscarCliente(int *arrDniCliente,int dniCliente,int nroCliente) ;

void ordenarReporte(int *arrCodigoPlato,double *arrPrecioPlato,
                    int *arrCantPlatosAtendidos,double *arrDescuentoPlato,int nroPlatos,
                    int *arrDniCliente,double *arrDescuentoCliente,
                    int *arrCantAtendida,int *arrCantNoAtendida,double *arrMontoEsperado,
                    double *arrMontoBruto,double *arrMontoRecibido);

void imprimirReporte(const char* nombArchRep,
                    int *arrCodigoPlato,double *arrPrecioPlato,
                    int *arrCantPlatosAtendidos,double *arrDescuentoPlato,int nroPlatos,
                    int *arrDniCliente,double *arrDescuentoCliente,int nroClientes,
                    int *arrCantAtendida,int *arrCantNoAtendida,double *arrMontoEsperado,
                    double *arrMontoBruto,double *arrMontoRecibido);

void eliminarNoAtendidos_0(int *arrCodigoPlato,double *arrPrecioPlato,
                        int *arrCantPlatosAtendidos,double *arrDescuentoPlato,int &nroPlatos,
                        int *arrCantAtendida,int *arrCantNoAtendida,double *arrMontoEsperado,
                        double *arrMontoBruto,double *arrMontoRecibido);

void eliminarElemento(int n,int *arrCodigoPlato,double *arrPrecioPlato,
                    int *arrCantPlatosAtendidos,double *arrDescuentoPlato,int &nroPlatos,
                    int *arrCantAtendida,int *arrCantNoAtendida,double *arrMontoEsperado,
                    double *arrMontoBruto,double *arrMontoRecibido);

//Modulos auxiliares
void imprimirCabeceraReporte(ofstream& archRep);
void imprimirCabeceraReporteClientes(ofstream& output);
void imprimirCabeceraReportePlatos(ofstream& output);
void swapInt(int&a,int&b);
void swapDouble (double&a,double&b);
void swapChar (char &a,char&b) ;
void ignorar(ifstream &input,char delimitador);
void imprimirLineas(char c,int cant,ofstream& archRep);

#endif //EX01_P2_24_2_FUNCIONESAUXILIARES_H
