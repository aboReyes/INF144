//
// Created by ASUS on 12/10/2025.
//

#include "FuncionesAuxiliares.h"

void aperturaArchivoLectura(const char* nombArch,ifstream& arch) {
    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"ERROR: el archivo"<<nombArch<<" no se puede abrir"<<endl;
        exit(1);
    }
}

void aperturaArchivoEscritura(const char* nombArch,ofstream& arch) {
    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout<<"ERROR: el archivo"<<nombArch<<" no se puede abrir"<<endl;
        exit(1);
    }
}

void cargarPlatosOfrecidos(const char* nombArchPlatOfre,int *arrCodigoPlato,
                            double *arrPrecioPlato,int *arrCantPlatosAtendidos,
                            double *arrDescuentoPlato,int &nroPlatos) {
    //cuando hay descuento: 31796 ANTICUCHO DE CORAZON AL PLATO}   31.90   43   19.94%
    //cuando no hay descuento: 53265 ANTICUCHO}   12.90   150
    ifstream archPlatOfre;
    aperturaArchivoLectura(nombArchPlatOfre,archPlatOfre);
    int codigoPlato;
    char c;
    while (true) {
        archPlatOfre>>codigoPlato;
        if (archPlatOfre.eof()) break;
        ignorar(archPlatOfre,'}');
        archPlatOfre>>arrPrecioPlato[nroPlatos];
        archPlatOfre>>arrCantPlatosAtendidos[nroPlatos];
        if (archPlatOfre.get()==' ') {
            archPlatOfre>>arrDescuentoPlato[nroPlatos];
            archPlatOfre>>c;
        }
        arrCodigoPlato[nroPlatos]=codigoPlato;
        nroPlatos++;
    }
    //cout<<"HAY "<<nroPlatos;
}

void cargarClientes(const char* nombArchClientes,
                    int *arrDniCliente,double *arrDescuentoCliente,int&nroClientes) {
    // con descuento:  90367684   CORONEL CHUMPITAZ HELI]   8594   Villa_Maria_del_Triunfo   M   S   13.04%
    // sin descuento: 66039166   LAURA WONG MELVIN HENRRY]   3562   Rimac   B   N
    ifstream archClientes;
    int dniCliente,codDistrito;
    double descuentoCliente;
    char hayDescuento,c,tipoVeh;
    aperturaArchivoLectura(nombArchClientes,archClientes);
    while (true) {
        archClientes>>dniCliente;
        if (archClientes.eof()) break;
        ignorar(archClientes,']');//nombreCliente
        archClientes>>codDistrito;//codDistrito
        ignorar(archClientes,' ');//nombreCiudad
        archClientes>>tipoVeh;//tipoVeh
        archClientes>>hayDescuento;
        if (hayDescuento=='S') {
            archClientes>>descuentoCliente;
            archClientes>>c;
        }else {
            ignorar(archClientes,'\n');
        }
        arrDescuentoCliente[nroClientes]=descuentoCliente;
        arrDniCliente[nroClientes]=dniCliente;
        nroClientes++;
    }
    //cout<<"HAY "<<nroClientes<<endl;
}

void reportePrueba(const char* nombArchRepPrueba,
                int *arrCodigoPlato,double *arrPrecioPlato,
                int *arrCantPlatosAtendidos,double *arrDescuentoPlato,int nroPlatos,
                int *arrDniCliente,double *arrDescuentoCliente,int nroClientes) {
    //CLIENTES:
    // con descuento:  90367684   CORONEL CHUMPITAZ HELI]   8594   Villa_Maria_del_Triunfo   M   S   13.04%
    // sin descuento: 66039166   LAURA WONG MELVIN HENRRY]   3562   Rimac   B   N
    //PLATOS:
    //cuando hay descuento: 31796 ANTICUCHO DE CORAZON AL PLATO}   31.90   43   19.94%
    //cuando no hay descuento: 53265 ANTICUCHO}   12.90   150
    ofstream archRepPrueba;
    aperturaArchivoEscritura(nombArchRepPrueba,archRepPrueba);
    imprimirLineas('=',90,archRepPrueba);
    imprimirCabeceraReportePlatos(archRepPrueba);
    archRepPrueba<<fixed<<setprecision(2);
    for (int i = 0; i < nroPlatos; i++) {
        archRepPrueba<<setw(15)<<right<<arrCodigoPlato[i];
        archRepPrueba<<setw(15)<<right<<arrPrecioPlato[i];
        archRepPrueba<<setw(15)<<right<<arrCantPlatosAtendidos[i];
        archRepPrueba<<setw(35)<<right<<arrDescuentoPlato[i]<<"%"<<endl;
    }
    imprimirLineas('=',90,archRepPrueba);
    imprimirCabeceraReporteClientes(archRepPrueba);
    for (int i = 0; i < nroClientes; i++) {
        archRepPrueba<<setw(15)<<right<<arrDniCliente[i];
        archRepPrueba<<setw(15)<<right<<arrDescuentoCliente[i]<<"%"<<endl;
    }
}

void imprimirCabeceraReportePlatos(ofstream& output) {
    output<<setw(10)<<" "<<"REPORTE DE PRUEBA PARA ARCHIVO PLATOS"<<endl;
    imprimirLineas('=',90,output);
    output<<setw(15)<<right<<"CODIGO";
    output<<setw(15)<<right<<"PRECIO";
    output<<setw(30)<<right<<"CANTIDAD PLATOS ATENDIDOS";
    output<<setw(25)<<right<<"DESCUENTO PLATO"<<endl;
    imprimirLineas('-',90,output);
}

void imprimirCabeceraReporteClientes(ofstream& output) {
    output<<setw(10)<<" "<<"REPORTE DE PRUEBA PARA ARCHIVO CLIENTES"<<endl;
    imprimirLineas('=',90,output);
    output<<setw(15)<<right<<"DNI";
    output<<setw(25)<<right<<"DESCUENTO CLIENTE"<<endl;
    imprimirLineas('-',90,output);
}


void cargarRepartosARealizar(const char* nombArchRepReali,
                            int *arrCodigoPlato,double *arrPrecioPlato,
                            int *arrCantPlatosAtendidos,double *arrDescuentoPlato,int nroPlatos,
                            int *arrDniCliente,double *arrDescuentoCliente,int nroClientes,
                            int *arrCantAtendida,int *arrCantNoAtendida,double *arrMontoEsperado,
                            double *arrMontoBruto,double *arrMontoRecibido) {
    //961419(nroPedido)   77324146(dniClien)   9(cantPedida)   53764(codPlato)   4   90766   1   90758....
    ifstream archRepRealizar;
    int nroPedido,dniCliente,cantPedida,codPlato,posPlato,cantFalta,posCliente;
    double pago ;
    aperturaArchivoLectura(nombArchRepReali,archRepRealizar);
    for (int i = 0; i < nroPlatos; i++)
        arrMontoEsperado[i] = arrCantPlatosAtendidos[i]*arrPrecioPlato[i];
    while(true) {
        archRepRealizar>>nroPedido;
        if (archRepRealizar.eof()) break;
        archRepRealizar>>dniCliente;
        posCliente=buscarCliente(arrDniCliente,dniCliente,nroClientes);
        while (true) {
            archRepRealizar>>cantPedida>>codPlato;
            posPlato=buscarPlato(arrCodigoPlato,codPlato,nroPlatos);
            if (posPlato!=NO_ENCONTRADO) {
                if (arrCantAtendida[posPlato]+cantPedida<=arrCantPlatosAtendidos[posPlato]) {
                    arrCantAtendida[posPlato]+=cantPedida;
                    cantFalta=0;
                }else {
                    cantFalta=arrCantPlatosAtendidos[posPlato]-arrCantAtendida[posPlato];
                    cantPedida-=cantFalta;
                    arrCantAtendida[posPlato]+=cantFalta;
                    arrCantNoAtendida[posPlato]+=cantPedida;
                }
                arrMontoBruto[posPlato]+=cantPedida*arrPrecioPlato[posPlato];
                pago=cantPedida*arrPrecioPlato[posPlato]*(1-arrDescuentoPlato[posPlato]/100.0);
                if (posCliente!=NO_ENCONTRADO) {
                    pago*=1-arrDescuentoCliente[posCliente]/100.0;
                }
                arrMontoRecibido[posPlato]+=pago;
            }
            if (archRepRealizar.get()=='\n') break;
        }
    }
}

void ordenarReporte(int *arrCodigoPlato,double *arrPrecioPlato,
                    int *arrCantPlatosAtendidos,double *arrDescuentoPlato,int nroPlatos,
                    int *arrDniCliente,double *arrDescuentoCliente,
                    int *arrCantAtendida,int *arrCantNoAtendida,double *arrMontoEsperado,
                    double *arrMontoBruto,double *arrMontoRecibido) {
    for (int i=0;i<nroPlatos-1; i++) {
     for (int j=i+1; j<nroPlatos; j++) {
         if (arrCantPlatosAtendidos[i]<arrCantPlatosAtendidos[j]) {
             swapInt(arrCodigoPlato[i],arrCodigoPlato[j]);
             swapDouble(arrPrecioPlato[i],arrPrecioPlato[j]);
             swapInt(arrCantPlatosAtendidos[i],arrCantPlatosAtendidos[j]);
             swapDouble(arrDescuentoPlato[i],arrDescuentoPlato[j]);
             swapInt(arrDniCliente[i],arrDniCliente[j]);
             swapDouble(arrDescuentoCliente[i],arrDescuentoCliente[j]);
             swapInt(arrCantAtendida[i],arrCantAtendida[j]);
             swapInt(arrCantNoAtendida[i],arrCantNoAtendida[j]);
             swapDouble(arrMontoEsperado[i],arrMontoEsperado[j]);
             swapDouble(arrMontoBruto[i],arrMontoBruto[j]);
             swapDouble(arrMontoRecibido[i],arrMontoRecibido[j]);
         }
     }
    }
}

void imprimirReporte(const char* nombArchRep,
                    int *arrCodigoPlato,double *arrPrecioPlato,
                    int *arrCantPlatosAtendidos,double *arrDescuentoPlato,int nroPlatos,
                    int *arrDniCliente,double *arrDescuentoCliente,int nroClientes,
                    int *arrCantAtendida,int *arrCantNoAtendida,double *arrMontoEsperado,
                    double *arrMontoBruto,double *arrMontoRecibido) {
    ofstream archRep;
    aperturaArchivoEscritura(nombArchRep,archRep);
    imprimirCabeceraReporte(archRep);
    archRep<<fixed<<setprecision(2);
    for (int i=0;i<nroPlatos;i++) {
        archRep<<arrCodigoPlato[i];
        archRep<<setw(15)<<right<<arrPrecioPlato[i];
        archRep<<setw(17)<<right<<arrCantPlatosAtendidos[i];
        archRep<<setw(16)<<right<<arrCantAtendida[i];
        archRep<<setw(18)<<right<<arrCantNoAtendida[i];
        archRep<<setw(23)<<right<<arrDescuentoCliente[i]<<"%";
        archRep<<setw(23)<<right<<arrMontoEsperado[i];
        archRep<<setw(15)<<right<<arrMontoBruto[i];
        archRep<<setw(15)<<right<<arrMontoRecibido[i]<<endl;
    }
}

void eliminarNoAtendidos_0(int *arrCodigoPlato,double *arrPrecioPlato,
                        int *arrCantPlatosAtendidos,double *arrDescuentoPlato,int &nroPlatos,
                        int *arrCantAtendida,int *arrCantNoAtendida,double *arrMontoEsperado,
                        double *arrMontoBruto,double *arrMontoRecibido) {
    int n=0;
    while (n<nroPlatos) {
        if (arrCantNoAtendida[n]==0) {
            eliminarElemento(n,arrCodigoPlato,arrPrecioPlato,arrCantPlatosAtendidos,
                           arrDescuentoPlato,nroPlatos,arrCantAtendida,arrCantNoAtendida,arrMontoEsperado,
                           arrMontoBruto,arrMontoRecibido);
        }else {
            n++;
        }
    }
}

void eliminarElemento(int n,int *arrCodigoPlato,double *arrPrecioPlato,
                    int *arrCantPlatosAtendidos,double *arrDescuentoPlato,int &nroPlatos,
                    int *arrCantAtendida,int *arrCantNoAtendida,double *arrMontoEsperado,
                    double *arrMontoBruto,double *arrMontoRecibido) {
    for (int i=n; i<nroPlatos-1; i++) {
        arrCodigoPlato[i]=arrCodigoPlato[i+1];
        arrPrecioPlato[i]=arrPrecioPlato[i+1];
        arrCantPlatosAtendidos[i]=arrCantPlatosAtendidos[i+1];
        arrDescuentoPlato[i]=arrDescuentoPlato[i+1];
        arrCantAtendida[i]=arrCantAtendida[i+1];
        arrCantNoAtendida[i]=arrCantNoAtendida[i+1];
        arrMontoEsperado[i]=arrMontoEsperado[i+1];
        arrMontoBruto[i]=arrMontoBruto[i+1];
        arrMontoRecibido[i]=arrMontoRecibido[i+1];
    }
    nroPlatos--;
}

void imprimirCabeceraReporte(ofstream& archRep) {
    archRep<<setw(55)<<" "<<"EMPRESA DE REPARTOS A DOMICILIO TP S. A."<<endl;
    archRep<<setw(60)<<" "<<"RELACION DE PLATOS VENDIDOS"<<endl;
    imprimirLineas('=',150,archRep);
    archRep<<setw(60)<<right<<"CANTIDAD DE PLATOS";
    archRep<<setw(75)<<right<<"MONTOS RECAUDADOS"<<endl;
    archRep<<"CODIGO";
    archRep<<setw(15)<<right<<"PRECIO";
    archRep<<setw(20)<<right<<"PREPARADOS";
    archRep<<setw(15)<<right<<"ATENDIDOS";
    archRep<<setw(20)<<right<<"NO ATENDIDOS";
    archRep<<setw(20)<<right<<"DESCUENTO";
    archRep<<setw(23)<<right<<"ESPERADO";
    archRep<<setw(14)<<right<<"BRUTO";
    archRep<<setw(15)<<right<<"RECIBIDO"<<endl;
    imprimirLineas('-',150,archRep);
}

int buscarCliente(int *arrDniCliente,int dniCliente,int nroCliente) {
    for (int i = 0; i < nroCliente; i++)
        if (arrDniCliente[i] == dniCliente) return i;
    return NO_ENCONTRADO;
}

int buscarPlato(int *arrCodigoPlato,int codPlato,int nroPlatos) {
    for (int i = 0; i < nroPlatos; i++)
        if (arrCodigoPlato[i] == codPlato) return i;
    return NO_ENCONTRADO;
}

void swapInt(int&a,int&b) {
    int aux=a;
    a=b;
    b=aux;
}

void swapDouble (double&a,double&b) {
    double aux=a;
    a=b;
    b=aux;
}

void swapChar (char &a,char&b) {
    char aux=a;
    a=b;
    b=aux;
}

void ignorar(ifstream &input,char delimitador) {
    char c;
    input>>ws;
    while (true) {
        c=input.get();
        if (c==delimitador) break;
    }
}

void imprimirLineas(char c,int cant,ofstream& archRep) {
    for (int i=0;i<cant;i++) archRep<<c;
    archRep<<endl;
}
