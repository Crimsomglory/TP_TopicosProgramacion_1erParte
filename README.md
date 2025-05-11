Variables #define;

#define NOM_TXT "socios.txt"
#define NOM_BIN "socios.dat"
#define NOM_ERRORTXT "socios_erroneos.txt"
#define FECHA_LOCAL 0

#define TAM_REG 110
#define TAM_NYAP 61
#define ERROR -1
#define TODO_OK 1
#define SOCIO_INVALIDO -3

#define ERROR_ARCHIVO 7
#define ARCHIVO_OK 8

#define ES_FECHA 2
#define NO_ES_FECHA -2
#define FECHA_VALIDA 3
#define FECHA_1_MAYOR 4
#define FECHA_2_MAYOR 5
#define FECHAS_IGUALES 6

Estructuras;

typedef struct
{
    int d;
    int m;
    int y;

}T_Fecha;

typedef struct
{
    long dni;
    char apYN[TAM_NYAP];
    T_Fecha fechaNac;
    char sexo;
    T_Fecha fechaAfil;
    char categoria[11];
    T_Fecha fechaCuota;
    char estado;
}T_Socio;
