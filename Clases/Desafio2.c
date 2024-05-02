#include <stdio.h>
int main()
{
    int numero;
    int secreto;

    secreto = 381;

    printf("Adivina el numero en el que estoy pensando\n");

    while (numero!= secreto)
    {

    printf("\nIngresa un numero del 1 al 500: ");

    scanf("%i", &numero);

    if (numero < secreto)
    //Si el numero es mas grande
    {
        printf("\nEscoge un numero mas grande\n");
    }

    if (numero > secreto)
    //Si el numero mas pequeño
    {
        printf("\nEscoge un numero mas pequeno\n");
    }

    if (numero == secreto)
    //Si el numero es igual
    {
        printf("\nMuy bien adivinaste el numero\n");
    }

    }

    return 0;
}
