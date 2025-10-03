
//
// Created by ASUS on 3/09/2025.
//

#ifndef LAB25_1_FUNCIONESAUXILIARES_H
#define LAB25_1_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
using namespace std;

void leerFecha_MostrarTitulo(int &diaIni,int &mesIni,int &añoIni,int &diaFin,int &mesFin,int &añoFin);
void leerFecha(int &diaIni,int &mesIni,int &añoIni);
void imprimirLineas(char c, int cant);
void leerImprimirReporteCompañia(int diaIni,int mesIni,int añoIni,
                                int diaFin,int mesFin,int añoFin);
void leerRepresentanteLegal();
void imprimirSubtitulo();
void procesarInfraccionVehiculo(int diaIni,int mesIni,int añoIni,
                                int diaFin,int mesFin,int añoFin,
                                double &multaTotalCom);
void leerImprimirTipoVehiculos(char tipoVehiculo);
void imprimirGravedad(char gravedad);
double retornarMulta(char gravedad);
double retornarMultaPorTipo(char tipoVehiculo,double multa);
int transformarDDMMAA_Numero(int dia,int mes,int año);
double retornarMultaPorFecha(double multa,int fechaIni,int fechaFin,int fecha);
int transformarHHMMSS_segundos(int hora,int min,int seg);
double retornarMultaPorHora(double multa,int horaMañana,int horaTarde,int horaNoche,
                            int hora);


#endif //LAB25_1_FUNCIONESAUXILIARES_H
