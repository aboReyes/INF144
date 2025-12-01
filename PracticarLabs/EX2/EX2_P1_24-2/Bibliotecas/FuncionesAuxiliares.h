//
// Created by ASUS on 30/11/2025.
//

#ifndef EX2_24_2_P1_FUNCIONESAUXILIARES_H
#define EX2_24_2_P1_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
using namespace std;
#include "Palabra.h"
#include "Comentario.h"
#include "Plato.h"
#include "Atencion.h"

#define NO_ENCONTRADO -1
#define MAX_PALABRAS 100
#define MAX_PLATOS 200
#define MAX_ATENCIONES 100

//aperturaArchivos
void aperturaArchivoLectura(const char* nombArch,ifstream& arch);
void aperturaArchivoEscritura(const char* nombArch,ofstream& arch);

//principales
void leerLexicon(const char*nombArch,Palabra *lexicon,int &cantidadPalabras);
void leerPlatos(const char* nombArch,Plato *platos,int &cantidadPlatos);
void leerProcesarAtenciones(const char*nombArch,
                            Atencion *atenciones,int &cantidadAtenciones,
                            Plato *platos,int cantidadPlatos);
int buscarPlato(char* codigoPlatoLeido,Plato *platos,int cantidadPlatos);
void preProcesarComentario(char* comentario);
void leerComentarios(const char* nombArch,Atencion *atenciones,int cantidadAtenciones,
                    Palabra *lexicon,int cantidadPalabras);
int buscarPolaridad(char* separador,Palabra *lexicon,int cantidadPalabras);
int procesarComentario(char *comentario,Palabra *lexicon,int cantidadPalabras,
                        Comentario &comentarioStruct);
int buscarAtencion(int nroAtencion,Atencion *atenciones,int cantidadAtenciones);

void emitirReporteAtenciones(const char* nombArch,
                             Atencion *atenciones,int cantidadAtenciones);

//auxiliares
void imprimirLineas(ofstream &arch, char c, int n);
double leerDouble(ifstream&input);
int leerEntero(ifstream& input);
void imprimirHora(ofstream& output,int hora);
int leerHora(ifstream&input);
char* asignarCadena(char* buffer);
char* leerCadenaExacta(ifstream& input,char delimitador,int n);


#endif //EX2_24_2_P1_FUNCIONESAUXILIARES_H
