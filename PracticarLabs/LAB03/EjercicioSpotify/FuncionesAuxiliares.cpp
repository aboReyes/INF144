//
// Created by ASUS on 6/09/2025.
//

#include "FuncionesAuxiliares.h"

void crearReporte() {
    int cantUsuario=1;
    int maxNumero=0; //despues lo transformare a formato HHMMSS
    int diaMayor=0,mesMayor=0,añoMayor=0;
    int horaMayor=0,minMayor=0,segundoMayor=0;
    imprimirCabeceraReporte();
    while (true) {
        leerImprimirDatosUsuario(cantUsuario,maxNumero,
                                diaMayor,mesMayor,añoMayor);
        if (cin.eof()) break;
    }
    transformarNumero_HHMMSS(maxNumero,horaMayor,minMayor,segundoMayor);
    int cantUsuariosFinal=cantUsuario-1;
    imprimirResumenTotalUsuarios(cantUsuariosFinal,
                                horaMayor,minMayor,segundoMayor,
                                diaMayor,mesMayor,añoMayor);
}

void imprimirLineas(char c,int cant) {
    for(int i=0;i<cant;i++) cout << c;
    cout << endl;
}

void imprimirCabeceraReporte() {
    imprimirLineas('*',130);
    cout<<setw(50)<<" "<<"SPOTIFY PLATFORM"<<endl;
    cout<<setw(35)<<" "<<"REPORT FOR DATES BETWEEN: 01/01/2000 AND "
                         "31/12/2010"<<endl;
    imprimirLineas('=',130);
}

void leerImprimirDatosUsuario(int &cantUsuario,int &mayorNumUsuario,
                            int &diaMay,int &mesMayor,int &añoMayor) {
    int diaCreacion,mesCreacion,añoCreacion,horaTotalRepro=0,minutoTotalRepro=0,segundoTotalRepro=0,
    totalReproducciones=0;
    char c;
    cin>>diaCreacion>>c>>mesCreacion>>c>>añoCreacion;
    if (cin.eof()) return;
    cout<<setw(15)<<left<<"CODE"<<"USERNAME ";
    cout.fill('0');
    cout<<setw(2)<<right<<cantUsuario;
    cout.fill(' ');
    cout<<setw(8)<<" "<<setw(18)<<left<<"#FOLLOWERS"<<setw(18)<<left<<"CREATED AT"<<endl;
    leerImprimirCodeUsuario();
    leerImprimirNombreUsuario();
    leerImprimirFollowers();
    imprimirFecha(diaCreacion,mesCreacion,añoCreacion);
    cout<<endl;
    imprimirLineas('-',130);
    imprimirSubtituloReproducciones();
    int totalSegUsuario=procesarReproduccionesUsuario(horaTotalRepro,minutoTotalRepro,segundoTotalRepro ,
                    totalReproducciones);
    elegirUsuarioMayorHoraReproducciones(totalSegUsuario,
                                        diaCreacion,mesCreacion,añoCreacion,
                                        mayorNumUsuario,diaMay,mesMayor,añoMayor);
    imprimirLineas('-',130);
    cantUsuario++;
    //while (cin.get() != '\n'); //me sirvió al empezar el laboratorio, para leer modulo por modulo
}

void leerImprimirCodeUsuario() {
    int codigoUsuario;
    char code;
    cin>>ws;
    cin>>code>>codigoUsuario;
    cout.fill('0');
    cout<<code<<setw(4)<<right<<codigoUsuario;
    cout.fill(' ');
    cout<<setw(10)<<" ";
}

void leerImprimirNombreUsuario() {
    int cantBlancos=0;
    char c;
    cin>>ws;
    while (true) {
        c=cin.get();
        if (c==' ') break;
        if (c>='a' and c<='z') c-='a'-'A'; //sirve para las mayusculas usando ASCI
        cout<<c;
        cantBlancos++;
    }
    cout<<setw(19-cantBlancos)<<" ";
}

void leerImprimirFollowers() {
    int numeroFollowers;
    cin>>numeroFollowers;
    cout<<setw(18)<<left<<numeroFollowers;
}

void imprimirFecha(int dia,int mes,int año) {
    cout.fill('0');
    cout<<setw(2)<<right<<dia<<"/"<<setw(2)<<right<<mes<<"/"
    <<setw(4)<<right<<año;
    cout.fill(' ');
}

int procesarReproduccionesUsuario(int &horaTotalRepro,int &minutoTotalRepro,int &segundoTotalRepro,
                                    int &totalRepro) {
    //02/02/2021   05:17:39   9
    int diaRepro,mesRepro,añoRepro,horaRepro,minutoRepro,segundoRepro,numRepro;
    int horaReproducida,totalHorasRepro=0,mayorHoraReproducida=0;
    char c;
    totalRepro=0;
    while (true) {
        cin>>diaRepro>>c>>mesRepro>>c>>añoRepro
        >>horaRepro>>c>>minutoRepro>>c>>segundoRepro>>numRepro;
        cout<<setw(15)<<" ";
        imprimirFecha(diaRepro,mesRepro,añoRepro);
        cout<<setw(9)<<" ";
        imprimirHoraReproducciones(horaRepro,minutoRepro,segundoRepro);
        horaReproducida=transformarHHMMSS_Numero(horaRepro,minutoRepro,segundoRepro);
        totalHorasRepro+=horaReproducida;
        cout<<setw(15)<<right<<numRepro;
        totalRepro+=numRepro;
        cout<<endl;
        if (cin.get()=='\n') break;
    }
    imprimirLineas('-',130);
    transformarNumero_HHMMSS(totalHorasRepro,horaTotalRepro,minutoTotalRepro,segundoTotalRepro);
    imprimirResumenPorUsuario(horaTotalRepro,minutoTotalRepro,segundoTotalRepro,totalRepro);
    return totalHorasRepro;
}

void imprimirSubtituloReproducciones() {
    cout<<"MOST RECENT PLAYS:"<<endl;
    cout<<setw(15)<<" "<<setw(19)<<left<<"DATE"
    <<setw(19)<<left<<"TIME"<<setw(15)<<left<<"#PLAYS"<<endl;
}

void imprimirHoraReproducciones(int hora,int minuto,int segundo) {
    cout.fill('0');
    cout<<setw(2)<<right<<hora<<":"<<setw(2)<<right<<minuto<<":"
    <<setw(2)<<right<<segundo;
    cout.fill(' ');
}

void imprimirResumenPorUsuario(int horaTotalRepro,int minutoTotalRepro,int segundoTotalRepro,
                            int totalReproducciones) {
    cout<<"Stats per User: "<<endl;
    cout<<"Total Time Played: "<<setw(20)<<" ";
    cout.fill('0');
    cout<<setw(2)<<right<<horaTotalRepro<<":"<<setw(2)<<right<<minutoTotalRepro<<":"
    <<setw(2)<<right<<segundoTotalRepro<<endl;
    cout.fill(' ');
    cout<<"Total Records played: "<<setw(20)<<" "<<totalReproducciones<<endl;
}

int transformarHHMMSS_Numero(int hora,int minuto,int segundo) {
    return hora*3600+minuto*60+segundo;
}

void transformarNumero_HHMMSS(int numero,int &hora,int &minuto,int &segundo) {
    hora= numero/3600;
    numero = numero%3600;
    minuto = numero/60;
    numero = numero%60;
    segundo = numero;
}

void imprimirResumenTotalUsuarios(int cantUsuariosFinal,
                            int horaUsuarioMay,int minUsuarioMay,int segUsuarioMay,
                            int diaUsuarioMay,int mesUsuarioMay,int añoUsuarioMay) {
    imprimirLineas('=',130);
    cout<<"Final Stats!"<<endl;
    cout<<setw(23)<<" "<<"Users: "<<cantUsuariosFinal<<endl;
    cout<<setw(11)<<" "<<"Playback Time Max: ";
    cout.fill('0');
    cout<<setw(2)<<right<<horaUsuarioMay<<":"<<setw(2)<<right<<minUsuarioMay<<":"
    <<setw(2)<<right<<segUsuarioMay<<endl;
    cout.fill(' ');
    cout<<setw(5)<<" "<<"Date with Max Playbacks: ";
    cout.fill('0');
    cout<<setw(2)<<right<<diaUsuarioMay<<"/"<<setw(2)<<right<<mesUsuarioMay<<"/"
    <<setw(4)<<right<<añoUsuarioMay;
    cout.fill(' ');
    cout<<endl;
    imprimirLineas('=',130);
}

void elegirUsuarioMayorHoraReproducciones(int horatotalReproUsuario,
                                            int dia,int mes,int año,int &mayNumRepro
                                            ,int &diaMay,int &mesMay,int &añoMay) {
    if (horatotalReproUsuario>mayNumRepro) {
        mayNumRepro = horatotalReproUsuario;
        diaMay = dia;
        mesMay = mes;
        añoMay=año;
    }
}
