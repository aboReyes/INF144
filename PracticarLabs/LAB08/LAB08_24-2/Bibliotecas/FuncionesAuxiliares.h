//
// Created by ASUS on 7/11/2025.
//

#ifndef LAB08_24_2_FUNCIONESAUXILIARES_H
#define LAB08_24_2_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;

#define MAX_DISTRITOS 50
#define MAX_PLATOS 120
#define MAX_CLIENTES 120
#define MAX_CARACTERES 100
#define NO_ENCONTRADO -1

#include "Plato.h"
#include "Cliente.h"
#include "Distrito.h"

//Apertura Archivos
void aperturaArchivoLectura(const char* nombArch,ifstream& arch);
void aperturaArchivoEscritura(const char* nombArch,ofstream& arch);

//Principales

void leerPlatosOfrecidos(const char* nombArchPlatos,
                         Plato *arrPlatos,int &cantPlatos);
void pruebaPlatosOfrecidos(const char* nombArchRep,
                        Plato *arrPlatos,int cantPlatos);

void leerDistritos(const char* nombArchDistritos,
                 Distrito *arrDistritos,int &cantDistritos);
void pruebaDistritos(const char* nombArchRep,
                Distrito *arrDistritos,int cantDistritos);

void leerClientes(const char* nombArchClientes,
                Cliente *arrClientes,int &cantClientes,
                Distrito *arrDistritos, int cantDistritos);
int buscarDistrito(char* codigoDistrito,Distrito *arrDistritos,int cantDistritos);
void pruebaClientes(const char* nombArchRep,
                Cliente *arrClientes,int cantClientes);

void procesarPedidosRealizados(const char* nombArchPedRe,
                            Plato *arrPlatos,int cantPlatos,
                            Distrito *arrDistritos,int cantDistritos,
                            Cliente *arrClientes,int cantClientes);
int buscarCliente(int dniCliente,Cliente *arrClientes,int cantClientes);
int buscarPlato(char * codigoPlato,Plato *arrPlatos,int cantPlatos);

void insertarPedido(Cliente &clienteElegido,Plato &platoElegido,
                    int codigoPedido,int cantidadPedida);

void ordenarClientes(Cliente *arrClientes,int cantClientes);

void ordenarPlatosPedidos(Cliente *arrCliente,int cantClientes);

void emitirReporte(const char* nombArchRep,
                Cliente *arrClientes,int cantClientes,
                Distrito *arrDistritos,int cantDistritos,
                Plato *arrPlatos,int cantPlatos);

void imprimirPedidosRealizados(ofstream &output,PlatoPedido *platoPedido,
                                int cantPlatoPedido,
                                Plato *arrPlatos,int cantPlatos);

//Auxiliares
void imprimirCabeceraPedidosRealizados(ofstream &output);
void imprimirCabeceraCliente(ofstream &output,int nroOrden);
void imprimirTitulo(ofstream &output);
void swapStrucPlatoPedido(PlatoPedido &dato1,PlatoPedido &dato2);
void swapStructCliente(Cliente &cliente1,Cliente &cliente2);
void imprimirCabeceraPruebaClientes(ofstream &output);
void imprimirCabeceraPruebaDistritos(ofstream &output);
void imprimirCabeceraPruebaPlatosOfrecidos(ofstream& output);
void imprimirLineas(char c,int cant,ofstream& output);
int readInt(ifstream& input);
double readDouble(ifstream& input);

#endif //LAB08_24_2_FUNCIONESAUXILIARES_H
