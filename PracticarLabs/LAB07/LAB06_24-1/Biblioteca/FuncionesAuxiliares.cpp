//
// Created by ASUS on 3/11/2025.
//

#include "FuncionesAuxiliares.h"

void aperturaArchivosLectura(const char*nombArch,ifstream &arch) {
    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"ERROR, el archivo "<<nombArch<<" no se puede abrir"<<endl;
        exit(1);
    }
}

void aperturaArchivosEscritura(const char*nombArch,ofstream &arch) {
    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout<<"ERROR, el archivo "<<nombArch<<" no se puede abrir"<<endl;
        exit(1);
    }
}

void preguntarFacultad(int& codigoFacultad) {
    cout<<"Ingrese el codigo de la facultad: ";
    cin>>codigoFacultad;
}

void cargarFacultades(const char* nombArch,
                    char **facultad,int *arrCodeFacultad,
                    int &cantFacultades) {
    ////FACULTAD_DE_DERECHO   400111
    ifstream input;
    aperturaArchivosLectura(nombArch,input);
    char nombreFac[30];
    int codigoFacultad;
    while (true) {
        input>>nombreFac;
        if (input.eof()) break;
        input>>codigoFacultad;
        insertarOrdenado(nombreFac,codigoFacultad,
                        facultad,arrCodeFacultad,cantFacultades);
    }
}

void insertarOrdenado(char* nombreFac,int codigoFacultad,
                    char **facultad,int *arrCodeFacultad,int &cantFacultades) {
    int i=cantFacultades-1;
    while (i>=0 and codigoFacultad<arrCodeFacultad[i]) {
        facultad[i+1]=facultad[i];
        arrCodeFacultad[i+1]=arrCodeFacultad[i];
        i--;
    }
    facultad[i+1]=new char[strlen(nombreFac)+1];
    strcpy(facultad[i+1],nombreFac);
    arrCodeFacultad[i+1]=codigoFacultad;
    cantFacultades++;
}

char* readString(ifstream& input) {
    char buffer[MAX_CARACTERES];
    input>>buffer;
    if (input.eof()) return nullptr;
    char* src=new char[strlen(buffer)+1];
    strcpy(src,buffer);
    return src;
}

void cargarCalificaciones(const char* nombArch,
                        int *arrCodigoAlumnos,int *arrNumCursos,
                        double *arrSumaPonderada,double *arrNumCreditos,
                        int &cantCalificaciones) {
    //Calificaciones.txt
    //DER614   5.75
    //se repite:
    //20238549   16
    //20205830   17
    ifstream input;
    aperturaArchivosLectura(nombArch,input);
    char codigoCurso[50];
    double creditosCurso;
    int codigoAlumno,notaAlumno;
    while (true) {
        input>>codigoCurso;
        if (input.eof()) break;
        input>>creditosCurso;
        while (true) {
            input>>codigoAlumno;
            input>>notaAlumno;
            procesamientoCalificaciones(codigoAlumno,notaAlumno,creditosCurso,
                                        arrCodigoAlumnos,arrNumCursos,
                                        arrSumaPonderada,arrNumCreditos,
                                        cantCalificaciones);
            if (input.get()=='\n') break;
        }
    }
}

void procesamientoCalificaciones(int codigoAlumno,int notaAlumno,double creditosCurso,
                                int *arrCodigoAlumnos,int *arrNumCursos,
                                double *arrSumaPonderada,double *arrNumCreditos,
                                int &cantCalificaciones) {
    int pos=buscarCalificacion(codigoAlumno,arrCodigoAlumnos,cantCalificaciones);
    if (pos!=NO_ENCONTRADO) {
        arrNumCursos[pos]++;
        arrSumaPonderada[pos]+=notaAlumno*creditosCurso;
        arrNumCreditos[pos]+=creditosCurso;
    }else {
        insertarOrdenado2(codigoAlumno,notaAlumno,creditosCurso,
                        arrCodigoAlumnos,arrNumCursos,arrSumaPonderada,
                        arrNumCreditos,cantCalificaciones);
    }
}

void insertarOrdenado2(int codigoAlumno,int notaAlumno,double creditosCurso,
                        int *arrCodigoAlumnos,int *arrNumCursos,double *arrSumaPonderada,
                        double *arrNumCreditos,int &cantCalificaciones) {
    int i=cantCalificaciones-1;
    while (i>=0 and codigoAlumno<arrCodigoAlumnos[i]) {
        arrCodigoAlumnos[i+1]=arrCodigoAlumnos[i];
        arrNumCursos[i+1]=arrNumCursos[i];
        arrSumaPonderada[i+1]=arrSumaPonderada[i];
        arrNumCreditos[i+1]=arrNumCreditos[i];
        i--;
    }
    arrCodigoAlumnos[i+1]=codigoAlumno;
    arrNumCursos[i+1]=1;
    arrSumaPonderada[i+1]=notaAlumno*creditosCurso;
    arrNumCreditos[i+1]=creditosCurso;
    cantCalificaciones++;
}

int buscarCalificacion(int codigoAlumno,int* arrCodigoAlumnos,int &cantCalificaciones) {
    int limiteInferior=0;
    int limiteSuperior=cantCalificaciones-1;
    int puntoMedio;
    while (true) {
        if (limiteInferior>limiteSuperior) return NO_ENCONTRADO;
        puntoMedio=(limiteInferior+limiteSuperior)/2;
        if (codigoAlumno==arrCodigoAlumnos[puntoMedio]) return puntoMedio;
        if (codigoAlumno>arrCodigoAlumnos[puntoMedio]) {
            limiteInferior=puntoMedio+1;
        }else {
            limiteSuperior=puntoMedio-1;
        }
    }
}

void generarReporte(const char* nombArchAlumnos,
                    const char* nombArchRep,
                    int codigoFacultad,int *arrCodigoFacultad,
                    char**facultad,
                    int *arrCodigoAlumnos,int *arrNumCursos,
                    double *arrSumaPonderada,double *arrNumCreditos,
                    int cantCalificaciones,
                    int cantFacultades) {
    //20227341     DIAZ/ANTEZANO/MAGALI-SILVANA   200451
    ifstream input;
    ofstream output;
    aperturaArchivosEscritura(nombArchRep,output);
    aperturaArchivosLectura(nombArchAlumnos,input);

    int posfacultad=buscarFacultad(codigoFacultad,arrCodigoFacultad,
                                    cantFacultades);
    if (posfacultad!=NO_ENCONTRADO) {
        imprimirCabeceraReporte(output,facultad[posfacultad]);
        int codigoAlumno,codigoFacultadLeido;
        char nombreAlumno[50];
        output<<fixed<<setprecision(2);
        while (true) {
            input>>codigoAlumno;
            if (input.eof()) break;
            input>>nombreAlumno;
            input>>codigoFacultadLeido;
            if (codigoFacultadLeido==codigoFacultad) {
                formato1(nombreAlumno);
                formato2(nombreAlumno);
                formato3(nombreAlumno);
                int posAlumno=buscarCalificacion(codigoAlumno,arrCodigoAlumnos,
                    cantCalificaciones);
                int cursos=0;
                double creditos=0.0,suma=0.0,prom=0.0;
                if (posAlumno!=NO_ENCONTRADO) {
                    cursos=arrNumCursos[posAlumno];
                    creditos=arrNumCreditos[posAlumno];
                    suma=arrSumaPonderada[posAlumno];
                    prom=arrSumaPonderada[posAlumno]/arrNumCreditos[posAlumno];
                }else {
                    continue; //gracias gpt :u
                }
                output <<setw(10)<<right<<codigoAlumno<<" - ";
                output <<setw(35)<<left<<nombreAlumno;
                output <<setw(15)<<right<<cursos;
                output <<setw(28)<<right<<suma;
                output <<setw(24)<<right<<creditos;
                output <<setw(26)<<right<<prom<<endl;
            }
        }
    }
}

void formato3(char* nombre) {
    //Prado Falcon Edgar Richard
    int ultimo=-1,penultimo=-1;
    for (int i=0;nombre[i];i++) {
        if (nombre[i]==' ') {
            penultimo=ultimo;
            ultimo=i;
        }
    }
    if (ultimo==-1) return;
    char aux[2*MAX_CARACTERES+3]; //crear buffer temporal grande
    aux[0]='\0'; //lo dejamos vacio para usar strcat
    strcat(aux,nombre+penultimo+1); //nombre=0 penultimo=12+1=13 apunta a E -->Edgar...
    strcat(aux," ");//concatenar aux con un espacio en blanco para lo siguiente:
    nombre[penultimo]='\0'; //original= Prado Falcon'\0' -->ahí muere
    strcat(aux,nombre);//concatenamos-->Edgar Alan Prado Falcon
    strcpy(nombre,aux);//copiamos al original
}

void formato2(char *nombre) {
    //PRADO FALCON EDGAR RICHARD
    bool esPrimero=true;
    for (int i=0;nombre[i];i++) {
        if (esPrimero) {
            esPrimero=false;
        }else {
            if (nombre[i]>='A' && nombre[i]<='Z') {
                nombre[i]+='a'-'A';
            }
            if (nombre[i]==' ') {
                esPrimero=true;
            }
        }
    }
}
void imprimirCabeceraReporte(ofstream& output,char *facultad) {
    output<<setw(65)<<" "<<"INSTITUCION EDUCATIVA TP"<<endl;
    output<<setw(55)<<" "<<"PROMEDIO PORNDERADO DE LOS ALUMNOS MATRICULADOS"<<endl;
    output<<setw(70)<<" "<<"CICLO: 2024-1"<<endl;
    formato1(facultad);
    output<<setw(65)<<" "<<facultad<<endl;
    imprimirLineas('=',150,output);
    output<<setw(15)<<right<<"ALUMNO";
    output<<setw(55)<<right<<"No. de Cursos";
    output<<setw(25)<<right<<"Suma Ponderada";
    output<<setw(25)<<right<<"No. de Creditos";
    output<<setw(25)<<right<<"Prom Ponderado"<<endl;
    imprimirLineas('-',150,output);
}

void imprimirLineas(char c,int cant,ofstream & output) {
    for (int i=0;i<cant;i++) output<<c;
    output<<endl;
}

void formato1(char* facultad) {
    for (int i=0;facultad[i];i++)
        if (facultad[i]=='_' or
            facultad[i]=='/' or
            facultad[i]=='-') facultad[i]=' ';
}

int buscarFacultad(int codigoFacultad,int *arrCodigoFacultad,
                    int cantFacultades) {
    int limiteInferior=0;
    int limiteSuperior=cantFacultades-1;
    int puntoMedio;
    while (true) {
        if (limiteInferior>limiteSuperior) return NO_ENCONTRADO;
        puntoMedio=(limiteInferior+limiteSuperior)/2;
        if (codigoFacultad==arrCodigoFacultad[puntoMedio]) return puntoMedio;
        if (codigoFacultad>arrCodigoFacultad[puntoMedio]) {
            limiteInferior=puntoMedio+1;
        }else {
            limiteSuperior=puntoMedio-1;
        }
    }
}
