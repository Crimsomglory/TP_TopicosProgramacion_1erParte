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

typedef struct
{
    long dni;
    char apYN[TAM_NYAP];
    T_Fecha fechaNac;
    char sexo;
    T_Fecha fechaAfil;
    char categoria[11];
    T_Fecha fechaCuota;
    char estado;
}T_Socio;


int crearArchivoSociosBin(const char* nombrearchTxt, const char* nombreArchBin, const char* nombreArchErrorTxt, T_Fecha* fechaProceso);
int validarSocio(T_Socio* socio, T_Fecha* fechaProceso, int avisarError);
void normalizarNyAp(char* nyap);
void trozarRegistro(T_Socio* socio, char* linea);

#endif // SOCIOS_H_INCLUDED
