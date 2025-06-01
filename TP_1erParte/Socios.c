#include "Socios.h"



int crear_archivo_socios_bin(const char* nombrearchTxt, const char* nombreArchBin, const char* nombreArchErrorTxt, t_fecha* fechaProceso)
{
    FILE* archTxt;
    FILE* archBin;
    FILE* archError;
    char registro[TAM_REG];
    char registroOriginal[TAM_REG];
    t_socio socio;

    //apertura de archivos
    if(abrir_archivo(&archTxt,nombrearchTxt,"r") == ERROR_ARCHIVO)
        return ERROR_ARCHIVO;

    if(abrir_archivo(&archBin,nombreArchBin,"wb") == ERROR_ARCHIVO)
    {
        cerrar_archivo(&archTxt);
        return ERROR_ARCHIVO;
    }

    if(abrir_archivo(&archError,nombreArchErrorTxt,"w") == ERROR_ARCHIVO)
    {
        cerrar_archivo(&archTxt);
        cerrar_archivo(&archBin);
        return ERROR_ARCHIVO;
    }

    //leer socios
    while(fgets(registro,sizeof(registro),archTxt) != NULL)
    {
        //printf("Registro txt a validar: %s",registro);
        strcpy(registroOriginal, registro);
        trozar_registro(&socio,registro);

        //validar socio
        if(validar_socio(&socio, fechaProceso, 0) == TODO_OK)
        {
            //cargar socio bin correcto

            fwrite(&socio,sizeof(t_socio),1,archBin);
        }
        else
        {
            //cargar socio error por reg en txt
            fprintf(archError,"%s",registroOriginal);
        }
    }

    //cierre de archivos
    cerrar_archivo(&archTxt);
    cerrar_archivo(&archBin);
    cerrar_archivo(&archError);

    //leer_archivo();

    return TODO_OK;
}

int validar_socio(t_socio* socio, t_fecha* fechaProceso,int avisarError)
{
    int resp;

    if(socio->dni < 10000 || socio->dni >100000000) //validar DNI 10.000 < DNI < 100.000.000
    {
        if(avisarError)
            puts("dni no valido");
        return SOCIO_INVALIDO;
    }

    if( validar_fecha(&socio->fechaNac)!=ES_FECHA) //validar fecha nac Validación formal y < fecha de proceso – 10 años
    {
        if(avisarError)
            puts("fecha nac no es fecha");
        return SOCIO_INVALIDO;
    }

    fechaProceso->y-=10;
    resp = comparar_fechas(&socio->fechaNac, fechaProceso);
    fechaProceso->y+=10;

    if(resp != FECHA_2_MAYOR)
    {
        if(avisarError)
            puts("fecha nac mayor a fecha proceso");
        return SOCIO_INVALIDO;
    }

    if(socio->sexo != 'F' && socio->sexo != 'M') //validar sexo F o M
    {
        if(avisarError)
            puts("sexo incorrecto");
        return SOCIO_INVALIDO;
    }

    resp = comparar_fechas(&socio->fechaAfil, &socio->fechaNac); //validar fecha afiliacion Validación formal, <= fecha de proceso y > fecha nacimiento
    if(resp != FECHA_1_MAYOR)
    {
        if(avisarError)
            puts("fecha afiliacion menor a fecha nac");
        return SOCIO_INVALIDO;
    }

    resp = comparar_fechas(&socio->fechaAfil,fechaProceso);
    if(resp==FECHA_1_MAYOR)
    {
        if(avisarError)
            puts("fecha afiliacion mayor a fecha proceso");
        return SOCIO_INVALIDO;
    }

    //validar categoria MENOR ADULTO VITALICIO u HONORARIO
    if(strcmp(socio->categoria, "MENOR") != 0 && strcmp(socio->categoria, "ADULTO") != 0 && strcmp(socio->categoria, "VITALICIO") != 0 && strcmp(socio->categoria, "HONORARIO") != 0)
    {
        if(avisarError)
            puts("categoria invalida");
        return SOCIO_INVALIDO;
    }

    resp = comparar_fechas(&socio->fechaCuota,&socio->fechaAfil); //validar fecha cuota > fecha de afiliación y <= fecha de proceso
    if(resp != FECHA_1_MAYOR)
    {
        if(avisarError)
            puts("fecha cuota menor a fecha afiliacion");
        return SOCIO_INVALIDO;
    }

    resp = comparar_fechas(&socio->fechaCuota,fechaProceso);
    if(resp == FECHA_1_MAYOR)
    {
        if(avisarError)
            puts("fecha cuota mayor a fecha proceso");
        return SOCIO_INVALIDO;
    }

    //validar estado, A o B
    if(socio->estado != 'A')
    {
        if(avisarError)
            puts("estado invalido");
        return SOCIO_INVALIDO;
    }

    //printf("dni:%ld apyn:%-20s fecha nac:%02d/%02d/%d sexo: %c fecha afil: %02d/%02d/%d categoria: %-10s fecha cuota: %02d/%02d/%d estado: %c\n",socio->dni,socio->apYN,socio->fechaNac.d,socio->fechaNac.m,socio->fechaNac.y,socio->sexo,socio->fechaAfil.d,socio->fechaAfil.m,socio->fechaAfil.y,socio->categoria,socio->fechaCuota.d,socio->fechaCuota.m,socio->fechaCuota.y,socio->estado);

    return TODO_OK;

}

void trozar_registro(t_socio *socio, char* linea)
{
    char* pos = strchr(linea,'\n');
    *pos = '\0';

    pos = strrchr(linea,SEPARADOR_TXT);
    sscanf(pos+1,"%c",&socio->estado);
    socio->estado = toupper((unsigned char)socio->estado);
    *pos = '\0';

    pos = strrchr(linea,SEPARADOR_TXT);
    sscanf(pos+1,"%d/%d/%d",&socio->fechaCuota.d,&socio->fechaCuota.m,&socio->fechaCuota.y);
    *pos = '\0';

    pos = strrchr(linea,SEPARADOR_TXT);
    strcpy(socio->categoria, pos + 1);
    pal_mayus(socio->categoria);
    *pos = '\0';

    pos = strrchr(linea,SEPARADOR_TXT);
    sscanf(pos+1,"%d/%d/%d",&socio->fechaAfil.d,&socio->fechaAfil.m,&socio->fechaAfil.y);
    *pos = '\0';

    pos = strrchr(linea,SEPARADOR_TXT);
    sscanf(pos+1,"%c",&socio->sexo);
    socio->sexo = toupper((unsigned char)socio->sexo);
    *pos = '\0';

    pos = strrchr(linea,SEPARADOR_TXT);
    sscanf(pos+1,"%d/%d/%d",&socio->fechaNac.d,&socio->fechaNac.m,&socio->fechaNac.y);
    *pos = '\0';

    pos = strrchr(linea,SEPARADOR_TXT);
    strcpy(socio->apYN, pos + 1);
    normalizarNyAp(socio->apYN);
    *pos = '\0';

    sscanf(linea,"%ld",&socio->dni);
    //printf("\n\n%c,%d/%d/%d,%s\n\n",socio->estado,socio->fechaCuota.d,socio->fechaCuota.m,socio->fechaCuota.y,socio->categoria);
}

void normalizarNyAp(char* nyap)
{
    char* pos = nyap;
    char palAux[TAM_NYAP];
    char* posPal = palAux;
    int comaAgregada = 0;

    while(*pos!='\0')
    {
        while(*pos!='\0' && (*pos == ' ' || *pos == ','))//busco primer caracter
            pos++;

        if(*pos!='\0')
        {
            *posPal = toupper(*pos);//primer letra a mayuscula
            pos++;
            posPal++;
        }

        while(*pos!='\0' && (*pos != ' ' && *pos != ','))
        {
            *posPal = tolower(*pos);//resto de letras en minuscula
            pos++;
            posPal++;
        }

        if(!comaAgregada)//agrego coma
        {
            *posPal = ',';
            posPal++;
            comaAgregada = 1;
        }

        *posPal = ' ';//finalizo con espacio
        posPal++;
    }
    //si viene un solo nombre sin apellido
    if(*(posPal-2) == ',')
        *(posPal-2) = '\0';
    else
        *(posPal-1) = '\0';

    //se copia la palabra normalizada a la cadena original
    //printf("pal aux %s\n",palAux);
    strcpy(nyap,palAux);
}

int abrir_archivo(FILE** ptr, const char* nomArch, const char* modo)
{
    *ptr = fopen(nomArch,modo);

    if(*ptr)
        return TODO_OK;

    printf("Error al abrir el archivo %s en modo %s\n",nomArch,modo);

    return ERROR_ARCHIVO;
}

void cerrar_archivo(FILE** ptr)
{
    if(*ptr)
        fclose(*ptr);
}

void leer_archivo()
{
    FILE* ptr = fopen("socios.dat","rb");

    if(!ptr)
        return;

    t_socio socio;

    fread(&socio,sizeof(t_socio),1,ptr);

    while(!feof(ptr))
    {
        printf("dni:%ld apyn:%-20s fecha nac:%02d/%02d/%d sexo: %c fecha afil: %02d/%02d/%d categoria: %-10s fecha cuota: %02d/%02d/%d estado: %c\n",socio.dni,socio.apYN,socio.fechaNac.d,socio.fechaNac.m,socio.fechaNac.y,socio.sexo,socio.fechaAfil.d,socio.fechaAfil.m,socio.fechaAfil.y,socio.categoria,socio.fechaCuota.d,socio.fechaCuota.m,socio.fechaCuota.y,socio.estado);
        fread(&socio,sizeof(t_socio),1,ptr);
    }

    fclose(ptr);

}

void ingresar_datos(t_socio* socio)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Ingrese nombre y apellido: ");
    fgets(socio->apYN, sizeof(socio->apYN), stdin); //viene con \n por input
    socio->apYN[strcspn(socio->apYN, "\n")] = '\0'; //coloco \0 en en el salto de linea
    normalizarNyAp(socio->apYN);

    fflush(stdin);
    printf("Ingrese fecha de nacimiento: ");
    scanf("%d/%d/%d",&socio->fechaNac.d,&socio->fechaNac.m,&socio->fechaNac.y);

    printf("Ingrese sexo: ");
    scanf(" %c",&socio->sexo);
    socio->sexo = toupper(socio->sexo);

    printf("Ingrese fecha de afiliacion: ");
    scanf("%d/%d/%d",&socio->fechaAfil.d,&socio->fechaAfil.m,&socio->fechaAfil.y);

    printf("Ingrese categoria: ");
    scanf("%s",socio->categoria);
    pal_mayus(socio->categoria);

    printf("Ingrese fecha de cuota: ");
    scanf("%d/%d/%d",&socio->fechaCuota.d,&socio->fechaCuota.m,&socio->fechaCuota.y);

    socio->estado = 'A';
}

void pal_mayus(char* linea)
{
    char* cad = linea;

    while(*cad)
    {
        *cad = toupper((unsigned char)*cad);
        cad++;
    }
}
