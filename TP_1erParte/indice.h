#ifndef INDICE_H_INCLUDED
#define INDICE_H_INCLUDED

#include "Socios.h"
#include <math.h>

#define SIN_MEM -4
#define VEC_LLENO 9
#define VEC_VACIO 10
#define TAM_VEC 1
#define ENCONTRADO 11
#define NO_ENCONTRADO 12
#define PORCENTAJE_CRECIMIENTO 30

typedef struct
{
    long dni;
    unsigned nroReg;
} t_reg_indice;

typedef struct
{
    void* vec;
    unsigned cap;
    unsigned tamElem;
    unsigned ce;
} t_indice;

void indice_crear(t_indice* vec);
int indice_insertar(t_indice* vec, const t_reg_indice* idx); //inserta ordenado
int indice_eliminar(t_indice* vec, t_reg_indice* idx);//elimina dni
int indice_vacio(const t_indice* vec);//verifica si esta vacio
int indice_lleno(const t_indice* vec);
int indice_buscar(const t_indice* vec, t_reg_indice* idx);//si existe el dni deja el nro de registro en idx
int indice_cargar(t_indice*vec, const char* path);
void indice_vaciar(t_indice* vec);
void mostrar_indice(t_indice* vec);

#endif // INDICE_H_INCLUDED
