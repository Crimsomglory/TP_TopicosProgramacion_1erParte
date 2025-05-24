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

}t_fecha;

int ingresar_fecha_proceso(t_fecha* fecha);
int validar_fecha(t_fecha* fecha);
int comparar_fechas(t_fecha* f1, t_fecha* f2);
void obtener_fecha_system(t_fecha* fecha);

#endif // FECHAS_H_INCLUDED
