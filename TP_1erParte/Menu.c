#include "Menu.h"

void desplegar_menu()
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

int seleccionar_opcion(t_indice* idx, char opcion,  char* nArch, t_fecha* fechaP)
{
    int resp;

    switch(opcion)
    {
        case 'a':
            resp = alta_socio(idx, nArch, fechaP);
            break;

        case 'b':
            resp = baja_socio(idx, nArch);
            break;

        case 'c':
            resp = modificar_socio(idx, nArch);
            break;

        case 'd':
            resp = mostrar_info_socio(idx, nArch);
            break;

        case 'e':
            resp = mostrar_socios_activos(idx, nArch);
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

int alta_socio(t_indice* idx, char* nArch, t_fecha* fechaP)
{
    t_socio socio;
    t_reg_indice reg;
    FILE* archivo;
    int resp;

    puts("Ingrese el DNI alta");
    scanf("%ld",&reg.dni);

    resp = indice_buscar(idx,&reg);

    if(resp == ENCONTRADO)
    {
        puts("DNI ingresado ya existe");
        return TODO_OK;
    }

    reg.dni = socio.dni;
    ingresar_datos(&socio);

    if(validar_socio(&socio,fechaP,1)!=TODO_OK )
        return TODO_OK; //salgo y no cargo el socio

    resp = abrir_archivo(&archivo,nArch,"a+b");

    if(resp!=TODO_OK)
        return resp;

    if((resp = indice_insertar(idx,&reg)) != TODO_OK)
    {
        cerrar_archivo(&archivo);
        return resp; //salgo y no cargo el socio
    }

    fseek(archivo,0,SEEK_END);
    fwrite(&socio,sizeof(t_socio),1,archivo);

    cerrar_archivo(&archivo);
    puts("Alta correcta");
    return TODO_OK;
}

int baja_socio(t_indice* idx, char* nArch)
{
    FILE* archivo;
    int resp;
    t_reg_indice reg;
    t_socio socio;

    resp = abrir_archivo(&archivo,nArch,"r+b");

    if(!resp)
        return resp;

    puts("Ingrese el DNI del socio que quiere dar de baja:");
    scanf("%ld", &reg.dni);
    fflush(stdin);

    resp = indice_buscar(idx, &reg);

    if(resp!=ENCONTRADO)
    {
        puts("Socio no encontrado");
        return resp;
    }

    fseek(archivo, reg.nroReg * sizeof(t_socio), SEEK_SET);
    fread(&socio, sizeof(t_socio), 1, archivo);
    socio.estado = 'B';
    fseek(archivo, -1 * (long)sizeof(t_socio), SEEK_CUR);
    fwrite(&socio, sizeof(t_socio), 1, archivo);

    indice_eliminar(idx, &reg);

    cerrar_archivo(&archivo);

    puts("Baja correcta");
    return TODO_OK;
}

int modificar_socio(t_indice* idx, char* nArch)
{
    puts("Modificacion correcta");
    return TODO_OK;
}

int mostrar_info_socio(t_indice* idx, char* nArch)
{
    FILE* archivo;
    int resp;
    t_reg_indice reg;
    t_socio socio;

    resp = abrir_archivo(&archivo,nArch,"rb");

    if(!resp)
        return resp;

    puts("Ingrese el DNI del socio que quiere mostrar:");
    scanf("%ld", &reg.dni);
    fflush(stdin);

    resp = indice_buscar(idx, &reg);

    if(resp!=ENCONTRADO)
    {
        puts("Socio no encontrado");
        return resp;
    }

    fseek(archivo, reg.nroReg * sizeof(t_socio), SEEK_SET);
    fread(&socio, sizeof(t_socio), 1, archivo);

    printf("dni:%ld apyn:%-20s fecha nac:%02d/%02d/%d sexo: %c fecha afil: %02d/%02d/%d categoria: %-10s fecha cuota: %02d/%02d/%d estado: %c\n",socio.dni,socio.apYN,socio.fechaNac.d,socio.fechaNac.m,socio.fechaNac.y,socio.sexo,socio.fechaAfil.d,socio.fechaAfil.m,socio.fechaAfil.y,socio.categoria,socio.fechaCuota.d,socio.fechaCuota.m,socio.fechaCuota.y,socio.estado);

    cerrar_archivo(&archivo);

    return TODO_OK;
}

int mostrar_socios_activos(t_indice* idx, char* nArch)
{
    FILE* archivo;
    int resp;
    t_socio socio;
    char* posIdx;

    resp = abrir_archivo(&archivo,nArch,"rb");

    if(!resp)
        return resp;

    puts("Listado de socios activos ordenados por DNI:");

    for(posIdx = idx->vec; posIdx < (char*)idx->vec + (idx->ce - 1) * idx->tamElem; posIdx += idx->tamElem)
    {
        fseek(archivo, ((t_reg_indice*)posIdx)->nroReg * sizeof(t_socio), SEEK_SET);
        fread(&socio, sizeof(t_socio), 1, archivo);

        if(socio.estado == 'A')
            printf("dni:%ld apyn:%-20s fecha nac:%02d/%02d/%d sexo: %c fecha afil: %02d/%02d/%d categoria: %-10s fecha cuota: %02d/%02d/%d estado: %c\n",socio.dni,socio.apYN,socio.fechaNac.d,socio.fechaNac.m,socio.fechaNac.y,socio.sexo,socio.fechaAfil.d,socio.fechaAfil.m,socio.fechaAfil.y,socio.categoria,socio.fechaCuota.d,socio.fechaCuota.m,socio.fechaCuota.y,socio.estado);
    }

    cerrar_archivo(&archivo);

    return TODO_OK;
}
