//
// Created by ASUS on 30/10/2025.
//

#include "FuncionesAuxiliares.h"


void aperturaArchivoLectura(const char* nombArch,ifstream& arch) {
    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"Error el archivo "<<nombArch<<" no se puede abrir"<<endl;
        exit(1);
    }
}

void aperturaArchivoEscritura(const char* nombArch,ofstream& arch) {
    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout<<"Error el archivo "<<nombArch<<" no se puede abrir"<<endl;
        exit(1);
    }
}

void cargarRepartos(const char* nombArch,
                    int *arrNumPlatosVendidos,int *arrCodigoPlatos,int &cantRepartos) {
    //RepartosARealizar.txt
    //358019   93231760
    //se repite...
    //8   11471
    //7   77572
    ifstream input;
    int numPedido,dniCliente,cantPlatos,codePlatos;
    aperturaArchivoLectura(nombArch,input);
    while (true) {
        input>>numPedido;
        if (input.eof()) break;
        input>>dniCliente;
        while (true) {
            input>>cantPlatos;
            input>>codePlatos;
            procesamientoPlatos(cantPlatos,codePlatos,
                            arrNumPlatosVendidos,arrCodigoPlatos,cantRepartos);
            if (input.get()=='\n') break;
        }
    }
}


void procesamientoPlatos(int cantPlatos,int codePlatos,
                    int *arrNumPlatosVendidos,int *arrCodigoPlatos,int &cantRepartos) {


    int posPlato=busquedaBinaria(codePlatos,arrCodigoPlatos,cantRepartos);

    if (posPlato!=NO_ENCONTRADO) {
        arrNumPlatosVendidos[posPlato]+=cantPlatos;
    }else {
        insertarOrdenado(cantPlatos,codePlatos,
                        arrNumPlatosVendidos,arrCodigoPlatos,cantRepartos);
    }
}

void insertarOrdenado(int cantPlatos,int codePlatos,
                    int *arrNumPlatosVendidos,int *arrCodigoPlatos,int &cantRepartos) {
    int i=cantRepartos-1;
    while (i>=0 and codePlatos>arrCodigoPlatos[i]) {
        arrNumPlatosVendidos[i+1]=arrNumPlatosVendidos[i];
        arrCodigoPlatos[i+1]=arrCodigoPlatos[i];
        i--;
    }
    arrNumPlatosVendidos[i+1]=cantPlatos;
    arrCodigoPlatos[i+1]=codePlatos;
    cantRepartos++;
}

int busquedaBinaria(int codePlato,int *arrCodePlato,int& cant) {
    int limiteInferior=0;
    int limiteSuperior=cant-1;
    int puntoMedio;
    //como tenemos el orden descendente tipo 9 8 7 6 .  ..
    while (true) {
        if (limiteInferior>limiteSuperior) return NO_ENCONTRADO;
        puntoMedio=(limiteInferior+limiteSuperior)/2;
        if (codePlato==arrCodePlato[puntoMedio]) return puntoMedio;
        if (codePlato>arrCodePlato[puntoMedio]) {
            limiteSuperior=puntoMedio-1;
        }else {
            limiteInferior=puntoMedio+1;
        }
    }
}


void procesarPlatos(const char* nombArch,
                int *arrNumPlatosVendidos,int *arrCodigoPlatos,int cantRepartos,
                double *arrPrecio,double *arrIngresoBruto,double *arrDescuento,double *arrTotal,
                bool *arrTieneDescuento) {
    //PlatosOfrecidos.txt
    //puede tener o no descuento
    //39747     COCA_COLA_1/2_LITRO      7      ADICIONAL    9.03%
    //90365     MOLLEGITAS_A_LA_PARRILLA    25.9    ADICIONAL
    ifstream input;
    int codePlato,posPlato;
    double precioPlato,descuentoPlato;
    char cadena[100];
    aperturaArchivoLectura(nombArch,input);
    while (true) {
        input>>codePlato;
        if (input.eof()) break;
        posPlato=busquedaBinaria(codePlato,arrCodigoPlatos,cantRepartos);
        if (posPlato!=NO_ENCONTRADO) {
            input>>cadena;
            input>>precioPlato;
            input>>cadena;
            if (input.get()==' ') {
                input>>descuentoPlato;
                arrDescuento[posPlato]=descuentoPlato;
                arrTieneDescuento[posPlato]=true;
                input.get();//Eliminar el %
            }else {
                arrTieneDescuento[posPlato]=false;
                arrDescuento[posPlato]=0.0;
            }
            arrPrecio[posPlato]=precioPlato;
            arrCodigoPlatos[posPlato]=codePlato;
            arrIngresoBruto[posPlato]=arrNumPlatosVendidos[posPlato]*arrPrecio[posPlato];
            arrTotal[posPlato]=arrIngresoBruto[posPlato]-(arrIngresoBruto[posPlato]*arrDescuento[posPlato]/100);
        }else {
            ignorar(input,'\n');
        }
    }
}

void pruebaDatos(const char* nombArchRep,
                int *arrNumPlatosVendidos,int *arrCodigoPlatos,int cantRepartos,
                double *arrPrecio,double *arrIngresoBruto,double *arrDescuento,double *arrTotal,
                bool *arrTieneDescuento) {
    ofstream output;
    aperturaArchivoEscritura(nombArchRep,output);
    imprimirSubtituloRepPrueba(output);
    output<<fixed<<setprecision(2);
    for (int i=0;i<cantRepartos;i++) {
        imprimirNroOrden(output,i+1);
        output<<setw(10)<<right<<arrCodigoPlatos[i];
        output<<setw(13)<<right<<arrNumPlatosVendidos[i];
        output<<setw(16)<<right<<arrPrecio[i];
        output<<setw(18)<<right<<arrIngresoBruto[i];
        if (arrTieneDescuento[i]==true) {
            output<<setw(17)<<right<<arrDescuento[i]<<"%";
        }else {
            output<<setw(15)<<right<<"-"<<setw(3)<<" ";
        }
        output<<setw(15)<<right<<arrTotal[i]<<endl;
    }
}

void crearReporte(const char *nombArchPlatos,
                const char* nombArchRep,
                int *arrNumPlatosVendidos,int *arrCodigoPlatos,int cantRepartos,
                double *arrPrecio,double *arrIngresoBruto,double *arrDescuento,double *arrTotal,
                bool *arrTieneDescuento) {
    ifstream input;
    ofstream output;
    aperturaArchivoLectura(nombArchPlatos,input);
    aperturaArchivoEscritura(nombArchRep,output);

    //39747     COCA_COLA_1/2_LITRO      7      ADICIONAL    9.03%
    //90365     MOLLEGITAS_A_LA_PARRILLA    25.9    ADICIONAL
    int codePlato,cantPlato,posPlato,nroOrden=0;
    char nombrePlato[100],categoriaPlato[100],c;
    double precioPlato,descuentoPlato;
    imprimirSubtituloRepFinal(output);
    output<<fixed<<setprecision(2);
    while (true) {
        input>>codePlato;
        if (input.eof()) break;
        posPlato=busquedaBinaria(codePlato,arrCodigoPlatos,cantRepartos);
        if (posPlato!=NO_ENCONTRADO) {
            input>>nombrePlato;
            input>>precioPlato;// ya no importa porque ya lo procesamos anteriormente
            input>>categoriaPlato;
            if (input.get()==' ') {
                input>>descuentoPlato>>c;// ya no importa porque ya lo procesamos anteriormente
            }
            modificarCadena(nombrePlato,categoriaPlato,arrTieneDescuento[posPlato]);
            nroOrden++;
            imprimirNroOrden(output,nroOrden);
            output<<setw(10)<<right<<codePlato;
            output<<"   "<<setw(65)<<left<<nombrePlato;
            output<<setw(16)<<right<<arrNumPlatosVendidos[posPlato];
            output<<setw(18)<<right<<arrPrecio[posPlato];
            output<<setw(18)<<right<<arrIngresoBruto[posPlato];
            if (arrTieneDescuento[posPlato]==true) {
                output<<setw(17)<<right<<arrDescuento[posPlato]<<"%";
            }else {
                output<<setw(15)<<right<<"-"<<setw(3)<<" ";
            }
            output<<setw(15)<<right<<arrTotal[posPlato]<<endl;
        }else {
            ignorar(input,'\n');
        }
    }
}

void imprimirSubtituloRepFinal(ofstream& output) {
    output<<setw(65)<<" "<<"EMPRESA DE REPARTOS A DOMICILIO TP S. A."<<endl;
    output<<setw(70)<<" "<<"RELACION DE PLATOS VENDIDOS"<<endl;
    imprimirLineas('=',170,output);
    output<<"No.";
    output<<setw(11)<<right<<"PLATO";
    output<<setw(11)<<right<<"OFRECIDO";
    output<<setw(80)<<right<<"CANTIDAD VENDIDA";
    output<<setw(12)<<right<<"PRECIO";
    output<<setw(20)<<right<<"INGRESO BRUTO";
    output<<setw(16)<<right<<"DESCUENTO";
    output<<setw(14)<<right<<"TOTAL"<<endl;
    imprimirLineas('-',170,output);
}

void modificarCadena(char *nombrePlato,char *categoriaPlato,bool tieneDescuento) {
    formato1(nombrePlato); //'_' --> ' '
    formato2(nombrePlato);//camelizar diego axel --> Diego Axel
    if (tieneDescuento)
        formato4(nombrePlato,categoriaPlato);//concatenar2--> nombrePlato-Promocionado-categoriaPlato
    else
        formato3(nombrePlato,categoriaPlato);// concatenar--> nombrePlato-categoriaPlato
}

void formato4(char* nombrePlato,char* categoriaPlato) {
    strcat(nombrePlato,"-PROMOCIONADO-");
    strcat(nombrePlato,categoriaPlato);
}

void formato3(char *nombrePlato,char* categoriaPlato) {
    strcat(nombrePlato,"-");
    strcat(nombrePlato,categoriaPlato);
}

void formato2(char *nombrePlato) {
    //DIEGO AXEL --> Diego Axel
    bool inicioPalabra=true;
    for (int i=0;nombrePlato[i];i++) {
        if (inicioPalabra) {
            if (nombrePlato[i]>='a' and nombrePlato[i]<='z') {
                nombrePlato[i]-='a'-'A';
            }
            inicioPalabra=false;
        }else {
            if (nombrePlato[i]==' ') {
                inicioPalabra=true;
            }else if (nombrePlato[i]>='A' and nombrePlato[i]<='Z') {
                nombrePlato[i]+='a'-'A';
            }
        }
    }
}

void formato1(char *nombrePlato) {
    for (int i=0;nombrePlato[i];i++)
        if (nombrePlato[i]=='_') nombrePlato[i]=' ';
}

void imprimirSubtituloRepPrueba(ofstream& output) {
    output<<setw(30)<<" "<<"REPORTE DE PRUEBA DE CARGA DE DATOS"<<endl;
    imprimirLineas('=',100,output);
    output<<"No.";
    output<<setw(11)<<right<<"PLATO";
    output<<setw(20)<<right<<"CANTIDAD VENDIDA";
    output<<setw(10)<<right<<"PRECIO";
    output<<setw(20)<<right<<"INGRESO BRUTO";
    output<<setw(16)<<right<<"DESCUENTO";
    output<<setw(14)<<right<<"TOTAL"<<endl;
    imprimirLineas('-',100,output);
}

void imprimirLineas(char c,int cant,ofstream& output) {
    for (int i=0;i<cant;i++) output<<c;
    output<<endl;
}

void imprimirNroOrden(ofstream& output,int nroOrden) {
    output.fill('0');
    output<<setw(3)<<right<<nroOrden<<")";
    output.fill(' ');
}

void ignorar(ifstream& input,char delimitador) {
    char c;
    input>>ws;
    while (true) {
        c=input.get();
        if (c==delimitador) break;
    }
}
