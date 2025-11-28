
//
// Created by aml on 21/11/2025.
//

#include "FuncionesAuxiliares.h"


void aperturaArchivoLectura(const char* nombArch,ifstream& arch) {
    arch.open(nombArch,ios::in);
    if(!arch.is_open()) {
        cout << "Error al abrir el archivo" << nombArch<<endl;
        exit(1);
    }
}

void aperturaArchivoEscritura(const char* nombArch,ofstream& arch) {
    arch.open(nombArch,ios::out);
    if(!arch.is_open()) {
        cout << "Error al abrir el archivo" << nombArch<<endl;
        exit(1);
    }
}

void leerLibros(const char* arch,
                Libro *arrLibros,int &cantidadLibros) {
    //QV96140,El Duque en su territorio,Fiorella Florencio Polo,12,37.47
    ifstream input;
    aperturaArchivoLectura(arch,input);
    char *codigoLibro;
    while (true) {
        codigoLibro=leerCadena(input,',',20);
        if (input.eof() or codigoLibro==nullptr) break;
        arrLibros[cantidadLibros].codigo=asignarCadena(codigoLibro);
        arrLibros[cantidadLibros].titulo=leerCadena(input,',',100);
        arrLibros[cantidadLibros].autor=leerCadena(input,',',100);
        arrLibros[cantidadLibros].cantidad=leerEntero(input);
        arrLibros[cantidadLibros].precio=leerDouble(input);
        arrLibros[cantidadLibros].usuarios=new UsuarioConElLibro[20];
        arrLibros[cantidadLibros].cantUsuarios=0;
        cantidadLibros++;
    }
}

void pruebaLibros(const char* nombArch,
                            Libro *arrLibros,int cantidadLibros,bool prestamo) {
    //QV96140,El Duque en su territorio,Fiorella Florencio Polo,12,37.47
    ofstream output;
    aperturaArchivoEscritura(nombArch,output);
    output<<setw(55)<<" "<<"REPORTE DE LIBROS"<<endl;
    imprimirLineas('=',130,output);
    output<<fixed<<setprecision(2);
    for (int i=0;i<cantidadLibros;i++) {
        imprimirCabeceraLibros(output);
        output<<setw(15)<<left<<arrLibros[i].codigo;
        output<<setw(35)<<left<<arrLibros[i].titulo;
        output<<setw(35)<<left<<arrLibros[i].autor;
        output<<setw(10)<<right<<arrLibros[i].precio;
        output<<setw(12)<<right<<arrLibros[i].cantidad;
        double subtotal=arrLibros[i].cantidad * arrLibros[i].precio;
        output<<setw(20)<<right<<subtotal<<endl;
        imprimirLineas('-',130,output);
        if (prestamo) {
            output<<"Dni Usuario";
            output<<setw(20)<<right<<"Fecha devolucion: "<<endl;
            for (int j=0;j<arrLibros[i].cantUsuarios;j++) {
                output<<setw(2)<<" "<<arrLibros[i].usuarios[j].dni;
                output<<setw(8)<<" ";
                imprimirFecha(output,arrLibros[i].usuarios[j].fechaDeDevolucion);
                output<<endl;
            }
            imprimirLineas('=',130,output);
        }
    }
}

void imprimirCabeceraLibros(ofstream& output) {
    output<<"Codigo";
    output<<setw(15)<<right<<"Titulo";
    output<<setw(34)<<right<<"Autor";
    output<<setw(40)<<right<<"Precio";
    output<<setw(15)<<right<<"Cantidad";
    output<<setw(18)<<right<<"Subtotal"<<endl;
}

void imprimirLineas(char c,int cant,ofstream& output) {
    for (int i=0;i<cant;i++) output<<c;
    output<<endl;
}

void leerUsuarios(const char* nombArch,
                Usuario *arrUsuarios,int &cantidadUsuarios) {
    //54393647,Reyes Tang Edward,V,13.00
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    int dni;
    while (true) {
        dni=leerEntero(input);
        if (input.eof()) break;
        arrUsuarios[cantidadUsuarios].dni=dni;
        arrUsuarios[cantidadUsuarios].nombre=leerCadena(input,',',100);
        arrUsuarios[cantidadUsuarios].categoria=leerChar(input);
        arrUsuarios[cantidadUsuarios].calificacion=leerDouble(input);
        arrUsuarios[cantidadUsuarios].libros=new LibroEnSuPoder[6];
        arrUsuarios[cantidadUsuarios].cantLibros=0;
        cantidadUsuarios++;
    }
}

void pruebaUsuarios(const char* nombArch,
                    Usuario *arrUsuarios,int cantidadUsuarios,bool prestamo) {
    //54393647,Reyes Tang Edward,V,13.00
    ofstream output;
    aperturaArchivoEscritura(nombArch,output);
    output<<setw(35)<<" "<<"REPORTE DE USUARIOS"<<endl;
    imprimirLineas('=',90,output);
    output<<fixed<<setprecision(2);
    imprimirCabeceraUsuarios(output);
    for (int i=0;i<cantidadUsuarios;i++) {
        output<<arrUsuarios[i].dni;
        output<<setw(4)<<" "<<setw(40)<<left<<arrUsuarios[i].nombre;
        output<<setw(10)<<right<<arrUsuarios[i].categoria;
        output<<setw(20)<<right<<arrUsuarios[i].calificacion<<endl;
        imprimirLineas('-',90,output);
        if (prestamo) {
            output<<"Codigo Libro";
            output<<setw(20)<<right<<"Fecha devolucion: "<<endl;
            for (int j=0;j<arrUsuarios[i].cantLibros;j++) {
                output<<setw(2)<<" "<<arrUsuarios[i].libros[j].codLibro;
                output<<setw(8)<<" ";
                imprimirFecha(output,arrUsuarios[i].libros[j].fechaDevolucion);
                output<<endl;
            }
            imprimirLineas('=',90,output);
        }
    }
}

void actualizarPrestamos(const char* nombArch,
                Libro *arrLibros,int cantidadLibros,Usuario *arrUsuarios,int cantidadUsuarios) {
    //QV96140
    //se repite: 17750908     3/07/2023     14500753     6/07/2023 ....
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    char* codigoLibro;
    int dniUsuario,fechaUsuario;
    while (true) {
        codigoLibro=leerCadena(input,' ',20);
        if (codigoLibro==nullptr or input.eof()) break;
        int posLibro=buscarCodigoLibro(codigoLibro,arrLibros,cantidadLibros);
        if (posLibro!=NO_ENCONTRADO) {
            while (true) {
                input>>dniUsuario;
                fechaUsuario=leerFecha(input);
                int posUsuario=buscarUsuario(dniUsuario,arrUsuarios,cantidadUsuarios);
                if (posUsuario!=NO_ENCONTRADO) {
                    //Para el caso de libros
                    int n=arrLibros[posLibro].cantUsuarios;
                    arrLibros[posLibro].usuarios[n].dni=dniUsuario;
                    arrLibros[posLibro].usuarios[n].fechaDeDevolucion=fechaUsuario;
                    arrLibros[posLibro].cantUsuarios++;

                    //Para el caso de usuarios
                    int j=arrUsuarios[posUsuario].cantLibros;
                    arrUsuarios[posUsuario].libros[j].codLibro=asignarCadena(codigoLibro);
                    arrUsuarios[posUsuario].libros[j].fechaDevolucion=fechaUsuario;
                    arrUsuarios[posUsuario].cantLibros++;
                }
                if (input.get()=='\n') break;
            }
        }else {
            while (input.get()!='\n');
        }

    }
}

void ordenarReporte(Libro *arrLibros,int cantidadLibros) {
    for (int i=0;i<cantidadLibros-1;i++) {
        for (int j=i+1;j<cantidadLibros;j++) {
            if (strcmp(arrLibros[i].codigo,arrLibros[j].codigo)>0) {
                SwapStruct(arrLibros[i],arrLibros[j]);
            }
        }
    }
}

void ordenarUsuarios(Libro &libros,int cantUsuarios) {
    for (int i=0;i<cantUsuarios;i++) {
        for (int j=i+1;j<cantUsuarios;j++) {
            UsuarioConElLibro &ui=libros.usuarios[i];
            UsuarioConElLibro &uj=libros.usuarios[j];
            if (libros.usuarios[i].fechaDeDevolucion<libros.usuarios[j].fechaDeDevolucion or
            libros.usuarios[i].fechaDeDevolucion==libros.usuarios[j].fechaDeDevolucion and
            libros.usuarios[i].dni>libros.usuarios[j].dni) {
                SwapStruct2(ui,uj);
            }
        }
    }
}

void SwapStruct2(UsuarioConElLibro&dato1,UsuarioConElLibro&dato2) {
    UsuarioConElLibro aux;
    aux=dato1;
    dato1=dato2;
    dato2=aux;
}

void SwapStruct(Libro &dato1,Libro &dato2) {
    Libro aux=dato1;
    dato1=dato2;
    dato2=aux;
}

int buscarUsuario(int dniUsuario,Usuario *arrUsuarios,int cantidadUsuarios) {
    for (int i=0;i<cantidadUsuarios;i++)
        if (dniUsuario==arrUsuarios[i].dni) return i;
    return NO_ENCONTRADO;
}

int buscarCodigoLibro(char *codigoLibro,Libro *arrLibros,int cantidadLibros){
    for (int i=0;i<cantidadLibros;i++)
        if (strcmp(codigoLibro,arrLibros[i].codigo)==0) return i;
    return NO_ENCONTRADO;
}

void imprimirCabeceraUsuarios(ofstream& output) {
    output<<"Dni";
    output<<setw(15)<<right<<"Nombre";
    output<<setw(48)<<right<<"Categoria";
    output<<setw(20)<<right<<"Calificacion"<<endl;
}

char leerChar(ifstream& input) {
    char c;
    input>>c;
    input.get();
    return c;
}


int leerFecha(ifstream& input) {
    int dd,mm,aa;
    char c;
    input>>dd>>c>>mm>>c>>aa;
    return aa*10000+mm*100+dd;
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
    output<<setw(2)<<right<<aa;
    output.fill(' ');
}

double leerDouble(ifstream& input) {
    double d;
    input >> d;
    input.get();
    return d;
}

int leerEntero(ifstream& input) {
    int i;
    input >> i;
    input.get();
    return i;
}

char* asignarCadena(char *fuente) {
    char* str=new char[strlen(fuente)+1];
    strcpy(str,fuente);
    return str;
}

char* leerCadena(ifstream& input,char delimitador,int n) {
    char buffer[n];
    input.getline(buffer,n,delimitador);
    if (input.eof()) return nullptr;
    char* str=new char[strlen(buffer)+1];
    strcpy(str,buffer);
    return str;
}
