#include "Socios.h"

#define NOM_TXT "socios.txt"
#define NOM_BIN "socios.dat"
#define NOM_ERRORTXT "socios_erroneos.txt"

int main()
{
    T_Fecha fechaProceso;
    int resp;

    resp = ingresarFechaProceso(&fechaProceso);

    if(resp != FECHA_VALIDA)
        return resp;

    resp = crearArchivoSociosBin(NOM_TXT,NOM_BIN,NOM_ERRORTXT,&fechaProceso);

    if(resp != TODO_OK)
        return resp;

    return 0;
}
