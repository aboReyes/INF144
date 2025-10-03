//
// Created by ASUS on 14/09/2025.
//

#ifndef LAB02_24_1_FUNCIONESAUXILIARES_H
#define LAB02_24_1_FUNCIONESAUXILIARES_H

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

void procesarReporte(const char* nomArchIn,const char* nomArchOut);
void imprimirCabeceraReporte(ofstream &archRep);
void imprimirLineas(char c,int cant,ofstream &archRep);
void imprimirSubtitulo(ofstream &archRep);
void leerImprimirDatosCitas(ofstream &archRep,ifstream &archCitas,
                            int &cantCitasRegistradas,int &cantCitasProcesadas,
                            double &pagoTotalAcumulado);
double convertirHHMMSS_Horas(int hora,int minuto,int seg);
void imprimirFecha(int dia,int mes,int año,ofstream &archRep);
void imprimirHora(int hora,int minuto,int segundo,ofstream &archRep);
int convertirHHMMSS_Seg(int hora,int min,int seg);
void convertirSeg_HHMMSS(int numero,int &hora,int &minuto,int &segundo);
double procesarPagoMedico(double montoMed,double porcSeguro,
                        double tarifaMedico,double duracionHoras );

void imprimirReporteFinal(ofstream &archRep,int cantCitasReg,
                        int cantCitasProcesadas);

#endif //LAB02_24_1_FUNCIONESAUXILIARES_H
