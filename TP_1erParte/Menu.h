#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "indice.h"

void desplegarMenu();
int seleccionarOpcion(T_indice* idx, char opcion,  char* nArch, T_Fecha* fechaP);

int altaSocio(T_indice* idx,  char* nArch, T_Fecha* fechaP); //alta si no existe
int bajaSocio(T_indice* idx,  char* nArch); //baja si existe
int modificarSocio(T_indice* idx,  char* nArch); //modificar si existe
int mostrarInfoSocio(T_indice* idx,  char* nArch); //mostrar info si existe
int mostrarSociosActivos(T_indice* idx,  char* nArch); //mostrar socios ordenados

#endif // MENU_H_INCLUDED
