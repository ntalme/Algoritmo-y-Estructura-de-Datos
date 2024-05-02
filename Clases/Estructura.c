#include <stdio.h>
#include <string.h>

struct perro{
    char nombre[20]; //nombre[20] cantidad de caracteres de esa variable
    int edad;
    char comidafav[20];
};

typedef struct perro tPerro; //Cambiar nombre

int main(){

    tPerro p1 = {"Loki", 2};
    //Cambio de nombre de la variable y definimos los datos q va a guardar, se tiene q poner apenas se declara

    printf("Ingresa nombre del perro: ");
    fgets(p1.nombre, 20, stdin);
    //fgets es para leer cadena de caracteres
    strtok(p1.nombre,"\n");
    //strtok quitar un enter que se genera

    printf("Ingresa la edad: ");
    scanf("%i", &p1.edad);
    //scanf(tipo de variable, donde se va a guardar)

    printf("Ingresa la comida: ");
    fgets(p1.comidafav, 20, stdin);

    printf("\nMi perro se llama %s, tiene %i a%cos y su comida favorita es %s", p1.nombre, p1.edad, pl.comidafav 164);
    //%c para poner un caracter





    return 0;
}
