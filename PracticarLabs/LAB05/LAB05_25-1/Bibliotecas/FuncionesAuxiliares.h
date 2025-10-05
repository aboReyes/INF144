//
// Created by ASUS on 5/10/2025.
//

#ifndef LAB5_25_1_FUNCIONESAUXILIARES_H
#define LAB5_25_1_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#define MAX_EMPRESAS 50
#define MAX_MULTAS 150
#define MAX_PLACAS 150

//Modulos de apertura de archivos
void aperturaArchivoLectura(const char* nombArch,ifstream& arch);
void aperturaArchivoEscritura(const char* nombArch,ofstream& arch);

//Modulos principales
void cargarRepresentantesEmpresas(const char* nombArchEmpresas,
                                int *arrDniRepreEmpresa, int &nroRepreEmpresa);
//void ordenarRepresentantesEmpresas(int *arrDniRepreEmpresa,int nroRepreEmpresa);

void cargarPlacas(const char*nombArchPlacasReg,int *arrDniRegistroPlaca,
                char*arrCodeCharPlaca,int *arrCodeIntPlaca,int &nroPlacas);

void cargarMultasInfraccion(const char* nombArchTablaInfra,char *arrCodeCharInfraccion,
                            int *arrCodeIntInfraccion,double *arrMultaInfraccion,int &nroMultas);

void procesarInfraccionesCometidas(const char* nombArchInfraCom,int *arrDniRepreEmpresa,int nroRepreEmpresa,
                            char *arrCodeCharInfraccion,int *arrCodeIntInfraccion,double *arrMultaInfraccion,int nroMultas,
                            int *arrDniRegistroPlaca,char* arrCodeCharPlaca,int *arrCodeIntPlaca,int nroPlacas,
                            int *arrCantLevesEmpresas,int *arrCantGravesEmpresas,int *arrCantMuyGravesEmpresas,
                            double *arrMontoLevesEmpresas,double *arrMontoGravesEmpresas,double *arrMontoMuyGravesEmpresas,
                            int *arrCantMultasInfraccion,double *arrTotalMultasInfraccion);

void ordenarReporte(int *arrDniRepreEmpresa,int nroRepreEmpresa,
                    int *arrCantLevesEmpresas,int *arrCantGravesEmpresas,int *arrCantMuyGravesEmpresas,
                    double *arrMontoLevesEmpresas,double *arrMontoGravesEmpresas,double *arrMontoMuyGravesEmpresas,
                    char *arrCodeCharInfraccion,int *arrCodeIntInfraccion,double *arrMultaInfraccion,int nroMultas,
                    int *arrCantMultasInfraccion,double *arrTotalMultasInfraccion);

void generarReporte(const char* nombArchRep,int *arrDniRepreEmpresa,int nroRepreEmpresa,
                    int *arrCantLevesEmpresas,int *arrCantGravesEmpresas,int *arrCantMuyGravesEmpresas,
                    double *arrMontoLevesEmpresas,double *arrMontoGravesEmpresas,double *arrMontoMuyGravesEmpresas,
                    char *arrCodeCharInfraccion,int *arrCodeIntInfraccion,double *arrMultaInfraccion,int nroMultas,
                    int *arrCantMultasInfraccion,double *arrTotalMultasInfraccion);

//Modulos auxiliares
void imprimirSubtituloMultasInfraccion(ofstream &output);
void imprimirSubtituloRepEmpresas(ofstream& output);
int obtenerDniEmpresa(char codeCharPlaca,int codeIntPlaca,int *arrDniRegistroPlaca,
                        char *arrCodeCharPlaca,int *arrCodeIntPlaca,int nroPlacas);
int buscarEmpresa(int dniEmpresa,int *arrDniRepreEmpresa,int nroRepreEmpresa) ;
int buscarMulta(char codeCharMulta,int codeIntMulta,char *arrCodeCharInfraccion,int *arrCodeIntInfraccion,int nroMultas);
void imprimirTitulo(ofstream& output);
void imprimirLineas(char c,int cant,ofstream& output);
void imprimirOrden(ofstream& output,int nroOrden);
void swapInt(int &a, int &b);
void swapDouble(double &a,double& b);
void swapChar(char &a,char&b);
void ignorar(ifstream& input,char delimitador);

#endif //LAB5_25_1_FUNCIONESAUXILIARES_H
