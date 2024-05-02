
#include <stdio.h>

int main()
{

    int numero;
    int secreto;

    secreto = 381;

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
