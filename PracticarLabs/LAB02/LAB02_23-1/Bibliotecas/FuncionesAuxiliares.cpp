//
// Created by DIEGO on 24/08/2025.
//

#include "FuncionesAuxiliares.h"

void  crearReporte() {
    int diaLimDoc,mesLimDoc,anioLimDoc;
    int diaLimEst,mesLimEst,anioLimEst;
    char c;
    cin>>diaLimDoc>>c>>mesLimDoc>>c>>anioLimDoc;
    cin>>diaLimEst>>c>>mesLimEst>>c>>anioLimEst;

    ImprimirCabeceraReporte(diaLimDoc,mesLimDoc,anioLimDoc,diaLimEst,mesLimEst,anioLimEst);

    int dniDocMayorDeuda, dniDocMasLibros;
    double mayorDeudaDoc=0, mayorCantLibrosDoc=0;

    int dniEstMayorDeuda,dniEstMasLibros;
    double mayorDeudaEst=0,mayorCantLibrosEst=0;

    int carne;
    char tipoUsuario;
    while (true) {
        cin>>carne>>tipoUsuario;
        if (cin.eof()) {//sirve para el fin de archivo
            cout<<setw(10)<<" "<<"..."<<setw(10)<<" "<<"..."<<setw(10)<<" "<<"..."<<endl;
            break;
        }
        if (tipoUsuario =='D') LeerInfoUsuario_ImpReporte(diaLimDoc,mesLimDoc,anioLimDoc,carne,tipoUsuario,dniDocMayorDeuda,mayorDeudaDoc,dniDocMasLibros,mayorCantLibrosDoc);
        else if (tipoUsuario =='E') LeerInfoUsuario_ImpReporte(diaLimEst,mesLimEst,anioLimEst,carne,tipoUsuario,dniEstMayorDeuda,mayorDeudaEst,dniEstMasLibros,mayorCantLibrosEst);
    }
    imprimirResumen(dniEstMayorDeuda,dniEstMasLibros,mayorDeudaEst,mayorCantLibrosEst,
                    dniDocMayorDeuda,dniDocMasLibros,mayorDeudaDoc,mayorCantLibrosDoc);
}

void imprimirResumen(int dniEstMayorDeuda,int dniEstMasLibros,double mayorDeudaEst,int mayorCantLibrosEst,int  dniDocMayorDeuda,int dniDocMasLibros,double mayorDeudaDoc,int mayorCantLibrosDoc){
    imprimirLineas(110,'=');
    cout<<"Resumen: "<<endl;
    cout<<"Con mayor deuda: "<<setw(14)<<" "<<"Docente: "<<dniDocMayorDeuda<<setw(2)<<" "<<"Deuda S/. "<<mayorDeudaDoc;
    cout<<setw(4)<<" "<<"Estudiante: "<<dniEstMayorDeuda<<setw(2)<<" "<<"Deuda S/. "<<mayorDeudaEst<<endl;

    cout<<"Con mayor cantidad de libros: "<<" "<<"Docente: "<<dniDocMasLibros<<setw(2)<<" "<<"Cantidad "<<mayorCantLibrosDoc<<" libros";
    cout<<setw(2)<<" "<<"Estudiante: "<<dniEstMasLibros<<setw(2)<<" "<<"Cantidad "<<mayorCantLibrosDoc<<" libros"<<endl;

    imprimirLineas(110,'=');
}


void imprimirLineas(int cant, char c) {
    for (int i = 0; i < cant; i++) {
        cout << c;
    }
    cout << endl;
}

void ImprimirCabeceraReporte(int diaLimDoc,int mesLimDoc,int anioLimDoc,int diaLimEst,int mesLimEst,int anioLimEst) {

    cout<<setw(65)<<right<<"BIBLIOTECA GENERA DE LA UNIVERSIDAD"<<endl;
    imprimirLineas(110,'=');
    cout<<setw(35)<<right<<"Fechas limite de devolucion: "<<endl;

    cout<<setw(40)<<" "<<setw(15)<<left<<"Docente: ";
    cout.fill('0');
    cout<<setw(2)<<right<<diaLimDoc<<"/"<<setw(2)<<right<<mesLimDoc<<"/"<<anioLimDoc<<endl;
    cout.fill(' ');

    cout<<setw(40)<<" "<<setw(15)<<left<<"Estudiante: ";
    cout.fill('0');
    cout<<setw(2)<<right<<diaLimEst<<"/"<<setw(2)<<right<<mesLimEst<<"/"<<anioLimEst<<endl;
    cout.fill(' ');

    imprimirLineas(110,'-');
    cout<<setw(58)<<right<<"RELACION DE USUARIO Y LIBROS"<<endl;
    imprimirLineas(110,'=');
}


void LeerInfoUsuario_ImpReporte(int dia,int mes, int anio,int carne,char tipoUsuario,
                                int &dniUsuarioMayorDeuda,double &mayorDeuda,
                                int &dniUsuarioMasLibros,double &mayorCantLibrosUsuario){
    cout<<setw(5)<<" "<<"Carne No.: "<<right<<setw(13)<<carne;
    cout<<setw(5)<<" ";

    double porcMulta;
    if (tipoUsuario=='D') {
        cout<<"Tipo: "<<setw(5)<<" "<<"Docente"<<endl;
        porcMulta=2.25;
    }
    else if (tipoUsuario=='E') {
        cout<<"Tipo: "<<setw(5)<<" "<<"Estudiante"<<endl;
        porcMulta=1;
    }
    imprimirLineas(110, '-');
    int codLibro,diaRet,mesRet,anioRet;
    char c;
    double precioLibro;
    cout<<setw(5)<<" "<<"Libros en su poder: "<<endl;
    cout<<setw(15)<<right<<"Codigo"<<setw(20)<<right<<"F. de retiro "<<setw(20)<<right<<"Observacion"<<endl;
    int cantLibrosConDeuda=0;
    double totalMultas=0;

    int cantLibros=0;
    while (true) {
        cin>>codLibro>>diaRet>>c>>mesRet>>c>>anioRet>>precioLibro;
        cantLibros++;
        procesarLibro(codLibro,diaRet,mesRet,anioRet,dia,mes,anio,precioLibro,porcMulta,cantLibrosConDeuda,totalMultas);
        if (cin.get()=='\n') break;
    }

    if (totalMultas>mayorDeuda) {
        mayorDeuda=totalMultas;
        dniUsuarioMayorDeuda=carne;
    }

    if (cantLibros>mayorCantLibrosUsuario) {
        mayorCantLibrosUsuario=cantLibros;
        dniUsuarioMasLibros=carne;
    }
    imprimirLineas(110, '=');
    cout<<setw(7)<<" "<<"Cantidad de libros adeudados: "<<setw(4)<<right<<cantLibrosConDeuda<<endl;
    cout<<setw(7)<<" "<<"Total de deudas por multa: "<<setw(10)<<right<<totalMultas<<endl;
    imprimirLineas(110, '=');
    imprimirLineas(110, '/');
    imprimirLineas(110, '=');

}

void procesarLibro(int codLibro,int diaRet,int mesRet,int anioRet,int dia,int mes,int anio,double precioLibro,double porcMulta,int &cantLibrosConDeuda,double &totalMultas) {
    cout<<setw(9)<<" ";
    cout.fill('0');
    cout<<setw(5)<<codLibro;
    cout.fill(' ');
    cout<<setw(8)<<" ";
    cout.fill('0');
    cout<<setw(2)<<diaRet<<"/"<<setw(2)<<mesRet<<"/"<<anioRet;
    cout.fill(' ');

    int fechaLimite = anio*10000+mes*100+dia;
    int fechaRetiro = anioRet*10000+mesRet*100+diaRet;

    cout<<fixed;
    cout.precision(2);
    if (fechaLimite<fechaRetiro) {
        double multa=precioLibro*(porcMulta/100);
        cout<<setw(21)<<right<<"EN DEUDA"<<setw(30)<<right<<"Multa: ";
        cout<<setw(10)<<right<<multa<<endl;
        cantLibrosConDeuda++;
        totalMultas+=multa;
    }else {
        cout<<setw(16)<<"---"<<endl;
    }
}
