//
// Created by ASUS on 26/10/2025.
//

#ifndef P2_HASTACANSARME_FUNCIONESAUXILIARES_H
#define P2_HASTACANSARME_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#define NO_ENCONTRADO -1
#define MAX_STREAMS 120

//ModulosAperturaDeArchvos
void aperturaArchivosLectura(const char* nombArch,ifstream& arch);
void aperturaArchivosEscritura(const char* nombArch,ofstream& arch);

//ModulosPrincipales
void cargarStreams(const char*nombArchStreams,
        int *arrCodeStream,int *arrDurStream,int *arrCodeIdioma,
        char *arrCodeCharCatIdioma,int *arrCodeIntCatIdioma,int &cantStreams);

void insertarOrdenado(int codeStream,int durStream,int codeIdioma,
            char codeCharCatIdioma,int codeIntCatIdioma,
            int *arrCodeStream,int *arrDurStream,int *arrCodeIdioma,
            char *arrCodeCharCatIdioma,int *arrCodeIntCatIdioma,int &cantStreams);

void pruebaStreams(const char* nombArchRep,
            int *arrCodeStream,int *arrDurStream,int *arrCodeIdioma,
            char *arrCodeCharCatIdioma,int *arrCodeIntCatIdioma,int cantStreams);

void procesarCanales(const char* nombArch,
        int *arrCodeStream,int *arrDurStream,int cantStreams,
        int *arrFechaAntiguaCanal,int *arrFechaRecienteCanal,
        double *arrPromDropCanal,double *arrPromRatingCanal,
        int *arrCantReproCanal,int *arrTiempoTotalReproCanal);

int busquedaBinaria(int codeStream,int *arrCodeStream,int cantStreams);

void imprimirReporte(const char *nombArchRep,
        int *arrCodeStream,int *arrDurStream,int *arrCodeIdioma,
        char *arrCodeCharCatIdioma,int *arrCodeIntCatIdioma,int cantStreams,
        int *arrFechaAntiguaCanal,int *arrFechaRecienteCanal,
        double *arrPromDropCanal,double *arrPromRatingCanal,
        int *arrCantReproCanal,int *arrTiempoTotalReproCanal,
        bool ordenado);

void ordenarReporte(int *arrCodeStream,int *arrDurStream,int *arrCodeIdioma,
        char *arrCodeCharCatIdioma,int *arrCodeIntCatIdioma,int cantStreams,
        int *arrFechaAntiguaCanal,int *arrFechaRecienteCanal,
        double *arrPromDropCanal,double *arrPromRatingCanal,
        int *arrCantReproCanal,int *arrTiempoTotalReproCanal);

void eliminar(int *arrCodeStream,int *arrDurStream,int *arrCodeIdioma,
        char *arrCodeCharCatIdioma,int *arrCodeIntCatIdioma,int cantStreams,
        int *arrFechaAntiguaCanal,int *arrFechaRecienteCanal,
        double *arrPromDropCanal,double *arrPromRatingCanal,
        int *arrCantReproCanal,int *arrTiempoTotalReproCanal);


//ModulosAuxiliares
void swapInt(int &a,int&b);
void swapChar(char &a,char&b);
void swapDouble(double &a,double&b);
void imprimirResumen(ofstream&output,
    int mayorDur,int mayorCode,int menorDur,int menorCode);
void imprimirGuiones(ofstream& output);
void imprimirSubtituloReporteFinal(ofstream& output);
void imprimirSubtituloReportePrueba(ofstream& output);
void imprimirLineas(char c,int cant,ofstream&output);
int leerFecha(ifstream& input);
void imprimirFecha(ofstream& output,int fecha);
int leerTiempo(ifstream&input);
void imprimirTiempo(ofstream& output,int tiempo);
void ignorar(ifstream& input,char delimitador);



#endif //P2_HASTACANSARME_FUNCIONESAUXILIARES_H
