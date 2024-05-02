#include <stdio.h>
#include <stdlib.h> //Ayuda a utilizar la funcion srand y rand
#include <time.h> // Ayuda a utilizar la funcion time

int main()
{
    int numero;
    int secreto;


    srand(time(NULL)); //Todo esto el q permite al programa generar un numero aleatorio

	secreto = rand() % 501 + 1; //Con esto definimos el rango q tendra para generarse el numero
    //Si queremos generar números del 0-10 ese número máximo seria “%11” (N+1).
    //Si quisiéramos generar números en un rango que no empiece en 0, si no q empiece en 20, tendríamos que sumarle 20 al número aleatorio generado: %11 + 20

    printf("Adivina el n%cmero en el que estoy pensando\n", 163 );
    // Se debe poner %c cuando se necesite poner un caracter de ASCII
    // Y al final despues de una coma se debe colocar el numero del caracter correspoondiente

    while (numero!= secreto)
    {

    printf("\nIngresa un n%cmero entero del 1 al 500: ", 163);

    scanf("%i", &numero);

    if (numero < secreto)
    //Si el numero es mas grande
    {
        printf("\nEscoge un n%cmero m%cs grande\n", 163, 160);
    }

    if (numero > secreto)
    //Si el numero mas pequeño
    {
        printf("\nEscoge un n%cmero m%cs pequeno\n", 163, 160);
    }

    if (numero == secreto)
    //Si el numero es igual
    {
        printf("\nMuy bien adivinaste%c El n%cmero era: %i",33 ,163 ,secreto );
    }

    }

    return 0;
}

