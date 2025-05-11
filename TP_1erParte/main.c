#include "Socios.h"

#define NOM_TXT "socios.txt"
#define NOM_BIN "socios.dat"
#define NOM_ERRORTXT "socios_erroneos.txt"
#define FECHA_LOCAL 0 //0 para obtener la fecha de sistema, 1 para obtener la fecha por input

int main()
{
    T_Fecha fechaProceso;
    int resp;

    if(FECHA_LOCAL)
    {
        resp = ingresarFechaProceso(&fechaProceso);
        if(resp != FECHA_VALIDA)
            return resp;
    }
    else
        obtenerFechaSystem(&fechaProceso);

    resp = crearArchivoSociosBin(NOM_TXT,NOM_BIN,NOM_ERRORTXT,&fechaProceso);

    if(resp != TODO_OK)
        return resp;

    return 0;
}
