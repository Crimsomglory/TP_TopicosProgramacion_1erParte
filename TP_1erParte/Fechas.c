#include "Fechas.h"

int ingresarFechaProceso(T_Fecha* fecha)
{
    puts("Ingrese fecha de proceso con formato dd/MM/yyyy");
    scanf("%d/%d/%d",&fecha->d,&fecha->m,&fecha->y);

    if(validarFecha(fecha)!= ES_FECHA)
    {
        puts("Fecha invalida");
        return NO_ES_FECHA;
    }

    return FECHA_VALIDA;
}

void obtenerFechaSystem(T_Fecha* fecha)
{
    time_t t = time(NULL);
    struct tm *fechaSys = localtime(&t);

    fecha->d = fechaSys->tm_mday;
    fecha->m = fechaSys->tm_mon+1;
    fecha->y = fechaSys->tm_year+1900;

    printf("Fecha de proceso: %02d/%02d/%04d\n",fecha->d, fecha->m, fecha->y);
}

int validarFecha(T_Fecha* fecha)
{
    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (fecha->y < 1900)
        return NO_ES_FECHA;

    if (fecha->m < 1 || fecha->m > 12)
        return NO_ES_FECHA;

    if ((fecha->y % 4 == 0 && fecha->y % 100 != 0) || (fecha->y % 400 == 0))
        diasPorMes[1] = 29;

    if (fecha->d < 1 || fecha->d > diasPorMes[fecha->m - 1])
        return NO_ES_FECHA;

    return ES_FECHA;
}

int compararFechas(T_Fecha* f1, T_Fecha* f2)
{
    if (f1->y > f2->y)
        return FECHA_1_MAYOR;

    if (f1->y < f2->y)
        return FECHA_2_MAYOR;

    if (f1->m > f2->m)
        return FECHA_1_MAYOR;

    if (f1->m < f2->m)
        return FECHA_2_MAYOR;

    if (f1->d > f2->d)
        return FECHA_1_MAYOR;

    if (f1->d < f2->d)
        return FECHA_2_MAYOR;

    return FECHAS_IGUALES;
}
