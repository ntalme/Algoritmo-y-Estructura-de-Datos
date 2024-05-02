#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void leeArchivo()
{
// VARIABLES
    char nomArchivo [20];
//    char nomArchivoSal [20];
    char linea [100];
    char *rut;
    char *nombre;
    char *cadena;
    int edad;
    FILE * archivo;
//    FILE * archivoSal;

// BUSCAR ARCHIVO
    printf("Ingrese nombre del archivo: ");
    fgets(nomArchivo, 20, stdin);
    strtok(nomArchivo, "\n");
    //printf("%s", nomArchivo);

    archivo = fopen(nomArchivo, "r");

// SI EL ARCHIVO NO SE ENCUENCUENTRA
    if (archivo == NULL)
    {
        printf(" Archivo no se encuentra, por lo que el programa se cerrara.");
        exit(-1);
    }
// LEER LA PRIMERA LINEA DEL ARCHIVO
//    fgets(linea, 100, archivo);
//    printf("%s", linea);

// CREAR ARCHIVO .SAL
//    strcpy(nomArchivoSal, nomArchivo); //Copiar el archivo
//    strtok(nomArchivoSal, "."); //Borrar desde un caracter el archivo
//    strcat(nomArchivoSal, ".sal"); //Añadirle al final
//    archivoSal = fopen(nomArchivoSal, "w");

// LEER TODO EL ARCHIVO
    while (fgets(linea, 100, archivo) != 0)
    {
      //printf("%s", linea);
        strtok(linea, "\n");

// SEPARAR LOS DATOS
        rut = strtok(linea, ","),
        nombre = strtok(NULL,",");
        cadena = strtok(NULL,",");

// TRANSFORMA A NUMERO
        edad = atoi(cadena);
        printf ("RUT: %s - Nombre: %s - Edad: %i \n", rut, nombre, edad);

////ESCRIBIR EN EL ARCHIVO CREADO
//     fprintf (archivoSal, "RUT: %s - Nombre: %s - Edad: %i \n", rut, nombre, edad);
    }

    fclose(archivo);
}

int main()
{
    leeArchivo();
    return 0;

}
