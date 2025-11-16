//
// Created by ASUS on 16/11/2025.
//

#ifndef LAB09_25_1_FUNCIONESAUXILIARES_H
#define LAB09_25_1_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#define MAX_CARACTERES 100
#define NO_ENCONTRADO -1
#define MAX_TABLA_INFRA 150
#define MAX_EMPRE_REG 50

#include "Fecha.h"
#include "TablaDeInfracciones.h"
#include "EmpresaRegistrada.h"
#include "InfraccionCometida.h"

//apertura archivos
void aperturaArchivoLectura(const char* nombArch,ifstream& arch);
void aperturaArchivoEscritura(const char* nombArch,ofstream& arch);

//modulos principales
void leerTablaDeInfracciones(const char* nombArch,
                            TablaDeInfracciones *arrTablaDeInfracciones,
                            int &cantTablaDeInfracciones);

void leerEmpresasRegistradas(const char* nombArch,
                            EmpresaRegistrada *arrEmpresasRegistradas,
                            int &cantEmpresasRegistradas);

void leerCompletarPlacasRegistradas(const char* nombArch,
                                    EmpresaRegistrada *arrEmpresasRegistradas,
                                    int cantEmpresasRegistradas);

int buscarPlaca(int dniLeido,EmpresaRegistrada *arrEmpresasRegistradas,int cantEmpresasRegistradas);

void leerInfraccionesCometidas(const char* nombArch,
                            TablaDeInfracciones *arrTablaDeInfracciones,
                            int cantTablaDeInfracciones,
                            EmpresaRegistrada *arrEmpresasRegistradas,
                            int cantEmpresasRegistradas);
int buscarEmpresa(char *placaLeida,EmpresaRegistrada *arrEmpresasRegistradas,int cantEmpresasRegistradas);
int buscarInfraccion(char *codigoInfraccion,TablaDeInfracciones *arrTablaDeInfracciones,int cantTablaDeInfracciones);

void agregarInfraccion(EmpresaRegistrada &empresa,TablaDeInfracciones infraccion,
                        int diaInfra,int mesInfra,int añoInfra,
                        int diaPago,int mesPago,int añoPago,char letraPago,char* placaLeida);

void calcularMontosTotalesYAdeudados(EmpresaRegistrada *arrEmpresaRegistrada,
                                    int cantEmpresasRegistradas);

void ordenarEmpresasRegistradas(EmpresaRegistrada *arrEmpresasRegistradas,int cantEmpresasRegistradas);

void ordenarInfracciones(EmpresaRegistrada &empresa);

void emitirReporte(const char* nombArchReporte,
                TablaDeInfracciones *arrTablaDeInfracciones,int cantTablaDeInfracciones,
                EmpresaRegistrada *arrEmpresasRegistradas,int cantEmpresasRegistradas);

void imprimirMultasEmpresa(ofstream &output,EmpresaRegistrada &empresa, bool esPagada);


//modulos auxiliares
void imprimirCabeceraMultas(ofstream& output,bool esPagada);
void imprimirCabeceraReporte(ofstream& output);
void imprimirLineas(char c,int cant,ofstream& output);
void imprimirOrden(ofstream& output,int nroOrden,bool formato1);
void swapInfraccion(InfraccionCometida &dato1,InfraccionCometida&dato2);
void swapStruct(EmpresaRegistrada &dato1,EmpresaRegistrada &dato2);
void imprimirFecha(ofstream& output,int fecha);
int leerFecha(ifstream& input);
void modificarTextoAMayus(char* texto);
double leerDouble(ifstream& input);
int leerEntero(ifstream& input);
char* leerCadena(ifstream& input,char delimitador,int n);
char* asignarCadena(const char* origen);



#endif //LAB09_25_1_FUNCIONESAUXILIARES_H
