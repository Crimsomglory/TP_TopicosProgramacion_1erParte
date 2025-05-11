#ifndef FECHAS_H_INCLUDED
#define FECHAS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ES_FECHA 2
#define NO_ES_FECHA -2
#define FECHA_VALIDA 3
#define FECHA_1_MAYOR 4
#define FECHA_2_MAYOR 5
#define FECHAS_IGUALES 6

typedef struct
{
    int d;
    int m;
    int y;

}T_Fecha;

int ingresarFechaProceso(T_Fecha* fecha);
int validarFecha(T_Fecha* fecha);
int compararFechas(T_Fecha* f1, T_Fecha* f2);
void obtenerFechaSystem(T_Fecha* fecha);

#endif // FECHAS_H_INCLUDED
