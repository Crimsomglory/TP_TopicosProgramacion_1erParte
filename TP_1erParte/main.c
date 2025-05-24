#include "menu.h"

#define NOM_TXT "socios.txt"
#define NOM_BIN "socios.dat"
#define NOM_ERRORTXT "socios_erroneos.txt"
#define FECHA_LOCAL 0 //0 para obtener la fecha de sistema, 1 para obtener la fecha por input

int main()
{
    t_fecha fechaProceso;
    t_indice idx;
    int resp;
    char opcion;

    if(FECHA_LOCAL)
    {
        resp = ingresar_fecha_proceso(&fechaProceso);
        if(resp != FECHA_VALIDA)
            return resp;
    }
    else
        obtener_fecha_system(&fechaProceso);

    resp = crear_archivo_socios_bin(NOM_TXT,NOM_BIN,NOM_ERRORTXT,&fechaProceso);

    indice_crear(&idx);
    indice_cargar(&idx,NOM_BIN);
    //mostrar_indice(&idx);

    desplegar_menu();
    scanf(" %c", &opcion);
    fflush(stdin);

    ///O ABRO EL ARCHIVO Y MANDO PUNTERO, O ABRO Y CIERRO POR CADA ACCION DEL MENU
    while(opcion != 'f' && resp == TODO_OK)
    {
        resp = seleccionar_opcion(&idx, opcion,NOM_BIN, &fechaProceso);
        desplegar_menu();
        scanf(" %c", &opcion);
        fflush(stdin);
    }

    if(resp!=TODO_OK)
        printf("\nRespuesta aplicacion: %d\n",resp);

    indice_vaciar(&idx);

    return 0;
}
