#include <stdio.h>
int main()
{

    int numero;
    //Se crea la variable numero, la cual es la que ingresa el usuario

    int secreto;
    //Se crea la variable secreto, la cual es el numero que hay que adivinar

    secreto = 381;
    //Valor de la variable secreto

    printf("Adivina el numero en el que estoy pensando\n");

    printf("\nIngresa un numero del 1 al 500: ");

    scanf("%i", &numero);
    /* Scanf sirve para leer lo que el usario digite
    En el scanf se le debe poner % y una letra minuscula segun el tipo de dato, por ejemplo si es un numero entero se debe poner %i
    Se debe poner el simbolo & para guardar el dato*/

    printf("\nEl numero que elegiste es: %i\n", numero);
    // Donde se pone %i es donde se mostrara la variable en la consola y ademas despues de la comilla se pone el nombre de la variable qu se quiere mostrar

    if (numero < secreto)
    //Si el numero es mas grande
    {
        printf("\nEscoge un numero mas grande");
    }

    if (numero > secreto)
    //Si el numero mas pequeño
    {
        printf("\nEscoge un numero mas pequeno");
    }

    if (numero == secreto)
    //Si el numero es igual
    {
        printf("\nMuy bien adivinaste el numero");
    }
    return 0;
}
