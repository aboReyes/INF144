//
// Created by ASUS on 23/11/2025.
//

#include "FuncionesAuxiliares.h"

void aperturaArchivoLectura(const char*nombArch,ifstream& arch) {
    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"Error al abrir el archivo"<<nombArch<<endl;
        exit(1);
    }
}

void aperturaArchivoEscritura(const char*nombArch,ofstream& arch) {
    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout<<"Error al abrir el archivo"<<nombArch<<endl;
        exit(1);
    }
}

void crearListaCategoria(const char* nombArch,NodoCategoria *&listaCategoria) {
    //UM163F47,just chatting,Casual conversations; reactions; and hangouts without a main game.
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    Categoria categoria{};
    while (true) {
        leerCategoria(input,categoria);
        if (input.eof()) break;
        insertarOrdenado(listaCategoria,categoria);
    }
}

void insertarOrdenado(NodoCategoria *&listaCategoria,Categoria categoria) {
    NodoCategoria *p=listaCategoria;
    NodoCategoria *anterior=nullptr;
    NodoCategoria *nuevo=new NodoCategoria;
    nuevo->dato=categoria;
    while (p!=nullptr and strcmp(listaCategoria->dato.nombre,categoria.nombre)<0) {
        anterior=p;
        p=p->siguiente;
    }
    nuevo->siguiente=p;
    if (anterior==nullptr) {
        listaCategoria=nuevo;
    }else {
        anterior->siguiente=nuevo;
    }
}

void actualizarReproducciones(const char* nombArch,NodoCategoria *&listaCategoria) {
    //Sardoche,ZT132U54,4.410,01:41:48
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    Reproduccion reproduccion{};
    char* nombreCanal,*codigoCanal;
    double rating;
    int duracion;
    while (true) {
        nombreCanal=leerCadena(input,',',50);
        if (input.eof() or nombreCanal==nullptr) break;
        codigoCanal=leerCadena(input,',',50);
        rating=leerDouble(input);
        duracion=leerTiempo(input);
        NodoCategoria *nodoAActualizar=buscarCanal(listaCategoria,codigoCanal);
        if (nodoAActualizar!=nullptr) {
            reproduccion.canal=asignarCadena(nombreCanal);
            reproduccion.rating=rating;
            reproduccion.duracion=duracion;
            if (nodoAActualizar->dato.reproducciones==nullptr) {
                nodoAActualizar->dato.reproducciones=new Reproduccion[15];
            }
            int n=nodoAActualizar->dato.numReproducciones;
            nodoAActualizar->dato.reproducciones[n]=reproduccion;
            nodoAActualizar->dato.numReproducciones++;
        }
    }
}

void actualizarComentarios(const char* nombArch,NodoCategoria *&listaCategoria) {
    //LCK,this is the problem with d1 rewards no consumables
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    char* nombreCanal,*descripcion;
    while (true) {
        nombreCanal=leerCadena(input,',',100);
        if (input.eof() or nombreCanal==nullptr) break;
        descripcion=leerCadena(input,'\n',200);
        insertarComentarios(listaCategoria,nombreCanal,descripcion);
    }
}

void calcularTotales(NodoCategoria *&listaCategoria) {
    NodoCategoria *p=listaCategoria;
    while (p) {
        p->dato.duracionTotal=0;
        p->dato.promedioRating=0.0;
        for (int i=0;i<p->dato.numReproducciones;i++) {
            p->dato.duracionTotal+=p->dato.reproducciones[i].duracion;
            p->dato.promedioRating+=p->dato.reproducciones[i].rating;
        }
        p->dato.promedioRating/=p->dato.numReproducciones;
        p=p->siguiente;
    }
}

void eliminarPorRating(NodoCategoria *&listaCategoria) {
    NodoCategoria *p=listaCategoria;
    NodoCategoria *anterior=nullptr;
    double limite=3.0; //condición que inventé

    while (p) {
        if (p->dato.promedioRating<limite) {
            if (anterior==nullptr) {//CASO INICIAL
                //Consideremos: LISTA --> N1 --->N2 --->N3--->nullptr
                //Donde: ANTERIOR=LISTA(nullptr) y P=N1
                listaCategoria=p->siguiente; //LISTA=N2
                delete p; //ElIMINAMOS N1
                p=listaCategoria; //N1=N2
                //CON ESTO, PASAMOS A:
                //LISTA-->N2--->N3--->nullptr
            }else {//CASO NO INICIAL (P EN CUALQUIER POSICION)
                //Consideremos: LISTA-->N1-->N2-->N3-->nullptr
                //Donde: ANTERIOR=N1 y P=N2
                anterior->siguiente=p->siguiente; //ANTERIOR(N1)->SIGUIENTE=N3
                delete p;//ELIMINAMOS N2
                p=anterior->siguiente;//P=N3
            }
        }else {//CASO EN EL QUE NO CUMPLE LA CONDICION
            //Consideremos: LISTA-->N1-->N  2-->N3-->nullptr
            //Donde: ANTERIOR=N1 y P=N2
            anterior=p; //ANTERIOR=N2
            p=p->siguiente; //P=N3
            //¿Qué paso?: Simplemente, saltamos una posición del nodo
        }
    }
}


void emitirReporte(const char* nombArch,NodoCategoria *listaCategoria) {
    ofstream output;
    aperturaArchivoEscritura(nombArch,output);
    NodoCategoria *p=listaCategoria;
    output<<setw(30)<<" "<<"REPORTE POR CATEGORIAS"<<endl;
    imprimirLineas('=',80,output);
    output<<fixed<<setprecision(2);
    while (p) {
        output<<"Nombre: "<<setw(5)<<" "<<p->dato.nombre<<endl;
        output<<"Codigo: "<<setw(5)<<" "<<p->dato.codigo<<endl;
        output<<"Descripcion: "<<p->dato.descripcion<<endl;
        imprimirLineas('-',80,output);
        output<<"REPRODUCCIONES: "<<endl;
        for (int i=0;i<p->dato.numReproducciones;i++) {
            output<<"CANAL: "<<setw(25)<<left<<p->dato.reproducciones[i].canal;
            output<<"RATING: "<<setw(5)<<right<<p->dato.reproducciones[i].rating;
            output<<setw(5)<<" "<<"DURACION: ";
            imprimirTiempo(output,p->dato.reproducciones[i].duracion);
            output<<endl;
            output<<setw(5)<<" "<<"COMENTARIOS: "<<endl;
            for (int j=0;j<p->dato.reproducciones[i].numComentarios;j++) {
                output<<setw(5)<<" "<<" - "<<p->dato.reproducciones[i].comentarios[j]<<endl;
            }
        }
        imprimirLineas('=',80,output);
        output<<"RATING PROMEDIO: "<<setw(9)<<right<<p->dato.promedioRating<<endl;
        output<<"DURACION TOTAL: "<<setw(5)<<" ";
        imprimirTiempo(output,p->dato.duracionTotal);
        output<<endl;
        imprimirLineas('=',80,output);
        p=p->siguiente;
    }
}

void imprimirLineas(char c,int cant,ofstream& output) {
    for (int i=0;i<cant;i++) output<<c;
    output<<endl;
}

void insertarComentarios(NodoCategoria *&listaCategoria,char *nombreCanal,char *descripcion) {
    NodoCategoria *p=listaCategoria;
    while (p) {
        for (int i=0;i<p->dato.numReproducciones;i++) {
            if (strcmp(p->dato.reproducciones[i].canal,nombreCanal)==0) {
                int n=p->dato.reproducciones[i].numComentarios;
                p->dato.reproducciones[i].comentarios[n]=asignarCadena(descripcion);
                p->dato.reproducciones[i].numComentarios++;
            }
        }
        p=p->siguiente;
    }
}

NodoCategoria *buscarCanal(NodoCategoria *listaCategoria,char* codigoCanal) {
    NodoCategoria *p=listaCategoria;
    while (p) {
        if (strcmp(p->dato.codigo,codigoCanal)==0) return p;
        p=p->siguiente;
    }
    return nullptr;
}

void leerCategoria(ifstream& input,Categoria &categoria) {
    char* codigoCanal=leerCadena(input,',',50);
    if (input.eof() or codigoCanal==nullptr) return;
    categoria.codigo=asignarCadena(codigoCanal);
    categoria.nombre=leerCadena(input,',',100);
    categoria.descripcion=leerCadena(input,'\n',200);
}

int leerTiempo(ifstream& input) {
    int hh,mm,ss;
    char c;
    input>>hh>>c>>mm>>c>>ss;
    input.get();
    return hh*3600+mm*60+ss;
}

void imprimirTiempo(ofstream& output,int tiempo) {
    int hh,mm,ss;
    hh=tiempo/3600;
    tiempo=tiempo%3600;
    mm=tiempo/60;
    tiempo=tiempo%60;
    ss=tiempo;
    output.fill('0');
    output<<setw(2)<<right<<hh<<":";
    output<<setw(2)<<right<<mm<<":";
    output<<setw(2)<<right<<ss;
    output.fill(' ');
}

double leerDouble(ifstream& input) {
    double d;
    input>>d;
    input.get();
    return d;
}

char* leerCadena(ifstream& input,char delimitador,int n) {
    char buffer[500];
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


