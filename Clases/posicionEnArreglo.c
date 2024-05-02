#include <stdio.h>
#include <stdlib.h>

int posicionEnArreglo(int *A, int n, int x)
{
    int i;

    i = 0;
    while (i < n)
    {
        if (A[i] == x)
        {
            return i;
        }
        i++;  //Es lo mismo que i = i+1
    }
    return -1;
}

int *creaArregloDinamico(int n)
{
    int *Arreglo;

    Arreglo = (int *)malloc(n*sizeof(int));
    if (Arreglo == NULL)
    {
        printf("Este programa se cerrara: En estos momentos no hay memoria suficiente.");
        printf("\nCierra algunas aplicaciones y vuelve a intentar. ");
        exit(1);
    }
    return Arreglo;
}

int main()
{
    int *L;
    int n, pos, x;

    n = 8;
    L = creaArregloDinamico(n);
    L[0] = 12;
    L[1] = 60;
    L[2] = 54;
    L[3] = 22;
    L[4] = -3;
    L[5] = 89;
    L[6] = 125;
    L[7] = 4;
    printf("Ingresa el numero a buscar: ");
    scanf("%i", &x);
    pos = posicionEnArreglo(L, n, x);
    if (pos == -1)
    {
        printf("\nEl numero %i, no esta en el arreglo.\n\n", x);
    }
    else
    {
        printf("\nEl numero %i esta en la posicion: %i.\n\n", x, pos);
    }
    system("pause"); //Esta instrucción sirve para que el ejecutable no se cierre de golpe!

    return 0;
}
