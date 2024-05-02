#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **Grafo; //Matriz del grafo
int numNodos;
int numArcos;

int **creaMatriz(int filas, int columnas)
{
   int **Matriz;
   int i;

   Matriz = calloc(filas, sizeof(int *));

   for(i=0; i<filas; i++)
   {
      Matriz[i] = calloc(columnas, sizeof(int));
   }
   return Matriz;
}
void imprimeMatriz(int **M, int n)
{
    int i, j;

    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            printf("%4i", M[i][j]);
        }
        printf("\n");
    }
}
void leeGrafo(char nomArchivo[30])
{
    FILE *arch;
    int i, nodo1, nodo2, costo;

    arch = fopen(nomArchivo, "r");

    if(arch == NULL)
    {
        printf("El archivo no se encontro, adios");
        exit(-1);
    }

    fscanf(arch, "%i", &numNodos);
    Grafo = creaMatriz(numNodos, numNodos);

    fscanf(arch, "%i", &numArcos);

    for(i=1; i<=numArcos; i++)
    {
       fscanf(arch, "%i", &nodo1);
       fscanf(arch, "%i", &nodo2);
       //fscanf(arch, "%i", &costo);

       Grafo[nodo1][nodo2] = 1; //como no exite costo se debe colocar el valor 1
       Grafo[nodo2][nodo1] = 1;
    }
    fclose(arch);
}

int AmigosEnComun(int nodo1, int nodo2)
{
    int i;
    int contador;
    contador = 0;

    for (i=0; i<numNodos; i++)
    {
        if (Grafo[nodo1][i] != 0 && Grafo[nodo2][i] != 0)
        {
            contador++;
        }
    }
    Grafo[nodo1][nodo2] = contador;
    return contador;
}

void inicioProceso()
{
    char nomArchivo[30];
    int Amigos;

    printf("Ingresa nombre del archivo: ");
    fgets(nomArchivo, 30, stdin);
    strtok(nomArchivo, "\n");

    leeGrafo(nomArchivo);

    imprimeMatriz(Grafo, numNodos);

    Amigos = AmigosEnComun(6,8);
    printf("Los amigos en comun son: %i \n", Amigos);

    //Hay que hacerlo global, es decir, que lo haga con cada uno que tenga en comun y asi actualizar la matriz
}

int main()
{
    inicioProceso();
    printf("\n\n");
    return 0;
}
