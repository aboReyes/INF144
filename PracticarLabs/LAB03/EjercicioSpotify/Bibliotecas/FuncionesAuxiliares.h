//
// Created by ASUS on 6/09/2025.
//

#ifndef SPOTIFY_FUNCIONESAUXILIARES_H
#define SPOTIFY_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
using namespace std;

void crearReporte();
void imprimirCabeceraReporte();
void imprimirLineas(char c,int cant);
void leerImprimirDatosUsuario(int &cantUsuario,int &mayorNumUsuario,
                            int &diaMay,int &mesMayor,int &añoMayor);
void leerImprimirCodeUsuario();
void leerImprimirNombreUsuario();
void leerImprimirFollowers();
void imprimirFecha(int dia,int mes,int año);
int procesarReproduccionesUsuario(int &horaTotalRepro,int &minutoTotalRepro,int &segundoTotalRepro,
                                    int &totalRepro);
void imprimirSubtituloReproducciones();
void imprimirFecha(int dia,int mes,int año);
void imprimirHoraReproducciones(int hora,int minuto,int segundo);
void imprimirResumenPorUsuario(int horaTotalRepro,int minutoTotalRepro,int segundoTotalRepro,
                            int totalReproducciones);
int transformarHHMMSS_Numero(int hora,int minuto,int segundo);
void transformarNumero_HHMMSS(int numero,int &hora,int &minuto,int &segundo) ;
void imprimirResumenTotalUsuarios(int cantUsuariosFinal,
                            int horaUsuarioMay,int minUsuarioMay,int segUsuarioMay,
                            int diaUsuarioMay,int mesUsuarioMay,int añoUsuarioMay);
void elegirUsuarioMayorHoraReproducciones(int horatotalReproUsuario,
                                            int dia,int mes,int año,int &mayNumRepro
                                            ,int &diaMay,int &mesMay,int &añoMay);

#endif //SPOTIFY_FUNCIONESAUXILIARES_H
