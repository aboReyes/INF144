

#include "Bilbiotecas/FuncionesAuxiliares.h"

int main(int argc, char **argv) {

    Conductor *conductores=new Conductor[MAX_CONDUCTORES]{};
    int cantidadConductores=0;

    Vehiculo *vehiculos=new Vehiculo[MAX_VEHICULOS]{};
    int cantidadVehiculos=0;

    Infraccion *infracciones=new Infraccion[MAX_INFRACCIONES]{};
    int cantidadInfracciones=0;

    leerConductores("ArchivoDeDatos/conductores.csv",conductores,cantidadConductores);

    leerVehiculos("ArchivoDeDatos/vehiculos.csv",vehiculos,cantidadVehiculos);

    leerInfracciones("ArchivoDeDatos/infracciones.csv",infracciones,cantidadInfracciones);

    actualizarInformaciones(conductores,cantidadConductores,
                            vehiculos,cantidadVehiculos,
                            infracciones,cantidadInfracciones);

    /* lo hago para verificar si mi generarEnlace estaba bien, lo cual si estaba
    char nombre[]   = "Paula";
    char apellido[] = "Castro";
    char licencia[] = "C7543";

    char *enlace;
    generarEnlace(nombre, apellido, licencia, enlace);

    cout << "Enlace generado: " << enlace << endl;*/

    emitirPapeletas(conductores,cantidadConductores);


    return 0;
}
