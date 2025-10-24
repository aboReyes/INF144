//
// Created by ASUS on 24/10/2025.
//

#ifndef P2_EX1_25_2_MODIFICADO_FUNCIONESAUXILIARES_H
#define P2_EX1_25_2_MODIFICADO_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#define MAX_STREAMS 120
#define NO_ENCONTRADO -1

//Modulos apertura de archivos
void aperturaArchivoLectura(const char* nombArch,ifstream& arch);
void aperturaArchivoEscritura(const char* nombArch,ofstream& arch);


//Modulos principales
void cargarStreams(const char* nombArchStreams,
        int *arrCodeStream,int *arrDurStream,int *arrCodeIdiomaStream,
        char *arrLetraCatIdiomaStream,int *arrNumCatIdiomaStream,
        int &cantStreams);

void insertarOrdenado(int codeStream,int durStream,int codeIdioma,
                    char letraCatIdioma,int numCatIdioma,
                    int *arrCodeStream,int *arrDurStream,
                    int *arrCodeIdiomaStream,
                    char *arrLetraCatIdiomaStream,int *arrNumCatIdiomaStream,
                    int &cantStreams);

void pruebaStreams(const char* nombArchRep,
                    int *arrCodeStream,int *arrDurStream,int *arrCodeIdiomaStream,
                    char *arrLetraCatIdiomaStream,int *arrNumCatIdiomaStream,
                    int cantStreams);

void procesarCanales(const char* nombArchCanales,
        int *arrCodeStream,int *arrDurStream,int cantStreams,
        int *arrFechaAntiguaCanal,int *arrFechaRecienteCanal,
        double *arrPromRatingCanal,double *arrPromDropCanal,
        int *arrCantReproCanal,int *arrTiempoTotalReproCanal);

int buscarBinario(int codeStream,int *arrCodeStream,int cantStream);

void reporteStream(const char* nombArchRep,
            int *arrCodeStream,int *arrCodeIdiomaStream,
            char *arrLetraCatIdiomaStream,int *arrNumCatIdiomaStream,
            int *arrFechaAntiguaCanal,int *arrFechaRecienteCanal,
            double*arrPromRatingCanal,double*arrPromDropCanal,int *arrDurStream,
            int *arrCantReproCanal,int *arrTiempoTotalReproCanal,
            int cantStreams,bool esOrdenado);

void imprimirResumen(ofstream& output,int mayorTiempo,int codeMayor,
                    int menorTiempo,int codeMenor);

void eliminar(int *arrCodeStream,int *arrCodeIdiomaStream,
            char *arrLetraCatIdiomaStream,int *arrNumCatIdiomaStream,
            int *arrFechaAntiguaCanal,int *arrFechaRecienteCanal,
            double *arrPromRatingCanal,double *arrPromDropCanal,int *arrDurStream,
            int *arrCantReproCanal,int *arrTiempoTotalReproCanal,
            int cantStreams);

void ordenarReporte(int *arrCodeStream,int *arrCodeIdiomaStream,
            char *arrLetraCatIdiomaStream,int *arrNumCatIdiomaStream,
            int *arrFechaAntiguaCanal,int *arrFechaRecienteCanal,
            double *arrPromRatingCanal,double *arrPromDropCanal,int *arrDurStream,
            int *arrCantReproCanal,int *arrTiempoTotalReproCanal,
            int cantStreams);


//Modulos auxiliares
void imprimirLineas(char c,int cant,ofstream& output);
void swapInt(int &a,int &b);
void swapChar(char &a,char &b);
void swapDouble(double &a,double &b);
void imprimirGuiones(ofstream& output);
void imprimirCabeceraReporte(ofstream& output);
void imprimirSubtituloPruebaStreams(ofstream& output);
void imprimirFecha(ofstream& output,int fecha);
int leerFecha(ifstream& input);
void ignorar(ifstream& input,char delimitador);
int leerTiempo(ifstream& input);
void imprimirTiempo(ofstream& output,int tiempo);

#endif //P2_EX1_25_2_MODIFICADO_FUNCIONESAUXILIARES_H
