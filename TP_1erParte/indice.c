#include "indice.h"

int compararRegs(const void* e1, const void* e2);

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

int indiceCargar(T_indice*vec, const char* path)
{
    FILE* ptrArch;
    int resp;
    T_Socio socio;
    T_reg_indice idx;
    int i=0; //posición de registros

    resp = abrirArchivo(&ptrArch,path,"rb");

    if(resp  == ERROR_ARCHIVO)
        return resp;

    fread(&socio,sizeof(T_Socio),1,ptrArch);

    while(!feof(ptrArch))
    {
        idx.dni = socio.dni;
        idx.nroReg = i;
        resp = indiceInsertar(vec,&idx);

        if(resp!=TODO_OK)
        {
            cerrarArchivo(&ptrArch);
            return resp; //sin espacio
        }

        fread(&socio,sizeof(T_Socio),1,ptrArch);
        i++;
    }

    cerrarArchivo(&ptrArch);
    return TODO_OK;
}

int indiceInsertar(T_indice* vec, const T_reg_indice* idx)
{
    void* ult = vec->vec + vec->ce * vec->tamElem;
    void* pos = vec->vec;

    if(vec->ce == vec->cap)
        return VEC_LLENO;

    while(pos<ult && compararRegs(pos,idx) < 0)
        pos+=vec->tamElem;

    for(void* i = ult; i > pos ; i-=vec->tamElem)
        memcpy(i,i-vec->tamElem,vec->tamElem);

    memcpy(pos,idx,vec->tamElem);
    vec->ce++;

    return TODO_OK;
}

int compararRegs(const void* e1, const void* e2)
{
    T_reg_indice* reg1 = (T_reg_indice*)e1;
    T_reg_indice* reg2 = (T_reg_indice*)e2;

    return reg1->dni - reg2->dni;
}

void mostrarIndice(T_indice* vec)
{
    void* ult = vec->vec + vec->ce * vec->tamElem;
    T_reg_indice* reg;

    for(void* i = vec->vec;i<ult;i+=vec->tamElem)
    {
        reg = (T_reg_indice*)i;
        printf("dni:%10ld nro reg: %d\n",reg->dni,reg->nroReg);
    }
}

int indiceVacio(const T_indice* vec)
{
    if(vec->ce == 0)
        return VEC_VACIO;

    return TODO_OK;
}

int indiceLleno(const T_indice* vec)
{
    if(vec->ce == vec->cap)
        return VEC_LLENO;

    return TODO_OK;
}

int indiceBuscar(const T_indice* vec, T_reg_indice* idx)
{
    void* ult = vec->vec + vec->ce * vec->tamElem;

    for(void* i = vec->vec;i<ult;i+=vec->tamElem)
    {
        if(compararRegs(i,idx)==0)
        {
            memcpy(idx,i,vec->tamElem);
            return ENCONTRADO;
        }
    }

    return NO_ENCONTRADO;
}
