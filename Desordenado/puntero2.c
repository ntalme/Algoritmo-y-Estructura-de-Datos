#include <stdio.h>

int main()
{
    char C;
    int I;
    float F;
    char *pC;
    int *pI;
    float *pF;

    C = '@';
    I = 25;
    F = 4.23;
    pC = &C;
    pI = &I;
    pF = &F;
    printf("\nvar C: %c", C);
    printf("\nvar I: %i", I);
    printf("\nvar F: %f", F);
    *pC = '+';
    *pI = (*pI)*2;
    *pF = (*pF)+10;
    printf("\n\nvar C: %c", C);
    printf("\nvar I: %i", I);
    printf("\nvar F: %f", F);

    printf("\n\n");
    return 0;
}
