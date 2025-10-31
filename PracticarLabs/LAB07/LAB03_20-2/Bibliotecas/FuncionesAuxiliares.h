//
// Created by ASUS on 30/10/2025.
//

#ifndef LAB03_20_2_FUNCIONESAUXILIARES_H
#define LAB03_20_2_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring> //funcion para manejar cadenas
using namespace std;
#define MAX_PRODUCTOS 100
#define NO_ENCONTRADO -1

//Modulos apertura archivos
void aperturaArchivoLectura(const char* nombArch,ifstream& arch);
void aperturaArchivoEscritura(const char* nombArch,ofstream& arch);

//Modulos principales
void cargarProductosConCstring(const char* nombArch,
                    int *arrCodeProducto,int *arrStockProducto,
                    char* *arrDescProd,int &cantProductos);

void cargarProductosSinCstring(const char* nombArch,
                    int *arrCodeProducto,int *arrStockProducto,
                    char* *arrDescProd,int &cantProductos);


void pruebaProductos(const char* nombArchRep,
                    int *arrCodeProducto,int *arrStockProducto,
                    char **arrDescProd,int cantProductos);

void procesarMovimientos(const char* nombArchMov,
                        int *arrCodeProducto,int *arrStockProducto,
                        char **arrDescProd,int &cantProductos,
                        int *arrCodeProductoDef,int *arrStockProductoDef,
                        char **arrDescProdDef,int &cantProductosDef);

void actualizarMovimientos(char tipoMov,int codeProducto,int cantMov,
                            int *arrCodeProducto,int *arrStockProducto,
                            char **arrDescProd,int &cantProductos,
                            int *arrCodeProductoDef,int *arrStockProductoDef,
                            char **arrDescProdDef,int &cantProductosDef);

void eliminarProducto(int *arrCodeProducto,int *arrStockProducto,
                        char **arrDescProd,int &cantProductos,int posProducto);

void enviarProductoAOtroArreglo(int codeProducto,int stockProducto,char *descProducto,
                                int *arrCodeProducto,int *arrStockProducto,char**arrDescProducto,
                                int &cantProductos) ;

void generarReporte(const char *nombArchRep,
        int *arrCodeProducto,int *arrStockProducto,char **arrDescProd,int cantProductos,
        int *arrCodeProductoDef,int *arrStockProductoDef,char **arrDescProdDef,int cantProductosDef);

void ordenarReporte(int *arrCodeProducto,int *arrStockProducto,char **arrDescProd,int cantProductos,
                    int *arrCodeProductoDef,int *arrStockProductoDef,char **arrDescProdDef,int cantProductosDef);
//Modulos auxiliares
void swapInt(int&a,int&b);
void swapChar(char* &a,char* &b);
void swapDouble(double&a,double&b);
void imprimirSubtituloReporte(ofstream& output);
int calcularLongitud(const char *arrDescProd);
void copiar(char* arrDescProd,const char* cadenaAux);
int buscarPosicion(int dato,int *arrDato,int cantDatos);
void imprimirSubtituloPruebaProductos(ofstream& output);
void imprimirLineas(char c,int cant,ofstream& output);

#endif //LAB03_20_2_FUNCIONESAUXILIARES_H
