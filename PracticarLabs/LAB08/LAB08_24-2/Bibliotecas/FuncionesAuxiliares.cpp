//
// Created by ASUS on 7/11/2025.
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

void leerPlatosOfrecidos(const char* nombArchPlatos,
                        Plato *arrPlatos,int &cantPlatos) {
    ////PO-11283,2 BOLAS DE HELADO,14.90,POSTRES
    ifstream input;
    aperturaArchivoLectura(nombArchPlatos,input);
    char codigoPlato[10],nombre[100],categoria[50];
    double precioPlato;
    while (true) {
        input.getline(codigoPlato,10,',');
        if (input.eof()) break;
        input.getline(nombre,100,',');
        precioPlato=readDouble(input);
        input.getline(categoria,50,'\n');
        strcpy(arrPlatos[cantPlatos].codigo,codigoPlato);
        strcpy(arrPlatos[cantPlatos].descripcion,nombre);
        strcpy(arrPlatos[cantPlatos].categoria,categoria);
        arrPlatos[cantPlatos].precio = precioPlato;
        arrPlatos[cantPlatos].cantidad=0; //despues se acumulará supongo
        cantPlatos++;
    }
}

void pruebaPlatosOfrecidos(const char* nombArchRep,
                        Plato *arrPlatos,int cantPlatos) {
    ofstream output;
    aperturaArchivoEscritura(nombArchRep,output);
    imprimirCabeceraPruebaPlatosOfrecidos(output);
    output<<fixed<<setprecision(2);
    for (int i=0;i<cantPlatos;i++) {
        output<<setw(10)<<right<<arrPlatos[i].codigo;
        output<<setw(5)<<" "<<setw(45)<<left<<arrPlatos[i].descripcion;
        output<<setw(10)<<right<<arrPlatos[i].precio;
        output<<setw(5)<<" "<<setw(15)<<left<<arrPlatos[i].categoria<<endl;
    }
}

int readInt(ifstream& input) {
    int i;
    input>>i;
    input.get(); //Para leer la coma
    return i;
}

double readDouble(ifstream& input) {
    double d;
    input>>d;
    input.get(); //Para leer la coma
    return d;
}

void imprimirCabeceraPruebaPlatosOfrecidos(ofstream& output) {
    output<<setw(30)<<" "<<"REPORTE PRUEBA PLATOS OFRECIDOS"<<endl;
    imprimirLineas('=',100,output);
    output<<setw(8)<<right<<"CODIGO";
    output<<setw(18)<<right<<"DESCRIPCION";
    output<<setw(45)<<right<<"PRECIO";
    output<<setw(13)<<right<<"CATEGORIA"<<endl;
    imprimirLineas('-',100,output);
}

void imprimirLineas(char c,int cant,ofstream& output) {
    for (int i=0;i<cant;i++) output<<c;
    output<<endl;
}

void leerDistritos(const char* nombArchDistritos,
                Distrito *arrDistritos,int &cantDistritos) {
    //LN3085,Ancon,NORTE
    ifstream input;
    aperturaArchivoLectura(nombArchDistritos,input);
    char codigo[20],nombre[50],ubicacion[20];
    while (true) {
        input.getline(codigo,20,',');
        if (input.eof()) break;
        input.getline(nombre,50,',');
        input.getline(ubicacion,20,'\n');
        strcpy(arrDistritos[cantDistritos].codigo,codigo);
        strcpy(arrDistritos[cantDistritos].nombre,nombre);
        strcpy(arrDistritos[cantDistritos].ubicacion,ubicacion);
        cantDistritos++;
    }
}

void pruebaDistritos(const char* nombArchRep,
                Distrito *arrDistritos,int cantDistritos) {
    ofstream output;
    aperturaArchivoEscritura(nombArchRep,output);
    imprimirCabeceraPruebaDistritos(output);
    for (int i=0;i<cantDistritos;i++) {
        output<<setw(8)<<right<<arrDistritos[i].codigo;
        output<<setw(5)<<" "<<setw(27)<<left<<arrDistritos[i].nombre;
        output<<setw(15)<<left<<arrDistritos[i].ubicacion<<endl;
    }
}

void imprimirCabeceraPruebaDistritos(ofstream &output) {
    output<<setw(15)<<" "<<"REPORTE PRUEBA DISTRITOS"<<endl;
    imprimirLineas('=',50,output);
    output<<setw(8)<<right<<"CODIGO";
    output<<setw(11)<<right<<"NOMBRE";
    output<<setw(28)<<right<<"UBICACION"<<endl;
    imprimirLineas('-',50,output);
}


void leerClientes(const char* nombArchClientes,
                Cliente *arrClientes,int &cantClientes,
                Distrito *arrDistritos, int cantDistritos) {
    //90367684,CORONEL CHUMPITAZ HELI,LO4328
    ifstream input;
    aperturaArchivoLectura(nombArchClientes,input);
    char nombreCliente[100],codigoDistrito[10];
    int dniCliente;
    while (true) {
        dniCliente=readInt(input);
        if (input.eof()) break;
        input.getline(nombreCliente,100,',');
        input.getline(codigoDistrito,10,'\n');
        arrClientes[cantClientes].dni=dniCliente;
        strcpy(arrClientes[cantClientes].nombre,nombreCliente);
        strcpy(arrClientes[cantClientes].distrito.codigo,codigoDistrito);
        int posDistrito=buscarDistrito(codigoDistrito,arrDistritos,cantDistritos);
        if (posDistrito!=NO_ENCONTRADO) {
            arrClientes[cantClientes].distrito = arrDistritos[posDistrito];
            /*
             *esto me sirve, pero el otro copia todos los datos, entonces ahorro líneas de codigo:u
            strcpy(arrClientes[cantClientes].distrito.nombre,arrDistritos[posDistrito].nombre);
            strcpy(arrClientes[cantClientes].distrito.ubicacion,arrDistritos[posDistrito].ubicacion);
            */
        }
        cantClientes++;
    }
}

int buscarDistrito(char* codigoDistrito,Distrito *arrDistritos,int cantDistritos) {
    for (int i=0;i<cantDistritos;i++)
        if (strcmp (codigoDistrito,arrDistritos[i].codigo)==0) return i;
    return NO_ENCONTRADO;
}

void pruebaClientes(const char* nombArchRep,
                Cliente *arrClientes,int cantClientes) {
    ofstream output;
    aperturaArchivoEscritura(nombArchRep,output);
    imprimirCabeceraPruebaClientes(output);
    for (int i=0;i<cantClientes;i++) {
        output<<setw(10)<<right<<arrClientes[i].dni;
        output<<setw(5)<<" "<<setw(40)<<left<<arrClientes[i].nombre;
        output<<setw(15)<<left<<arrClientes[i].distrito.codigo<<endl;
    }
}

void imprimirCabeceraPruebaClientes(ofstream &output) {
    output<<setw(25)<<" "<<"REPORTE PRUEBA CLIENTES"<<endl;
    imprimirLineas('=',70,output);
    output<<setw(5)<<right<<"DNI";
    output<<setw(16)<<right<<"NOMBRE";
    output<<setw(45)<<right<<"CODIGO DISTRITO"<<endl;
    imprimirLineas('-',70,output);
}

void procesarPedidosRealizados(const char* nombArchPedRe,
                            Plato *arrPlatos,int cantPlatos,
                            Distrito *arrDistritos,int cantDistritos,
                            Cliente *arrClientes,int cantClientes) {
    //117660      68114999        AP-73428       3
    ifstream input;
    aperturaArchivoLectura(nombArchPedRe,input);
    int codigoPedido,cantidadPedida,dniCliente;
    char codigoPlato[10];
    while (true) {
        input>>codigoPedido;
        if (input.eof()) break;
        input>>dniCliente>>codigoPlato>>cantidadPedida;
        int posCliente=buscarCliente(dniCliente,arrClientes,cantClientes);
        int posPlato=buscarPlato(codigoPlato,arrPlatos,cantPlatos);
        if (posCliente!=NO_ENCONTRADO and posPlato!=NO_ENCONTRADO) {
            insertarPedido(arrClientes[posCliente],arrPlatos[posPlato],
                            codigoPedido,cantidadPedida);
        }
    }
}

void insertarPedido(Cliente &clienteElegido,Plato &platoElegido,
                    int codigoPedido,int cantidadPedida) {
    int pos=clienteElegido.cantidadDePedidos; //es como decir pos=0


    //recordar que las igualdades son par int=int double=double
    //acumulaciones también PERO para los char[]=char[] es con el strcpy como vemos:
    //considerar que ahí ya con char** chambea el asignarStr de erasmo

    clienteElegido.pedidos[pos].codigoPedido=codigoPedido;
    clienteElegido.pedidos[pos].cantidad=cantidadPedida;
    clienteElegido.pedidos[pos].precio=platoElegido.precio;
    clienteElegido.pedidos[pos].subtotal=platoElegido.precio*cantidadPedida;

    strcpy(clienteElegido.pedidos[pos].codigoPlato,platoElegido.codigo);
    strcpy(clienteElegido.pedidos[pos].descripcion,platoElegido.descripcion);

    clienteElegido.montoTotal+=cantidadPedida*platoElegido.precio;
    platoElegido.cantidad+=cantidadPedida;

    clienteElegido.cantidadDePedidos++;
}

void ordenarClientes(Cliente *arrClientes,int cantClientes){
    //ascendentemente por el nombre del cliente
    for (int i=0;i<cantClientes-1;i++) {
        for (int j=i+1;j<cantClientes;j++) {
            if (strcmp(arrClientes[i].nombre,arrClientes[j].nombre)>0) {
                swapStructCliente(arrClientes[i],arrClientes[j]);
            }
        }
    }
}

void swapStructCliente(Cliente &cliente1,Cliente &cliente2) {
    Cliente temp=cliente1;
    cliente1=cliente2;
    cliente2=temp;
}

void ordenarPlatosPedidos(Cliente *arrCliente,int cantClientes) {
    //ascendentemente por el codigo del pedido
    //descendentemente por el codigo del plato
    //este es el for más pendejo que vi hasta el momento
    for (int k=0;k<cantClientes;k++) { //para cada cliente
        //el doble for de manual
        int n=arrCliente[k].cantidadDePedidos;
        for (int i=0;i<n-1;i++) {
            for (int j=i+1;j<n;j++) {
                if (arrCliente[k].pedidos[i].codigoPedido>arrCliente[k].pedidos[j].codigoPedido or
                    arrCliente[k].pedidos[i].codigoPedido==arrCliente[k].pedidos[j].codigoPedido and
                    strcmp(arrCliente[k].pedidos[i].codigoPlato,arrCliente[k].pedidos[j].codigoPlato)<0) {
                    swapStrucPlatoPedido(arrCliente[k].pedidos[i],arrCliente[k].pedidos[j]);
                }
            }
        }
    }
}

void swapStrucPlatoPedido(PlatoPedido &dato1,PlatoPedido &dato2) {
    PlatoPedido temp=dato1;
    dato1=dato2;
    dato2=temp;
}

void emitirReporte(const char* nombArchRep,
                Cliente *arrClientes,int cantClientes,
                Distrito *arrDistritos,int cantDistritos,
                Plato *arrPlatos,int cantPlatos) {
    ofstream output;
    aperturaArchivoEscritura(nombArchRep,output);

    imprimirTitulo(output);
    output<<fixed<<setprecision(2);
    for (int i=0;i<cantClientes;i++) {
        imprimirCabeceraCliente(output,i+1);
        output<<arrClientes[i].dni;
        output<<setw(5)<<" "<<setw(36)<<left<<arrClientes[i].nombre;
        output<<setw(10)<<left<<arrClientes[i].distrito.codigo;
        output<<setw(20)<<left<<arrClientes[i].distrito.nombre;
        output<<setw(17)<<right<<arrClientes[i].montoTotal<<endl;
        imprimirLineas('-',150,output);
        imprimirCabeceraPedidosRealizados(output);
        if (arrClientes[i].cantidadDePedidos>0) {
            imprimirPedidosRealizados(output,arrClientes[i].pedidos,
                                        arrClientes[i].cantidadDePedidos,
                                        arrPlatos,cantPlatos);
        }
        imprimirLineas('=',150,output);
    }
}

void imprimirPedidosRealizados(ofstream &output,PlatoPedido *platoPedido,
                                int cantPlatoPedido,
                                Plato *arrPlatos,int cantPlatos) {
    for (int i=0;i<cantPlatoPedido;i++) {
        int posPlato=buscarPlato(platoPedido[i].codigoPlato,arrPlatos,cantPlatos);
        output<<setw(13)<<" ";
        output.fill('0');
        output<<setw(3)<<i+1;
        output.fill(' ');
        output<<setw(10)<<right<<platoPedido[i].codigoPedido;
        output<<setw(5)<<" "<<setw(15)<<left<<platoPedido[i].codigoPlato;
        output<<setw(50)<<left<<platoPedido[i].descripcion;
        if (posPlato!=NO_ENCONTRADO) {
            output<<setw(15)<<left<<arrPlatos[posPlato].categoria;
        }
        output<<setw(10)<<right<<platoPedido[i].precio;
        output<<setw(10)<<right<<platoPedido[i].cantidad;
        output<<setw(15)<<right<<platoPedido[i].subtotal<<endl;
    }
}

int buscarPlato(char * codigoPlato,Plato *arrPlatos,int cantPlatos){
    for (int i=0;i<cantPlatos;i++)
        if (strcmp(codigoPlato,arrPlatos[i].codigo)==0) return i;
    return NO_ENCONTRADO;
}

void imprimirCabeceraPedidosRealizados(ofstream &output) {
    output<<setw(33)<<right<<"PEDIDOS REALIZADOS: "<<endl;
    output<<setw(17)<<right<<"NO. ";
    output<<setw(9)<<right<<"PEDIDO";
    output<<setw(11)<<right<<"CODIGO";
    output<<setw(20)<<right<<"DESCRIPCION";
    output<<setw(48)<<right<<"CATEGORIA";
    output<<setw(17)<<right<<"PRECIO";
    output<<setw(13)<<right<<"CANTIDAD";
    output<<setw(12)<<right<<"SUBTOTAL"<<endl;
}

void imprimirCabeceraCliente(ofstream &output,int nroOrden) {
    output.fill('0');
    output<<"CLIENTE No. "<<setw(3)<<right<<nroOrden;
    output.fill(' ');
    output<<endl;
    output<<"DNI";
    output<<setw(16)<<right<<"NOMBRE";
    output<<setw(38)<<right<<"DISTRITO";
    output<<setw(40)<<right<<"PAGO TOTAL"<<endl;
}

void imprimirTitulo(ofstream &output) {
    output<<setw(50)<<" "<<"EMPRESA DE REPARTOS A DOMICILIO TP S. A."<<endl;
    output<<setw(55)<<" "<<"RELACION DE PEDIDOS POR CLIENTE"<<endl;
    imprimirLineas('=',150,output);
}

int buscarCliente(int dniCliente,Cliente *arrClientes,int cantClientes){
    for (int i=0;i<cantClientes;i++)
        if (dniCliente==arrClientes[i].dni) return i;
    return NO_ENCONTRADO;
}
