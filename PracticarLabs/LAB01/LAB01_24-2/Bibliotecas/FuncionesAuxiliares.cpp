//
// Created by DIEGO on 29/08/2025.
//
#define PI 3.14159265358979323846
#include <cmath>
#include "FuncionesAuxiliares.h"

void crearReporte() {
    int dia,mes,anio;
    char c;
    int dniRepMayRec=0,dniRepMenRec=0;
    double distRepMayRec=0,distRepMenRec=0;
    int esPrimero=1;


    cin>>dia>>c>>mes>>c>>anio;
    imprimirCabeceraReporte(dia,mes,anio);
    while (true) {
        leerRepartidor_ImpReporte(dniRepMayRec,distRepMayRec,
                                  dniRepMenRec,distRepMenRec,
                                  esPrimero);
        if (cin.eof()) break;
    }
    imprimirReporte(dniRepMayRec,distRepMayRec,dniRepMenRec,distRepMenRec);
}

void imprimirReporte(int dniRepMayRec,double distRepMayRec, int dniRepMenRec,double distRepMenRec) {
    imprimirLineas('/',140);
    cout<<"REPARTIDOR CON MAYOR RECORRIDO: "<<endl;
    cout<<"DNI: "<<dniRepMayRec<<endl;
    cout<<"DISTANCIA: "<<distRepMayRec<<" km."<<endl;

    cout<<"REPARTIDOR CON MENOR RECORRIDO: "<<endl;
    cout<<"DNI: "<<dniRepMenRec<<endl;
    cout<<"DISTANCIA: "<<distRepMenRec<<" km."<<endl;
}

void actualizarResumen(int dni, double recorrido,
                       int &dniMax, double &distMax,
                       int &dniMin, double &distMin,
                       int &esPrimero) {
    if (esPrimero) {
        dniMax=dniMin=dni;
        distMax=distMin=recorrido;
        esPrimero=0;
        return;
    }
    if (recorrido>distMax) {
        distMax=recorrido;
        dniMax=dni;
    }
    if (recorrido<distMin) {
        distMin=recorrido;
        dniMin=dni;
    }
}

void imprimirLineas(char c,int cant) {
    int i;
    for (i=0;i<cant;i++) {
        cout<<c;
    }
    cout<<endl;
}

void imprimirCabeceraReporte(int dia,int mes,int anio) {
    cout<<setw(50)<<" "<<"EMPRESA DE REPARTOS A DOMICILIO TP S. A."<<endl;
    cout<<setw(54)<<" "<<"FECHA DE LOS REPARTOS: ";
    cout.fill('0');
    cout<<setw(2)<<dia<<"/"<<setw(2)<<mes<<"/"<<anio<<endl;
    cout.fill(' ');
    imprimirLineas('=',140);
}

void leerRepartidor_ImpReporte(int &dniRepMayRec,double &distRepMayRec,
                               int &dniRepMenRec,double &distRepMenRec,
                               int &esPrimero) {
    int dni;
    cin>>dni;
    if (cin.eof()) return; //return solo, significa que el modulo termino
    leerNombre_ImpRep(dni);
    double recorridoTotal=leerRuta_ImpRep();
    //while (cin.get()!='\n'); //artificio que te permite eliminar datos que no vas a usar
    actualizarResumen(dni,recorridoTotal,dniRepMayRec,distRepMayRec,dniRepMenRec,distRepMenRec,esPrimero);
}

void leerNombre_ImpRep(int dni) {
    cin>>ws; //sirve cuando tienes que leer nombre, ya que hay espacios en blanco que se toman como char antes de leer el nombre
    cout<<"Repartidor: "<<endl;
    cout<<"Nombre: "<<" ";
    int cant=0;
    char c;
    while (true) {
        c=cin.get();
        if (c==' ') break;
        cout<<c;
        cant++;
    }
    cout<<setw(50-cant)<<" "<<"DNI: "<<dni<<endl;
    imprimirLineas('-',140);
}

double leerRuta_ImpRep() {
    int horaInc,minutoInc,segundoInc;
    char c;
    cin>>horaInc>>c>>minutoInc>>c>>segundoInc;

    double velocidadProm;
    int horaFin,minutoFin,segundoFin;
    int grados,minutos,segundos;

    double xIni=0,yIni=0;
    double distanciaAcumulada=0;
    double pagoTotal=0;

    cout<<"DATOS DE LA RUTA: "<<endl;
    cout<<setw(18)<<right<<"HORA INI "<<"HORA FIN "<<"VELOCIDAD "<<"DISTANCIA "<<"PUNTO DE PARTIDA (X,Y) "<<"PUNTO DE LLEGADA(X,Y) "<<"DISTANCIA ACUMULADA";
    cout<<setw(15)<<right<<"PAGO POR ENVIO"<<endl;
    for (int i=1;i<=3;i++) {
        cin>>velocidadProm>>horaFin>>c>>minutoFin>>c>>segundoFin>>grados>>c>>minutos>>c>>segundos>>c;
        double pago=imprimirTramo(i,horaInc,minutoInc,segundoInc,velocidadProm,
                                horaFin,minutoFin,segundoFin,grados,minutos,segundos,
                                xIni,yIni,distanciaAcumulada);
        pagoTotal+=pago;
    //hice cambio
        horaInc = horaFin;
        minutoInc = minutoFin;
        segundoInc = segundoFin;
    }
    imprimirRetorno(horaFin,minutoFin,segundoFin,velocidadProm,xIni,yIni,distanciaAcumulada);
    imprimirLineas('-',140);
    cout<<fixed;
    cout.precision(2);
    cout<<"PAGO TOTAL AL REPARTIDOR: "<<setw(5)<<right<<pagoTotal<<endl;
    imprimirLineas('=',140);

    return distanciaAcumulada;
}

double imprimirTramo(int i,int horaInc,int minutoInc,int segundoInc,double velocidadProm,
                   int horaFin,int minutoFin,int segundoFin,int grados,int minutos,int segundos,double &xIni,double &yIni,double &distanciaAcumulada) {
    cout<<"Tramo "<<i<<": ";

    cout.fill('0');
    cout<<setw(2)<<right<<horaInc<<":"<<setw(2)<<minutoInc<<":"<<setw(2)<<segundoInc;
    cout.fill(' ');

    cout<<setw(4)<<" ";

    cout.fill('0');
    cout<<setw(2)<<right<<horaFin<<":"<<setw(2)<<minutoFin<<":"<<setw(2)<<segundoFin;
    cout.fill(' ');

    cout<<fixed;
    cout.precision(2);
    cout<<setw(8)<<right<<velocidadProm;

    double distancia=calcularDistancia(horaInc,minutoInc,segundoInc,horaFin,minutoFin,segundoFin,velocidadProm);
    double pago=calcularPago(distancia);
    distanciaAcumulada+=distancia;
    cout<<setw(8)<<right<<distancia;
    double xFin,yFin;
    calcularCoordenadaLlegada(xIni,yIni,grados,minutos,segundos,distancia,xFin,yFin);
    cout<<setw(10)<<xIni<<" - "<<setw(6)<<yIni<<setw(12)<<xFin<<" - "<<setw(6)<<yFin;
    cout<<setw(18)<<right<<distanciaAcumulada<<setw(16)<<right<<pago<<endl;;
    xIni=xFin;
    yIni=yFin;

    return pago;
}

double calcularDistancia(int horaInc,int minutoInc,int segundoInc,int horaFin,int minutoFin,int segundoFin,double velocidadProm) {
    double distancia;
    double horasDemora = (horaFin+minutoFin/60.0+segundoFin/3600.0) - (horaInc+minutoInc/60.0+segundoInc/3600.0);
    distancia=horasDemora*velocidadProm;
    return distancia;
}

void calcularCoordenadaLlegada(double xIni,double yIni,int grados,int minutos,int segundos,double distancia,double &xFin,double &yFin) {
    double anguloSexa= grados+minutos/60.0+segundos/3600.0;
    double anguloRad= anguloSexa*(PI/180.0);
    xFin=xIni+distancia*cos(anguloRad); //hize cambio
    yFin=yIni+distancia*sin(anguloRad);
}

double calcularPago(double distancia) {
    if (distancia<=10.5)return 8.5;
    else if (distancia<=20.5)return 17.75;
    else if (distancia<=35.5)return 29.85;
    else return 45.69;
}

void imprimirRetorno(int horaFin,int minutoFin,int segundoFin,double velocidadProm,
                    double xIni,double yIni,double &distanciaAcumulada) {
    cout<<"Retorno: ";

    cout.fill('0');
    cout<<setw(2)<<right<<horaFin<<":"<<setw(2)<<minutoFin<<":"<<setw(2)<<segundoFin;
    cout.fill(' ');

    cout<<setw(4)<<" ";

    double distancia=sqrt(pow(xIni-0,2)+pow(yIni-0,2));

    double tiempo= distancia/velocidadProm;
    int horaTermino,minutoTermino,segundoTermino;

    calcularHoraTermino(tiempo,horaTermino,minutoTermino,segundoTermino,horaFin,minutoFin,segundoFin);

    cout.fill('0');
    cout<<setw(2)<<right<<horaTermino<<":"<<setw(2)<<minutoTermino<<":"<<setw(2)<<segundoTermino;
    cout.fill(' ');

    cout<<fixed;
    cout.precision(2);
    cout<<setw(8)<<right<<velocidadProm;

    distanciaAcumulada+=distancia;
    cout<<setw(8)<<right<<distancia;

    double xFin=0,yFin=0;
    cout<<setw(10)<<xIni<<" - "<<setw(6)<<yIni<<setw(12)<<xFin<<" - "<<setw(6)<<yFin;
    cout<<setw(18)<<right<<distanciaAcumulada<<endl;
}

void calcularHoraTermino(double tiempo,int &horaTermino,int &minutoTermino,int &segundoTermino,
                         int horaFin,int minutoFin,int segundoFin){

    horaTermino=horaFin;
    minutoTermino=minutoFin;
    segundoTermino=segundoFin;

    int tiempoSeg= int(tiempo*3600);

    int horas=tiempoSeg/3600;
    tiempoSeg=tiempoSeg%3600;

    int minutos=tiempoSeg/60;
    int segundos=tiempoSeg%60;

    segundoTermino=segundoTermino+segundos;
    if (segundoTermino>=60) {
        segundoTermino=segundoTermino-60;
        minutoTermino++;
    }
    minutoTermino=minutoTermino+minutos;
    if (minutoTermino>=60) {
        minutoTermino=minutoTermino-60;
        horaTermino++;
    }
    horaTermino+=horas;
}
