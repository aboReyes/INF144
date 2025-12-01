//
// Created by ASUS on 30/11/2025.
//

#include "FuncionesAuxiliares.h"

#include <cmath>
#include <stop_token>

void aperturaArchivoLectura(const char* nombArch,ifstream& arch) {
    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"Error al abrir el archivo"<<nombArch<<endl;
        exit(1);
    }
}

void aperturaArchivoEscritura(const char* nombArch,ofstream& arch) {
    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout<<"Error al abrir el archivo"<<nombArch<<endl;
        exit(1);
    }
}

void leerLexicon(const char*nombArch,Palabra *lexicon,int &cantidadPalabras) {
    //rapido,1
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    char texto[100];
    while (true) {
        input.getline(texto,100,',');
        if (input.eof()) break;
        lexicon[cantidadPalabras].texto=asignarCadena(texto);
        lexicon[cantidadPalabras].polaridad=leerEntero(input);
        cantidadPalabras++;
    }
}

void leerPlatos(const char* nombArch,Plato *platos,int &cantidadPlatos) {
    //A3H6GJ,Causa de Atun,12.57
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    char codigoPlato[20];
    while (true) {
        input.getline(codigoPlato,20,',');
        if (input.eof()) break;
        platos[cantidadPlatos].codigo=asignarCadena(codigoPlato);
        platos[cantidadPlatos].nombre=leerCadenaExacta(input,',',100);
        platos[cantidadPlatos].precio=leerDouble(input);
        platos[cantidadPlatos].cantidad=0;
        cantidadPlatos++;
    }
}

void leerProcesarAtenciones(const char*nombArch,
                            Atencion *atenciones,int &cantidadAtenciones,
                            Plato *platos,int cantidadPlatos) {
    //415217 21:36 B959AG 2 FK25HJ 1 S92K8X 3
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    int nroAtencion,horaAtencion,cantPlato;
    char codigoPlatoLeido[40];
    while (true) {
        input>>nroAtencion;
        if (input.eof()) break;
        horaAtencion=leerHora(input);
        atenciones[cantidadAtenciones].codigo=nroAtencion;
        atenciones[cantidadAtenciones].hora=horaAtencion;
        atenciones[cantidadAtenciones].cantidadPlatos=0;
        atenciones[cantidadAtenciones].totalVenta=0.0;
        atenciones[cantidadAtenciones].cantidadComentarios=0;
        atenciones[cantidadAtenciones].platosAtendidos=new Plato[20]{};
        atenciones[cantidadAtenciones].comentarios=new Comentario[20]{};
        while (true) {
            input.getline(codigoPlatoLeido,20,' ');
            input>>cantPlato;
            int posPlato=buscarPlato(codigoPlatoLeido,platos,cantidadPlatos);
            if (posPlato!=NO_ENCONTRADO) {
                int n=atenciones[cantidadAtenciones].cantidadPlatos;
                atenciones[cantidadAtenciones].platosAtendidos[n].codigo=asignarCadena(codigoPlatoLeido);
                atenciones[cantidadAtenciones].platosAtendidos[n].nombre=asignarCadena(platos[posPlato].nombre);
                atenciones[cantidadAtenciones].platosAtendidos[n].precio=platos[posPlato].precio;
                atenciones[cantidadAtenciones].platosAtendidos[n].cantidad=cantPlato;
                atenciones[cantidadAtenciones].totalVenta+=atenciones[cantidadAtenciones].platosAtendidos[n].precio*
                                                atenciones[cantidadAtenciones].platosAtendidos[n].cantidad;
                atenciones[cantidadAtenciones].cantidadPlatos++;
            }
            if (input.get()=='\n') break;
        }
        cantidadAtenciones++;
    }
}

int buscarPlato(char* codigoPlatoLeido,Plato *platos,int cantidadPlatos) {
    for (int i=0;i<cantidadPlatos;i++)
        if (strcmp(codigoPlatoLeido,platos[i].codigo)==0) return i;
    return NO_ENCONTRADO;
}

void leerComentarios(const char* nombArch,Atencion *atenciones,int cantidadAtenciones,
                    Palabra *lexicon,int cantidadPalabras) {
    //394386,"Los platos estuvieron muy ricos y sabrosos, el pedido fue rapido. ¡Volveria seguramente!"
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    int nroAtencion;
    char comentario[200];
    while (true) {
        nroAtencion=leerEntero(input);
        if (input.eof()) break;
        input.getline(comentario,200,'\n');
        char comentarioOriginal[200];
        strcpy(comentarioOriginal,comentario);
        int posAtencion=buscarAtencion(nroAtencion,atenciones,cantidadAtenciones);
        if (posAtencion!=NO_ENCONTRADO) {
            int n=atenciones[posAtencion].cantidadComentarios;
            atenciones[posAtencion].comentarios[n].texto=asignarCadena(comentarioOriginal);
            preProcesarComentario(comentario);
            atenciones[posAtencion].comentarios[n].preProcesado=asignarCadena(comentario);
            int polaridadTotal=procesarComentario(atenciones[posAtencion].comentarios[n].preProcesado,
                                                    lexicon,cantidadPalabras,
                                                    atenciones[posAtencion].comentarios[n]);
            atenciones[posAtencion].comentarios[n].polaridadTotal=polaridadTotal;
            atenciones[posAtencion].cantidadComentarios++;
        }
    }
}

int buscarAtencion(int nroAtencion,Atencion *atenciones,int cantidadAtenciones) {
    for (int i=0;i<cantidadAtenciones;i++)
        if (nroAtencion==atenciones[i].codigo) return i;
    return NO_ENCONTRADO;
}

int procesarComentario(char *comentario,Palabra *lexicon,int cantidadPalabras,
                        Comentario &comentarioStruct) {
    char buffer[200];
    strcpy(buffer,comentario);

    char* separador=strtok(buffer," "); //dios bendiga strtok
    int polaridadTotal=0;
    int index=0;
    while (separador!=nullptr and index<20) {
        int polaridad=buscarPolaridad(separador,lexicon,cantidadPalabras);
        polaridadTotal+=polaridad;
        comentarioStruct.palabras[index].texto=asignarCadena(separador);
        comentarioStruct.palabras[index].polaridad=polaridad;
        separador=strtok(nullptr," "); //siguiente palabra
        index++;
    }
    comentarioStruct.cantidadPalabras=index;
    return polaridadTotal;
}

int buscarPolaridad(char* separador,Palabra *lexicon,int cantidadPalabras) {
    for (int i=0;i<cantidadPalabras;i++)
        if (strcmp(separador,lexicon[i].texto)==0) return lexicon[i].polaridad;
    return 0;
}

void preProcesarComentario(char* comentario) {
    char c;
    int k=0;
    for (int i=0;comentario[i];i++) {
        c=comentario[i];
        if (isalpha(c) or c==' ') {
            comentario[k]=tolower(c);
            k++;
        }
    }
    comentario[k]='\0';
}

void emitirReporteAtenciones(const char* nombArch,
                             Atencion *atenciones,int cantidadAtenciones) {
    ofstream output;
    aperturaArchivoEscritura(nombArch,output);

    // Cabecera del reporte
    output << "EMPRESA DE REPARTOS A DOMICILIO TP S. A." << endl;
    output << "RELACION DE ATENCIONES" << endl;
    imprimirLineas(output,'=',100);

    for (int i = 0; i < cantidadAtenciones; i++) {

        // Cabecera de la atencion
        output << left << "No.  ATENCION " << atenciones[i].codigo;
        // alineamos la hora hacia la derecha
        output << setw(60 - (int)log10(atenciones[i].codigo) ) << " "
               << "Atendido a las: ";
        imprimirHora(output, atenciones[i].hora);
        output << endl;

        imprimirLineas(output,'-',100);

        // Detalle de platos atendidos
        for (int j = 0; j < atenciones[i].cantidadPlatos; j++) {
            Plato &p = atenciones[i].platosAtendidos[j];
            double subtotal = p.precio * p.cantidad;

            // Ejemplo de formato: CODIGO) NOMBRE .... PRECIO CANT SUBTOTAL
            output << left << setw(7) << p.codigo << ") ";
            output << left << setw(40) << p.nombre;
            output << right << fixed << setprecision(2)
                   << setw(10) << p.precio
                   << setw(6)  << p.cantidad
                   << setw(10) << subtotal
                   << endl;
        }

        // Polaridad total de los comentarios
        int sumaPolaridad = 0;
        for (int k = 0; k < atenciones[i].cantidadComentarios; k++) {
            sumaPolaridad += atenciones[i].comentarios[k].polaridadTotal;
        }

        output << "Polaridad total de los comentarios : "
               << setw(5) << sumaPolaridad << endl;

        imprimirLineas(output,'=',100);
    }
}

void imprimirLineas(ofstream &arch, char c, int n) {
    for (int i = 0; i < n; i++) arch.put(c);
    arch << endl;
}

int leerEntero(ifstream& input) {
    int i;
    input>>i;
    input.get();
    return i;
}

int leerHora(ifstream&input) {
    int mm,ss;
    char c;
    input>>mm>>c>>ss;
    input.get();
    return mm*60+ss;
}

void imprimirHora(ofstream& output,int hora) {
    int hh,mm,ss;
    hh=hora/3600;
    hora=hora%3600;
    mm=hora/60;
    hora=hora%60;
    ss=hora;
    output.fill('0');
    output<<setw(2)<<right<<hh<<":";
    output<<setw(2)<<right<<mm<<":";
    output<<setw(2)<<right<<ss;
    output.fill(' ');
}

double leerDouble(ifstream&input) {
    double d;
    input>>d;
    input.get();
    return d;
}

char* asignarCadena(char* buffer) {
    char* src=new char[strlen(buffer)+1];
    strcpy(src,buffer);
    return src;
}

char* leerCadenaExacta(ifstream& input,char delimitador,int n) {
    char buffer[n];
    input.getline(buffer,n,delimitador);
    if (input.eof()) return  nullptr;
    char* src=new char[strlen(buffer)+1];
    strcpy(src,buffer);
    return src;
}


