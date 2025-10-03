//
// Created by DIEGO on 29/08/2025.
//

#ifndef LAB01_24_2_FUNCIONESAUXILIARES_H
#define LAB01_24_2_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
using namespace std;

void crearReporte();
void imprimirCabeceraReporte(int dia,int mes,int anio);

void imprimirLineas(char c,int cant);
void leerNombre_ImpRep(int dni);
double leerRuta_ImpRep();
double imprimirTramo(int i,int horaInc,int minutoInc,int segundoInc,double velocidadProm,
                   int horaFin,int minutoFin,int segundoFin,int grados,int minutos,int segundos,double &xIni,double &yIni,double &distanciaAcumulada);
double calcularDistancia(int horaInc,int minutoInc,int segundoInc,int horaFin,int minutoFin,int segundoFin,double velocidadProm);
void calcularCoordenadaLlegada(double xIni,double yIni,int grados,int minutos,int segundos,double distancia,double &xFin,double &yFin);
double calcularPago(double distancia);
void calcularHoraTermino(double tiempo,int &horaTermino,int &minutoTermino,int &segundoTermino,int horaFin,int minutoFin,int segundoFin);


void imprimirReporte(int dniRepMayRec,double distRepMayRec, int dniRepMenRec,double distRepMenRec);
void actualizarResumen(int dni, double recorrido,
                       int &dniMax, double &distMax,
                       int &dniMin, double &distMin,
                       int &esPrimero);
void imprimirRetorno(int horaFin,int minutoFin,int segundoFin,double velocidadProm,double xIni,double yIni,double &distanciaAcumulada);
void leerRepartidor_ImpReporte(int &dniRepMayRec,double &distRepMayRec,
                               int &dniRepMenRec,double &distRepMenRec,
                               int &esPrimero);



#endif //LAB01_24_2_FUNCIONESAUXILIARES_H
