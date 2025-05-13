#include "indice.h"

void indiceCrear(T_indice* vec)
{
    void* ptr = malloc(TAM_VEC* sizeof(T_reg_indice));

    if(!ptr)
    {
        puts("Sin memoria");
        return;
    }

    vec->vec = ptr;
    vec->cap = TAM_VEC;
    vec->ce = 0;
    vec->tamElem = sizeof(T_reg_indice);
}

void indiceVaciar(T_indice* vec)
{
    if(!vec->vec)
        free(vec->vec);
}
