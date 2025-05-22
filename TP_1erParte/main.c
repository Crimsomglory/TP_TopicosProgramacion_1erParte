#include "menu.h"

#define NOM_TXT "socios.txt"
#define NOM_BIN "socios.dat"
#define NOM_ERRORTXT "socios_erroneos.txt"
#define FECHA_LOCAL 0 //0 para obtener la fecha de sistema, 1 para obtener la fecha por input

int main()
{
    T_Fecha fechaProceso;
    T_indice idx;
    int resp;
    char opcion;

    if(FECHA_LOCAL)
    {
        resp = ingresarFechaProceso(&fechaProceso);
        if(resp != FECHA_VALIDA)
            return resp;
    }
    else
        obtenerFechaSystem(&fechaProceso);

    resp = crearArchivoSociosBin(NOM_TXT,NOM_BIN,NOM_ERRORTXT,&fechaProceso);

    indiceCrear(&idx);
    indiceCargar(&idx,NOM_BIN);
    //mostrarIndice(&idx);

    desplegarMenu();
    scanf(" %c", &opcion);

    ///O ABRO EL ARCHIVO Y MANDO PUNTERO, O ABRO Y CIERRO POR CADA ACCION DEL MENU
    while(opcion != 'f' && resp == TODO_OK)
    {
        resp = seleccionarOpcion(&idx, opcion,NOM_BIN, &fechaProceso);
        system("pause");
        system("cls");
        desplegarMenu();
        scanf(" %c", &opcion);
    }

    if(resp!=TODO_OK)
        printf("\nRespuesta aplicacion: %d\n",resp);

    indiceVaciar(&idx);

    return 0;
}
