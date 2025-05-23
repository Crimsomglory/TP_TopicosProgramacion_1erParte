#include "Menu.h"

void desplegarMenu()
{
    puts("");
    puts("Seleccione una opcion");
    puts("a. Alta");
    puts("b. Baja");
    puts("c. Modificacion");
    puts("d. Mostrar informacion de un socio");
    puts("e. Listado de socios ordenados por clave(DNI)");
    puts("f. Salir");
    puts("");
}

int seleccionarOpcion(T_indice* idx, char opcion,  char* nArch, T_Fecha* fechaP)
{
    int resp;

    switch(opcion)
    {
        case 'a':
            resp = altaSocio(idx, nArch, fechaP);
            break;

        case 'b':
            resp = bajaSocio(idx, nArch);
            break;

        case 'c':
            resp = modificarSocio(idx, nArch);
            break;

        case 'd':
            resp = mostrarInfoSocio(idx, nArch);
            break;

        case 'e':
            resp = mostrarSociosActivos(idx, nArch);
            break;

        case 'f':
            resp = TODO_OK;
            break;

        default:
            resp = puts("Opcion invalida");
            break;
    }

    return resp;
}

int altaSocio(T_indice* idx, char* nArch, T_Fecha* fechaP)
{
    T_Socio socio;
    T_reg_indice reg;
    FILE* archivo;
    int resp;

    if(indiceLleno(idx) == VEC_LLENO)
    {
        puts("Registro lleno");
        return TODO_OK;
    }

    puts("Ingrese el DNI alta");
    scanf("%ld",&reg.dni);

    resp = indiceBuscar(idx,&reg);

    if(resp == ENCONTRADO)
    {
        puts("DNI ingresado ya existe");
        return TODO_OK;
    }

    reg.dni = socio.dni;
    ingresarDatos(&socio);

    if(validarSocio(&socio,fechaP,1)!=TODO_OK )
        return TODO_OK; //salgo y no cargo el socio

    resp = abrirArchivo(&archivo,nArch,"a+b");

    if(resp!=TODO_OK)
        return resp;

    if(indiceInsertar(idx,&reg) != TODO_OK)
    {
        cerrarArchivo(&archivo);
        return TODO_OK; //salgo y no cargo el socio
    }

    fseek(archivo,0,SEEK_END);
    fwrite(&socio,sizeof(T_Socio),1,archivo);

    cerrarArchivo(&archivo);
    puts("Alta correcta");
    return TODO_OK;
}

int bajaSocio(T_indice* idx, char* nArch)
{
    puts("Baja correcta");
    return TODO_OK;
}

int modificarSocio(T_indice* idx, char* nArch)
{
    puts("Modificacion correcta");
    return TODO_OK;
}

int mostrarInfoSocio(T_indice* idx, char* nArch)
{
    return TODO_OK;
}

int mostrarSociosActivos(T_indice* idx, char* nArch)
{
    return TODO_OK;
}
