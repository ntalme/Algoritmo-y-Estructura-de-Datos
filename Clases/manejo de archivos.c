#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Como se abren 2 archivos en este programa, con esta función se centraliza el proceso de analizar si se pudo
// abrir correctamente el archivo, en vez de escribir esto 2 veces.
void analizaArchivo(FILE *arch, char nomArch[30])
{
    if (arch == NULL) {
        printf("No se puede abrir el archivo %s.", nomArch);
        printf("\nEste programa se cerrara.");
        printf("\n");
        system("pause");
        exit(-1);
    }
}
void leeArchivo()
{
    char nomArch[30], nomArchSalida[30], linea[100];
    FILE *arch, *archSalida;
    char *rut;
    char *nombre;
    char *trozo;
    int edad;

    printf("Ingresa el nombre del archivo: ");
    fgets(nomArch, 30, stdin);
    strtok(nomArch, "\n");   //Le corta el "ENTER" del final de la línea.

    arch = fopen(nomArch, "r");
    analizaArchivo(arch, nomArch); //Función que revisa si un archivo se abrió correctamente.

    strcpy(nomArchSalida, nomArch);
    strtok(nomArchSalida, ".");
    strcat(nomArchSalida, ".sal");

    archSalida = fopen(nomArchSalida, "w");
    analizaArchivo(archSalida, nomArchSalida);

    while (fgets(linea, 200, arch) != 0) //"fgets" retorna un 0 cuando no queda más información dentro del archivo.
    {
        if (strlen(linea) == 1) //Por si el archivo trae líneas extras en blanco: Si es así, se termina el ciclo de lectura
        {
            break;
        }
        strtok(linea, "\n");
        rut = strtok(linea, ",");
        nombre = strtok(NULL, ",");
        trozo = strtok(NULL, ",");
        edad = atoi(trozo);
        printf("rut: %10s nombre: %-25s edad: %4i\n", rut, nombre, edad);
        fprintf(archSalida, "rut: %10s nombre: %-25s edad: %4i\n", rut, nombre, edad);
    }
    fclose(arch);
    fclose(archSalida);
    printf("\nRevisa el archivo \"%s\" en la ubicacion de este programa!!!", nomArchSalida);
}
void proceso()
{
    leeArchivo();
}

int main()
{
    proceso();
    printf("\n\n");
    system("pause");

    return 0;
}
