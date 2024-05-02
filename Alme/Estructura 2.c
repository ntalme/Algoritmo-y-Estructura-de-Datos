
#include <stdio.h>
#include <string.h>

struct fecha
{
    int dia;
    int mes;
    int anno;
    char mesTexto[10];
};

typedef struct fecha tFecha;

int main()
{
    tFecha h;

    h.dia = 15;
    h.mes = 04;
    h.anno = 2023;
//  h.mesTexto = "Abril";
    //En una estructura para poner string se debe poner:
    strcpy(h.mesTexto, "Abil");

    printf("Hoy: %i de %s del %i\n", h.dia, h.mesTexto, h.anno);

    h.mesTexto[2] = 'r';
    h.mesTexto[3] = 'i';
    h.mesTexto[4] = 'l';
    h.mesTexto[5] = '\0';

    printf("Hoy: %i de %s del %i", h.dia, h.mesTexto, h.anno);
}

