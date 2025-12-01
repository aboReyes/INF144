

#include "Bibliotecas/FuncionesAuxiliares.h"

int main(int argc, char **argv) {

    Palabra *lexicon=new Palabra[MAX_PALABRAS]{};
    int cantidadPalabras=0; //cantidadLexicones xddd

    leerLexicon("ArchivoDeDatos/lexicon.csv",lexicon,cantidadPalabras);

    Plato *platos=new Plato[MAX_PLATOS]{};
    int cantidadPlatos=0;

    leerPlatos("ArchivoDeDatos/platos.csv",platos,cantidadPlatos);

    Atencion *atenciones=new Atencion[MAX_ATENCIONES]{};
    int cantidadAtenciones=0;

    leerProcesarAtenciones("ArchivoDeDatos/atenciones.txt",
                            atenciones,cantidadAtenciones,
                            platos,cantidadPlatos);

    leerComentarios("ArchivoDeDatos/comentarios.csv",atenciones,cantidadAtenciones,
                    lexicon,cantidadPalabras);

    emitirReporteAtenciones("ArchivoDeReportes/ReporteAtencionesAnalisisSentimiento.txt",
                        atenciones,cantidadAtenciones);



    return 0;
}
