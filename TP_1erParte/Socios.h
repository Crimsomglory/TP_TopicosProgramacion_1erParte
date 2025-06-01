#ifndef SOCIOS_H_INCLUDED
#define SOCIOS_H_INCLUDED

#include "Fechas.h"
#include <string.h>
#include <ctype.h>

#define TAM_REG 110
#define TAM_NYAP 61
#define ERROR -1
#define TODO_OK 1
#define SOCIO_INVALIDO -3
#define SEPARADOR_TXT ';'

#define ERROR_ARCHIVO 7
#define ARCHIVO_OK 8

typedef struct
{
    long dni;
    char apYN[TAM_NYAP];
    t_fecha fechaNac;
    char sexo;
    t_fecha fechaAfil;
    char categoria[11];
    t_fecha fechaCuota;
    char estado;
}t_socio;

int crear_archivo_socios_bin(const char* nombrearchTxt, const char* nombreArchBin, const char* nombreArchErrorTxt, t_fecha* fechaProceso);
int validar_socio(t_socio* socio, t_fecha* fechaProceso, int avisarError);
void normalizarNyAp(char* nyap);
void trozar_registro(t_socio* socio, char* linea);
void ingresar_datos(t_socio* socio);

int abrir_archivo(FILE** ptr, const char* nomArch, const char* modo);
void cerrar_archivo(FILE** ptr);
void leer_archivo();//aux para comprobar datos escritos
void pal_mayus(char* linea);

#endif // SOCIOS_H_INCLUDED
