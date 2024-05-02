#include <stdio.h>
#include <string.h> //Sirve para trabajar con arreglos de caracteres


void generaCorreo() //void significa q no retorna nada
{
//  - char es para poner variables con letras (sting) y lo que esta adentro [] sigifica la cantidad de caracteres
    char nombre[50], aPaterno[50], aMaterno[50], correo[150];

//  Nombre
    printf("Primer nombre: ");
    fgets(nombre, 50, stdin);
//     - fgets(nombre arreglo, tamaño, stdin) esto sirve para mostrar todo el string
    printf("\nNombre: %s \n", nombre);
//      - %s es para leer strings
    strtok(nombre, "\n");

//    printf("\nNombre: %s_", nombre);
//    strtok(nombre, "\n");
//     - strtok sirve para cortar el enter que esta leyendo fgets
//    printf("\nNombre: %s_\n", nombre);
//     - Se debe volver a colocar para que _ se pomga al lado

//  Apellido Paterno
    printf("Apellido Paterno (omite los espacios): ");
    fgets(aPaterno, 50, stdin);
    printf("\nApellido Paterno: %s \n", aPaterno);
    strtok(aPaterno, "\n");

//  Apellido Materno
    printf("Apellido Materno (omite los espacios): ");
    fgets(aMaterno, 50, stdin);
    printf("\nApellido Materno: %s \n", aMaterno);
    strtok(aMaterno, "\n");

//  Correo
//    strcpy(correo, nombre);
//    - strcpy sirve para copiar algo y colocarlo en otra parte pero elimina lo que habia anteriormente
    correo[0] = nombre[0];
//    - se pone en la posicion 0 de la variable correo el caracter que esta en la posicion 0 de la variable nombre
    correo[1] = '\0';
    strcat(correo, ".");
//    - strcat sirve para copiar algo y colocarlo en otra parte e ir encadenandolo
    strcat(correo, aPaterno);
    strcat(correo, aMaterno);
    strcat(correo, "@uandresbello.edu");
    printf("Correo unab: %s", correo);
}


int main ()
{
    generaCorreo();
//  - recordar llamar a la funcion
    return 0;
}
