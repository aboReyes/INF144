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


void generarReporte(const char* nombArchClientes,
                    const char* nombArchPlatosOfrecidos,
                    const char* nombArchRepartidores,
                    const char* nombArchRepartosARealizar,
                    const char* nombArchReporte) {
    ifstream archClientes,archPlatOfrec,archRepartidores,archRepaRealizar;
    ofstream archReporte;

    aperturaArchivoLectura(nombArchClientes,archClientes);
    aperturaArchivoLectura(nombArchPlatosOfrecidos,archPlatOfrec);
    aperturaArchivoLectura(nombArchRepartidores,archRepartidores);
    aperturaArchivoLectura(nombArchRepartosARealizar,archRepaRealizar);
    aperturaArchivoEscritura(nombArchReporte,archReporte);

    int dniCliente,codeDistrito;
    char tipoVehiculo;
    double descuento;
    imprimirTitulo(archReporte);
    archReporte<<fixed<<setprecision(2);
    while (true) {
        leerImprimirInformeCliente(archClientes,archPlatOfrec,
                                archRepartidores,archRepaRealizar,
                                archReporte,dniCliente,codeDistrito,
                                tipoVehiculo,descuento);
        if (archClientes.eof()) break;
    }
}

void leerImprimirInformeCliente(ifstream& archClientes,ifstream& archPlatOfrec,
                                ifstream& archRepartidores,ifstream& archRepaRealizar,
                                ofstream& archReporte,int &dniCliente,int &codeDistrito,
                                char &tipoVehiculo,double &descuento) {
    //90367684   CORONEL CHUMPITAZ HELI]   8594   Villa_Maria_del_Triunfo   M  varia  S   13.04%
    double descuentoCliente;
    char tieneDescuento;
    double subtotalPorCliente = 0.0, descuentosPorCliente = 0.0;
    while (true) {
        archClientes>>dniCliente;
        if (archClientes.eof()) break;
        subtotalPorCliente   = 0.0;
        descuentosPorCliente = 0.0;
        archReporte<<"CLIENTE: "<<dniCliente<<" - ";
        leerImprimirNombresVariados(archClientes,archReporte,']',35,true);
        archClientes>>codeDistrito;
        archReporte<<"DISTRITO: ";
        leerImprimirNombresVariados(archClientes,archReporte,' ',25,false);
        archClientes>>tipoVehiculo;
        filtrarTipoVehiculo(tipoVehiculo,archReporte);
        archReporte<<setw(15)<<right << "DESCUENTO: ";
        archClientes>>tieneDescuento;
        descuentoCliente=verificarDescuento(archClientes,archReporte,tieneDescuento);
        imprimirLineas('-',150,archReporte);
        archReporte<<"REPARTOS: "<<endl;
        imprimirLineas('-',150,archReporte);
        int cantPedidos=0;
        buscarRepartosARealizar(archRepaRealizar,archPlatOfrec,archReporte,
                                dniCliente,cantPedidos,
                                subtotalPorCliente,descuentosPorCliente);
        buscarRepartidor(archRepartidores,archReporte,tipoVehiculo,codeDistrito);
        imprimirResumen(archReporte,subtotalPorCliente,descuentosPorCliente,descuentoCliente,tipoVehiculo);
        imprimirLineas('=',150,archReporte);
    }
}

void imprimirResumen(ofstream& archRep,double subtotalPorCliente,double descuentosPorCliente,
                    double descuentoCliente,char tipoVehiculo) {
    archRep<<setw(5)<<" "<<"TOTAL PEDIDO SIN DESCUENTOS:"<<setw(25)<<right<<subtotalPorCliente<<endl;
    archRep<<setw(5)<<" "<<"DESCUENTO TOTAL POR PLATOS:"<<setw(26)<<right<<descuentosPorCliente<<endl;
    double descuentoClienteRep=descuentoCliente/100.0*subtotalPorCliente;
    archRep<<setw(5)<<" "<<"DESCUENTO DEL CLIENTE:"<<setw(31)<<right<<descuentoClienteRep<<endl;
    double totalPagadoCliente=subtotalPorCliente-descuentosPorCliente-descuentoClienteRep;
    archRep<<setw(5)<<" "<<"TOTAL PAGADO POR EL CLIENTE:"<<setw(25)<<right<<totalPagadoCliente<<endl;
    double verificarDescuentoVeh=verificarDescuentoPorVeh(tipoVehiculo);
    double pagoRepartidor=verificarDescuentoVeh*totalPagadoCliente;
    archRep<<setw(5)<<" "<<"PAGO AL REPARTIDOR:"<<setw(34)<<right<<pagoRepartidor<<endl;
}

double verificarDescuentoPorVeh(char tipoVehiculo) {
    if (tipoVehiculo=='M') {
        return 0.1;
    }else if (tipoVehiculo=='B') {
        return 0.05;
    }
    return 0;
}

void buscarRepartosARealizar(ifstream& archRepaRealizar,ifstream& archPlatOfrec,ofstream& archRep,
                            int dniCliente,int &cantPedidos,
                            double &subtotalPorCliente,double &descuentosPorCliente) {
    //961419   77324146   9   53764   4   90766   1   90758
    int codePedido,dniClienteArch,cantidadPlato,codePlato;
    archRepaRealizar.clear();
    archRepaRealizar.seekg(0,ios::beg);
    while (true) {
        archRepaRealizar>>codePedido;
        if (archRepaRealizar.eof()) break;
        archRepaRealizar>>dniClienteArch;
        if (dniClienteArch==dniCliente) {
            cantPedidos++;
            imprimirOrden(archRep,cantPedidos,true);
            archRep<<setw(10)<<right<<"PEDIDO: "<<setw(8)<<right<<codePedido<<endl;
            imprimirSubtituloRepartos(archRep);
            int cantPlatos=0;
            while (true) {
                archRepaRealizar>>cantidadPlato>>codePlato;
                buscarPlatosOfrecidos(archPlatOfrec,archRep,cantidadPlato,codePlato,cantPlatos,
                                    subtotalPorCliente,descuentosPorCliente);
                if (archRepaRealizar.get()=='\n') break;
            }
            imprimirLineas('-',150,archRep);
        }else {
            while (archRepaRealizar.get()!='\n');
        }
    }
}

void buscarPlatosOfrecidos(ifstream& archPlatOfrec,ofstream &archRep,
                            int cantidadPlato,int codePlato,int &cantPlatos,
                            double &subtotalPorCliente,double &descuentosPorCliente) {
    //31796 ANTICUCHO DE CORAZON AL PLATO}   31.90   43   19.94%  -->caso descuento
    //15823   1/4 POLLO BBQ/HOT ENCAMOTADO}   36.90   84 -->caso sin descuento
    int codePlatoArch,cantPlatosOfrecidos;
    double precioPlato,descuentoPlato,subtotal,calcularDescuento;
    char c;
    archPlatOfrec.clear();
    archPlatOfrec.seekg(0,ios::beg);
    while (true) {
        archPlatOfrec>>codePlatoArch;
        if (archPlatOfrec.eof()) break;
        subtotal = 0.0;
        calcularDescuento = 0.0;
        if (codePlato==codePlatoArch) {
            cantPlatos++;
            archRep<<setw(4)<<" "; imprimirOrden(archRep,cantPlatos,false);
            archRep<<setw(7)<<right<<codePlatoArch<<" - ";
            leerImprimirNombresVariados(archPlatOfrec,archRep,'}',50,true);
            archPlatOfrec>>precioPlato>>cantPlatosOfrecidos;
            archRep<<setw(5)<<right<<cantidadPlato<<setw(15)<<precioPlato;
            subtotal=precioPlato*cantidadPlato;
            archRep<<setw(13)<<right<<subtotal;
            if (archPlatOfrec.get()!='\n') {
                archPlatOfrec>>descuentoPlato>>c;
                archRep<<setw(10)<<right<<descuentoPlato<<"% - ";
                calcularDescuento=(descuentoPlato/100.0)*subtotal;
                archRep<<setw(5)<<right<<calcularDescuento<<endl;
            }else {
                archRep<<setw(15)<<right<<"-----"<<endl;;
            }
        }else {
            while (archPlatOfrec.get()!='\n');
        }
        descuentosPorCliente+=calcularDescuento;
        subtotalPorCliente+=subtotal;
    }
}

void imprimirSubtituloRepartos(ofstream& archRep) {
    archRep<<setw(18)<<right<<"PLATO";
    archRep<<setw(57)<<right<<"CANTIDAD";
    archRep<<setw(12)<<right<<"PRECIO";
    archRep<<setw(13)<<right<<"SUBTOTAL";
    archRep<<setw(17)<<right<<"DESCUENTO"<<endl;
}

void imprimirOrden(ofstream& archRep,int nroOrden,bool conCero) {
    if (conCero) {
        archRep.fill('0');
        archRep<<setw(2)<<right<<nroOrden<<")";
        archRep.fill(' ');
    }else {
        archRep<<setw(2)<<right<<nroOrden<<")";
    }
}

void buscarRepartidor(ifstream& archRepartidores,ofstream& archReporte,
                        char tipoVehiculo,int codeDistrito){
    //54805724   Motocicleta   4826   Vizcardo_Sinche_Maribel
    int dniRepartidor,codeDistritoArch;
    char tipoVehiculoArch;
    archRepartidores.clear();
    archRepartidores.seekg(0,ios::beg);
    while (true) {
        archRepartidores>>dniRepartidor;
        if (archRepartidores.eof()) break;
        archRepartidores>>ws;
        tipoVehiculoArch=archRepartidores.get();
        ignorar(archRepartidores,' ');
        archRepartidores>>codeDistritoArch;
        if (tipoVehiculoArch==tipoVehiculo and codeDistritoArch==codeDistrito) {
            archReporte<<"REPARTIDOR: "<<dniRepartidor<<" - ";
            leerImprimirNombresVariados(archRepartidores,archReporte,
                                '\n',25,false);
            archReporte<<endl;
            imprimirLineas('-',150,archReporte);
        }else {
            while (archRepartidores.get()!='\n');
        }
    }
}

void ignorar(ifstream &input,char delimitador) {
    char c;
    while (true) {
        c=input.get();
        if (c==delimitador) break;
    }
}

double verificarDescuento(ifstream& input,ofstream& output,char tieneDescuento) {
    double descuento;
    char c;
    if (tieneDescuento=='S') {
        input>>descuento>>c;
        output<<setw(10)<<right<<descuento<<"%"<<endl;
        return descuento;
    }else if (tieneDescuento=='N'){
        output<<setw(10)<<"0.00%"<<endl;
        return 0;
    }
    return 0;
}


void filtrarTipoVehiculo(char tipoVehiculo,ofstream& archReporte) {
    if (tipoVehiculo == 'M')  archReporte<<setw(20)<<"Motocicleta";
    else if (tipoVehiculo == 'B') archReporte<<setw(20)<<"Bicicleta";
}

void leerImprimirNombresVariados(ifstream& input,ofstream& output,
                            char delimitador,int tam,bool mayus) {
    int cantEspaciosBlanco=0;
    char c,primerCar;
    input>>ws;
    while (true) {
        c=input.get();
        if (c==delimitador) break;
        if (c=='_') c=' ';
        if (mayus) {
            if (c>='a' and c<='z') c-='a'-'A';
        }
        output<<c;
        cantEspaciosBlanco++;
    }
    output<<setw(tam-cantEspaciosBlanco)<<" ";
}


void imprimirTitulo(ofstream &archRep) {
    archRep<<setw(55)<<" "<<"EMPRESA DE REPARTOS A DOMICILIO TP S. A."<<endl;
    archRep<<setw(65)<<" "<<"CLIENTES POR ATENDER"<<endl;
    imprimirLineas('=',150,archRep);
}

void imprimirLineas(char c,int cant,ofstream& archRep) {
    for (int i=0;i<cant;i++) archRep<<c;
    archRep<<endl;
}
