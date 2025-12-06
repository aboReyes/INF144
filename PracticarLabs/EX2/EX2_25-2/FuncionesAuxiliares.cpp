//
// Created by DIEGO on 05/12/2025.
//

#include "FuncionesAuxiliares.h"

void aperturaArchivoLectura(const char* nombArch,ifstream& arch) {
    arch.open(nombArch,ios::in);
    if (not arch.is_open() ) {
        cout<<"Error, no se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
}


void aperturaArchivoEscritura(const char* nombArch,ofstream& arch) {
    arch.open(nombArch,ios::out);
    if (not arch.is_open() ) {
        cout<<"Error, no se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
}

void cargarTransmisiones(const char* nombArch,Transmision *transmisiones,int &cantidadTransmisiones) {
    //5002,194,03-06-2025,279
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    int id_transmision;
    while (true) {
        id_transmision = leerEntero(input);
        if (input.eof()) break;
        transmisiones[cantidadTransmisiones].id_transmision=id_transmision;
        transmisiones[cantidadTransmisiones].streamer.id_streamer=leerEntero(input);
        transmisiones[cantidadTransmisiones].fecha=leerFecha(input);
        transmisiones[cantidadTransmisiones].duracion=leerEntero(input);

        //Inicializaciones:
        transmisiones[cantidadTransmisiones].comentarios=new Comentario[10]{};
        transmisiones[cantidadTransmisiones].cantidad_comentarios=0;
        cantidadTransmisiones++;
    }
}

void cargarStreamers(const char* nombArch,Transmision *transmisiones,int cantidadTransmisiones) {
    //754,retromonk68,dota2,483748
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    int id_streamer,cantSeguidores;
    char nombreStreamer[100],categoriaStreamer[100];
    while (true) {
        id_streamer = leerEntero(input);
        if (input.eof()) break;
        input.getline(nombreStreamer,100,',');
        input.getline(categoriaStreamer,100,',');
        cantSeguidores=leerEntero(input);
        for (int i=0;i<cantidadTransmisiones;i++) {
            //int posStreamer=buscarStreamer(id_streamer,transmisiones,cantidadTransmisiones);
            //if (posStreamer!=NO_ENCONTRADO) {
                transmisiones[i].streamer.nombre_canal=asignarCadena(nombreStreamer);
                transmisiones[i].streamer.categoria=asignarCadena(categoriaStreamer);
                transmisiones[i].streamer.cantidad_seguidores=cantSeguidores;
            //}
        }
    }
}

int buscarStreamer(int id_streamer,Transmision *transmisiones,int cantidadTransmisiones) {
    for (int i=0;i<cantidadTransmisiones;i++)
        if (transmisiones[i].streamer.id_streamer==id_streamer) return i;
    return NO_ENCONTRADO;
}

void cargarComentarios(const char* nombArch,Transmision *transmisiones,int cantidadTransmisiones) {
    //2232,sir_spamless,"La explicacion estuvo clarisima, gracias."
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    int idTransmision;
    char comentador[100],comentarioOriginal[200];
    while (true) {
        idTransmision = leerEntero(input);
        if (input.eof()) break;
        input.getline(comentador,100,',');
        input.getline(comentarioOriginal,250,'\n');
        int posComentario=buscarComentarios(idTransmision,transmisiones,cantidadTransmisiones);
        if (posComentario!=NO_ENCONTRADO) {
            int n=transmisiones[posComentario].cantidad_comentarios;
            transmisiones[posComentario].comentarios[n].id_transmision=idTransmision;
            transmisiones[posComentario].comentarios[n].comentador=asignarCadena(comentador);
            transmisiones[posComentario].comentarios[n].comentario_original=asignarCadena(comentarioOriginal);
            transmisiones[posComentario].comentarios[n].comentario_pre_procesado=
                preProcesarComentario(transmisiones[posComentario].comentarios[n].comentario_original);
            transmisiones[posComentario].cantidad_comentarios++;
        }
    }
}

char* preProcesarComentario(char* comentarioOriginal) {
    int k=0;
    char bufferPreProcesado[200];
    for (int i=0;comentarioOriginal[i];i++) {
        if (comentarioOriginal[i]>='a' and comentarioOriginal[i]<='z' or
            comentarioOriginal[i]>='A' and comentarioOriginal[i]<='Z' or
            comentarioOriginal[i]=='/' or comentarioOriginal[i]==' ' ) {
            if (comentarioOriginal[i]>='A' and comentarioOriginal[i]<='Z') comentarioOriginal[i]+=32;
            bufferPreProcesado[k]=comentarioOriginal[i];
            k++;
        }
    }
    bufferPreProcesado[k]='\0';
    comentarioOriginal=asignarCadena(bufferPreProcesado);
    return comentarioOriginal;
}

int buscarComentarios(int idTransmision,Transmision *transmisiones,int cantidadTransmisiones) {
    for (int i=0;i<cantidadTransmisiones;i++)
        if (transmisiones[i].id_transmision==idTransmision) return i;
    return NO_ENCONTRADO;
}

void emitirReporte(const char* nombArch,Transmision *transmisiones,int cantidadTransmisiones) {
    ofstream output;
    aperturaArchivoEscritura(nombArch,output);
    imprimirCabeceraReporte(output);
    for (int i=0;i<cantidadTransmisiones;i++) {
        output<<transmisiones[i].id_transmision;
        output<<setw(18)<<" ";imprimirFecha(output,transmisiones[i].fecha);
        output<<setw(13)<<right<<transmisiones[i].duracion<<"m";
        output<<setw(19)<<right<<transmisiones[i].streamer.id_streamer;
        output<<setw(11)<< " "<<setw(23)<<left<<transmisiones[i].streamer.nombre_canal;
        output<<setw(15)<<left<<transmisiones[i].streamer.categoria;
        output<<transmisiones[i].streamer.cantidad_seguidores<<endl;
        imprimirLineas('=',150,output);
        for (int j=0;j<transmisiones[i].cantidad_comentarios;j++) {
            if (j==0) {
                output<<"COMENTARIOS DE LA TRANSMISION "<<transmisiones[i].id_transmision<<":"<<endl;
                output<<setw(50)<<" "<<"ORIGINAL"<<setw(55)<<right<<"PRE-PROCESADO"<<endl;
            }
            output<<setw(10)<<" "<<setw(40)<<left<<transmisiones[i].comentarios[j].comentador;
            output<<setw(50)<<left<<transmisiones[i].comentarios[j].comentario_original;
            output<<transmisiones[i].comentarios[j].comentario_pre_procesado<<endl;
        }
        imprimirLineas('-',150,output);
    }
}

void imprimirCabeceraReporte(ofstream &output) {
    output<<setw(55)<<" "<<"REPORTE DE TRANSMISIONES "<<endl;
    imprimirLineas('=',150,output);
    output<<"ID TRANSMISION";
    output<<setw(15)<<right<<"FECHA";
    output<<setw(20)<<right<<"DURACION";
    output<<setw(20)<<right<<"ID STREAMER";
    output<<setw(20)<<right<<"NOMBRE CANAL";
    output<<setw(15)<<right<<"CATEGORIA";
    output<<setw(25)<<right<<"CANTIDAD SEGUIDORES"<<endl;
    imprimirLineas('-',150,output);
}

void imprimirLineas(char c,int cant,ofstream& output) {
    for (int i=0;i<cant;i++) output<<c;
    output<<endl;
}


int leerFecha(ifstream& input) {
    int dd,mm,aa;
    char c;
    input>>dd>>c>>mm>>c>>aa;
    input.get();
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
    output<<setw(2)<<right<<dd<<"-";
    output<<setw(2)<<right<<mm<<"-";
    output<<setw(4)<<right<<aa;
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
    input>>i;
    input.get();
    return i;
}

char* asignarCadena(char *buffer) {
    char* src=new char[strlen(buffer)+1];
    strcpy(src,buffer);
    return src;
}

char* leerCadena(ifstream& input,char delimitador,int n) {
    char buffer[n];
    input.getline(buffer,n,delimitador);
    if (input.eof()) return nullptr;
    char* src=new char[strlen(buffer)+1];
    strcpy(src,buffer);
    return src;
}
