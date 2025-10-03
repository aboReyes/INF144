//
// Created by ASUS on 3/09/2025.
//

#include "FuncionesAuxiliares.h"

void leerFecha_MostrarTitulo(int &diaIni,int &mesIni,int &añoIni,int &diaFin,int &mesFin,int &añoFin) {
    //28/01/2024    25/02/2025
    leerFecha(diaIni,mesIni,añoIni);
    leerFecha(diaFin,mesFin,añoFin);
    cout<<setw(60)<<" "<<"MINISTERIO DE TRANSPORTE"<<endl;
    cout<<setw(55)<<" "<<"MULTAS IMPUESTAS A LAS COMPAÑIAS"<<endl;

    cout<<setw(45)<<" "<<"RANGO DE FECHAS A CONSIDERAR: DEL ";
    cout.fill('0');
    cout<<setw(2)<<diaIni<<"/"<<setw(2)<<mesIni<<"/"<<setw(4)<<añoIni<<" AL "
    <<setw(2)<<diaFin<<"/"<<setw(2)<<mesFin<<"/"<<setw(4)<<añoFin<<endl;
    cout.fill(' ');
    imprimirLineas('=',130);
}
void leerFecha(int &diaIni,int &mesIni,int &añoIni) {
    char c;
    cin>>diaIni>>c>>mesIni>>c>>añoIni;
}

void imprimirLineas(char c, int cant) {
    for (int i = 0; i < cant; i++) cout << c;
    cout<<endl;
}

void leerImprimirReporteCompañia(int diaIni,int mesIni,int añoIni,
                                int diaFin,int mesFin,int añoFin) {
    int nroCompañia=1,dni;
    double totalCompañia;
    while (true) {
        cin>>dni;
        if (cin.eof()) break;
        cout<<"COMPAÑIA No. "<<nroCompañia<<endl;
        cout<<"REPRESENTANTE LEGAL: ";
        leerRepresentanteLegal();
        cout<<"DNI: "<<dni<<endl;
        imprimirLineas('-',130);
        imprimirSubtitulo(); //modulo para solo imprimir TIPO PLACA FECHA...
        procesarInfraccionVehiculo(diaIni,mesIni,añoIni,
                                diaFin,mesFin,añoFin,totalCompañia);
        cout<<"PAGO TOTAL : "<<totalCompañia<<endl;
        imprimirLineas('=',130);
        //while (cin.get() != '\n');
        nroCompañia++;
    }
}

void leerRepresentanteLegal() {
    //Contreras/Chang/Johana-Cinthia
    char c;
    int cant=1;
    cin>>ws;
    while (true) {
        c=cin.get();
        if (c==' ') break;
        if (c=='/' or c=='-') c=' ';
        if (c>='a' and c<='z') c-='a' - 'A';
        cout<<c;
        cant++;
    }
    cout<<setw(50-cant)<<" ";
}

void imprimirSubtitulo() {
    cout<<"VEHICULOS INFRACCIONADOS: "<<endl;
    cout<<setw(78)<<" "<<"INCREMENTOS"<<endl;
    cout<<setw(3)<<" "<<setw(10)<<left<<"TIPO"
        <<setw(10)<<left<<"PLACA"<<setw(13)<<left<<"FECHA"
        <<setw(10)<<left<<"HORA"<<setw(13)<<left<<"GRAVEDAD"
        <<setw(12)<<left<<"MULTA"<<setw(12)<<left<<"POR TIPO"
        <<setw(12)<<left<<"POR FECHA"<<setw(12)<<left<<"POR HORA"<<"TOTAL A PAGAR"<<endl;
}

void leerImprimirTipoVehiculos(char tipoVehiculo) {
    if (tipoVehiculo=='P') cout<<"PEQUEÑO ";
    else if (tipoVehiculo=='M') cout<<"MEDIANO ";
    else cout<<"GRANDE  ";
}

void procesarInfraccionVehiculo(int diaIni,int mesIni,int añoIni,
                                int diaFin,int mesFin,int añoFin,
                                double &multaTotalCom) {
    //P599-629    12/12/2023  10:42:26      L
    char tipoVehiculo,c,gravedad;
    int placa1,placa2,dia,mes,año,hora,minuto,segundo,rangoInicial,rangoFinal,
    fechaRepresentante,horaMañana,horaTarde,horaNoche,horaRepresentante;
    double multa,multaTipo,multaFecha,multaHora,multaTotal;
    while (true) {
        cin>>tipoVehiculo>>placa1>>c>>placa2>>dia>>c>>mes>>c>>año>>hora>>c
        >>minuto>>c>>segundo>>gravedad;
        cout<<"-  ";
        leerImprimirTipoVehiculos(tipoVehiculo);
        //PLACA
        cout<<setw(1)<<" "<<tipoVehiculo<<placa1<<placa2<<setw(3)<<" ";

        //FECHA
        cout.fill('0');
        cout<<setw(2)<<right<<
            dia<<"/"<<setw(2)<<right<<mes<<"/"<<setw(4)<<año;
        cout.fill(' ');

        //HORA
        cout<<setw(3)<<" ";
        cout.fill('0');
        cout<<setw(2)<<right<<hora<<":"<<setw(2)<<right<<minuto<<":"
            <<setw(2)<<right<<segundo;
        cout.fill(' ');

        //GRAVEDAD
        cout<<setw(3)<<" ";
        imprimirGravedad(gravedad);

        //MULTA
        multa=retornarMulta(gravedad);
        cout<<setw(10)<<right<<multa;

        //MULTA POR TIPO
        multaTipo=retornarMultaPorTipo(tipoVehiculo,multa);
        cout<<setw(12)<<right<<multaTipo;

        //MULTA POR FECHA
        rangoInicial=transformarDDMMAA_Numero(diaIni,mesIni,añoIni);
        fechaRepresentante=transformarDDMMAA_Numero(dia,mes,año);
        rangoFinal=transformarDDMMAA_Numero(diaFin,mesFin,añoFin);
        multaFecha=retornarMultaPorFecha(multa,rangoInicial,rangoFinal,
                                    fechaRepresentante);
        cout<<setw(13)<<right<<multaFecha;

        //MULTA POR HORA
        horaMañana=transformarHHMMSS_segundos(4,30,0);
        horaTarde=transformarHHMMSS_segundos(11,25,0);
        horaNoche=transformarHHMMSS_segundos(20,40,0);
        horaRepresentante=transformarHHMMSS_segundos(hora,minuto,segundo);
        multaHora=retornarMultaPorHora(multa,horaMañana,horaTarde,horaNoche,horaRepresentante);
        cout<<setw(13)<<right<<multaHora;

        //TOTAL A PAGAR:
        multaTotal=multa+multaTipo+multaFecha+multaHora;
        cout<<setw(13)<<right<<multaTotal<<endl;
        multaTotalCom+=multaTotal;
        if (cin.get()=='\n') break;
    }
    imprimirLineas('-',130);
}

void imprimirGravedad(char gravedad) {
    if (gravedad=='L') cout<<"LEVE     ";
    else if (gravedad=='G') cout<<"GRAVE    ";
    else cout<<"MUY GRAVE";
}

double retornarMulta(char gravedad) {
    if (gravedad=='L') return 158.33;
    else if (gravedad=='G') return 516.75;
    else return 3920.25;
}

double retornarMultaPorTipo(char tipoVehiculo,double multa) {
    if (tipoVehiculo=='P') return multa*0.027;
    else if (tipoVehiculo=='M') return multa*0.117;
    else return multa*0.153;
}

int transformarDDMMAA_Numero(int dia,int mes,int año) {
    return año*10000+mes*100+dia;
}

double retornarMultaPorFecha(double multa,int fechaIni,int fechaFin,int fecha) {
    if (fechaIni<=fecha and fecha<=fechaFin) return multa*0.0725;
    else if (fecha<=fechaIni) return multa*0.1075;
    else return multa*0.0;
}

int transformarHHMMSS_segundos(int hora,int min,int seg) {
    return hora*3600+min*60+seg;
}

double retornarMultaPorHora(double multa,int horaMañana,int horaTarde,int horaNoche,
                            int hora) {
    if (horaMañana>=hora and hora<=horaTarde) return multa*0.085;
    else if (horaTarde>=hora and hora<=horaNoche) return multa*0.058;
    else return multa*0.037;
}
