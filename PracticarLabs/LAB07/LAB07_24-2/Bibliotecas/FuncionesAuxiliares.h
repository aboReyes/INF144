//
// Created by ASUS on 31/10/2025.
//

#ifndef LAB07_24_2_FUNCIONESAUXILIARES_H
#define LAB07_24_2_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
using namespace std;
#define NO_ENCONTRADO -1
#define MAX_REPARTIDORES 70
#define MAX_PLATOS_OFRECIDOS 120
#define MAX_CARACTERES 100


//Aperturar archivos
void aperturaArchivoLectura(const char* nombArch,ifstream& arch);
void aperturaArchivoEscritura(const char* nombArch,ofstream& arch);

//Principales
void cargarRepartidores(const char* nombArch,
                        int *arrDniRepartidor,char **arrNombreRepartidor,
                        char **arrTipoVehiculo,int *arrCodigoDistrito,
                        char **arrNombreDistrito,int &cantRepartidores);

void cargarPlatos(const char *nombArch,
                int *arrCodigoPlato,char **arrNombrePlato,
                double *arrPrecioPlato,char **arrCategoriaPlato,
                double *arrDescuentoPlato,int &cantPlatos);

void reportePrueba(const char* nombArchRep,
            int *arrDniRepartidor,char **arrNombreRepartidor,
            char **arrTipoVehiculo,int *arrCodigoDistrito,
            char **arrNombreDistrito,int cantRepartidores,
            int *arrCodigoPlato,char **arrNombrePlato,
            double *arrPrecioPlato,char **arrCategoriaPlato,
            double *arrDescuentoPlato,int cantPlatos);

void ordenarRepartidores(int *arrDniRepartidor,char **arrNombreRepartidor,
                        char **arrTipoVehiculo,int *arrCodigoDistrito,
                        char **arrNombreDistrito,int cantRepartidores);

void procesarRepartosARealizar(const char* nombArch,
                            char **arrTipoVehiculo,int *arrCodigoDistrito,int cantRepartidores,
                            int *arrCodigoPlato,double *arrPrecioPlato,double *arrDescuentoPlato,int cantPlatos,
                            int *arrTotalCantPlatosRep,double *arrMontoTotalPlatos,double *arrDescuentoPorPlatos,
                            double *arrDescuentoPorClientes,double *arrPagoAlRepartidor,double *arrTotalIngresadoRep,
                            int *arrTotalCantPlatos,double *arrMontoVendido,double *arrDescuentoAlPlato,
                            double *arrDescuentoAlCliente,double *arrTotalIngresadoPlatos);

void procesarPlatosRepartidos(ifstream& input,int *arrCodigoPlato,
                            double *arrPrecioPlato,double *arrDescuentoPlato,int cantPlatos,
                            double descuentoReparto,double porcPagoRep,
                            int &arrTotalCantPlatosRep,double &arrMontoTotalPlatos,
                            double &arrDescuentoPorPlatos,double &arrDescuentoPorClientes,
                            double &arrPagoAlRepartidor,int *arrTotalCantPlatos,
                            double *arrMontoVendido,double *arrDescuentoAlPlato,
                            double *arrDescuentoAlCliente);

void ordenarPlatos(int *arrCodigoPlato,char **arrNombrePlato,
                double *arrPrecioPlato,char **arrCategoriaPlato,
                double *arrDescuentoPlato,int cantPlatos,
                int *arrTotalCantPlatos,double *arrMontoVendido,
                double *arrDescuentoAlPlato,double *arrDescuentoAlCliente,
                double *arrTotalIngresadoPlatos);

void generarReportePorRepartidores(const char* nombArchRep,
                                int *arrDniRepartidor,char **arrNombreRepartidor,char **arrTipoVehiculo,
                                char **arrNombreDistrito,int *arrTotalCantPlatosRep,double *arrMontoTotalPlatos,
                                double *arrDescuentoPorPlatos,double *arrDescuentoPorClientes,double *arrPagoAlRepartidor,
                                double *arrTotalIngresadoRep,int cantRepartidores);

void generarReportePorPlatos(const char* nombArchRep,
                            int *arrCodigoPlato,char **arrNombrePlato,char **arrCategoriaPlato,
                            double *arrPrecioPlato,double *arrDescuentoPlato,int *arrTotalCantPlatos,
                            double *arrMontoVendido,double *arrDescuentoAlPlato,double *arrDescuentoAlCliente,
                            double *arrTotalIngresadoPlatos,int cantPlatos);

void imprimirResumenRep(ofstream& output,int cantTotalPlatos,double montoTotalPlatos,double totalDescuentoPorPlatos,
                    double totalDescuentoPorClientes,double totalPagoRep,double totalGlobalIngresado);

void imprimirResumenPlato(ofstream& output,int totalCantidad,double totalMontoVendido,double totalDescuentoAlPlato,
                        double totalDescuentoAlCliente,double totalGlobalIngresado);

//auxiliares
void imprimirCabeceraReporteRep(ofstream &output);
void imprimirCabeceraReportePlatos(ofstream &output);
int buscarPlato(int codigoPlato,int *arrCodigoPlato,int cantPlatos);
double calcularPagoRep(char *vehiculoRep);
void ignorar(ifstream&input,char delimitador);
int buscarRepartidor(int *arrCodigoDistrito,char **arrTipoVehiculo,
                    int codigoDistrito,char *vehiculoRep,int cantRepartidores); //IMPORTANTE
void swapInt(int& a,int &b);
void swapDouble(double&a,double&b);
void swapString(char*&a,char*&b);
void imprimirSubRepPruebaRep(ofstream &output);
void imprimirSubRepPruebaPlatos(ofstream &output);
void modificarCadena(char *cadena,bool nombreRep,bool tipoVeh,bool distrito);//IMPORTANTE
void formato3(char *cadena);//IMPORTANTE
void formato2(char *cadena);//IMPORTANTE
void formato1(char * cadena);//IMPORTANTE
char *leerString(ifstream& input); //IMPORTANTE
void imprimirLineas(char c,int cant,ofstream&output);


#endif //LAB07_24_2_FUNCIONESAUXILIARES_H
