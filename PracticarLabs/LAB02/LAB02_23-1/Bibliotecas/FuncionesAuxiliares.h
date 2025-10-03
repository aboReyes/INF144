//
// Created by DIEGO on 24/08/2025.
//

#ifndef LAB02_23_1_FUNCIONESAUXILIARES_H
#define LAB02_23_1_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
using namespace std;

void crearReporte();
void imprimirLineas(int cant, char c);
void ImprimirCabeceraReporte(int diaLimDoc,int mesLimDoc,int anioLimDoc,int diaLimEst,int mesLimEst,int anioLimEst);
void LeerInfoUsuario_ImpReporte(int dia,int mes, int anio,int carne,char tipoUsuario,int &dniUsuarioMayorDeuda,double &mayorDeuda,int &dniUsuarioMasLibros,double &mayorCantLibrosUsuario);
void procesarLibro(int codLibro,int diaRet,int mesRet,int anioRet,int dia,int mes,int anio,double precioLibro,double porcMulta,int &cantLibrosConDeuda,double &totalMultas);
void imprimirResumen(int dniEstMayorDeuda,int dniEstMasLibros,double mayorDeudaEst,int mayorCantLibrosEst,int  dniDocMayorDeuda,int dniDocMasLibros,double mayorDeudaDoc,int mayorCantLibrosDoc);


#endif //LAB02_23_1_FUNCIONESAUXILIARES_H
