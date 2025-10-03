//
// Created by ASUS on 14/09/2025.
//

#include "FuncionesAuxiliares.h"

void procesarReporte(const char* nomArchIn,const char* nomArchOut) {
    ifstream archCitas(nomArchIn,ios::in);
    if (not archCitas.is_open()) {
        cout<<"Error al abrir el archivo"<<endl;
        exit(1);
    }
    ofstream archRep(nomArchOut,ios::out);

    imprimirCabeceraReporte(archRep);
    imprimirSubtitulo(archRep);

    int cantCitasRegistradas=0;
    int cantCitasProcesadas=0;
    double pagoTotalAcumulado=0.0;
    while (true) {
        leerImprimirDatosCitas(archRep,archCitas,cantCitasRegistradas,
                        cantCitasProcesadas,pagoTotalAcumulado);
        if (archCitas.eof()) break;
    }
    imprimirLineas('=',120,archRep);
    archRep<<"Total de ingresos: "<<setw(2)<<" "<<pagoTotalAcumulado<<endl;
    imprimirLineas('=',120,archRep);
    imprimirReporteFinal(archRep,cantCitasRegistradas,cantCitasProcesadas);
    imprimirLineas('=',120,archRep);
}

void imprimirCabeceraReporte(ofstream &archRep) {
    archRep<<setw(50)<<" "<<"EMPRESA DE SALUD S.A"<<endl;
    imprimirLineas('=',120,archRep);
    archRep<<setw(10)<<" "<<"REGISTRO DE CITAS DE LAS CONSULTAS MEDICAS EN PEDIATRIA"<<endl;
    archRep<<setw(10)<<" "<<"ENTRE 1 HORA CON 15 MINUTOS Y 30 SEGUNDOS Y 2 HORAS 30 MINUTOS Y"
             <<" 25 SEGUNDOS DE DURACION"<<endl;
    imprimirLineas('=',120,archRep);
}

void imprimirLineas(char c,int cant,ofstream &archRep) {
    for (int i=0;i<cant;i++) archRep<<c;
    archRep<<endl;
}

void imprimirSubtitulo(ofstream &archRep) {
    archRep<<setw(13)<<left<<"Fecha"<<setw(13)<<left<<"Paciente"<<
    setw(12)<<left<<"Inicio"<<setw(8)<<left<<"Fin"<<
    setw(17)<<left<<"Duracion(H:M:S)"<<setw(14)<<left<<"Duracion(H)"<<
    setw(15)<<left<<"% por Seguro"<<setw(20)<<left<<"Pago (cita+medicinas)"<<endl;
    imprimirLineas('-',120,archRep);
}

void leerImprimirDatosCitas(ofstream &archRep,ifstream &archCitas,
                            int &cantCitasRegistradas,int &cantCitasProcesadas,
                            double &pagoTotalAcumulado) {
    int dia,mes,año,dniPaciente,horaIni,minIni,segIni,horaFin,minFin,segFin,
    rangoInicial,rangoFinal,rango,hora,minuto,segundo;
    double porcSeguro,tarifaMedico,duracionHoras,montoMed,pagoTotal;
    char c,espMedico,recetaronMedicina;

    archCitas>>dia;
    if (archCitas.eof()) return;

    archCitas>>c>>mes>>c>>año>>dniPaciente>>porcSeguro>>
    horaIni>>c>>minIni>>c>>segIni>>horaFin>>c>>minFin>>c>>segFin;

    rangoInicial=convertirHHMMSS_Seg(1,15,30);
    rango=convertirHHMMSS_Seg(horaFin,minFin,segFin) - convertirHHMMSS_Seg(horaIni,minIni,segIni);
    rangoFinal=convertirHHMMSS_Seg(2,30,25);

    if (rango>=rangoInicial and rango<=rangoFinal) {
        archCitas>>tarifaMedico;
        archCitas>>ws;
        archCitas>>espMedico;
        archCitas>>ws;
        archCitas>>recetaronMedicina;
        imprimirFecha(dia,mes,año,archRep);
        archRep<<setw(3)<<" "<<setw(12)<<left<<dniPaciente;
        imprimirHora(horaIni,minIni,segIni,archRep);
        archRep<<setw(3)<<" ";
        imprimirHora(horaFin,minFin,segFin,archRep);
        archRep<<setw(5)<<" ";
        convertirSeg_HHMMSS(rango,hora,minuto,segundo);
        imprimirHora(hora,minuto,segundo,archRep);
        archRep<<setw(8)<<" ";
        duracionHoras=convertirHHMMSS_Horas(hora,minuto,segundo);
        archRep<<fixed;
        archRep.precision(4);
        archRep<<setw(15)<<left<<duracionHoras;
        archRep.unsetf(ios::fixed); //para quitar el fixed
        archRep<<fixed;
        archRep.precision(2);
        archRep<<setw(5)<<right<<porcSeguro<<"%";
        if (recetaronMedicina=='S') {
            archCitas>>montoMed;
        }else {
            montoMed=0.0;
        }
        pagoTotal=procesarPagoMedico(montoMed,porcSeguro,tarifaMedico,duracionHoras);
        archRep<<setw(20)<<right<<pagoTotal;
        pagoTotalAcumulado+=pagoTotal;
        archRep<<endl;
        cantCitasProcesadas++;
    }
    cantCitasRegistradas++;
    while (archCitas.get()!='\n');
}

double procesarPagoMedico(double montoMed,double porcSeguro,
                        double tarifaMedico,double duracionHoras ) {
    double montoConsulta=tarifaMedico*duracionHoras;
    double montoConsultaDesc=montoConsulta*(porcSeguro/100.0);
    double nuevoDescSeg=porcSeguro/2.0;
    double montoMedicinas=montoMed*(nuevoDescSeg/100.0);
    return montoConsultaDesc+montoMedicinas;
}

double convertirHHMMSS_Horas(int hora,int minuto,int seg) {
    return hora+minuto/60.0+seg/3600.0;
}

void imprimirFecha(int dia,int mes,int año,ofstream &archRep) {
    archRep.fill('0');
    archRep<<setw(2)<<right<<dia<<"/"<<setw(2)<<right<<mes<<"/"<<
    setw(4)<<año;
    archRep.fill(' ');
}

void imprimirHora(int hora,int minuto,int segundo,ofstream &archRep) {
    archRep.fill('0');
    archRep<<setw(2)<<right<<hora<<":"<<setw(2)<<right<<minuto<<":"<<
    setw(2)<<right<<segundo;
    archRep.fill(' ');
}

int convertirHHMMSS_Seg(int hora,int min,int seg) {
    return hora*3600+min*60+seg;
}

void convertirSeg_HHMMSS(int numero,int &hora,int &minuto,int &segundo) {
    hora=numero/3600;
    numero=numero%3600;
    minuto=numero/60;
    numero=numero%60;
    segundo=numero;

}

void imprimirReporteFinal(ofstream &archRep,int cantCitasReg,
                        int cantCitasProcesadas) {
    double porcRegistrosProcesados=((double)cantCitasProcesadas/(double)cantCitasReg)*100;
    archRep<<"ESTADISTICAS OBTENIDAS:"<<endl;
    archRep<<"Cantidad de registros del archivo:"<<setw(5)<<" "<<cantCitasReg<<endl;
    archRep<<"Cantidad de registros procesados:"<<setw(6)<<" "<<cantCitasProcesadas<<endl;
    archRep<<"ESTADISTICAS OBTENIDAS:"<<setw(17)<<" "<<porcRegistrosProcesados<<"%"<<endl;

}
