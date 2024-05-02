#include <stdio.h>
#include <string.h>

void prueba()
{
    char letra [10];
    char nombre [50];

    printf("Primer nombre: ");
    fgets(nombre, 50, stdin);
    strtok(nombre, "\n");

    letra[0] = nombre[4];
    printf("%s", letra);
}



int main()
{
    prueba();
    return 0;
}
