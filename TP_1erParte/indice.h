#ifndef INDICE_H_INCLUDED
#define INDICE_H_INCLUDED

#include "Socios.h"

#define SIN_MEM -4
#define VEC_LLENO 9
#define VEC_VACIO 10
#define TAM_VEC 100
#define ENCONTRADO 11
#define NO_ENCONTRADO 12

typedef struct
{
    long dni;
    unsigned nroReg;

}T_reg_indice;

typedef struct
{
    void* vec;
    unsigned cap;
    unsigned tamElem;
    unsigned ce;

}T_indice;

void indiceCrear(T_indice* vec);
int indiceInsertar(T_indice* vec, const T_reg_indice* idx); //inserta ordenado
int indiceEliminar(T_indice* vec, T_reg_indice* idx);//elimina dni
int indiceVacio(const T_indice* vec);//verifica si esta vacio
int indiceLleno(const T_indice* vec);
int indiceBuscar(const T_indice* vec, T_reg_indice* idx);//si existe el dni deja el nro de registro en idx
int indiceCargar(T_indice*vec, const char* path);
void indiceVaciar(T_indice* vec);

void mostrarIndice(T_indice* vec);

#endif // INDICE_H_INCLUDED
