#include "indice.h"

int comparar_regs(const void* e1, const void* e2);

void indice_crear(t_indice* vec)
{
    void* ptr = malloc(TAM_VEC* sizeof(t_reg_indice));

    if(!ptr)
    {
        puts("Sin memoria");
        return;
    }

    vec->vec = ptr;
    vec->cap = TAM_VEC;
    vec->ce = 0;
    vec->tamElem = sizeof(t_reg_indice);
}

void indice_vaciar(t_indice* vec)
{
    if(vec->vec)
    {
        free(vec->vec);
        vec->vec = NULL;
    }
    vec->ce = 0;
    vec->cap = 0;
}

int indice_cargar(t_indice*vec, const char* path)
{
    FILE* ptrArch;
    int resp;
    t_socio socio;
    t_reg_indice idx;
    int i=0; //posición de registros

    resp = abrir_archivo(&ptrArch,path,"rb");

    if(resp  == ERROR_ARCHIVO)
        return resp;

    fread(&socio,sizeof(t_socio),1,ptrArch);

    while(!feof(ptrArch))
    {
        idx.dni = socio.dni;
        idx.nroReg = i;
        resp = indice_insertar(vec,&idx);

        if(resp!=TODO_OK)
        {
            cerrar_archivo(&ptrArch);
            return resp; //sin espacio
        }

        fread(&socio,sizeof(t_socio),1,ptrArch);
        i++;
    }

    fclose(ptrArch);
    return TODO_OK;
}

int indice_insertar(t_indice* vec, const t_reg_indice* idx)
{
    void* ult;
    void* pos;
    void* aux;
    unsigned nuevaCapacidad;

    if(vec->ce == vec->cap)
    {
        nuevaCapacidad = (size_t)ceil((float)(vec->cap * (PORCENTAJE_CRECIMIENTO)));
        //printf("redimension de %d a %u\n",vec->cap,nuevaCapacidad);

        aux = realloc(vec->vec, nuevaCapacidad * vec->tamElem);

        if(!aux)
            return SIN_MEM;

        vec->vec = aux;
        vec->cap = nuevaCapacidad;
    }

    ult = vec->vec + vec->ce * vec->tamElem;
    pos = vec->vec;

    while(pos<ult && comparar_regs(pos,idx) < 0)
        pos+=vec->tamElem;
    //voy moviendo todos los elementos desde el ultimo dato ingresado, uno siempre a la derecha
    for(void* i = ult; i > pos ; i-=vec->tamElem)
        memcpy(i,i-vec->tamElem,vec->tamElem);

    memcpy(pos,idx,vec->tamElem);
    vec->ce++;

    return TODO_OK;
}

int indice_eliminar(t_indice* vec, t_reg_indice* idx)
{
    char* ult = vec->vec + vec->ce * vec->tamElem;
    char* pos = vec->vec;
    int res;

    while(pos<ult && (res = comparar_regs(pos,idx)) < 0)
        pos+=vec->tamElem;

    if(res != 0)
        return NO_ENCONTRADO;

    memmove(pos, pos + vec->tamElem, ult - (pos + vec->tamElem));

    vec->ce--;

    return TODO_OK;
}

int comparar_regs(const void* e1, const void* e2)
{
    t_reg_indice* reg1 = (t_reg_indice*)e1;
    t_reg_indice* reg2 = (t_reg_indice*)e2;

    return reg1->dni - reg2->dni;
}

void mostrar_indice(t_indice* vec)
{
    void* ult = vec->vec + vec->ce * vec->tamElem;
    t_reg_indice* reg;

    for(void* i = vec->vec;i<ult;i+=vec->tamElem)
    {
        reg = (t_reg_indice*)i;
        printf("dni:%10ld nro reg: %d\n",reg->dni,reg->nroReg);
    }
}

int indice_vacio(const t_indice* vec)
{
    if(vec->ce == 0)
        return VEC_VACIO;

    return TODO_OK;
}

int indice_lleno(const t_indice* vec)
{
    if(vec->ce == vec->cap)
        return VEC_LLENO;

    return TODO_OK;
}

int indice_buscar(const t_indice* vec, t_reg_indice* idx)
{
    void* ult = vec->vec + vec->ce * vec->tamElem;

    for(void* i = vec->vec;i<ult;i+=vec->tamElem)
    {
        if(comparar_regs(i,idx)==0)
        {
            memcpy(idx,i,vec->tamElem);
            return ENCONTRADO;
        }
    }

    return NO_ENCONTRADO;
}
