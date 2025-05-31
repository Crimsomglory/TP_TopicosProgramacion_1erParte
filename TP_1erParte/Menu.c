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

void desplegar_menu_mod()
{
    puts("");
    puts("Seleccione una opcion a modificar");
    puts("a. Nombre y Apellido");
    puts("b. Fecha de nacimiento");
    puts("c. Sexo");
    puts("d. Fecha de afiliacion");
    puts("e. Categoria");
    puts("f. Fecha de cuota");
    puts("g. Salir");
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
            resp = modificar_socio(idx, nArch, fechaP);
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
            puts("Opcion invalida");
            resp = TODO_OK;
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

    socio.dni = reg.dni;

    ingresar_datos(&socio);

    puts("");

    if(validar_socio(&socio,fechaP,1)!=TODO_OK )
        return TODO_OK; //salgo y no cargo el socio

    normalizarNyAp(socio.apYN);

    resp = abrir_archivo(&archivo,nArch,"a+b");

    if(resp!=TODO_OK)
        return resp;

    fseek(archivo,0,SEEK_END);
    reg.nroReg = (unsigned)ftell(archivo)/sizeof(t_socio);

    if((resp = indice_insertar(idx,&reg)) != TODO_OK)
    {
        cerrar_archivo(&archivo);
        return resp; //salgo y no cargo el socio
    }

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

    resp = indice_buscar(idx, &reg);

    if(resp!=ENCONTRADO)
    {
        puts("Socio no encontrado");
        return TODO_OK;
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

int modificar_socio(t_indice* idx, char* nArch, t_fecha* fechaP)
{
    t_socio socio;
    t_reg_indice reg;
    FILE* archivo;
    int resp;
    char opcion;

    resp = abrir_archivo(&archivo,nArch,"r+b");

    if(resp!=TODO_OK)
        return resp;

    puts("Ingrese el DNI para la modificacion");
    scanf("%ld",&reg.dni);

    resp = indice_buscar(idx,&reg);

    if(resp != ENCONTRADO)
    {
        puts("DNI no econtrado");
        return TODO_OK;
    }

    fseek(archivo,sizeof(t_socio)*reg.nroReg,SEEK_CUR);
    fread(&socio,sizeof(t_socio),1,archivo);
    desplegar_menu_mod();
    scanf(" %c", &opcion);
    opcion = tolower(opcion);

    while(opcion != 'g')
    {
        switch(opcion)
        {
        case 'a':
            printf("Ingrese nombre y apellido: ");
            //Lee todo el buffer y elimina el \n para que no lo tome en la proxima lectura
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            fgets(socio.apYN, sizeof(socio.apYN), stdin);
            socio.apYN[strcspn(socio.apYN, "\n")] = '\0';
            normalizarNyAp(socio.apYN);
            break;

        case 'b':
            printf("Ingrese fecha de nacimiento: ");
            scanf("%d/%d/%d",&socio.fechaNac.d,&socio.fechaNac.m,&socio.fechaNac.y);
            printf("%d/%d/%d",socio.fechaNac.d,socio.fechaNac.m,socio.fechaNac.y);
            break;

        case 'c':
            printf("Ingrese sexo: ");
            scanf(" %c",&socio.sexo);
            break;

        case 'd':
            printf("Ingrese fecha de afiliacion: ");
            scanf("%d/%d/%d",&socio.fechaAfil.d,&socio.fechaAfil.m,&socio.fechaAfil.y);
            break;

        case 'e':
            printf("Ingrese categoria: ");
            scanf("%s",socio.categoria);
            break;

        case 'f':
            printf("Ingrese fecha de cuota: ");
            scanf("%d/%d/%d",&socio.fechaCuota.d,&socio.fechaCuota.m,&socio.fechaCuota.y);
            break;

        case 'g':
            break;
        default:
            puts("Opcion invalida");
            break;
        }

        if(opcion != 'g')
        {
            resp = validar_socio(&socio,fechaP,1);
            if(resp!=TODO_OK)
            {
                fclose(archivo);
                return TODO_OK;
            }

        }

        desplegar_menu_mod();
        scanf(" %c", &opcion);
        opcion = tolower(opcion);
    }

    fseek(archivo,-(long)sizeof(t_socio),SEEK_CUR);
    fwrite(&socio,sizeof(t_socio),1,archivo);
    fclose(archivo);

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
        return TODO_OK;
    }

    fseek(archivo, reg.nroReg * sizeof(t_socio), SEEK_SET);
    fread(&socio, sizeof(t_socio), 1, archivo);

    puts("");
    puts("");
    printf("dni:%ld \napyn:%-20s \nfecha nac:%02d/%02d/%d \nsexo: %c \nfecha afil: %02d/%02d/%d \ncategoria: %-10s \nfecha cuota: %02d/%02d/%d \nestado: %c\n",socio.dni,socio.apYN,socio.fechaNac.d,socio.fechaNac.m,socio.fechaNac.y,socio.sexo,socio.fechaAfil.d,socio.fechaAfil.m,socio.fechaAfil.y,socio.categoria,socio.fechaCuota.d,socio.fechaCuota.m,socio.fechaCuota.y,socio.estado);

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
