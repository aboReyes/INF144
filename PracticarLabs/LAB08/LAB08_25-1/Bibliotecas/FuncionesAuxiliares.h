//
// Created by ASUS on 9/11/2025.
//

#ifndef LAB08_25_1_FUNCIONESAUXILIARES_H
#define LAB08_25_1_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;

#define MAX_TABLA_INFRA 150
#define MAX_EMPRESA_REG 50
#define MAX_CARACTERES 100
#define NO_ENCONTRADO -1

#include "TablaDeInfracciones.h"
#include "EmpresasRegistradas.h"

//Apertura de archivos
void aperturaArchivoDatos(const char* nombArch,ifstream& arch);
void aperturaArchivoReporte(const char* nombArch,ofstream& arch);

//Principales
void leerTablaInfracciones(const char* nombArch,
                            TablaDeInfracciones *arrTablaDeInfracciones,
                            int& cantTablaDeInfracciones);

void leerEmpresasRegistradas(const char* nombArchEmpReg,
                            EmpresasRegistradas *arrEmpresasRegistradas,
                            int& cantEmpresasRegistradas);

void completarPlacasRegistradas(const char* nombArch,
                            EmpresasRegistradas *arrEmpresasRegistradas,
                            int cantEmpresasRegistradas);
int buscarEmpresa(int dniEmpresa,EmpresasRegistradas *arrEmpresasRegistradas,
                    int cantEmpresasRegistradas);

void completarInfracciones(const char* nombArch,
                           TablaDeInfracciones *arrTablaDeInfracciones,int cantTablaDeInfracciones,
                           EmpresasRegistradas *arrEmpresasRegistradas,int cantEmpresasRegistradas);
int buscarPlacaEnEmpresas(char* placa,EmpresasRegistradas *arrEmpresasRegistradas,
                            int cantEmpresasRegistradas);
int buscarInfraccion(char* codigoInfra,TablaDeInfracciones *arrTablaDeInfracciones,
                    int cantTablaDeInfracciones);
void actualizarDatosEmpresasRegistradas(ifstream& input,
                                        char c,int posEmpresa,double multa,
                                        EmpresasRegistradas *arrEmpresasRegistradas);

void ordenarEmpresasRegistradas(EmpresasRegistradas *arrEmpresasRegistradas,
                                int cantEmpresasRegistradas);

void ordenarTablaDeInfracciones(TablaDeInfracciones *arrTablaDeInfracciones,
                                int cantTablaDeInfracciones);

void imprimirReporte(const char* nombArchRep,
                    TablaDeInfracciones *arrTablaDeInfracciones,int cantTablaDeInfracciones,
                    EmpresasRegistradas *arrEmpresasRegistradas,int cantEmpresasRegistradas);


//Auxiliares
void imprimirCabeceraReporteInfracciones(ofstream& output);
void imprimirLineas(char c,int cant,ofstream& output);
void imprimirCabeceraReporteEmpresas(ofstream& output);
void swapStruct(EmpresasRegistradas &datoA,EmpresasRegistradas &datoB);
void swapStruct2(TablaDeInfracciones &datoA,TablaDeInfracciones &datoB);
void imprimirFecha(ofstream& output,int fecha);
void formatoAMayus(char* nombre);
char* readString(ifstream& input,char delimitador);
int readInt(ifstream& input,bool esUltimo);
double readDouble(ifstream& input,bool esUltimo);


#endif //LAB08_25_1_FUNCIONESAUXILIARES_H
