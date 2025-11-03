//
// Created by ASUS on 2/11/2025.
//

#ifndef LAB06_25_1_FUNCIONESAUXILIARES_H
#define LAB06_25_1_FUNCIONESAUXILIARES_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;
#define NO_ENCONTRADO -1
#define MAX_CARACTERES 200
#define MAX_TABLA_INFRA 150
#define MAX_INFRA_COM 800


//apertura de archivos
void aperturaArchivoLectura(const char*nombArch,ifstream& arch);
void aperturaArchivoEscritura(const char*nombArch,ofstream& arch);

//principales
char *readString(ifstream& input);
void cargarInfracciones(const char* nombArch,
                        int *arrCodigoInfraccion,double *arrMultasInfraccion,
                        int &cantInfracciones);
void insertarOrdenado(int codigoInfra,double multaInfra,
                    int *arrCodigoInfraccion,double *arrMultasInfraccion,
                    int &cantInfracciones);
void cargarInfraCom(const char *nombArch,
                   const char* nombArchRep,
                   int *arrCodigoInfraccion,double *arrMultasInfraccion,int cantInfracciones,
                   int *arrDni,int *arrMasMultaAntigua,int *arrUltimaPendiente,
                   double *arrTotalMultas,double *arrTotalPagadas,double *arrTotalPendientes,
                   char **arrPlacasEmpresa,int &cantInfraCom);
int busquedaBinaria(int codigoInfraccion,int *arrCodigoInfraccion,int cantInfracciones);

void insertarActualizarInformacion(int fechaInfraccion,int dniRepEmpresa,char pago,
                                    int fechaPago,double valorMulta,
                                    int *arrDni,int *arrMasMultaAntigua,int *arrUltimaPendiente,
                                    double *arrTotalMultas,double* arrTotalPagadas,char *placa,
                                    char** arrPlacasEmpresa,int &cantInfraCom);

void insertarOrdenadoInfraCom(int fechaInfraccion,int dniRepEmpresa,char pago,
                                int fechaPago,double valorMulta,
                                int *arrDni,int *arrMasMultaAntigua,int *arrUltimaPendiente,
                                double *arrTotalMultas,double* arrTotalPagadas,char *placa,
                                char **arrPlacasEmpresa,int &cantInfraCom);

void crearReporte(const char* nombArch,
                const char* nombArchRep,
                int *arrDni,int *arrMasMultaAntigua,int *arrUltimaPendiente,char **arrPlacasEmpresa,
                double *arrTotalMultas,double *arrTotalPagadas,int cantInfraCom);

//auxiliares
void imprimirCabeceraReporte(ofstream& output);
void imprimirLinea(char c,int cant,ofstream& output);
void imprimirFecha(ofstream &output,int fecha);
int leerFecha(ifstream &input);
void ignorar(ifstream &input,char delimitador);

#endif //LAB06_25_1_FUNCIONESAUXILIARES_H
