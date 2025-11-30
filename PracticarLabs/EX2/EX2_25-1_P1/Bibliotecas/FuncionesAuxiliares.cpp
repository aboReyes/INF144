//
// Created by ASUS on 30/11/2025.
//

#include "FuncionesAuxiliares.h"

void aperturaArchivoLectura(const char* nombArch,ifstream& arch) {
    arch.open(nombArch, ios::in);
    if (not arch.is_open()) {
        cout<<"Error al abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
}

void aperturaArchivoEscritura(const char* nombArch,ofstream& arch) {
    arch.open(nombArch, ios::out);
    if (not arch.is_open()) {
        cout<<"Error al abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
}

void leerConductores(const char* nombArch,Conductor *conductores,int &cantidadConductores) {
    //95822412,Lucia,Garcia,C5506
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    int dniConductor;
    while (true) {
        dniConductor=leerEntero(input);
        if (input.eof()) break;
        conductores[cantidadConductores].dni=dniConductor;
        conductores[cantidadConductores].nombre=leerCadenaExacta(input,',',50);
        conductores[cantidadConductores].apellido=leerCadenaExacta(input,',',50);
        conductores[cantidadConductores].licencia=leerCadenaExacta(input,'\n',50);
        //Inicializaciones:
        conductores[cantidadConductores].infracciones=new Infraccion[10]{};
        conductores[cantidadConductores].cantidadInfracciones=0;
        cantidadConductores++;
    }
}

void leerVehiculos(const char* nombArch,Vehiculo *vehiculos,int& cantidadVehiculos) {
    //10076758,GCU985,Fiat Uno
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    int dniPropVeh;
    while (true) {
        dniPropVeh=leerEntero(input);
        if (input.eof()) break;
        vehiculos[cantidadVehiculos].dniPropietario=dniPropVeh;
        vehiculos[cantidadVehiculos].placa=leerCadenaExacta(input,',',30);
        vehiculos[cantidadVehiculos].marcaModelo=leerCadenaExacta(input,'\n',50);
        cantidadVehiculos++;
    }
}

void leerInfracciones(const char* nombArch,Infraccion *infracciones,int &cantidadInfracciones) {
    //45059710,1/05/2025,B2,HABLAR CELULAR,Leve,150
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    int dniInfraccion;
    while (true) {
        dniInfraccion=leerEntero(input);
        if (input.eof())break;
        infracciones[cantidadInfracciones].dniConductor=dniInfraccion;
        infracciones[cantidadInfracciones].fechaInfraccion.aammdd=leerFecha(input);
        infracciones[cantidadInfracciones].codigo=leerCadenaExacta(input,',',10);
        infracciones[cantidadInfracciones].descripcion=leerCadenaExacta(input,',',100);
        infracciones[cantidadInfracciones].gravedad=leerCadenaExacta(input,',',20);
        infracciones[cantidadInfracciones].monto=leerDouble(input);
        procesarInfraccion(infracciones[cantidadInfracciones]);
        cantidadInfracciones++;
    }
}

void procesarInfraccion(Infraccion &infraccion) {
    for (int i=0;infraccion.codigo[i];i++) {
        if (infraccion.codigo[i]=='C') {
            infraccion.monto+=infraccion.monto*0.2;
            break;
        }
    }
}

void actualizarInformaciones(Conductor *conductores,int cantidadConductores,
                            Vehiculo *vehiculos,int cantidadVehiculos,
                            Infraccion *infracciones,int cantidadInfracciones) {
    //Conductores:
    for (int i=0;i<cantidadConductores;i++) {
        for (int j=0;j<cantidadVehiculos;j++) {
            if (conductores[i].dni==vehiculos[j].dniPropietario) {
                conductores[i].vehiculo.dniPropietario=vehiculos[j].dniPropietario;
                conductores[i].vehiculo.marcaModelo=asignarCadena(vehiculos[j].marcaModelo);
                conductores[i].vehiculo.placa=asignarCadena(vehiculos[j].placa);
                break; //solo puede haber un vehículo para cada conductor
            }
        }
        for (int k=0;k<cantidadInfracciones;k++) {
            if (conductores[i].dni==infracciones[k].dniConductor) {
                int n=conductores[i].cantidadInfracciones;
                conductores[i].infracciones[n].fechaInfraccion.aammdd=infracciones[k].fechaInfraccion.aammdd;
                conductores[i].infracciones[n].codigo=asignarCadena(infracciones[k].codigo);
                conductores[i].infracciones[n].descripcion=asignarCadena(infracciones[k].descripcion);
                conductores[i].infracciones[n].gravedad=asignarCadena(infracciones[k].gravedad);
                conductores[i].infracciones[n].monto=infracciones[k].monto;
                conductores[i].infracciones[n].dniConductor=infracciones[k].dniConductor;
                conductores[i].cantidadInfracciones++;
            }
        }
    }
}

void generarEnlace(char* nombre,char* apellido,char* licencia,char* &enlace) {
    char formato[200];
    strcpy(formato,"papeletas/");
    strcat(formato,apellido); //Castro
    strcat(formato,nombre);   //CastroPaula
    strcat(formato,licencia); //CastroPaulaC7543
    strcat(formato,".txt"); //CastroPaulaC7543.txt
    enlace=new char[strlen(formato)+1];
    strcpy(enlace,formato);
}

void emitirPapeletas(Conductor *conductores,int cantidadConductores) {
    char* enlace[MAX_CONDUCTORES]{};
    for (int i=0;i<cantidadConductores;i++) {
        generarEnlace(conductores[i].nombre,conductores[i].apellido,
                        conductores[i].licencia,enlace[i]);
        ofstream output;
        aperturaArchivoEscritura(enlace[i],output);
        output<<fixed<<setprecision(2);
        for (int j=0;j<conductores[i].cantidadInfracciones;j++) {
            output<<"Fecha de Infraccion: ";
            imprimirFecha(output,conductores[i].infracciones[j].fechaInfraccion.aammdd);
            output<<endl;
            output<<endl;

            output<<"Conductor: "<<endl;
            output<<setw(2)<<" "<<setw(15)<<left<<"Nombres"<<": "<<conductores[i].nombre<<endl;
            output<<setw(2)<<" "<<setw(15)<<left<<"Apellidos"<<": "<<conductores[i].apellido<<endl;
            output<<setw(2)<<" "<<setw(15)<<left<<"DNI"<<": "<<conductores[i].dni<<endl;
            output<<setw(2)<<" "<<setw(15)<<left<<"Licencia"<<": "<<conductores[i].licencia<<endl;

            output<<endl;
            output<<"Conductor: "<<endl;
            output<<setw(2)<<" "<<setw(15)<<left<<"Placa"<<": "<<conductores[i].vehiculo.placa<<endl;
            output<<setw(2)<<" "<<setw(15)<<left<<"Marca/Modelo"<<": "<<conductores[i].vehiculo.marcaModelo<<endl;

            output<<endl;
            output<<"Infraccion: "<<endl;
            output<<setw(2)<<" "<<setw(15)<<left<<"Codigo"<<": "<<conductores[i].infracciones[j].codigo<<endl;
            output<<setw(2)<<" "<<setw(15)<<left<<"Descripcion"<<": "<<conductores[i].infracciones[j].descripcion<<endl;
            output<<setw(2)<<" "<<setw(15)<<left<<"Gravedad"<<": "<<conductores[i].infracciones[j].gravedad<<endl;

            output<<endl;
            output<<"Monto a Pagar:"<<" S/ "<<setw(7)<<right<<conductores[i].infracciones[j].monto<<endl;
            output<<endl;
        }
    }
}

double leerDouble(ifstream& input) {
    double d;
    input>>d;
    input.get();
    return d;
}

int leerEntero(ifstream& input) {
    int i;
    input>>i;
    input.get();
    return i;
}

void imprimirFecha(ofstream& output,int fecha) {
    int dd,mm,aa;
    aa=fecha/10000;
    fecha=fecha%10000;
    mm=fecha/100;
    fecha=fecha%100;
    dd=fecha;
    output.fill('0');
    output<<setw(2)<<right<<dd<<"/";
    output<<setw(2)<<right<<mm<<"/";
    output<<setw(4)<<right<<aa;
    output.fill(' ');
}

int leerFecha(ifstream& input) {
    int dd,mm,aa;
    char c;
    input>>dd>>c>>mm>>c>>aa;
    input.get();
    return aa*10000+mm*100+dd;
}

char* leerCadenaExacta(ifstream&input,char delimitador,int n) {
    char buffer[n];
    input.getline(buffer,n,delimitador);
    if (input.eof()) return nullptr;
    char* src=new char[strlen(buffer)+1];
    strcpy(src,buffer);
    return src;
}

char* asignarCadena(char* buffer) {
    char* src=new char[strlen(buffer)+1];
    strcpy(src,buffer);
    return src;
}
