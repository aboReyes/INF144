//
// Created by ASUS on 22/09/2025.
//

#include "FuncionesAuxiliares.h"


void aperturaArchivoLectura(const char* nombArch,ifstream&arch) {
    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"ERROR: el archivo"<<nombArch<<" no se pudo abrir"<<endl;
        exit(1);
    }
}

void aperturaArchivoEscritura(const char* nombArch,ofstream& arch) {
    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout<<"ERROR: el archivo"<<nombArch<<" no se pudo abrir"<<endl;
        exit(1);
    }
}

void leerTarifa(double &tarifa) {
    cout<<"Ingrese la tarifa: ";
    cin>>tarifa;
}

void crearReporte(const char* nombArchArt,const char* nombArchCan,const char* nombArchRepro,
                    const char* nombArchReporte) {
    ifstream archArt,archCan,archRepro;
    ofstream archReporte;

    aperturaArchivoLectura(nombArchArt,archArt);
    aperturaArchivoLectura(nombArchCan,archCan);
    aperturaArchivoLectura(nombArchRepro,archRepro);
    aperturaArchivoEscritura(nombArchReporte,archReporte);

    double tarifa=0.85;
    //leerTarifa(tarifa);

    archReporte<<fixed;
    archReporte.precision(2);

    imprimirTitulo(archReporte,tarifa);
    int nroArtista=0,numCodArtista,nroCancion=0;
    char letraCodArtista;
    while (true) {
        leerImprimirDatosArtista(archArt,archReporte,nroArtista,letraCodArtista,numCodArtista);
        imprimirDatosCancionesArtista(archRepro,archCan,archReporte,letraCodArtista,numCodArtista,nroCancion);
        if (archArt.eof()) break;
    }
}

void imprimirDatosCancionesArtista(ifstream& archRepro,ifstream &archCan,ofstream& archReporte,char letraCodArtista,int numCodArtista,int &nroCancion) {
    archRepro.clear();
    archRepro.seekg(0,ios::beg);
    int diaCre,mesCre,añoCre,numCodArtArch,codeCancion;
    long long nroRepro;
    char c,letraCodArtArch;
    imprimirSubtitulo2(archReporte);
    nroCancion=0;
    while (true) {
        archRepro>>diaCre;
        if (archRepro.eof())break;
        archRepro>>c>>mesCre>>c>>añoCre>>ws>>letraCodArtArch>>numCodArtArch>>codeCancion>>nroRepro;
        if (letraCodArtArch==letraCodArtista and numCodArtArch==numCodArtista) {
            nroCancion++;
            imprimirNro(archReporte,nroCancion); archReporte<<setw(5)<<" ";
            imprimirFecha(diaCre,mesCre,añoCre,archReporte);
            archReporte<<setw(10)<<right<<codeCancion; archReporte<<setw(9)<<" ";
            int duracionSeg=procesarDatosCancion(archCan,archReporte,codeCancion);
            archReporte<<setw(15)<<right<<nroRepro<<setw(5)<<" ";
            int totalPlays=duracionSeg*nroRepro;
            convertirSeg_HHMMSS(archReporte,totalPlays);
            archReporte<<endl;
        }else {
            while (archRepro.get()!='\n');
        }
    }
    imprimirLineas('-',100,archReporte);
}

int procesarDatosCancion(ifstream &archCan,ofstream& archReporte,int codeCancion) {
    int codeCancionArch;
    archCan.clear();
    archCan.seekg(0,ios::beg);
    while (true) {
        archCan>>codeCancionArch;
        if (archCan.eof()) break;
        if (codeCancionArch==codeCancion) {
            leerImprimirNombreArtistayCancion(archCan,archReporte,15);
            int totalSeg=leerMMSS_Seg(archCan);
            convertirSeg_HHMMSS(archReporte,totalSeg);
            return totalSeg;
        }else {
            while (archCan.get()!='\n');
        }
    }
    return 0;
}

void leerImprimirDatosArtista(ifstream& archArt,ofstream& archReporte,int &nroArtista,char &letraCodArtista,int &numCodArtista) {
    char c;
    int diaDeb,mesDeb,añoDeb;
    double rating;
    archArt>>diaDeb;
    if (archArt.eof()) return;
    nroArtista++;
    archArt>>c>>mesDeb>>c>>añoDeb>>ws>>letraCodArtista>>numCodArtista;
    archReporte<<"Artits No."<<nroArtista<<endl;
    imprimirSubtitulo(archReporte);
    leerImprimirNombreArtistayCancion(archArt,archReporte,19);
    archReporte<<letraCodArtista<<setw(10)<<left<<numCodArtista;
    imprimirFecha(diaDeb,mesDeb,añoDeb,archReporte);
    archArt>>rating;
    archReporte<<setw(10)<<right<<rating<<endl;;
    imprimirLineas('-',100,archReporte);
    while (archArt.get()!='\n');
}

int leerMMSS_Seg(ifstream& archCan) {
    char c;
    int min,seg;
    archCan>>min>>c>>seg;
    return min*60+seg;
}

void convertirSeg_HHMMSS(ofstream &archRep,int numero) {
    archRep.fill('0');
    archRep<<setw(2)<<right<<(numero/3600)<<":";
    numero=numero%3600;
    archRep<<setw(2)<<right<<(numero/60)<<":";
    numero=numero%60;
    archRep<<setw(2)<<right<<numero;
    archRep.fill(' ');
}

void imprimirNro(ofstream& archReporte,int nro) {
    archReporte.fill('0');
    archReporte<<setw(2)<<right<<nro;
    archReporte.fill(' ');
}

void imprimirSubtitulo2(ofstream &archReporte) {
    archReporte<<"PLAYED SONGS"<<endl;
    archReporte<<"No."<<setw(10)<<" "<<"DATE"<<setw(10)<<" "<<"CODE"<<setw(10)<<" "<<"TITLE"<<setw(10)<<" "<<"DURATION"<<
    setw(8)<<" "<<"N.PLAYS"<<setw(5)<<" "<<"TOTAL"<<endl;
}

void leerImprimirNombreArtistayCancion(ifstream& arch,ofstream& archReporte,int tamaño) {
    char c;
    int cantEspaciosBlanco=0;
    arch>>ws;
    while (true) {
        c=arch.get();
        if (c==' ') break;
        if (c>='a' and c<='z') c=c-32;
        archReporte<<c;
        cantEspaciosBlanco++;
    }
    archReporte<<setw(tamaño-cantEspaciosBlanco)<<" ";
}

void imprimirSubtitulo(ofstream& archReporte) {
    archReporte<<"NAME"<<setw(15)<<" "<<"CODE"<<setw(7)<<" "<<"DEBUT DATE"<<setw(10)<<" "<<"RATING"<<endl;
}

void imprimirFecha(int dia,int mes,int año,ofstream& archReporte) {
    archReporte.fill('0');
    archReporte<<setw(2)<<right<<dia<<"/"<<setw(2)<<right<<mes<<"/"<<año;
    archReporte.fill(' ');
    archReporte<<setw(5)<<" ";
}


void imprimirTitulo(ofstream &archReporte,double tarifa) {
    archReporte<<setw(35)<<" "<<"PLATAFORMA KPOP_MUSIC"<<endl;
    archReporte<<setw(30)<<" "<<"TARIFA POR MINUTO DE REPRODUCCION: "<<tarifa<<endl;
    imprimirLineas('=',100,archReporte);
}

void imprimirLineas(char c,int cant,ofstream& archReporte) {
    for (int i=0;i<cant;i++) archReporte<<c;
    archReporte<<endl;
}
