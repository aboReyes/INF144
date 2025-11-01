//
// Created by ASUS on 31/10/2025.
//

#include "FuncionesAuxiliares.h"

void aperturaArchivoLectura(const char* nombArch,ifstream& arch) {
    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"ERROR, el archivo "<<nombArch<<" no se puede abrir"<<endl;
        exit(1);
    }
}

void aperturaArchivoEscritura(const char* nombArch,ofstream& arch) {
    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout<<"ERROR, el archivo "<<nombArch<<" no se puede abrir"<<endl;
        exit(1);
    }
}

void cargarRepartidores(const char *nombArch,
                        int *arrDniRepartidor,char **arrNombreRepartidor,
                        char **arrTipoVehiculo,int *arrCodigoDistrito,
                        char **arrNombreDistrito,int &cantRepartidores){
    //54805724   Vizcardo_Sinche_Maribel     Motocicleta      4826   Santa_Rosa
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    int dniRepartidor;
    while (true) {
        input>>dniRepartidor;
        if (input.eof()) break;
        arrNombreRepartidor[cantRepartidores]=leerString(input);
        modificarCadena(arrNombreRepartidor[cantRepartidores],true,false,false);
        arrTipoVehiculo[cantRepartidores]=leerString(input);
        modificarCadena(arrTipoVehiculo[cantRepartidores],false,true,false);
        input>>arrCodigoDistrito[cantRepartidores];
        arrNombreDistrito[cantRepartidores]=leerString(input);
        modificarCadena(arrNombreDistrito[cantRepartidores],false,false,true);
        arrDniRepartidor[cantRepartidores]=dniRepartidor;
        cantRepartidores++;
    }
}

void cargarPlatos(const char *nombArch,
                int *arrCodigoPlato,char **arrNombrePlato,
                double *arrPrecioPlato,char **arrCategoriaPlato,
                double *arrDescuentoPlato,int &cantPlatos) {
    //con y sin descuento
    //73428       TEQUENOS       19.50       APERITIVO
    //11283   2_BOLAS_DE_HELADO      14.90   POSTRES    17.72%
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    int codigoPlato;
    while (true) {
        input>>codigoPlato;
        if (input.eof()) break;
        arrNombrePlato[cantPlatos]=leerString(input);
        input>>arrPrecioPlato[cantPlatos];
        arrCategoriaPlato[cantPlatos]=leerString(input);
        if (input.get()==' ') {
            input>>arrDescuentoPlato[cantPlatos];
            input.get();
        }else {
            arrDescuentoPlato[cantPlatos]=0.0;
        }
        arrCodigoPlato[cantPlatos]=codigoPlato;
        cantPlatos++;
    }
}

void reportePrueba(const char* nombArchRep,
            int *arrDniRepartidor,char **arrNombreRepartidor,
            char **arrTipoVehiculo,int *arrCodigoDistrito,
            char **arrNombreDistrito,int cantRepartidores,
            int *arrCodigoPlato,char **arrNombrePlato,
            double *arrPrecioPlato,char **arrCategoriaPlato,
            double *arrDescuentoPlato,int cantPlatos){
    ofstream output;
    aperturaArchivoEscritura(nombArchRep,output);

    imprimirSubRepPruebaPlatos(output);
    output<<fixed<<setprecision(2);
    for (int i=0;i<cantPlatos;i++) {
        output<<setw(10)<<right<<arrCodigoPlato[i];
        output<<setw(10)<<" "<<setw(50)<<left<<arrNombrePlato[i];
        output<<setw(10)<<right<<arrPrecioPlato[i];
        output<<setw(10)<<" "<<setw(30)<<left<<arrCategoriaPlato[i];
        output<<setw(10)<<right<<arrDescuentoPlato[i]<<endl;
    }
    imprimirSubRepPruebaRep(output);
    output<<fixed<<setprecision(2);
    for (int i=0;i<cantRepartidores;i++) {
        output<<arrDniRepartidor[i];
        output<<setw(10)<<" "<<setw(50)<<left<<arrNombreRepartidor[i];
        output<<setw(10)<<" "<<setw(20)<<left<<arrTipoVehiculo[i];
        output<<setw(7)<<right<<arrCodigoDistrito[i];
        output<<setw(18)<<" "<<setw(30)<<left<<arrNombreDistrito[i]<<endl;
    }

}

void ordenarRepartidores(int *arrDniRepartidor,char **arrNombreRepartidor,
                        char **arrTipoVehiculo,int *arrCodigoDistrito,
                        char **arrNombreDistrito,int cantRepartidores) {
    for (int i=0;i<cantRepartidores-1;i++) {
        for (int j=i+1;j<cantRepartidores;j++) {
            if (strcmp(arrNombreRepartidor[i],arrNombreRepartidor[j])>0) {
                swapInt(arrDniRepartidor[i],arrDniRepartidor[j]);
                swapString(arrNombreRepartidor[i],arrNombreRepartidor[j]);
                swapString(arrTipoVehiculo[i],arrTipoVehiculo[j]);
                swapInt(arrCodigoDistrito[i],arrCodigoDistrito[j]);
                swapString(arrNombreDistrito[i],arrNombreDistrito[j]);
            }
        }
    }
}

void procesarRepartosARealizar(const char* nombArch,
                            char **arrTipoVehiculo,int *arrCodigoDistrito,int cantRepartidores,
                            int *arrCodigoPlato,double *arrPrecioPlato,double *arrDescuentoPlato,int cantPlatos,
                            int *arrTotalCantPlatosRep,double *arrMontoTotalPlatos,double *arrDescuentoPorPlatos,
                            double *arrDescuentoPorClientes,double *arrPagoAlRepartidor,double *arrTotalIngresadoRep,
                            int *arrTotalCantPlatos,double *arrMontoVendido,double *arrDescuentoAlPlato,
                            double *arrDescuentoAlCliente,double *arrTotalIngresadoPlatos) {
    //RepartosARealizar.txt
    //358019   93231760   7752        Bicicleta        S        19.47%
    //se repite
    //8   11471
    //7   77572

    //804501   71422479   8280       Motocicleta       N
    ////se repite
    //3   39475
    //1   15760

    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    int codigoPedido,dniRep,codigoDistrito,posReparto;
    char vehiculoRep[50],hayDescuento,c;
    double descuentoReparto,porcPagoRep;
    while (true) {
        input>>codigoPedido;
        if (input.eof()) break;
        input>>dniRep;
        input>>codigoDistrito;
        input>>vehiculoRep;
        formato3(vehiculoRep);
        input>>hayDescuento;
        if (hayDescuento=='S') input>>descuentoReparto>>c;
        else descuentoReparto=0;
        posReparto=buscarRepartidor(arrCodigoDistrito,arrTipoVehiculo,
                                    codigoDistrito,vehiculoRep,cantRepartidores);
        if (posReparto!=NO_ENCONTRADO) {
            porcPagoRep=calcularPagoRep(vehiculoRep);
            procesarPlatosRepartidos(input,arrCodigoPlato,
                                    arrPrecioPlato,arrDescuentoPlato,cantPlatos,
                                    descuentoReparto,porcPagoRep,
                                    arrTotalCantPlatosRep[posReparto],arrMontoTotalPlatos[posReparto],
                                    arrDescuentoPorPlatos[posReparto],arrDescuentoPorClientes[posReparto],
                                    arrPagoAlRepartidor[posReparto],arrTotalCantPlatos,
                                    arrMontoVendido,arrDescuentoAlPlato,
                                    arrDescuentoAlCliente);
        }else {
            ignorar(input,'\n');
        }
    }
    for (int i=0;i<cantRepartidores;i++) {
        arrTotalIngresadoRep[i]=arrMontoTotalPlatos[i]-arrDescuentoPorPlatos[i]-arrDescuentoPorClientes[i]
                                -arrPagoAlRepartidor[i];
    }
    for (int i=0;i<cantPlatos;i++) {
        arrTotalIngresadoPlatos[i]=arrMontoVendido[i]-arrDescuentoAlCliente[i]-arrDescuentoAlCliente[i];
    }
}

void procesarPlatosRepartidos(ifstream& input,int *arrCodigoPlato,
                            double *arrPrecioPlato,double *arrDescuentoPlato,int cantPlatos,
                            double descuentoReparto,double porcPagoRep,
                            int &arrTotalCantPlatosRep,double &arrMontoTotalPlatos,
                            double &arrDescuentoPorPlatos,double &arrDescuentoPorClientes,
                            double &arrPagoAlRepartidor,int *arrTotalCantPlatos,
                            double *arrMontoVendido,double *arrDescuentoAlPlato,
                            double *arrDescuentoAlCliente) {
    int cantidadPedida,codigoPlato,posPlato;
    double montoPedido=0;
    while (true) {
        input>>cantidadPedida>>codigoPlato;
        posPlato=buscarPlato(codigoPlato,arrCodigoPlato,cantPlatos);
        if (posPlato!=NO_ENCONTRADO) {
            montoPedido+=cantidadPedida*arrPrecioPlato[posPlato];

            //Repartidores
            arrTotalCantPlatosRep+=cantidadPedida;
            arrDescuentoPorPlatos+=cantidadPedida*arrPrecioPlato[posPlato]*(arrDescuentoPlato[posPlato]/100);

            //Platos
            arrTotalCantPlatos[posPlato]+=cantidadPedida;
            arrMontoVendido[posPlato]+=cantidadPedida*arrPrecioPlato[posPlato];
            arrDescuentoAlPlato[posPlato]+=cantidadPedida*arrPrecioPlato[posPlato]*(arrDescuentoPlato[posPlato]/100);
            arrDescuentoAlCliente[posPlato]+=cantidadPedida*arrPrecioPlato[posPlato]*(descuentoReparto/100);
        }
        if (input.get()=='\n') break;
    }
    arrMontoTotalPlatos+=montoPedido;
    arrDescuentoPorClientes+=montoPedido*(descuentoReparto/100);
    arrPagoAlRepartidor+=montoPedido*(porcPagoRep/100);
}

void ordenarPlatos(int *arrCodigoPlato,char **arrNombrePlato,
                double *arrPrecioPlato,char **arrCategoriaPlato,
                double *arrDescuentoPlato,int cantPlatos,
                int *arrTotalCantPlatos,double *arrMontoVendido,
                double *arrDescuentoAlPlato,double *arrDescuentoAlCliente,
                double *arrTotalIngresadoPlatos) {
    for (int i=0;i<cantPlatos-1;i++) {
        for (int j=i+1;j<cantPlatos;j++) {
            if (arrTotalCantPlatos[i]<arrTotalCantPlatos[j] or
                arrTotalCantPlatos[i]==arrTotalCantPlatos[j] and
                strcmp(arrNombrePlato[i],arrNombrePlato[j])<0) {
                swapInt(arrCodigoPlato[i],arrCodigoPlato[j]);
                swapString(arrNombrePlato[i],arrNombrePlato[j]);
                swapDouble(arrPrecioPlato[i],arrPrecioPlato[j]);
                swapString(arrCategoriaPlato[i],arrCategoriaPlato[j]);
                swapDouble(arrDescuentoPlato[i],arrDescuentoPlato[j]);
                swapInt(arrTotalCantPlatos[i],arrTotalCantPlatos[j]);
                swapDouble(arrMontoVendido[i],arrMontoVendido[j]);
                swapDouble(arrDescuentoAlPlato[i],arrDescuentoAlPlato[j]);
                swapDouble(arrDescuentoAlCliente[i],arrDescuentoAlCliente[j]);
                swapDouble(arrTotalIngresadoPlatos[i],arrTotalIngresadoPlatos[j]);
            }
        }
    }
}

void generarReportePorRepartidores(const char* nombArchRep,
                                int *arrDniRepartidor,char **arrNombreRepartidor,char **arrTipoVehiculo,
                                char **arrNombreDistrito,int *arrTotalCantPlatosRep,double *arrMontoTotalPlatos,
                                double *arrDescuentoPorPlatos,double *arrDescuentoPorClientes,double *arrPagoAlRepartidor,
                                double *arrTotalIngresadoRep,int cantRepartidores) {
    ofstream output;
    int cantTotalPlatos=0;
    double montoTotalPlatos=0.0,totalDescuentoPorPlatos=0.0,totalDescuentoPorClientes=0.0,
            totalPagoRep=0.0,totalGlobalIngresado=0.0;
    aperturaArchivoEscritura(nombArchRep, output);
    imprimirCabeceraReporteRep(output);
    output<<fixed<<setprecision(2);
    for (int i=0;i<cantRepartidores-1;i++) {
        output<<arrDniRepartidor[i];
        output<<setw(5)<<" "<<setw(40)<<left<<arrNombreRepartidor[i];
        output<<setw(5)<<" "<<setw(20)<<left<<arrTipoVehiculo[i];
        output<<setw(5)<<" "<<setw(25)<<left<<arrNombreDistrito[i];
        output<<setw(20)<<right<<arrTotalCantPlatosRep[i];
        output<<setw(20)<<right<<arrMontoTotalPlatos[i];
        output<<setw(20)<<right<<arrDescuentoPorPlatos[i];
        output<<setw(20)<<right<<arrDescuentoPorClientes[i];
        output<<setw(20)<<right<<arrPagoAlRepartidor[i];
        output<<setw(20)<<right<<arrTotalIngresadoRep[i]<<endl;
        cantTotalPlatos+=arrTotalCantPlatosRep[i];
        montoTotalPlatos+=arrMontoTotalPlatos[i];
        totalDescuentoPorPlatos+=arrDescuentoPorPlatos[i];
        totalDescuentoPorClientes+=arrDescuentoPorClientes[i];
        totalPagoRep+=arrPagoAlRepartidor[i];
        totalGlobalIngresado+=arrTotalIngresadoRep[i];
    }
    imprimirResumenRep(output,cantTotalPlatos,montoTotalPlatos,totalDescuentoPorPlatos,
                    totalDescuentoPorClientes,totalPagoRep,totalGlobalIngresado);
}

void imprimirResumenRep(ofstream& output,int cantTotalPlatos,double montoTotalPlatos,double totalDescuentoPorPlatos,
                    double totalDescuentoPorClientes,double totalPagoRep,double totalGlobalIngresado) {
    imprimirLineas('-',235,output);
    output<<"TOTALES OBTENIDOS:";
    output<<setw(110)<<right<<cantTotalPlatos;
    output<<setw(20)<<right<<montoTotalPlatos;
    output<<setw(20)<<right<<totalDescuentoPorPlatos;
    output<<setw(20)<<right<<totalDescuentoPorClientes;
    output<<setw(20)<<right<<totalPagoRep;
    output<<setw(20)<<right<<totalGlobalIngresado<<endl;
    imprimirLineas('=',235,output);
}

void imprimirCabeceraReporteRep(ofstream &output) {
    output<<setw(100)<<" "<<"EMPRESA DE REPARTOS A DOMICILIO TP S. A."<<endl;
    output<<setw(105)<<" "<<"ENTREGAS POR REPARTIDORES"<<endl;
    imprimirLineas('=',235,output);
    output<<setw(132)<<right<<"TOTAL DE";
    output<<setw(20)<<right<<"MONTO TOTAL";
    output<<setw(19)<<right<<"DESCUENTO";
    output<<setw(19)<<right<<"DESCUENTOS";
    output<<setw(19)<<right<<"PAGO AL";
    output<<setw(19)<<right<<"TOTAL"<<endl;
    output<<"DNI";
    output<<setw(16)<<right<<"NOMBRE";
    output<<setw(47)<<right<<"VEHICULO";
    output<<setw(25)<<right<<"DISTRITO";
    output<<setw(40)<<right<<"PLATOS";
    output<<setw(20)<<right<<"POR PLATOS";
    output<<setw(20)<<right<<"POR PLATOS";
    output<<setw(20)<<right<<"POR CLIENTES";
    output<<setw(20)<<right<<"REPARTIDOR";
    output<<setw(20)<<right<<"INGRESADO"<<endl;
    imprimirLineas('-',235,output);
}

void generarReportePorPlatos(const char* nombArchRep,
                            int *arrCodigoPlato,char **arrNombrePlato,char **arrCategoriaPlato,
                            double *arrPrecioPlato,double *arrDescuentoPlato,int *arrTotalCantPlatos,
                            double *arrMontoVendido,double *arrDescuentoAlPlato,double *arrDescuentoAlCliente,
                            double *arrTotalIngresadoPlatos,int cantPlatos) {
    ofstream output;
    int totalCantidad=0;
    double totalMontoVendido=0.0,totalDescuentoAlPlato=0.0,totalDescuentoAlCliente=0.0,totalGlobalIngresado=0.0;
    aperturaArchivoEscritura(nombArchRep,output);
    imprimirCabeceraReportePlatos(output);
    output<<fixed<<setprecision(2);
    for (int i=0;i<cantPlatos;i++) {
        output<<arrCodigoPlato[i];
        output<<setw(5)<<" "<<setw(45)<<left<<arrNombrePlato[i];
        output<<setw(5)<<" "<<setw(10)<<left<<arrCategoriaPlato[i];
        output<<setw(20)<<right<<arrPrecioPlato[i];
        if (arrDescuentoPlato[i]==0) {
            output<<setw(20)<<right<<"NO"<<setw(2)<<" ";
        }else {
            output<<setw(20)<<right<<arrDescuentoPlato[i]<<"% ";
        }

        output<<setw(20)<<right<<arrTotalCantPlatos[i];
        output<<setw(20)<<right<<arrMontoVendido[i];

        if (arrDescuentoAlPlato[i]==0) {
            output<<setw(18)<<right<<"NO"<<setw(2)<<" ";
        }else {
            output<<setw(20)<<right<<arrDescuentoAlPlato[i];
        }

        if (arrDescuentoAlCliente[i]==0) {
            output<<setw(18)<<right<<"NO"<<setw(2)<<" ";
        }else {
            output<<setw(20)<<right<<arrDescuentoAlCliente[i];
        }

        output<<setw(20)<<right<<arrTotalIngresadoPlatos[i]<<endl;

        totalCantidad+=arrTotalCantPlatos[i];
        totalMontoVendido+=arrMontoVendido[i];
        totalDescuentoAlPlato+=arrDescuentoAlPlato[i];
        totalDescuentoAlCliente+=arrDescuentoAlCliente[i];
        totalGlobalIngresado+=arrTotalIngresadoPlatos[i];
    }
    imprimirResumenPlato(output,totalCantidad,totalMontoVendido,totalDescuentoAlPlato,
                        totalDescuentoAlCliente,totalGlobalIngresado);
}

void imprimirResumenPlato(ofstream& output,int totalCantidad,double totalMontoVendido,double totalDescuentoAlPlato,
                        double totalDescuentoAlCliente,double totalGlobalIngresado) {
    imprimirLineas('-',215,output);
    output<<"TOTALES OBTENIDOS:";
    output<<setw(114)<<right<<totalCantidad;
    output<<setw(20)<<right<<totalMontoVendido;
    output<<setw(20)<<right<<totalDescuentoAlPlato;
    output<<setw(20)<<right<<totalDescuentoAlCliente;
    output<<setw(20)<<right<<totalGlobalIngresado<<endl;
    imprimirLineas('=',215,output);
}

void imprimirCabeceraReportePlatos(ofstream &output) {
    output<<setw(90)<<" "<<"EMPRESA DE REPARTOS A DOMICILIO TP S. A."<<endl;
    output<<setw(100)<<" "<<"ENTREGAS POR PLATOS"<<endl;
    imprimirLineas('=',215,output);
    output<<setw(151)<<right<<"MONTO";
    output<<setw(21)<<right<<"DESCUENTO";
    output<<setw(20)<<right<<"DESCUENTO";
    output<<setw(18)<<right<<"TOTAL"<<endl;
    output<<"CODIGO";
    output<<setw(15)<<right<<"DESCRIPCION";
    output<<setw(48)<<right<<"CATEGORIA";
    output<<setw(22)<<right<<"PRECIO";
    output<<setw(23)<<right<<"DESCUENTO";
    output<<setw(21)<<right<<"CANTIDAD";
    output<<setw(17)<<right<<"VENDIDO";
    output<<setw(20)<<right<<"AL PLATO";
    output<<setw(20)<<right<<"AL CLIENTE";
    output<<setw(20)<<right<<"INGRESADO"<<endl;
    imprimirLineas('-',215,output);
}

int buscarPlato(int codigoPlato,int *arrCodigoPlato,int cantPlatos) {
    for (int i=0;i<cantPlatos;i++)
        if (codigoPlato==arrCodigoPlato[i]) return i;
    return NO_ENCONTRADO;
}

double calcularPagoRep(char *vehiculoRep) {
    if (strcmp(vehiculoRep,"MOTOCICLETA")==0) return 10.0;
    if (strcmp(vehiculoRep,"BICICLETA")==0) return 5.0;
    return 0.0;
}

void ignorar(ifstream&input,char delimitador) {
    char c;
    input>>ws;
    while (true) {
        c=input.get();
        if (c==delimitador) break;
    }
}

int buscarRepartidor(int *arrCodigoDistrito,char **arrTipoVehiculo,
                    int codigoDistrito,char *vehiculoRep,int cantRepartidores) {
    for (int i=0;i<cantRepartidores;i++)
        if (arrCodigoDistrito[i]==codigoDistrito and
            strcmp(arrTipoVehiculo[i],vehiculoRep)==0) return i;
    return NO_ENCONTRADO;
}

void swapInt(int& a,int &b) {
    int aux=a;
    a=b;
    b=aux;
}

void swapDouble(double&a,double&b) {
    double aux=a;
    a=b;
    b=aux;
}

void swapString(char*&a,char*&b) {
    char* aux=a;
    a=b;
    b=aux;
}


void imprimirSubRepPruebaPlatos(ofstream &output) {
    //73428       TEQUENOS       19.50       APERITIVO
    //11283   2_BOLAS_DE_HELADO      14.90   POSTRES    17.72%
    imprimirLineas('=',150,output);
    output<<setw(50)<<" "<<"REPORTE DE PRUEBA PARA PLATOS"<<endl;
    imprimirLineas('=',150,output);
    output<<setw(11)<<right<<"CODIGO";
    output<<setw(20)<<right<<"DESCRIPCION";
    output<<setw(50)<<right<<"PRECIO";
    output<<setw(18)<<right<<"CATEGORIA";
    output<<setw(34)<<right<<"DESCUENTO"<<endl;
    imprimirLineas('-',150,output);
}

void imprimirSubRepPruebaRep(ofstream &output) {
    //54805724   Vizcardo_Sinche_Maribel     Motocicleta      4826   Santa_Rosa
    imprimirLineas('=',150,output);
    output<<setw(50)<<" "<<"REPORTE DE PRUEBA PARA REPARTIDORES"<<endl;
    imprimirLineas('=',150,output);
    output<<setw(5)<<right<<"DNI";
    output<<setw(19)<<right<<"NOMBRE";
    output<<setw(62)<<right<<"VEHICULO";
    output<<setw(25)<<right<<"CODIGO DISTRITO";
    output<<setw(27)<<right<<"NOMBRE DISTRITO"<<endl;
    imprimirLineas('-',150,output);
}

char *leerString(ifstream& input) {
    char *str,buffer[MAX_CARACTERES];
    //lectura del buffer:
    input>>buffer;
    if (input.eof()) return nullptr;
    //reserva de memoria dinamica
    str=new char[strlen(buffer)+1];
    strcpy(str,buffer);
    return str;
}

void modificarCadena(char *cadena,bool nombreRep,bool tipoVeh,bool distrito) {
    if (nombreRep or distrito) {
        formato1(cadena);//para poder pasar de 'DIEGO_REYES' --> 'DIEGO REYES'
        formato2(cadena);//DIEGO REYES--> Diego Reyes
    }

    if (tipoVeh) {
        formato3(cadena); //Diego -->DIEGO
    }
}


void formato3(char *cadena) {
    for (int i=0;cadena[i];i++) {
        if (cadena[i]>='a' and cadena[i]<='z') {
            cadena[i]-='a'-'A';
        }
    }
}

void formato2(char *cadena) {
    bool esPrimero=true;
    for (int j=0;cadena[j];j++) {
        if (esPrimero) {
            if (cadena[j]>='a' and cadena[j]<='z') {
                cadena[j]-='a'-'A';
            }
            esPrimero=false;
        }else {
            if (cadena[j]==' ') {
                esPrimero=true;
            }else if (cadena[j]>='A' and cadena[j]<='Z') {
                cadena[j]+='a'-'A';
            }
        }
    }
}

void formato1(char * cadena) {
    for (int i=0;cadena[i];i++) {
        if (cadena[i]=='_') cadena[i]=' ';
    }
}
void imprimirSubRepartidores(ofstream&output) {
    output<<"REPORTE DE PRUENA PARA REPARTIDORES"<<endl;
    imprimirLineas('=',100,output);

}

void imprimirSubPlatos(ofstream&output) {

}

void imprimirLineas(char c,int cant,ofstream&output) {
    for (int i=0;i<cant;i++) output<<c;
    output<<endl;
}

