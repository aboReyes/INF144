//
// Created by ASUS on 12/10/2025.
//

#ifndef EX01_P1_24_2_FUNCIONESAUXILIARES_H
#define EX01_P1_24_2_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

//modulo apertura de archivos
void aperturaArchivoLectura(const char* nombArch,ifstream& arch);
void aperturaArchivoEscritura(const char* nombArch,ofstream& arch);

//modulos principales
void generarReporte(const char* nombArchClientes,
                    const char* nombArchPlatosOfrecidos,
                    const char* nombArchRepartidores,
                    const char* nombArchRepartosARealizar,
                    const char* nombArchReporte);

void leerImprimirInformeCliente(ifstream& archClientes,ifstream& archPlatOfrec,
                                ifstream& archRepartidores,ifstream& archRepaRealizar,
                                ofstream& archReporte,int &dniCliente,int &codeDistrito,
                                char &tipoVehiculo,double &descuento);

void buscarRepartosARealizar(ifstream& archRepaRealizar,ifstream& archPlatOfrec,ofstream& archRep,
                            int dniCliente,int &cantPedidos,
                            double &subtotalPorCliente,double &descuentosPorCliente);

void buscarRepartidor(ifstream& archRepartidores,ofstream& archReporte,
                        char tipoVehiculo,int codeDistrito);

void buscarPlatosOfrecidos(ifstream& archPlatOfrec,ofstream &archRep,
                            int cantidadPlato,int codePlato,int &cantPlatos,
                            double &subtotalPorCliente,double &descuentosPorCliente);

void imprimirResumen(ofstream& archRep,double subtotalPorCliente,double descuentosPorCliente,
                    double descuentoCliente,char tipoVehiculo);



//modulos auxiliares
double verificarDescuentoPorVeh(char tipoVehiculo) ;
void imprimirSubtituloRepartos(ofstream& archRep);
void imprimirOrden(ofstream& archRep,int nroOrden,bool conCero);
void ignorar(ifstream &input,char delimitador);
double verificarDescuento(ifstream& input,ofstream& output,char tieneDescuento);
void filtrarTipoVehiculo(char tipoVehiculo,ofstream& archReporte);
void leerImprimirNombresVariados(ifstream& input,ofstream& output,
                            char delimitador,int tam,bool mayus);
void imprimirTitulo(ofstream &archRep);
void imprimirLineas(char c,int cant,ofstream& archRep);

#endif //EX01_P1_24_2_FUNCIONESAUXILIARES_H
