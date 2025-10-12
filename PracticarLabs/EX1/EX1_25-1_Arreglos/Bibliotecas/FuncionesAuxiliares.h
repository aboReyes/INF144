//
// Created by ASUS on 11/10/2025.
//

#ifndef EX01_25_1_ARREGLOS_FUNCIONESAUXILIARES_H
#define EX01_25_1_ARREGLOS_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#define MAX_TABLA_INFRACCIONES 150
#define MAX_INFRA_COMETIDAS 200
#define NO_ENCONTRADO -1

//modulos apertura de archivos
void aperturaArchivoLectura(const char* nombArch,ifstream& arch);
void aperturaArchivoEscritura(const char* nombArch,ofstream& arch);

//Modulos principales
void leerTablaInfracciones(const char* nombArchTablaInfra,
                        char *arrLetraInfraccion,int *arrNumInfraccion,
                        double* arrMultaInfraccion,int &cantInfraccion);

void pruebaTablaInfracciones(const char* nombArchRepTabInfra,
                            char* arrLetraInfraccion,int *arrNumInfraccion,
                            double* arrMultaInfraccion,int cantInfraccion);

void leerInfraccionesCometidas(const char* nombArchInfraCom,
                            char *arrLetraInfraccion,int *arrNumInfraccion,
                            double *arrMultaInfraccion,int cantInfraccion,
                            char *arrLetraPlacaInfraCom,int *arrNum1PlacaInfraCom,
                            int *arrNum2PlacaInfraCom,int *arrCantMultasPagadasInfraCom,
                            double* arrTotalMultasPagadasInfraCom,int *arrCantMultasPendInfraCom,
                            double *arrTotalMultasPendInfraCom,int *arrFechaMasAntiguaInfraCom,
                            int &cantPlacas);

void registrarPlacaNueva(char*arrLetraPlacaInfraCom,int *arrNum1PlacaInfraCom,int *arrNum2PlacaInfraCom,
                        char letraPlaca,int num1Placa,int num2Placa,int cantPlacas);

int buscarPlaca(char *arrLetraPlacaInfraCom,int *arrNum1PlacaInfraCom,int *arrNum2PlacaInfraCom,
                char letraPlaca,int num1Placa,int num2Placa,int cantPlacas);

double buscarMulta(char *arrLetraInfraccion,int *arrNumInfraccion,double* arrMultaInfraccion,
                    char letraInfraArch,int numInfraArch,int cantInfraccion);

void ordenarPlacas(char *arrLetraInfraccion,int *arrNumInfraccion,
                    double *arrMultaInfraccion,
                    char *arrLetraPlacaInfraCom,int *arrNum1PlacaInfraCom,
                    int *arrNum2PlacaInfraCom,int *arrCantMultasPagadasInfraCom,
                    double *arrTotalMultasPagadasInfraCom,int *arrCantMultasPendInfraCom,
                    double *arrTotalMultasPendInfraCom,int *arrFechaMasAntiguaInfraCom,
                    int cantPlacas);

void generarReporte(const char* nombArchRep,
                    char *arrLetraPlacaInfraCom,int *arrNum1PlacaInfraCom,
                    int *arrNum2PlacaInfraCom,int *arrCantMultasPagadasInfraCom,
                    double* arrTotalMultasPagadasInfraCom,int *arrCantMultasPendInfraCom,
                    double *arrTotalMultasPendInfraCom,int *arrFechaMasAntiguaInfraCom,
                    int cantPlacas);

//Modulos auxiliares
void imprimirNroOrden(ofstream& archRep,int orden);
void imprimirCabeceraReporte(ofstream& archRep);
void swapChar(char &a,char &b);
void swapInt(int &a,int &b);
void swapDouble(double &a,double &b);
void imprimirFecha(ofstream& output,int fecha);
int leerFecha(ifstream& input);
void imprimirCabeceraRepTablaInfra(ofstream& archRep);
void imprimirLineas(char c,int cant,ofstream& archRep);
void ignorar(ifstream& input,char delimitador);

#endif //EX01_25_1_ARREGLOS_FUNCIONESAUXILIARES_H
