//
// Created by ASUS on 11/09/2025.
//

#ifndef LAB01_25_2_FUNCIONESAUXILIARES_H
#define LAB01_25_2_FUNCIONESAUXILIARES_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;

void procesarDatos(const char* nomArchIn,const char* nomArchOut);

void leerDatosCanalReporte(ifstream &archTwitch,ofstream &archRep,
                        int &cantTotalStreams,int &durTotalStreamsSeg,double &ingTotalStreams,
                        double &mayorIngresoCanal,int &codigoCanalMayorIngreso,char &letraCanalMayorIngreso,int &nroCanal);

void imprimirCabeceraCanal(int dia,int mes,int año,char letraCodCanal,int numCodCanal,
                            ifstream &archTwitch,ofstream &archRep,int nroCanal);

void leerImprimirNombreCanal(ifstream &archTwitch,ofstream &archRep);

void imprimirLinea(char c,int cant,ofstream &archRep);

void leerStreamsReporte(ifstream &archTwitch,ofstream &archRep,
                        int &cantTotalStreams,int &durTotalStreamsSeg,double &ingTotalStreams,
                        double &mayorIngresoCanal,int &codigoCanalMayorIngreso,char &letraCanalMayorIngreso,
                        char letraCodCanal,int numCodCanal );

void procesarDatosTransmision(int dia,int mes,int año,int hora,int minuto,int segundo,int cantVistas,
                                int &durStreamsCanalSeg,int &ultimaFechaStreamCanal,int &cantStreamsCanal);

double imprimirResumenCanal(ofstream &archRep,int durStreamsCanalSeg,int ultimaFechaStreamCanal,int cantStreamsCanal);

void imprimirDatosTransmisiones(int dia,int mes,int año,int hora,int minuto,int segundo,int cantVistas,ofstream &archRep);

void imprimirResumenFinal(ofstream &archRep,int cantTotalStreamers,int durTotalStreamsSeg,
                        double ingTotalStreams,double mayorIngresoCanal,int codCanalMayorIngreso,char letraCanalMayorIngreso);

void imprimirHora(ofstream &archRep,int hora,int minuto,int segundo);
void imprimirFecha(ofstream &archRep,int dia,int mes,int año);



#endif //LAB01_25_2_FUNCIONESAUXILIARES_H
