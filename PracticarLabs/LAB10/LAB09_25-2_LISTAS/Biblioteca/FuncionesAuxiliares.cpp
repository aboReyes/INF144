//
// Created by ASUS on 22/11/2025.
//

#include "FuncionesAuxiliares.h"

void aperturaArchivoLectura(const char*nombArch,ifstream&arch) {
    arch.open(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"Error, no se puede abrir el archivo"<<nombArch<<endl;
        exit(1);
    }
}

void aperturaArchivoEscritura(const char*nombArch,ofstream&arch) {
    arch.open(nombArch,ios::out);
    if (not arch.is_open()) {
        cout<<"Error, no se puede abrir el archivo"<<nombArch<<endl;
        exit(1);
    }
}

void leerCategorias(const char* nombArch,Nodo *&listaCategoria,
                    bool inicio,bool final,bool ordenado) {
    //UM163F47,just chatting,Casual conversations; reactions; and hangouts without a main game.
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    Categoria categoria{}; //la variable donde voy a leer
    while (true) {
        leerCategoria(input,categoria); //mejor hacer un módulo y leer
        if (input.eof()) break;
        //aquí pueden estar los 3 casos de inserción:
        if (inicio) insertarAlInicio(listaCategoria,categoria); //caso1:
        if (final) insertarAlFinal(listaCategoria,categoria); //caso 2:
        if (ordenado) insertarOrdenado(listaCategoria,categoria); //caso3:
    }
}

void insertarAlInicio(Nodo *&listaCategoria,Categoria categoria) {
    Nodo *nuevo = new Nodo;             //damos vida
    nuevo->dato = categoria;            // copia la categoría

    if (listaCategoria==nullptr) {
        nuevo->siguiente = nullptr;  // apunta al antiguo primero
        listaCategoria = nuevo;             // ahora este es el nuevo primero
    }else {
        nuevo->siguiente=listaCategoria;//reconexion
        listaCategoria=nuevo;
    }
}

//acá no vamos a modificar su memoria por ende, categoria no llevará "&"
void insertarAlFinal(Nodo *&listaCategoria,Categoria categoria) {
    /*Nodo *nuevo=new Nodo;        //creamos el nuevo nodo
    nuevo->dato=categoria;       //copiamos la categoría en el campo "dato"
    nuevo->siguiente=nullptr;   //el siguiente nuevo nodo apunta a nullptr  (estará al final)

    if (listaCategoria==nullptr) { //si la lista está vacía
        listaCategoria=nuevo;       //el nuevo nodo se convierte en el primer y único nodo
    }else {
        Nodo *recorrido=listaCategoria;     //creamos el recorrido que empieza desde el primer nodo
        while (recorrido->siguiente!=nullptr) {
            recorrido=recorrido->siguiente; //hasta que sea nullptr recorremos toda la lista
        }
        recorrido->siguiente=nuevo;         //hacemos la conexion al nuevo nodo como siguiente del último nodo
    }*/

    //LA OTRA VERSIÓN DE INSERTAR AL FINAL
    //creo que a este "p", erasmo le llama recorrido
    Nodo *p=listaCategoria; //creamos un puntero encargado de recorrer la lista
    Nodo *anterior=nullptr;
    Nodo *nuevo; //no apunta a nada, es como un fantasma


    nuevo=new Nodo; //le doy vida al nodo
    nuevo->dato=categoria;

    //importante para RECORRER HASTA EL FINAL Y AHÍ INSERTARLO
    //recomendación, insertar al final e insertar ordenado es el mismo codigo solo que
    //le agregas la condición, en este caso el strcmp
    //OJO: CON LAS ÓRDENES AL REVÉZ
    while (p!=nullptr /*and strcmp(p->dato.nombre,categoria.nombre)<0*/) {
        anterior=p;
        p=p->siguiente;
    }

    //terminó el while, p es nullptr ahora
    nuevo->siguiente=p; //el siguiente del nuevo nodo debe apuntar a nullptr

    if (anterior==nullptr) {
        listaCategoria=nuevo;
    }else {
        anterior->siguiente=nuevo;
    }
}


void insertarOrdenado(Nodo *&listaCategoria,Categoria categoria) {
    //1) Crear el nuevo nodo
    Nodo *nuevo;
    Nodo *p=listaCategoria;
    Nodo *anterior=nullptr;

    //2)Armar el nuevo nodo
    nuevo=new Nodo;
    nuevo->dato=categoria;

    //3)Buscar la posicion y actulizar "recorrido" y "anterior"
    while (p) {
        if (strcmp(p->dato.nombre,categoria.nombre)>0) break; //puede varian la condicion según el enunciado
        anterior=p;
        p=p->siguiente;
    }

    //4)Encontramos la posicion --> toca hacer las conexiones
    nuevo->siguiente=p;
    if (anterior==nullptr) listaCategoria=nuevo;
    else anterior->siguiente=nuevo;
}
void pruebaCategorias(const char* nombArch,
                    Nodo *listaCategoria) {
    ofstream output;
    aperturaArchivoEscritura(nombArch,output);
    Nodo *p=listaCategoria;
    output<<setw(30)<<" "<<"REPORTE POR CATEGORIAS"<<endl;
    imprimirLineas('=',80,output);
    while (p) {//p!=nullptr
        output<<"Codigo: "<<setw(13)<<right<<p->dato.codigo<<endl;
        output<<"Nombre: "<<setw(5)<<" "<<p->dato.nombre<<endl;
        output<<"Descripcion: "<<p->dato.descripcion<<endl;
        imprimirLineas('-',80,output);
        p=p->siguiente; //avanzar en la lista
    }
}

void actualizarLista(const char* nombArch,Nodo *&listaCategoria) {
    //Sardoche,ZT132U54,4.410,01:41:48
    ifstream input;
    aperturaArchivoLectura(nombArch,input);

    //acá da flojera hacer módulo, entonces, se lee de frente
    Reproduccion reproduccion{};
    char* nombreCanal,*codigoCanal;
    double rating;
    int duracion;
    while (true) {
        nombreCanal=leerCadena(input,',',50);
        if (input.eof() or nombreCanal==nullptr) break;
        codigoCanal=leerCadena(input,',',20);
        rating=leerDouble(input);
        duracion=leerHora(input);
        //encontraremos NO AHORA EL POS/INDEX SINO AHORA COPIAREMOS EL NODO
        Nodo *nodoAActualizar=buscarCategoria(listaCategoria,codigoCanal);
        if (nodoAActualizar!=nullptr) { //es como el pos!=NO_ENCONTRADO
            reproduccion.canal=asignarCadena(nombreCanal);
            reproduccion.rating=rating;
            reproduccion.duracion=duracion;
            if (nodoAActualizar->dato.reproducciones==nullptr) {
                nodoAActualizar->dato.reproducciones=new Reproduccion[15]; //le asignamos memoria
            }
            int n=nodoAActualizar->dato.numReproducciones;
            nodoAActualizar->dato.reproducciones[n]=reproduccion;
            nodoAActualizar->dato.numReproducciones++;
        }
    }
}

void actualizarComentarios(const char* nombArch,Nodo *&listaCategoria) {
    //LCK,this is the problem with d1 rewards no consumables
    ifstream input;
    aperturaArchivoLectura(nombArch,input);
    char *nombreCanal,*comentario;
    while (true) {
        nombreCanal=leerCadena(input,',',50);
        if (input.eof() or nombreCanal==nullptr) break;
        comentario=leerCadena(input,'\n',200);
        insertarNodoEspecial(nombreCanal,listaCategoria,comentario);
    }
}

void generarReporte(const char* nombArch,Nodo *listaCategoria) {
    ofstream output;
    aperturaArchivoEscritura(nombArch,output);
    Nodo *p=listaCategoria;
    output<<setw(30)<<" "<<"REPORTE POR CATEGORIAS"<<endl;
    imprimirLineas('=',80,output);
    output<<fixed<<setprecision(2);
    while (p!=nullptr) {
        output<<"Codigo: "<<setw(13)<<right<<p->dato.codigo<<endl;
        output<<"Nombre: "<<setw(5)<<" "<<p->dato.nombre<<endl;
        output<<"Descripcion: "<<p->dato.descripcion<<endl;
        imprimirLineas('-',80,output);
        output<<"REPRODUCCIONES:"<<endl;
        for (int i=0;i<p->dato.numReproducciones;i++) {
            output<<"CANAL: "<<p->dato.reproducciones[i].canal<<endl;
            output<<"RATING: "<<setw(15)<<right<<p->dato.reproducciones[i].rating<<endl;
            output<<setw(5)<<" "<<"DURACION: ";
            imprimirHora(output,p->dato.reproducciones[i].duracion);
            output<<endl;
            output<<setw(5)<<" "<<"COMENTARIOS: "<<endl;
            for (int j=0;j<p->dato.reproducciones[i].numComentarios;j++) {
                output<<setw(5)<<" "<<" - "<<p->dato.reproducciones[i].comentarios[j]<<endl;
            }
        }
        imprimirLineas('=',80,output);
        p=p->siguiente; //avanzar en la lista
    }
}

void insertarNodoEspecial(char *nombreCanal,Nodo *&listaCategoria,
                                    char* comentario) {
    Nodo *p=listaCategoria;
    while (p!=nullptr) {
        if (p->dato.reproducciones!=nullptr) {
            for (int i=0;i<p->dato.numReproducciones;i++) {
                if (strcmp(p->dato.reproducciones[i].canal,nombreCanal)==0) {
                    int n=p->dato.reproducciones[i].numComentarios;
                    p->dato.reproducciones[i].comentarios[n]=asignarCadena(comentario);
                    p->dato.reproducciones[i].numComentarios++;
                }
            }
        }
        p=p->siguiente;
    }
}

struct Nodo* buscarCategoria(Nodo *listaCategoria,char *codigoCanal) {
    Nodo *p=listaCategoria;
    while (p!=nullptr) {
        if (strcmp(p->dato.codigo,codigoCanal)==0) break;
        p=p->siguiente;
    }

    if (p==nullptr or strcmp(p->dato.codigo,codigoCanal)!=0) {
        return nullptr;
    }else {
        return p;
    }
}

void imprimirLineas(char c,int cant,ofstream &output) {
    for (int i=0;i<cant;i++) output<<c;
    output<<endl;
}

void leerCategoria(ifstream &input,Categoria &categoria) {
    char *codigo,*nombre,*descripcion;

    codigo=leerCadena(input,',',20);
    if (codigo== nullptr or input.eof()) return;
    nombre=leerCadena(input,',',50);
    descripcion=leerCadena(input,'\n',150);

    categoria.codigo=asignarCadena(codigo);
    categoria.nombre=asignarCadena(nombre);
    categoria.descripcion=asignarCadena(descripcion);
}

char* leerCadena(ifstream& input,char delimitador,int n) {
    char buffer[n];
    input.getline(buffer,n,delimitador);
    if (input.eof()) return nullptr;
    char* src=new char[strlen(buffer)+1];
    strcpy(src,buffer);
    return src;
}

char* asignarCadena(char* buffer) {
    char *src=new char[strlen(buffer)+1];
    strcpy(src,buffer);
    return src;
}

int leerHora(ifstream& input) {
    int hh,mm,ss;
    char c;
    input>>hh>>c>>mm>>c>>ss;
    input.get();
    return hh*3600+mm*60+ss;
}

void imprimirHora(ofstream& output,int tiempo) {
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
