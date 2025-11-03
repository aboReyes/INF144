//
// Created by ASUS on 3/11/2025.
//

#ifndef LAB06_24_1_FUNCIONESAUXILIARES_H
#define LAB06_24_1_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#define MAX_FACULTADES 10
#define NO_ENCONTRADO -1
#define MAX_CARACTERES 100
#define MAX_CALIFICACIONES 80

//Apertura de archivos
void aperturaArchivosLectura(const char*nombArch,ifstream &arch);
void aperturaArchivosEscritura(const char*nombArch,ofstream &arch);
//Principales
void preguntarFacultad(int& codigoFacultad);
void cargarFacultades(const char* nombArch,
                    char **facultad,int *arrCodeFacultad,
                    int &cantFacultades);
void insertarOrdenado(char* nombreFac,int codigoFacultad,
                    char **facultad,int *arrCodeFacultad,int &cantFacultades);
int buscarFacultad(int codigoFacultad,int *arrCodigoFacultad,
                    int cantFacultades);

void cargarCalificaciones(const char* nombArch,
                        int *arrCodigoAlumnos,int *arrNumCursos,
                        double *arrSumaPonderada,double *arrNumCreditos,
                        int &cantCalificaciones);

void procesamientoCalificaciones(int codigoAlumno,int notaAlumno,double creditosCurso,
                                int *arrCodigoAlumnos,int *arrNumCursos,
                                double *arrSumaPonderada,double *arrNumCreditos,
                                int &cantCalificaciones);

int buscarCalificacion(int codigoAlumno,int* arrCodigoAlumnos,int &cantCalificaciones);

void insertarOrdenado2(int codigoAlumno,int notaAlumno,double creditosCurso,
                        int *arrCodigoAlumnos,int *arrNumCursos,double *arrSumaPonderada,
                        double *arrNumCreditos,int &cantCalificaciones);

void generarReporte(const char* nombArchAlumnos,
                    const char* nombArchRep,
                    int codigoFacultad,int *arrCodigoFacultad,
                    char**facultad,
                    int *arrCodigoAlumnos,int *arrNumCursos,
                    double *arrSumaPonderada,double *arrNumCreditos,
                    int cantCalificaciones,
                    int cantFacultades);


//Auxiliares
void formato3(char* nombre) ;
void formato2(char *nombre);
void imprimirLineas(char c,int cant,ofstream & output);
void imprimirCabeceraReporte(ofstream& output,char *facultad);
void formato1(char* facultad);
char* readString(ifstream& input);


#endif //LAB06_24_1_FUNCIONESAUXILIARES_H
