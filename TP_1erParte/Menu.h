#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "indice.h"

void desplegar_menu();
int seleccionar_opcion(t_indice* idx, char opcion,  char* nArch, t_fecha* fechaP);

int alta_socio(t_indice* idx,  char* nArch, t_fecha* fechaP); //alta si no existe
int baja_socio(t_indice* idx,  char* nArch); //baja si existe
int modificar_socio(t_indice* idx,  char* nArch, t_fecha* fechaP); //modificar si existe
int mostrar_info_socio(t_indice* idx,  char* nArch); //mostrar info si existe
int mostrar_socios_activos(t_indice* idx,  char* nArch); //mostrar socios ordenados

#endif // MENU_H_INCLUDED
