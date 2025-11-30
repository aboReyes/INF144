//
// Created by ASUS on 30/11/2025.
//

#ifndef EX2_25_1_P1_FUNCIONESAUXILIARES_H
#define EX2_25_1_P1_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "Conductor.h"
#include "Vehiculo.h"
#include "Infraccion.h"
#include "Fecha.h"

#define MAX_CONDUCTORES 120
#define MAX_VEHICULOS 160
#define MAX_INFRACCIONES 160

//apertura de archivos
void aperturaArchivoLectura(const char* nombArch,ifstream& arch);
void aperturaArchivoEscritura(const char* nombArch,ofstream& arch);

//principales
void leerConductores(const char* nombArch,Conductor *conductores,int &cantidadConductores);
void leerVehiculos(const char* nombArch,Vehiculo *vehiculos,int& cantidadVehiculos);
void leerInfracciones(const char* nombArch,Infraccion *infracciones,int &cantidadInfracciones);
void procesarInfraccion(Infraccion &infraccion);
void actualizarInformaciones(Conductor *conductores,int cantidadConductores,
                            Vehiculo *vehiculos,int cantidadVehiculos,
                            Infraccion *infracciones,int cantidadInfracciones);
void generarEnlace(char* nombre,char* apellido,char* licencia,char* &enlace);
void emitirPapeletas(Conductor *conductores,int cantidadConductores);
//auxiliares
char* leerCadenaExacta(ifstream&input,char delimitador,int n);
char* asignarCadena(char* buffer);
void imprimirFecha(ofstream& output,int fecha);
int leerFecha(ifstream& input);
double leerDouble(ifstream& input);
int leerEntero(ifstream& input);

#endif //EX2_25_1_P1_FUNCIONESAUXILIARES_H
